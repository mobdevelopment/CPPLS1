#include "dungeonrow.h"

using namespace game;

DungeonRow::DungeonRow() noexcept :
	width(0)
{
}

DungeonRow::~DungeonRow() noexcept
{
	for (auto* const node : nodes)
	{
		if (node != nullptr)
			delete node;
	}
}

DungeonRow::iterator DungeonRow::begin()
{
	return nodes.begin();
}

DungeonRow::const_iterator DungeonRow::begin() const
{
	return nodes.begin();
}

DungeonRow::const_iterator DungeonRow::cbegin() const
{
	return nodes.cbegin();
}

DungeonRow::iterator DungeonRow::end()
{
	return nodes.end();
}

DungeonRow::const_iterator DungeonRow::end() const
{
	return nodes.end();
}

DungeonRow::const_iterator DungeonRow::cend() const
{
	return nodes.cend();
}

nodes::NodeInterface* DungeonRow::operator[](const unsigned int index) noexcept
{
	return nodes[index];
}

const nodes::NodeInterface* DungeonRow::operator[](const unsigned int index) const noexcept
{
	return nodes[index];
}

unsigned int DungeonRow::GetWidth() const noexcept
{
	return width;
}

void DungeonRow::SetWidth(const unsigned int width)
{
	if (width == this->width)
		return;

	if (width < this->width)
	{
		unsigned int index = width;
		if (index > 0)
			index--;

		for (unsigned int i = index; i < this->width; i++)
		{
			if (nodes[i] != nullptr)
				delete nodes[i];
		}
	}

	nodes.resize(width);
	this->width = width;
}

DungeonRow::NodesContainer& DungeonRow::GetNodes() noexcept
{
	return nodes;
}

const DungeonRow::NodesContainer& DungeonRow::GetNodes() const noexcept
{
	return nodes;
}

DungeonRow::RoomsContainer DungeonRow::GetRooms() const noexcept
{
	RoomsContainer rooms;

	for (nodes::NodeInterface* const node : nodes)
	{
		if (node != nullptr && node->GetType() == nodes::Type::ROOM)
			rooms.push_back((nodes::Room*)node);
	}

	return rooms;
}

void DungeonRow::SetNode(const unsigned int index, nodes::NodeInterface* node) noexcept
{
	if (nodes[index] != nullptr)
		delete nodes[index];

	nodes[index] = node;
}
