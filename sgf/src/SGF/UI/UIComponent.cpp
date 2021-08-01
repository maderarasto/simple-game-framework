#include "sgfpch.h"
#include "UIComponent.h"

#include "SGF/Core/Vector2.h"

using namespace SGF::UI;


UIComponent::UIComponent(const ComponentProperties& properties) :
	m_Position(properties.position),
	m_Size(properties.size)
{
	_UpdateBorder();
}


UIComponent::~UIComponent()
{

}


Vector2i UIComponent::GetPosition() const
{
	return m_Position;
}


void UIComponent::SetPosition(int x, int y)
{
	m_Position = Vector2i(x, y);
	_UpdateBorder();
}


void UIComponent::SetPosition(Vector2i position)
{
	m_Position = position;
	_UpdateBorder();
}


Vector2i UIComponent::GetSize() const
{
	return m_Size;
}


void UIComponent::SetSize(int w, int h)
{
	m_Size = Vector2i(w, h);
	_UpdateBorder();
}


void UIComponent::SetSize(Vector2i size)
{
	m_Size = size;
	_UpdateBorder();
}


void UIComponent::_UpdateBorder()
{
	m_Border = {
		(int)m_Position.x,
		(int)m_Position.y,
		(int)m_Size.x,
		(int)m_Size.y
	};
}