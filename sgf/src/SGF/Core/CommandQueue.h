#pragma once

#include "SGF/api.h"

#include "Structures.h"

namespace SGF::Core
{
	class SGF_API CommandQueue
	{
	public:
		typedef std::unique_ptr<CommandQueue> Ptr;

		inline bool IsEmpty() const { return m_Queue.size() == 0; }

		void Push(Command command);
		Command Pop();
		void Clear();

	private:
		std::vector<Command> m_Queue;
	};
}