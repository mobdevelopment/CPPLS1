#include "save.h"
#include <algorithm>


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
	save.seed = std::stoi(seed);

	// Then its spaces seperating the values.
	sstream >> save.width;
	sstream >> save.height;
	sstream >> save.layers;

	// TODO: Items.
	// All the following lines are items.

	// Check for stream error.
	if (!stream)
		throw std::system_error(Error::STREAM_ERROR);
		
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
	// Stats on the first line.
	/*stream << hero.name << ',' <<
		hero.level << ' ' <<
		hero.maxLifePoints << ' ' <<
		hero.experiencePoints << ' ' <<
		hero.attackChance << ' ' <<
		hero.defenseChance << ' ' <<
		hero.attackAmount << ' ' <<
		hero.minDamage << ' ' <<
		hero.maxDamage << ' ' <<
		'\n';*/

	// TODO: Items.
	// Items next.

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