#include "sgfpch.h"
#include "Text.h"

#include "SGF/Assets/Asset.h"

using namespace SGF::UI;


Text::Text(const ComponentProperties& properties) :
	UIComponent(properties)
{
	auto props = static_cast<const TextProperties&>(properties);
	
	m_Font = props.font;
	m_Color = props.color;
	m_Text = props.text;

	_ResolveTextSize();
}


Text::~Text()
{

}


SGF::Assets::Font& Text::GetFont() const
{
	return *m_Font;
}


void Text::SetFont(Assets::Font& font)
{
	m_Font = &font;
	_ResolveTextSize();
}


SDL_Color Text::GetColor() const
{
	return m_Color;
}


void Text::SetColor(SDL_Color color)
{
	m_Color = color;
}


std::string Text::GetText() const
{
	return m_Text;
}


void Text::SetText(std::string text)
{
	m_Text = text;
	_ResolveTextSize();
}


void Text::Render(SDL_Renderer* renderer)
{
	SDL_Surface* surface = TTF_RenderText_Solid(m_Font->GetPointer(), m_Text.c_str(), m_Color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect border = GetBorder();

	SDL_RenderCopy(renderer, texture, NULL, &border);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}


void Text::_ResolveTextSize()
{
	int width, height;

	TTF_SizeText(m_Font->GetPointer(), m_Text.c_str(), &width, &height);
	SetSize(width, height);
}