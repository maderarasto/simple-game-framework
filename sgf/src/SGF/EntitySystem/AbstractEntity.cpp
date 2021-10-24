#include "sgfpch.h"
#include "AbstractEntity.h"

#include "Sprite.h"
#include "SGF/Assets/Asset.h"
#include "SGF/Core/Logger.h"

using namespace SGF::EntitySystem;


AbstractEntity::AbstractEntity(Vector2f position, Vector2f size, Assets::Image& image) :
	m_Position(position),
	m_Size(size)
{
	m_Sprite = std::make_unique<Sprite>(*this, image);
	m_Collider = NULL;
	m_Layer = "Entity";
}


AbstractEntity::~AbstractEntity()
{

}

std::string AbstractEntity::GetLayer() const
{
	return m_Layer;
}

void AbstractEntity::SetLayer(const std::string& layerName)
{
	m_Layer = layerName;
}


Collider*  AbstractEntity::GetCollider() const
{
	return m_Collider.get();
}


void AbstractEntity::SetCollider(Vector2f position, Vector2f size)
{
	if (m_Collider == NULL)
		m_Collider = std::make_unique<Collider>();

	m_Collider->position = position;
	m_Collider->size = size;
}


Vector2f AbstractEntity::GetPosition() const
{
	return m_Position;
}


void AbstractEntity::SetPosition(Vector2f position)
{
	m_Position = position;
	m_Sprite->UpdateBorder();

	if (m_Collider != NULL)
		m_Collider->position = position;
}


Vector2f AbstractEntity::GetSize() const
{
	return m_Size;
}


void AbstractEntity::SetSize(Vector2f size)
{
	m_Size = size;
	m_Sprite->UpdateBorder();

	if (m_Collider != NULL)
		m_Collider->size = size;
}


void AbstractEntity::OnCommand(Core::Command& command)
{
	if (command.category == GetCategory())
	{
		command.action(*this);
	}
}

void AbstractEntity::OnCollision(AbstractEntity& otherEntity)
{
	CORE_LOG_TRACE("Collision");
}

void AbstractEntity::OnCollisionEnter(AbstractEntity& otherEntity)
{
	CORE_LOG_TRACE("Collision Enter");
}

void AbstractEntity::OnCollisionExit(AbstractEntity& otherEntity)
{
	CORE_LOG_TRACE("Collision Exit");
}


void AbstractEntity::Render(SDL_Renderer* renderer)
{
	m_Sprite->Render(renderer);

	if (m_Collider != NULL)
	{
		SDL_Rect colliderBounds = m_Collider->GetColliderBox().ToRect();
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &colliderBounds);
	}
}