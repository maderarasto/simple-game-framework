#pragma once

#include "SGF/api.h"
#include "Structures.h"

namespace SGF::States
{
	class SGF_API AbstractState
	{
	public:
		typedef std::unique_ptr<AbstractState> Ptr;

		AbstractState(StateStack& stack, Context context);
		virtual ~AbstractState();

		AbstractState(const AbstractState&) = delete;
		AbstractState& operator=(const AbstractState&) = delete;

		inline Context GetContext() { return m_Context; }

		virtual bool HandleEvent(SDL_Event& event) = 0;
		virtual bool Update(double deltaTime) = 0;
		virtual void Render() = 0;

		void RequestPushState(const std::string& stateName);
		void RequestPopState();
		void RequestClearStates();

		virtual void LoadResources() = 0;

	protected:
		std::unique_ptr<UI::Canvas> m_Canvas;

	private:
		StateStack* m_Stack;
		Context m_Context;
	};
}