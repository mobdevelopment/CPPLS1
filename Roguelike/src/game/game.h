#ifndef GAME_GAME_HEADER_INCLUDED
#define GAME_GAME_HEADER_INCLUDED

#include <system_error>

#include "errorcategory.h"
#include "dungeon.h"
#include "hero.h"
#include "monster.h"

#include "nodes/room.h"

namespace game
{
	class Game
	{
	private:
		bool			isRunning;
		bool			isCleared;
		bool			enableRandomMonsters;
		bool			BossSpawned;

		MonstersContainer container;
		Dungeon			dungeon;
		Hero			hero;

		MonstersContainer monsterContainer;

		nodes::Space*	heroLocation;
		unsigned int	dungeonLayer;

		const void OnMove();

	public:
		Game();

		void Start();
		void Stop();

		bool IsRunning() const;
		bool IsCleared() const;

		void Clear();

		int GetDungeonLayer();

		void SetDungeon(const Dungeon& dungeon);
		const Dungeon& GetDungeon() const;

		void RandomizeDungeon(const unsigned int layerCount, const unsigned int width, const unsigned int height, const unsigned int seed);

		void SetHero(const Hero& hero);
		const Hero& GetHero() const;

		void EnableRandomMonsters(const bool enable);
		bool EnableRandomMonsters() const;
		game::Monster& GetMonster() const;
		void DoDamage(int damage);

		nodes::Space* GetHeroLocation();
		const nodes::Space* MoveUp();
		const nodes::Space* MoveDown();
		const nodes::Space* MoveLeft();
		const nodes::Space* MoveRight();
	}; // class Game
} // namespace game

#endif // #ifndef GAME_GAME_HEADER_INCLUDED
