#include "sgfpch.h"
#include "AbstractEntity.h"

#include "Sprite.h"
#include "SGF/Assets/Asset.h"

using namespace SGF::EntitySystem;


AbstractEntity::AbstractEntity(Vector2f position, Vector2f size, Assets::Image& image) :
	m_Position(position),
	m_Size(size)
{
	m_Sprite = std::make_unique<Sprite>(*this, image);
}


AbstractEntity::~AbstractEntity()
{

}


Vector2f AbstractEntity::GetPosition() const
{
	return m_Position;
}


void AbstractEntity::SetPosition(Vector2f position)
{
	m_Position = position;
	m_Sprite->UpdateBorder();
}


Vector2f AbstractEntity::GetSize() const
{
	return m_Size;
}


void AbstractEntity::SetSize(Vector2f size)
{
	m_Size = size;
	m_Sprite->UpdateBorder();
}


void AbstractEntity::OnCommand(Core::Command& command)
{
	if (command.category == GetCategory())
	{
		command.action(*this);
	}
}


void AbstractEntity::Render(SDL_Renderer* renderer)
{
	m_Sprite->Render(renderer);
}