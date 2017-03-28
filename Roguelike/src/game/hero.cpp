#include "hero.h"

using namespace game;
using namespace boost;

namespace
{
	const std::string HERO_NAMES[] =
	{
		"Salvatore Maranzano",
		"Salvatore Bonanno",
		"Joseph Bonanno",
		"Charles Luciano",
		"Nicola Schiro",
		"Vito Bonventre",
		"Gaspar DiGregorio",
		"Philip Rastelli",
		"Natale Evola",
		"Philip Rastelli",
		"Carmine Galante",
		"Joseph Massino",
		"Vincent Basciano",
		"Michael Mancuso",
		"Paul Sciacca"
	};

	const std::string HERO_FILES_FOLDER = "./heroes";
	const std::string HERO_FILE_EXTENSION = ".hero";
}

const std::string& game::GetRandomHeroName() noexcept
{
	int numberOfHeroNames = (sizeof(HERO_NAMES) / sizeof(*HERO_NAMES));

	int index = rand() % numberOfHeroNames;

	return HERO_NAMES[index];
}

Hero game::ParseHero(std::istream& stream)
{
	Hero hero;

	// First line are hero name and stats
	std::string statsLine;
	std::getline(stream, statsLine);
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);

	// Parse the name and stats.
	std::stringstream sstream(statsLine);

	// Name is until the first comma.
	std::getline(sstream, hero.name, ',');

	// Then its spaces seperating the values.
	sstream >> hero.level;
	sstream >> hero.lifePoints;
	sstream >> hero.experiencePoints;
	sstream >> hero.attackChance;
	sstream >> hero.defenseChance;
	sstream >> hero.attackAmount;
	sstream >> hero.minDamage;
	sstream >> hero.maxDamage;

	// TODO: Items.
	// All the following lines are items.

	// Check for stream error.
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);

	return hero;
}

Hero game::ParseHero(std::istream& stream, std::error_code& errorBuffer)
{
	try
	{
		return ParseHero(stream);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

void game::WriteHero(std::ostream& stream, const Hero& hero)
{
	// Stats on the first line.
	stream << hero.name << ',' <<
		hero.level << ' ' <<
		hero.lifePoints << ' ' <<
		hero.experiencePoints << ' ' <<
		hero.attackChance << ' ' <<
		hero.defenseChance << ' ' <<
		hero.attackAmount << ' ' <<
		hero.minDamage << ' ' <<
		hero.maxDamage << ' ' <<
		'\n';

	// TODO: Items.
	// Items next.

	// Check for stream error.
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);
}

void game::WriteHero(std::ostream& stream, const Hero& hero, std::error_code& errorBuffer)
{
	try
	{
		return WriteHero(stream, hero);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

HeroesContainer game::GetSavedHeroes()
{
	HeroesContainer heroes;

	if (!filesystem::exists(HERO_FILES_FOLDER))
		return heroes;

	filesystem::directory_iterator iterator(HERO_FILES_FOLDER);
	const filesystem::directory_iterator end;
	
	for (; iterator != end; ++iterator)
	{
		if (iterator->path().extension() == HERO_FILE_EXTENSION)
		{
			std::ifstream stream(iterator->path().string());

			std::error_code errorBuffer;
			Hero hero = ParseHero(stream, errorBuffer);
			if (errorBuffer)
				continue;

			heroes.emplace(hero.name, hero);
		}
	}

	return heroes;
}

Hero game::GetSavedHero(std::string heroName)
{
	return ParseHero(std::ifstream(HERO_FILES_FOLDER + '/' + heroName));
}

Hero game::GetSavedHero(std::string heroName, std::error_code& errorBuffer)
{
	try
	{
		return GetSavedHero(heroName);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

void game::SaveHero(const Hero& hero)
{
	WriteHero(std::ofstream(HERO_FILES_FOLDER + '/' + hero.name + HERO_FILE_EXTENSION), hero);
}

void game::SaveHero(const Hero& hero, std::error_code& errorBuffer)
{
	try
	{
		return SaveHero(hero);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}
