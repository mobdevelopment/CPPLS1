#include "save.h"
#include <algorithm>

#include <boost\algorithm\string.hpp>

using namespace game;
using namespace boost;

namespace
{
	const std::string SAVE_FILES_FOLDER = "./saves";
	const std::string SAVE_FILE_EXTENSION = ".save";
}

game::Save::Save()
{
}

game::Save::~Save()
{
}

Save game::ParseSave(std::istream& stream)
{
	Save save;
	
	// First line are hero name and stats
	std::string statsLine;
	std::getline(stream, statsLine);
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);

	// Parse the name and stats.
	std::stringstream sstream(statsLine);
	std::string seed;
	// Name is until the first comma.
	std::getline(sstream, seed, ',');
	save.seed = std::stoull(seed);

	// Then its spaces seperating the values.
	sstream >> save.width;
	sstream >> save.height;
	sstream >> save.layers;

	std::string lineType;
	MonstersContainer posMonsters = game::GetSavedMonsters();

	while (std::getline(stream, statsLine))
	{
		std::stringstream sstream(statsLine);
		// Name is until the first comma.
		std::getline(sstream, lineType, ',');
		if (boost::iequals(lineType, "hero"))
		{
			sstream >> save.heroName;
			sstream >> save.heroHp;
			sstream >> save.heroExp;
			sstream >> save.startX;
			sstream >> save.startY;
			sstream >> save.startZ;
		}
		else if (boost::iequals(lineType, "monster"))
		{
			SaveMonster sm;

			sstream >> sm.name;
			sstream >> sm.x;
			sstream >> sm.y;
			sstream >> sm.z;
			sstream >> sm.hp;

			save.monsters.emplace(save.monsters.size(), sm);
		}
		else if (boost::iequals(lineType, "item"))
		{
			items::SaveItem si;

			sstream >> si.name;
			sstream >> si.x;
			sstream >> si.y;
			sstream >> si.z;

			save.items.emplace(save.items.size(), si);
		}
		else if (boost::iequals(lineType, "bag"))
		{
			items::SaveItem si;

			sstream >> si.name;
			sstream >> si.amount;

			save.bag.emplace(save.bag.size(), si);
		}
		else if (boost::iequals(lineType, "equip"))
		{
			items::SaveItem si;

			sstream >> si.name;
			sstream >> si.x;
			sstream >> si.y;
			sstream >> si.z;

			save.equipment.emplace(save.equipment.size(), si);
		}

		if (!stream)
			throw std::system_error(Error::STREAM_ERROR);
	}

	// TODO: Items.
	// All the following lines are items.

	// Check for stream error.
	//if (!stream)
	//	throw std::system_error(Error::STREAM_ERROR);
		
	return save;
}

Save game::ParseSave(std::istream& stream, std::error_code& errorBuffer)
{
	try
	{
		return ParseSave(stream);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

void game::WriteSave(std::ostream& stream, const Save& save)
{
	// Write Seed: Seed number, x y z (width, length, height)
	stream << save.seed << ", " << save.width << ' ' << save.height << ' ' << save.layers << '\n';
	// Write Hero: 'hero, ' name x y z (location)
	stream << "hero, " << save.heroName << ' ' << save.heroHp << ' ' << save.heroExp << ' ' << save.startX << ' ' << save.startY << ' ' << save.startZ << '\n';
	// Write Equips: 'leg, ' name
	for (auto ei : save.equipment) {
		stream << "equip, " << ei.second.name << '\n';
	}
	// Write Bag items: 'bag, ' name (possible amount) in case of consumables
	for (auto b : save.bag) {
		if (!b.second.amount) {
			// equipable items or consumable items which only have 1 amount
			stream << "bag, " << b.second.name << '\n';
		}
		else {
			// consumable items which amount is more than 1
			stream << "bag, " << b.second.name << ' ' << b.second.amount << '\n';
		}	
	}
	// Write not defeated Monsters: 'monster, ' name x y z hp
	for (auto m : save.monsters) {
		stream << "monster, " << m.second.name << ' ' << m.second.x << ' ' << m.second.y << ' ' << m.second.z << ' ' << m.second.hp << '\n';
	}
	// Write not pickedup Items: 'item, ' name x y z
	for (auto i : save.items) {
		stream << "item, " << i.second.name << ' ' << i.second.x << ' ' << i.second.y << ' ' << i.second.z <<'\n';
	}

	// Check for stream error.
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);
}

void game::WriteSave(std::ostream& stream, const Save& save, std::error_code& errorBuffer)
{
	try
	{
		return WriteSave(stream, save);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

SavesContainer game::GetSavedSaves()
{
	SavesContainer saves;

	if (!filesystem::exists(SAVE_FILES_FOLDER))
		return saves;

	filesystem::directory_iterator iterator(SAVE_FILES_FOLDER);
	const filesystem::directory_iterator end;

	for (; iterator != end; ++iterator)
	{
		if (iterator->path().extension() == SAVE_FILE_EXTENSION)
		{
			std::ifstream stream(iterator->path().string());

			std::error_code errorBuffer;
			Save save = ParseSave(stream, errorBuffer);
			if (errorBuffer)
				continue;

			std::string basename = iterator->path().filename().string();
			saves.emplace(basename.substr(0, basename.find_last_of(".")), save);
		}
	}

	return saves;
}

Save game::GetSavedGame(std::string date)
{
	return ParseSave(std::ifstream(SAVE_FILES_FOLDER + '/' + date));
}

Save game::GetSavedGame(std::string date, std::error_code& errorBuffer)
{
	try
	{
		return GetSavedGame(date);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}

void game::SaveGame(const Save& save)
{
	WriteSave(std::ofstream(SAVE_FILES_FOLDER + '/' + save.name + SAVE_FILE_EXTENSION), save);
}

void game::SaveGame(const Save& save, std::error_code& errorBuffer)
{
	try
	{
		return SaveGame(save);
	}
	catch (std::system_error exception)
	{
		errorBuffer = exception.code();
	}
}