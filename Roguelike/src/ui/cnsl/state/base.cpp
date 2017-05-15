#include "base.h"

using namespace ui::cnsl::state;

BaseInterface::BaseInterface(Context& context) noexcept :
	context(context)
{
}

BaseInterface::~BaseInterface() noexcept = default;
