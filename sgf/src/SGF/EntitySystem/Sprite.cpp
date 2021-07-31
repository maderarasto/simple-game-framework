#include "sgfpch.h"
#include "Sprite.h"

#include "AbstractEntity.h"
#include "SGF/Assets/Asset.h"

using namespace SGF::EntitySystem;


Sprite::Sprite(AbstractEntity& entity, Assets::Image& image) :
	m_Entity(&entity),
	m_Image(&image)
{
	UpdateBorder();
}


Sprite::~Sprite()
{

}


void Sprite::SetImage(Assets::Image& image)
{
	m_Image = &image;
}


void Sprite::UpdateBorder()
{
	Vector2f entityPosition = m_Entity->GetPosition();
	Vector2f entitySize = m_Entity->GetSize();

	m_Border = {
		(int)entityPosition.x,
		(int)entityPosition.y,
		(int)entitySize.x,
		(int)entitySize.y
	};
}


void Sprite::Render(SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, m_Image->GetPointer());

	SDL_RenderCopy(renderer, texture, NULL, &m_Border);
	SDL_DestroyTexture(texture);
}