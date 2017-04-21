#ifndef GAME_HERO_HEADER_INCLUDED
#define GAME_HERO_HEADER_INCLUDED

#include <system_error>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

#include "save.h"
#include "items/consumable.h"
#include "items/equipment.h"
#include <boost/filesystem.hpp>

#include "errorcategory.h"

namespace game
{

	class Hero;

	namespace items {
		class Consumable;
		class Equipment;
		class Item;
	}

	typedef std::unordered_map<std::string, Hero> HeroesContainer;

	class Hero
	{
	public:
		Hero();
		~Hero();

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

		items::Equipment*	leftHand = nullptr; // shield, defencechance
		items::Equipment*	rightHand = nullptr; // weapon, damage
		items::Equipment*	feet = nullptr; // shoes, attackAmount (kicking)
		items::Equipment*	legs = nullptr; // legs, defencechance
		items::Equipment*	body = nullptr; // plate, attackchance

		std::vector<items::Item*> items;
		
		void Heal(int amount);
		void RareCandy();

		void AddEquipables(SavedItemsContainer items);
		void AddItems(SavedItemsContainer items);
		void AddExp(int exp);
		std::vector<items::Item*> GetItems();
		void AddItem(items::Equipment* item);
		void AddItem(items::Consumable* item);
		std::unordered_map<int, items::SaveItem> equipedItems();
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
