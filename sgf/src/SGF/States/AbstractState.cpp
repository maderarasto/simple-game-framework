#include "sgfpch.h"
#include "AbstractState.h"
#include "StateStack.h"

using namespace SGF::States;


AbstractState::AbstractState(StateStack& stack, Context context) :
	m_Stack(&stack),
	m_Context(context)
{

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