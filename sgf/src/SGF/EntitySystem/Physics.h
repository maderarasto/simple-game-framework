#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::EntitySystem
{
	class SGF_API Physics
	{
	public:
		typedef std::unique_ptr<Physics> Ptr;

		Physics(std::vector<AbstractEntityPtr>& entities);
		~Physics();

		Physics(const Physics&) = delete;
		Physics& operator=(const Physics&) = delete;

		void AddCollisionLayer(const std::string& layerName);
		void RemoveCollisionLayer(const std::string& layerName);
		void SetLayerRelation(const std::string& layerName, const std::string& otherLayerName, bool value);

		void HandleCollisions();

	private:
		std::vector<Collision>::iterator _FindCollision(const AbstractEntity& entityA, const AbstractEntity& entityB);
		bool _CheckCollision(const AbstractEntity& entityA, const AbstractEntity& entityB) const;
		bool _CheckCollisionLayers(const AbstractEntity& entityA, const AbstractEntity& entityB) const;
		void _HandleBasicCollision(AbstractEntity& stateEntityA, AbstractEntity& stateEntityB) const;

	private:
		std::vector<AbstractEntityPtr>* m_Entities;
		std::vector<Collision> m_Collisions;
		std::vector<std::string> m_Layers;
		std::vector<CollisionLayer> m_LayerRelations;
	};
}