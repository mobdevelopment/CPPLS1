#ifndef UI_CNSL_STATE_BASE_HEADER_INCLUDED
#define UI_CNSL_STATE_BASE_HEADER_INCLUDED

#include <vector>

#include "registrar.hpp"

namespace ui
{
namespace cnsl
{
	class CommandDescription;
	
namespace state
{
	class Context;

	class BaseInterface
	{
	protected:
		Context& context;

	public:
		BaseInterface(Context& context) noexcept;
		virtual ~BaseInterface() noexcept = 0;

		virtual BaseInterface* Clone() const = 0;

		virtual void Initialize() = 0;
		virtual void Terminate() = 0;

		virtual void DrawConsole() const = 0;
		virtual void GetAvailableCommands(std::vector<CommandDescription>& commandDescriptionsBuffer) const = 0;
	}; // class BaseInterface

	template<typename Derived>
	class Base :
		public BaseInterface
	{
	private:
		static const Registrar<Derived> registrar;

	public:
		using BaseInterface::BaseInterface;
		virtual ~Base() noexcept {};

		virtual BaseInterface* Clone() const override
		{
			// Force registrar initialization. Has to happen somewhere and don't feel like defining a ctor...
			static const int dummy = registrar.Dummy();

			return static_cast<BaseInterface*>(new Derived(static_cast<const Derived&>(*this)));
		}
	}; // class Base

	// Static member Base::Registrar initalization.
	template<typename Derived>
	const Registrar<Derived> Base<Derived>::registrar(Derived::TYPE);

} // namespace state
} // namespace cnsl
} // namespace ui

#endif // #ifndef UI_CNSL_STATE_BASE_HEADER_INCLUDED
