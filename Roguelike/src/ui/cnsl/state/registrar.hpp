#ifndef UI_CNSL_STATE_REGISTRAR_HEADER_INCLUDED
#define UI_CNSL_STATE_REGISTRAR_HEADER_INCLUDED

#include <functional>
#include <memory>

#include "base.h"
#include "factory.h"

namespace ui
{
namespace cnsl
{
namespace state
{
	enum class Type;
	class Context;

	template<typename State>
	class Registrar
	{
	public:
		Registrar(const Type type)
		{
			auto assembler = [](Context& context)
			{
				return (BaseInterface*)new State(context);
			};

			Factory::GetInstance().AddAssembler(type, Assembler(assembler));
		}

		int Dummy() const noexcept
		{
			return 0;
		}
	}; // class Registrar
} // namespace state
} // namespace cnsl
} // namespace ui

#endif // UI_CNSL_STATE_REGISTRAR_HEADER_INCLUDED
