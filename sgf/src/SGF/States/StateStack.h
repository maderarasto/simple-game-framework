#pragma once

#include "Structures.h"

namespace SGF::States
{
	class StateStack
	{
	public:
		StateStack(Context context);
		~StateStack();

		void Push(const std::string& stateName);
		void Pop();
		void Clear();

		void HandleEvent(SDL_Event& event);
		void Update(double deltaTime);
		void Render();

		template<typename State>
		void RegisterState(const std::string& name);

	private:
		AbstractStatePtr _CreateState(const std::string& stateName);
		void _ApplyPendingChanges();

	private:
		enum class StackAction
		{
			Push, 
			Pop,
			Clear
		};

		struct PendingChange
		{
			StackAction action;
			std::string stateName = "";
		};

	private:
		std::vector<AbstractStatePtr> m_States;
		std::vector<PendingChange> m_PendingChanges;
		std::unordered_map<std::string, StateFactory> m_StateFactories;

		Context m_Context;
	};

	template<typename State>
	void StateStack::RegisterState(const std::string& stateName)
	{
		m_StateFactories[stateName] = [this]()
		{
			return std::make_unique<State>(*this, m_Context);
		};
	}
}