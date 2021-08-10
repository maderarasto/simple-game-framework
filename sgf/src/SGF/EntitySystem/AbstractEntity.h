#pragma once

#include "SGF/api.h"
#include "Structures.h"

#include "SGF/Core/Structures.h"


namespace SGF::EntitySystem
{
	class SGF_API AbstractEntity
	{
	public:
		AbstractEntity(Vector2f position, Vector2f size, Assets::Image& image);
		virtual ~AbstractEntity();

		AbstractEntity(const AbstractEntity&) = delete;
		AbstractEntity& operator=(const AbstractEntity&) = delete;

		inline virtual std::string GetCategory() const { return "Entity"; }

		Vector2f GetPosition() const;
		void SetPosition(Vector2f position);

		Vector2f GetSize() const;
		void SetSize(Vector2f position);

		void OnCommand(Core::Command& command);

		virtual void Update(double deltaTime) = 0;
		virtual void Render(SDL_Renderer* renderer);

	private:
		Vector2f m_Position;
		Vector2f m_Size;

		SpritePtr m_Sprite;
	};
}