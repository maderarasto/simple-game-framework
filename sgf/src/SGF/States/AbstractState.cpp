#include "sgfpch.h"
#include "AbstractState.h"
#include "StateStack.h"

#include "SGF/UI/Canvas.h"

using namespace SGF::States;


AbstractState::AbstractState(StateStack& stack, Context context) :
	m_Stack(&stack),
	m_Context(context)
{
	m_Canvas = std::make_unique<UI::Canvas>(1024, 768);
}


AbstractState::~AbstractState()
{

}


void AbstractState::RequestPushState(const std::string& stateName)
{
	m_Stack->Push(stateName);
}


void AbstractState::RequestPopState()
{
	m_Stack->Pop();
}


void AbstractState::RequestClearStates()
{
	m_Stack->Clear();
}