#include "sgfpch.h"
#include "Canvas.h"

#include "UIComponent.h"

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


void Canvas::AddComponent(UIComponentPtr component)
{
	m_Components.push_back(std::move(component));
}


void Canvas::RemoveComponentAt(Uint32 index)
{
	m_Components.erase(std::next(m_Components.begin() + index));
}


void Canvas::HandleEvent(SDL_Event& event)
{

}


void Canvas::Update(double deltaTime)
{

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