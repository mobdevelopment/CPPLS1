#include "game.h"
#include <typeinfo>

using namespace game;

Game::Game() :
	isRunning(false),
	isCleared(true),
	enableRandomMonsters(true),
	enableRandomItems(true),
	dungeonLayer(0)
{
}

/** Copy assignment operator */
Game & game::Game::operator=(const Game & other)
{
	Game tmp(other);         // re-use copy-constructor
	*this = std::move(tmp); // re-use move-assignment
	return *this;
}

Game::~Game() noexcept
{
	Clear();
}

game::Game::Game(const Game & other)
{
	isRunning = &other.isRunning;
	isCleared = &other.isCleared;
	enableRandomMonsters = &other.enableRandomMonsters;
	enableRandomItems = &other.enableRandomItems;
	dungeon = other.dungeon;
	dungeonLayer = other.dungeonLayer;
	heroLocation = other.heroLocation;
	container = other.container;
	BossSpawned = &other.BossSpawned;
	encounterableItems = other.encounterableItems;
	hero = other.hero;
	monsterContainer = other.monsterContainer;
}

void Game::Start()
{
	if (IsRunning())
		throw std::system_error(Error::GAME_ALREADY_RUNNING);

	// Put the hero in a random room.
	heroLocation = dungeon[dungeonLayer].GetRandomRoom(dungeonSeed);

	if (enableRandomMonsters)
	{
		container = game::GetSavedMonsters();
	}
	if (enableRandomItems) {
		encounterableItems = items::GetSavedItems();
	}

	isRunning = true;
	isCleared = false;
}

void Game::Stop()
{
	if (!IsRunning())
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

	for_each(encounterableItems.begin(), encounterableItems.end(), std::default_delete<items::Item>());
	encounterableItems.clear();
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
	dungeonSeed = seed;
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

void Game::EnableRandomItems(const bool enable) {
	//itemContainer = /*list of items*/
	enableRandomItems = enable;
}

bool Game::EnableRandomItems() const {
	return enableRandomItems;
}

const bool Game::HasItem() const {
	if (auto room = dynamic_cast<nodes::Room*>(heroLocation)) {
		return room->HasItem();
	}
	return false;
}

game::items::Item Game::GetItem() {
	return *static_cast<nodes::Room*>(heroLocation)->GetItem();
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
				if (!room->HasMonster() || room->GetMonster()->lifePoints <= 0)
				{
					int min = 1, max = 100;
					double perc = (rand() % (max - min + 1)) + min;

					if (perc < MONSTER_SPAWN_CHANCE)
					{
						int maxLevel = 0;

						for (auto m : container)
						{
							if (m.second.level != Monster::boss)
								if (m.second.level > maxLevel)
									maxLevel = m.second.level;
						}
						maxLevel++; // always count the boss as the lastlevel

						Monster monster;
						int sumWeight = 0;
						for (auto mp : container)
						{
							Monster m = mp.second;
							int level = (m.level == Monster::boss) ? maxLevel : m.level;
							int correctedLevel = level * (dungeon.GetLayers().size() / maxLevel);
							sumWeight += dungeon.GetLayers().size() - (abs(int(dungeonLayer - correctedLevel)));
						}

						int mperc = (rand() % (sumWeight - 0 + 1)) + 0;

						int curWeight = 0;
						Monster oldM;
						for (auto mp : container)
						{
							Monster m = mp.second;
							int level = (m.level == Monster::boss) ? 10 : m.level;
							int correctedLevel = level * (dungeon.GetLayers().size() / maxLevel);
							curWeight += dungeon.GetLayers().size() - (abs(int(dungeonLayer - correctedLevel)));

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

		if (enableRandomItems)
		{
			if (auto room = dynamic_cast<nodes::Room*>(heroLocation))
			{
				// generate item
				if (!room->HasItem())
				{
					int min = 0, max = 100;
					double itemSpawn = (rand() % (max - min + 1)) + min;

					if (itemSpawn < ITEM_SPAWN_CHANCE)
					{
						int min = 1, max = encounterableItems.size() - 1;
						double randItem = (rand() % (max - min + 1)) + min;

						auto* item = encounterableItems[randItem];
						
						//hero.AddItem(item);
						room->SetItem(*item);
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

