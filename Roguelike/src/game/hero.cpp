#include "hero.h"
#include <algorithm>

#include <boost\algorithm\string.hpp>

using namespace game;
using namespace boost;

namespace
{
	const std::string HERO_NAMES[] =
	{
		"Carmine",
		"Charles",
		"Gaspar",
		"Joseph",
		"Michael",
		"Natale",
		"Nicola",
		"Paul"
		"Philip",
		"Salvatore",
		"Vincent",
		"Vito",
	};

	const std::string HERO_FILES_FOLDER = "./heroes";
	const std::string HERO_FILE_EXTENSION = ".hero";
}

game::Hero::Hero()
{
}

game::Hero::~Hero()
{
	if (legs != nullptr)
		legs = nullptr;

	for_each(itemsList.begin(), itemsList.end(), std::default_delete<items::Item>());
	itemsList.clear();
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
	sstream >> hero.maxLifePoints;
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
		hero.maxLifePoints << ' ' <<
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

void game::Hero::AddEquipables(SavedItemsContainer items)
{
	if (itemsList.empty())
		itemsList = items::GetSavedItems();

	for (auto i : items)
	{
		auto ti = i.second;
		for (auto ic : itemsList)
		{
			if (boost::iequals(ti.name, ic->name))
			{
				if (auto equipable = dynamic_cast<game::items::Equipment*>(ic))
				{
					bool hasItem = false;
					for (auto i : GetItems())
						if (i->name == equipable->name)
							hasItem = true;

					if (!hasItem)
					{
						AddItem(equipable);
						equipable->Use(*this);
					}
						
				}
			}
		}
	}
}

void game::Hero::AddItems(SavedItemsContainer items)
{
	if (itemsList.empty())
		itemsList = items::GetSavedItems();

	for (auto i : items)
	{
		auto ti = i.second;
		for (auto ic : itemsList)
		{
			if (boost::iequals(ti.name, ic->name))
			{
				if (auto consumable = dynamic_cast<game::items::Consumable*>(ic))
				{
					consumable->amount = ti.amount;
					AddItem(consumable);
				}
				else if (auto equipable = dynamic_cast<game::items::Equipment*>(ic))
				{
					bool hasItem = false;
					for (auto i : GetItems())
						if (i->name == equipable->name)
							hasItem = true;

					if (!hasItem)
						AddItem(equipable);
				}
			}
		}
	}
}

void game::Hero::AddExp(int exp)
{
	experiencePoints += exp;

	if (experiencePoints >= getLevelExp(level + 1))
	{
		level++;

		if (level % 2 == 0)
			minDamage += (rand() % (1 - 0 + 1)) + 0;
		if (level % 2 == 1)
			maxDamage += (rand() % (1 - 0 + 1)) + 0;
		if (level % 4 == 0)
			attackChance += (rand() % (5 - 1 + 1)) + 1;
		if (level % 5 == 0)
			attackAmount += (rand() % (1 - 0 + 1)) + 0;
		if (level % 1 == 0)
		{
			maxLifePoints += 10; // No chance, always add 10 
			lifePoints += 10;
		}
	}
}

const int game::getLevelExp(const int xplevel)
{
	if (xplevel == 1)
		return 100;
	return getLevelExp(xplevel - 1) + (getLevelExp(xplevel - 1) * 1.1); // xp prev level + (xp prev level + 10%)
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

void Hero::Heal(int amount)
{
	if ((lifePoints + amount) <= maxLifePoints) {
		lifePoints += amount;
	}
	else {
		lifePoints = maxLifePoints;
	}
	
}

void Hero::RareCandy()
{
	int neededExp = (getLevelExp(level + 1) - experiencePoints) + 1;
	AddExp(neededExp);
}

std::vector<items::Item*> Hero::GetItems() {
	return items;
}

void Hero::AddItem(items::Consumable* item) {

	if (!items.empty() && std::find(items.begin(), items.end(), item) != items.end())	{
		// item is already in bag, add quantity
		for (auto i : items) {
			if (auto ci = dynamic_cast<items::Consumable*>(i))
			{
				if (ci->name == item->name) {
					ci->amount++;
				}
			}
		}
	}
	else {
		items.push_back(item);
	}
}

std::unordered_map<int, items::SaveItem> game::Hero::equipedItems()
{
	int count = 1;
	std::unordered_map<int, items::SaveItem> _equipeditems;
	items::SaveItem i;
	if (leftHand != NULL) {
		i.name = leftHand->name;
		_equipeditems[count] = i;
		count++;
	}
	else if (rightHand != NULL) {
		i.name = rightHand->name;
		_equipeditems[count] = i;
		count++;
	}
	else if (feet != NULL) {
		i.name = feet->name;
		_equipeditems[count] = i;
		count++;
	}
	else if (legs != NULL) {
		i.name = legs->name;
		_equipeditems[count] = i;
		count++;
	}
	else if (body != NULL) {
		i.name = body->name;
		_equipeditems[count] = i;
		count++;
	}
	return _equipeditems;
}

void Hero::AddItem(items::Equipment* item) {
	items.push_back(item);
}