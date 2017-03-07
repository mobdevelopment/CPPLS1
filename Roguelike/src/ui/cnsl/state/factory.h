#ifndef UI_CNSL_STATE_FACTORY_HEADER_INCLUDED
#define UI_CNSL_STATE_FACTORY_HEADER_INCLUDED

#include <unordered_map>
#include <functional>

#include <utils/enumclasshash.hpp>

#include "context.h"
#include "type.h"

namespace ui
{
namespace cnsl
{
namespace state
{
	class BaseInterface;

	typedef std::function<BaseInterface*(Context& context)> Assembler;

	class Factory
	{
		typedef std::unordered_map<Type, Assembler, utils::EnumClassHash> AssemblersMap;

	private:
		Factory() noexcept;

		AssemblersMap assemblers;

	public:
		static Factory& GetInstance() noexcept;

		void AddAssembler(const Type type, Assembler assembler);

		BaseInterface* ConstructDefaultState(Context& context) const;
		BaseInterface* Construct(const Type type, Context& context) const;
	}; // class Factory
} // namespace state
} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_STATE_FACTORY_HEADER_INCLUDED