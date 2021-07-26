#include "sgfpch.h"
#include "StateStack.h"
#include "AbstractState.h"

using namespace SGF::States;


StateStack::StateStack(Context context) :
	m_Context(context)
{

}


StateStack::~StateStack()
{

}


void StateStack::Push(const std::string& stateName)
{
	m_PendingChanges.push_back({ StackAction::Push, stateName });
}


void StateStack::Pop()
{
	m_PendingChanges.push_back({ StackAction::Pop });
}


void StateStack::Clear()
{
	m_PendingChanges.push_back({ StackAction::Clear });
}


void StateStack::HandleEvent(SDL_Event& event)
{
	for (auto iterator = m_States.rbegin(); iterator != m_States.rend(); ++iterator)
	{
		if (!(*iterator)->HandleEvent(event))
			return;
	}

	_ApplyPendingChanges();
}


void StateStack::Update(double deltaTime)
{
	for (auto iterator = m_States.rbegin(); iterator != m_States.rend(); ++iterator)
	{
		if (!(*iterator)->Update(deltaTime))
			return;
	}

	_ApplyPendingChanges();
}


void StateStack::Render()
{
	for (AbstractStatePtr& state : m_States)
	{
		state->Render();
	}
}


AbstractStatePtr StateStack::_CreateState(const std::string& stateName)
{
	return m_StateFactories[stateName]();
}


void StateStack::_ApplyPendingChanges()
{
	for (PendingChange change : m_PendingChanges)
	{
		switch (change.action)
		{
		case StackAction::Push:
			m_States.push_back(_CreateState(change.stateName));
			break;
		case StackAction::Pop:
			m_States.pop_back();
			break;
		case StackAction::Clear:
			m_States.clear();
		}
	}

	m_PendingChanges.clear();
}