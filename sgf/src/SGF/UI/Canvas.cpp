#include "sgfpch.h"
#include "Canvas.h"

#include "UIComponent.h"
#include "Button.h"

#include "SGF/Assets/Asset.h"

using namespace SGF::UI;


Canvas::Canvas(int width, int height) :
	m_Width(width),
	m_Height(height)
{
	m_Border = { 0, 0, m_Width, m_Height };
}


Canvas::~Canvas()
{

}


SDL_Color Canvas::GetBackgroundColor() const
{
	return m_BackgroundColor;
}


void Canvas::SetBackgroundColor(SDL_Color color)
{
	m_BackgroundColor = color;
}


void Canvas::RemoveComponentAt(Uint32 index)
{
	m_Components.erase(std::next(m_Components.begin() + index));
}


void Canvas::HandleEvent(SDL_Event& event)
{
	for (UIComponentPtr& component : m_Components)
	{
		if (dynamic_cast<Button*>(component.get()))
		{
			Button* button = static_cast<Button*>(component.get());
			button->HandleEvent(event);
		}
	}
}


void Canvas::Update(double deltaTime)
{
	for (UIComponentPtr& component : m_Components)
	{
		if (dynamic_cast<Button*>(component.get()))
		{
			Button* button = static_cast<Button*>(component.get());
			button->Update(deltaTime);
		}
	}
}


void Canvas::Render(SDL_Renderer* renderer)
{
	//SDL_SetRenderDrawColor(renderer, m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, m_BackgroundColor.a);
	//SDL_RenderFillRect(renderer, &m_Border);

	for (UIComponentPtr& component : m_Components)
	{
		component->Render(renderer);
	}
}