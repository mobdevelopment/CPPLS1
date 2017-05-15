#include "factory.h"

using namespace ui::cnsl::state;

namespace
{
	static const Type DEFAULT_STATE = Type::MENU;
}

Factory::Factory() noexcept
{
}

Factory& Factory::GetInstance() noexcept
{
	static auto instance = Factory();
	return instance;
}

void Factory::AddAssembler(const Type type, Assembler assembler)
{
	assemblers.emplace(type, assembler);
}

BaseInterface* Factory::ConstructDefaultState(Context& context) const
{
	return Construct(DEFAULT_STATE, context);
}

BaseInterface* Factory::Construct(const Type type, Context& context) const
{
	return assemblers.at(type)(context);
}
