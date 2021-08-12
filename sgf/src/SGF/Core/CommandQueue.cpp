#include "sgfpch.h"
#include "CommandQueue.h"

using namespace SGF::Core;


void CommandQueue::Push(Command command)
{
	m_Queue.push_back(command);
}


Command CommandQueue::Pop()
{
	Command command = m_Queue.front();
	
	m_Queue.erase(m_Queue.begin());

	return command;
}


void CommandQueue::Clear()
{
	m_Queue.clear();
}