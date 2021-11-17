#include "sgfpch.h"
#include "Image.h"

#include "SGF/Assets/Asset.h"

using namespace SGF::UI;


Image::Image(const ComponentProperties* properties) :
	UIComponent(properties)
{
	auto props = static_cast<const ImageProperties*>(properties);

	m_SourceImage = props->imageSource;
}


Image::~Image()
{

}


SGF::Assets::Image& Image::GetSourceImage() const
{
	return *m_SourceImage;
}


void Image::SetSourceImage(SGF::Assets::Image& sourceImage)
{
	m_SourceImage = &sourceImage;
}


void Image::Render(SDL_Renderer* renderer)
{
	if (m_SourceImage)
	{
		SDL_Surface* surfaceImage = m_SourceImage->GetPointer();
		SDL_Texture* textureImage = SDL_CreateTextureFromSurface(renderer, surfaceImage);
		SDL_Rect border = GetBorder();

		SDL_RenderCopy(renderer, textureImage, NULL, &border);
		SDL_DestroyTexture(textureImage);
	}
}