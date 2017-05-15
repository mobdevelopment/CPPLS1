#include "monster.h"

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace game;
using namespace boost;
using namespace std;

namespace
{
	const std::string MONSTER_FILES_FOLDER = "./";
	const std::string MONSTER_FILE_EXTENSION = ".txt";
}

MonstersContainer game::ParseMonster(std::istream& stream)
{
	MonstersContainer container;

	// First line are monster name and stats
	std::string monsterLine;
	while (std::getline(stream, monsterLine))
	{
		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);

		if (monsterLine.empty() || monsterLine[0] != '[')
			continue;

		Monster monster;
		// parse text

		if ((monsterLine.length() > 2) &&
			(monsterLine[0] == '[') &&
			(monsterLine[monsterLine.length() - 1] == ']'))
		{
			string szNewMonsterLine = monsterLine.substr(1, monsterLine.length() - 2);
			stringstream ss(szNewMonsterLine);

			string level, ac, aa, mind, maxd, dc, lp;

			std::getline(ss, monster.name, ';');
			std::getline(ss, level, ';');
			std::getline(ss, ac, 'x');
			std::getline(ss, aa, ';');
			std::getline(ss, mind, '-');
			std::getline(ss, maxd, ';');
			std::getline(ss, dc, ';');
			std::getline(ss, lp, ';');

			if (level == "BAAS")
				monster.level		= Monster::boss;
			else
				monster.level		= stoi(level);
			
			monster.attackChance	= stoi(ac);
			monster.attackAmount	= stoi(aa);
			monster.minDamage		= stoi(mind);
			monster.maxDamage		= stoi(maxd);
			monster.defenseChance	= stoi(dc);
			monster.lifePoints		= stoi(lp);
		}
		
		// Check for stream error.
		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);

		container.emplace(container.size(), monster);
	}

	return container;
}

MonstersContainer game::ParseMonster(std::istream& stream, std::error_code& errorBuffer)
{
	try
	{
		return ParseMonster(stream);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

MonstersContainer game::GetSavedMonsters()
{
	MonstersContainer monsters;

	if (!filesystem::exists(MONSTER_FILES_FOLDER))
		return monsters;

	filesystem::directory_iterator iterator(MONSTER_FILES_FOLDER);
	const filesystem::directory_iterator end;

	
	std::ifstream stream(MONSTER_FILES_FOLDER + "/monsters" + MONSTER_FILE_EXTENSION);

	std::error_code errorBuffer;
	monsters = ParseMonster(stream, errorBuffer);
	if (errorBuffer)
		return MonstersContainer();

	return monsters;
}