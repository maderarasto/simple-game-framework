#include "Application.h"
#include "SGF/Core/Logger.h"

using namespace SGF;


Application::Application()
{
	Core::Logger::Init();
	
	CORE_LOG_TRACE("The appliation successfully initialized.");
}


void Application::Run()
{

}