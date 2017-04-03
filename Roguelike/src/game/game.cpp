#include "game.h"
#include <typeinfo>

using namespace game;

Game::Game() :
	isRunning(false),
	isCleared(true),
	enableRandomMonsters(true),
	dungeonLayer(0)
{
}

void Game::Start()
{
	if (IsRunning())
		throw std::system_error(Error::GAME_ALREADY_RUNNING);

	// Put the hero in a random room.
	heroLocation = dungeon[dungeonLayer].GetRandomRoom();

	if (enableRandomMonsters)
	{
		container = game::GetSavedMonsters();
	}

	isRunning = true;
	isCleared = false;
}

void Game::Stop()
{
	if (IsRunning())
		throw std::system_error(Error::GAME_NOT_RUNNING);

	isRunning = false;
}

bool Game::IsRunning() const
{
	return isRunning;
}

bool Game::IsCleared() const
{
	return isCleared;
}

void Game::Clear()
{
	if (IsRunning())
		Stop();

	dungeon.Clear();
	container.clear();
	heroLocation = nullptr;
	dungeonLayer = 0;

	isCleared = true;
}

void Game::SetDungeon(const Dungeon& dungeon)
{
	if (!IsCleared())
		throw std::system_error(Error::GAME_NOT_CLEARED);

	this->dungeon = dungeon;
}

const Dungeon& Game::GetDungeon() const
{
	return dungeon;
}

void Game::RandomizeDungeon(const unsigned int layerCount, const unsigned int width, const unsigned int height, const unsigned int seed)
{
	dungeon.Randomize(layerCount, width, height, seed);
}

void Game::SetHero(const Hero& hero)
{
	if (!IsCleared())
		throw std::system_error(Error::GAME_NOT_CLEARED);

	this->hero = hero;
}

const Hero& Game::GetHero() const
{
	return hero;
}

void Game::EnableRandomMonsters(const bool enable)
{
	container = game::GetSavedMonsters();
	enableRandomMonsters = enable;
}

bool Game::EnableRandomMonsters() const
{
	return enableRandomMonsters;
}

const bool Game::HasMonster() const
{
	if (auto room = dynamic_cast<nodes::Room*>(heroLocation))
	{
		return room->HasMonster();
	}

	return false;
}

game::Monster* Game::GetMonster()
{
	return static_cast<nodes::Room*>(heroLocation)->GetMonster();
}

nodes::Space* Game::GetHeroLocation()
{
	return heroLocation;
}

const nodes::Space* Game::MoveUp()
{
	if (heroLocation->southCorridor != nullptr && !heroLocation->southCorridor->collapsed)
		heroLocation = heroLocation->southCorridor->GetSouthRoom();

	OnMove();

	return heroLocation;
}

const nodes::Space* Game::MoveDown()
{
	if (heroLocation->northCorridor != nullptr && !heroLocation->northCorridor->collapsed)
		heroLocation = heroLocation->northCorridor->GetNorthRoom();

	OnMove();

	return heroLocation;
}

const nodes::Space* Game::MoveLeft()
{
	if (heroLocation->westCorridor != nullptr && !heroLocation->westCorridor->collapsed)
		heroLocation = heroLocation->westCorridor->GetWestRoom();

	OnMove();

	return heroLocation;
}

const nodes::Space* Game::MoveRight()
{
	if (heroLocation->eastCorridor != nullptr && !heroLocation->eastCorridor->collapsed)
		heroLocation = heroLocation->eastCorridor->GetEastRoom();

	OnMove();

	return heroLocation;
}

const void Game::OnMove()
{
	bool movedLayer = false;

	if (auto stairdown = dynamic_cast<nodes::StairsDown*>(heroLocation))
	{
		if (stairdown->GetBottomRoom() != nullptr)
		{
			heroLocation = stairdown->GetBottomRoom();
			dungeonLayer--;
			movedLayer = true;
		}
	}
	else if (auto stairup = dynamic_cast<nodes::StairsUp*>(heroLocation))
	{
		if (stairup->GetTopRoom() != nullptr)
		{
			heroLocation = stairup->GetTopRoom();
			dungeonLayer++;
			movedLayer = true;
		}	
	}

	if (!movedLayer)
	{
		if (enableRandomMonsters)
		{
			if (auto room = dynamic_cast<nodes::Room*>(heroLocation))
			{
				if (!room->HasMonster())
				{
					int min = 0, max = 100;
					double perc = (rand() % (max - min + 1)) + min;

					if (perc < 100)
					{
						Monster monster;
						int sumWeight = 0;
						for (auto mp : container)
						{
							Monster m = mp.second;
							int level = (m.level == Monster::boss) ? 10 : m.level;
							sumWeight += dungeon.GetLayers().size() - (abs(int(dungeonLayer - level)));
						}

						int mperc = (rand() % (sumWeight - 0 + 1)) + 0;

						int curWeight = 0;
						Monster oldM;
						for (auto mp : container)
						{
							Monster m = mp.second;
							int level = (m.level == Monster::boss) ? 10 : m.level;
							curWeight += dungeon.GetLayers().size() - (abs(int(dungeonLayer - level)));

							if (curWeight >= mperc)
							{
								if (m.level == Monster::boss)
								{
									if (!BossSpawned)
										BossSpawned = true;
									else
										monster = oldM;
									break;
								}

								monster = m;
								break;
							}

							if (m.level != Monster::boss)
								oldM = m;
						}

						room->SetMonster(monster);
					}
				}
			}
		}
	}
	
}

int Game::GetDungeonLayer()
{
	return dungeonLayer;
}

