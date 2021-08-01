#include "sgfpch.h"
#include "UIComponent.h"
#include "Canvas.h"

#include "SGF/Core/Vector2.h"

using namespace SGF::UI;


UIComponent::UIComponent(const ComponentProperties* properties) :
	m_Position(properties->position),
	m_Size(properties->size),
	m_Canvas(NULL),
	m_Anchor(Alignment::None, Alignment::None)
{
	_UpdateBorder();
}


UIComponent::~UIComponent()
{

}


void UIComponent::SetAnchorToCanvas(Canvas& canvas, Anchor anchor)
{
	m_Canvas = &canvas;
	m_Anchor = anchor;

	_UpdateBorder();
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


void UIComponent::_ResolveHorizontalAnchor()
{
	int positionX = m_Position.x;

	if (m_Anchor.horizontal != Alignment::None && m_Canvas == NULL)
		throw std::runtime_error(" There is a missing pointer to Canvas object!");

	if (m_Anchor.horizontal == Alignment::Start)
		positionX = m_Anchor.indent.x;
	else if (m_Anchor.horizontal == Alignment::Center)
		positionX = (m_Canvas->GetWidth() - m_Size.x) / 2;
	else if (m_Anchor.horizontal == Alignment::End)
		positionX = m_Canvas->GetWidth() - m_Anchor.indent.x - m_Size.x;

	m_Border.x = positionX;
}


void UIComponent::_ResolveVerticalAnchor()
{
	int positionY = m_Position.y;

	if (m_Anchor.vertical != Alignment::None && m_Canvas == NULL)
		throw std::runtime_error(" There is a missing pointer to Canvas object!");

	if (m_Anchor.vertical == Alignment::Start)
		positionY = m_Anchor.indent.y;
	else if (m_Anchor.vertical == Alignment::Center)
		positionY = (m_Canvas->GetHeight() - m_Size.y) / 2;
	else if (m_Anchor.vertical == Alignment::End)
		positionY = m_Canvas->GetHeight() - m_Anchor.indent.y - m_Size.y;

	m_Border.y = positionY;
}


void UIComponent::_UpdateBorder()
{
	m_Border.w = m_Size.x;
	m_Border.h = m_Size.y;
	
	_ResolveHorizontalAnchor();
	_ResolveVerticalAnchor();
}