#include "fight.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Fight::TYPE(Type::FIGHT);

void Fight::FightCommandHandler(utils::cmd::Command& command)
{	
	int min = 1, max = 2;
	int firstStrike = (rand() % (max - min + 1)) + min;

	if (context.game.HasMonster())
	{
		auto monster = context.game.GetMonster();
		if (monster->lifePoints > 0 && context.hero.lifePoints > 0)
		{
			std::vector<std::string> heroOutput, monsterOutput;

			if (firstStrike == 1)
			{
				monsterOutput = AttackByEnemy();
				heroOutput = AttackByHero();
			}
			else
			{
				monsterOutput = AttackByHero();
				heroOutput = AttackByEnemy();
			}

			std::string firstOutput, secondOutput;
			for (auto const& value : monsterOutput) {
				firstOutput += value + "\n";
			}
			for (auto const& value : heroOutput) {
				secondOutput += value + "\n";
			}

			if (context.hero.lifePoints <= 0)
			{
				context.userInterface.SetState(Type::GAMEOVER);
				return;
			}

			context.userInterface.DrawConsole(firstOutput + "\n" + secondOutput + "\n\nYou still have " + std::to_string(context.hero.lifePoints));
			return;
		}
		else
		{
			if (context.hero.lifePoints > 0)
				context.userInterface.DrawConsole(monster->name + " is already deceased");
			else
			{
				context.userInterface.SetState(Type::GAMEOVER);
			}
		}
	}

	// Go to the dungeon selection state.
	context.userInterface.SetState(Type::FIGHT);
}

std::vector<std::string> Fight::AttackByEnemy()
{
	auto hero = context.game.GetHero();

	std::vector<std::string> output;
	
	if (context.game.HasMonster())
	{
		auto monster = context.game.GetMonster();
		
		for (int a = 0; a < monster->attackAmount; a++) {
			if (monster->lifePoints > 0 && hero.lifePoints > 0)
			{
				int min = 0, max = 100;
				double attackChance = (rand() % (max - min + 1)) + min;

				if (attackChance < monster->attackChance)
				{
					double defenseChance = (rand() % (max - min + 1)) + min;
					int hDefenseChance = hero.defenseChance + (hero.leftHand != nullptr ? hero.leftHand->GetEffect() : 0) + (hero.legs != nullptr ? hero.legs->GetEffect() : 0);
					if (defenseChance < hDefenseChance)
					{
						output.push_back(hero.name + " defended itself by an attack from the " + monster->name);
					}
					else
					{
						int damage = (rand() % (monster->maxDamage - monster->minDamage));
						context.hero.lifePoints -= damage;
						if (hero.lifePoints <= 0) {
							output.push_back("The" + monster->name + " attacked and killed " + hero.name);
							return output; // end the attack
						}
						else {
							output.push_back("The " + monster->name + " attacked and did " + std::to_string(damage) + "hp damage");
						}
					}
				}
				else
				{
					output.push_back("The " + monster->name + " tried to attack but missed");
				}
			}
		}
	}

	return output;
}

std::vector<std::string> Fight::AttackByHero()
{
	auto hero	= context.game.GetHero();
	std::vector<std::string> output;

	auto* temp = &context.game;

	if (context.game.HasMonster())
	{
		auto monster = context.game.GetMonster();
		
		for (int a = 0; a < hero.attackAmount + (hero.feet != nullptr ? hero.feet->GetEffect() : 0); a++) {
			if (monster->lifePoints > 0 && hero.lifePoints > 0)
			{
				int min = 0, max = 100;
				double attackChance = (rand() % (max - min + 1)) + min;

				if (attackChance < hero.attackChance + (hero.body != nullptr ? hero.body->GetEffect() : 0))
				{
					double defenseChance = (rand() % (max - min + 1)) + min;
					if (defenseChance < monster->defenseChance)
					{
						output.push_back("The " + monster->name + " defended itself by an attack from " + hero.name);
					}
					else
					{
						int minDamage = hero.minDamage + (hero.rightHand != nullptr ? hero.rightHand->GetEffect() : 0);
						int maxDamage = hero.maxDamage + (hero.rightHand != nullptr ? hero.rightHand->GetEffect() : 0);
						int damage = (rand() % (maxDamage - minDamage + 1)) + minDamage;
						monster->lifePoints -= damage;
						if (monster->lifePoints <= 0) {
							int oldLevel = context.hero.level;
							context.hero.AddExp(100 + (monster->level * 10));
							output.push_back(hero.name + " attacked and killed the " + monster->name);
							if (context.hero.level > oldLevel)
							{
								output.push_back(hero.name + " leveled up");
							}
							
							return output; // end the attack
						}
						else {
							output.push_back(hero.name + " attacked and did " + std::to_string(damage) + "hp damage");
						}
						
					}
				}
				else
				{
					output.push_back(hero.name + " tried to attack but missed");
				}
			}
		}
	}

	return output;
}

void Fight::Initialize()
{
	context.userInterface.RegisterCommand("Fight", std::bind(&Fight::FightCommandHandler, this, std::placeholders::_1));
	
	context.userInterface.RegisterCommand("Flee", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::ROOM); });

	if (context.game.HasMonster())
		return;
	else
		context.userInterface.SetState(Type::ROOM);
}

void Fight::Terminate()
{
	context.userInterface.UnregisterCommand("Fight");
	context.userInterface.UnregisterCommand("Flee");
}

void Fight::DrawConsole() const
{
	if (context.game.HasMonster())
	{
		auto m = context.game.GetMonster();
		if (m->lifePoints > 0)
			std::cout << std::endl << "There is a " << m->name << " in this room with " << m->lifePoints << "hp" << std::endl;
		else
			std::cout << std::endl << "There is a deceased " << m->name << " in this room" << std::endl;
	}
}

void Fight::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription fleeCommandDescription;
	fleeCommandDescription.command = "Flee";
	fleeCommandDescription.description = "Leave the fight.";

	commandDescriptionsBuffer.emplace_back(std::move(fleeCommandDescription));

	if (context.game.HasMonster() && context.game.GetMonster()->lifePoints > 0 && context.hero.lifePoints > 0)
	{
		CommandDescription fightCommandDescription;
		fightCommandDescription.command = "Fight";
		fightCommandDescription.description = "Fight the monster in this room";

		commandDescriptionsBuffer.emplace_back(std::move(fightCommandDescription));
	}
}
