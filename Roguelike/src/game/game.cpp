#include "game.h"

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

	// TODO: Validate dungeon.

	// TODO: Validate hero.

	// Put the hero in a random room.
	heroLocation = dungeon[dungeonLayer].GetRandomRoom();

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
	enableRandomMonsters = enable;
}

bool Game::EnableRandomMonsters() const
{
	return enableRandomMonsters;
}

const nodes::Room* Game::GetHeroLocation()
{
	return heroLocation;
}
