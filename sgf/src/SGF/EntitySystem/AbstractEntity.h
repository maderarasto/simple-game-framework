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

		std::string GetLayer() const;
		void SetLayer(const std::string& layerName);

		Collider* GetCollider() const;
		void SetCollider(Vector2f position, Vector2f size);

		Vector2f GetPosition() const;
		void SetPosition(Vector2f position);

		Vector2f GetSize() const;
		void SetSize(Vector2f position);

		void OnCommand(Core::Command& command);
		virtual void OnCollision(AbstractEntity& other);
		virtual void OnCollisionEnter(AbstractEntity& other);
		virtual void OnCollisionExit(AbstractEntity& other);

		virtual void Update(double deltaTime) = 0;
		virtual void Render(SDL_Renderer* renderer);

	private:
		Vector2f m_Position;
		Vector2f m_Size;
		std::string m_Layer;

		SpritePtr m_Sprite;
		Collider::Ptr m_Collider;
	};
}