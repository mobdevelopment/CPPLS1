#ifndef GAME_HERO_HEADER_INCLUDED
#define GAME_HERO_HEADER_INCLUDED

#include <system_error>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

#include "items/item.h"
#include <boost/filesystem.hpp>

#include "errorcategory.h"

namespace game
{
	class Hero;
	namespace items {
		class Item;
	}
	

	typedef std::unordered_map<std::string, Hero> HeroesContainer;

	class Hero
	{
	public:
		std::string		name;
		int				level;
		int				experiencePoints = 0;
		int				minDamage = 0;
		int				maxDamage = 0;
		int				attackChance = 0;
		int				attackAmount = 0;
		int				defenseChance = 0;
		int				maxLifePoints = 0;  // Normally 10 for each 10 level's but with special item you might get extra.

		int				lifePoints = 0;

		int				extraDefenseChance = 0;
		int				extraAttackChance = 0;
		int				extraAttackAmount = 0;
		int				extraMinDamage = 0;
		int				extraMaxDamage = 0;

		bool			leftHandInUse = false; // shield, defencechance
		bool			rightHandInUse = false; // weapon, damage
		bool			feetCovered = false; // shoes, attackAmount (kicking)
		bool			legsCovered = false; // legs, defencechance
		bool			bodyCovered = false; // plate, attackchance

		std::vector<items::Item*> items;
		
		
		void Heal(int amount);
		void DefUp(int amount);
		void RareCandy();

		void AddExp(int exp);
		std::vector<items::Item*> GetItems();
		void AddItem(items::Item* item);
	}; // class Hero

	const int getLevelExp(const int xplevel);

	const std::string& GetRandomHeroName() noexcept;

	Hero ParseHero(std::istream& stream);
	Hero ParseHero(std::istream& stream, std::error_code& errorBuffer);

	void WriteHero(std::ostream& stream, const Hero& hero);
	void WriteHero(std::ostream& stream, const Hero& hero, std::error_code& errorBuffer);

	HeroesContainer GetSavedHeroes();

	Hero GetSavedHero(std::string heroName);
	Hero GetSavedHero(std::string heroName, std::error_code& errorBuffer);

	void SaveHero(const Hero& hero);
	void SaveHero(const Hero& hero, std::error_code& errorBuffer);

	
}

#endif // #ifndef GAME_HERO_HEADER_INCLUDED
