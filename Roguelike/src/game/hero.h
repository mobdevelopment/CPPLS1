#ifndef GAME_HERO_HEADER_INCLUDED
#define GAME_HERO_HEADER_INCLUDED

#include <system_error>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stdlib.h>

#include <boost/filesystem.hpp>

#include "errorcategory.h"

namespace game
{
	class Hero;

	typedef std::unordered_map<std::string, Hero> HeroesContainer;

	class Hero
	{
	public:
		std::string		name;
		int				level;
		int				lifePoints;
		int				experiencePoints;
		int				attackPoints;
		int				defensePoints;
	}; // class Hero

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
