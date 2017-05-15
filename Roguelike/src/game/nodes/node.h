#ifndef GAME_NODES_NODE_HEADER_INCLUDED
#define GAME_NODES_NODE_HEADER_INCLUDED

#include <type_traits>

#include "visitor.h"

namespace game
{
namespace nodes
{
	enum class Type;

	class NodeInterface
	{
	public:
		virtual ~NodeInterface() noexcept = 0;
		
		virtual unsigned int GetWeight() const = 0;

		virtual void Visit(Visitor& visitor) = 0;
		virtual Type GetType() const noexcept = 0;
	}; // class NodeInterface

	template<typename Derived,
		const Type type>
	class Node :
		public NodeInterface
	{
		//static_assert(std::is_base_of<NodeInterface, U>::value, "Derived template parameter type must derive from the Node class.");

	public:
		void Visit(Visitor& visitor) override
		{
			visitor.Visit(static_cast<Derived&>(*this));
		}

		Type GetType() const noexcept override
		{
			return type;
		}
	}; // class Node
} // namespace nodes
} // namespace game

#endif // #ifndef GAME_NODES_NODE_HEADER_INCLUDED
