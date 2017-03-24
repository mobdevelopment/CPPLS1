#include "fight.h"

using namespace ui::cnsl;
using namespace ui::cnsl::state;

const Type Fight::TYPE(Type::FIGHT);

void Fight::FightCommandHandler(utils::cmd::Command& command)
{	
	int min = 1, max = 2;
	int firstStrike = (rand() % (max - min + 1)) + min;

	if (firstStrike == 1)
	{
		AttackByEnemy();
		AttackByHero();
	}
	else
	{
		AttackByHero();
		AttackByEnemy();
	}

	context.userInterface.DrawConsole("");
	return;

	// Go to the dungeon selection state.
	//context.userInterface.SetState(Type::ROOM);
}

void Fight::AttackByEnemy()
{

}

void Fight::AttackByHero()
{
	auto hero = context.game.GetHero();

	if (auto room = dynamic_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
	{
		if (room->HasMonster())
		{
			game::Monster monster = room->GetMonster();
			if (monster.lifePoints > 0)
			{
				for (int a = 0; a < monster.attackAmount; a++) {
					int min = 0, max = 100;
					double attackChance = (rand() % (max - min + 1)) + min;

					if (monster.attackChance < attackChance)
					{

					}
				}
			}
		}
	}
}

void Fight::Initialize()
{
	context.userInterface.RegisterCommand<std::string>("Fight", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::FIGHT);  });
	
	context.userInterface.RegisterCommand("Flee", [this](const utils::cmd::Command& command) { context.userInterface.SetState(Type::ROOM); });
}

void Fight::Terminate()
{
	context.userInterface.UnregisterCommand("Fight");
	context.userInterface.UnregisterCommand("Flee");
}

void Fight::DrawConsole() const
{
	if (auto room = dynamic_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
	{
		if (room->HasMonster())
		{
			if (room->GetMonster().lifePoints > 0)
				std::cout << std::endl << "There is a : " << room->GetMonster().name << " in this room" << std::endl;
			else
				std::cout << std::endl << "There is a deceased " << room->GetMonster().name << " in this room" << std::endl;
		}
	}
}

void Fight::GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const
{
	CommandDescription fleeCommandDescription;
	fleeCommandDescription.command = "Flee";
	fleeCommandDescription.description = "Leave the fight.";

	commandDescriptionsBuffer.emplace_back(std::move(fleeCommandDescription));

	if (auto room = dynamic_cast<game::nodes::Room*>(context.game.GetHeroLocation()))
	{
		if (room->HasMonster() && room->GetMonster().lifePoints > 0)
		{
			CommandDescription fightCommandDescription;
			fightCommandDescription.command = "Fight";
			fightCommandDescription.description = "Fight the monster in this room";

			commandDescriptionsBuffer.emplace_back(std::move(fightCommandDescription));
		}
	}
}
