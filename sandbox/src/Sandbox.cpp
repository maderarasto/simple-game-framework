#include "SGF.h"

class Sandbox : public SGF::Application
{
public:
	Sandbox()
	{
	}
};

int main(int argc, char** argv)
{
	try {
		Sandbox* sandbox = new Sandbox();
		sandbox->Run();
		delete sandbox;
	}
	catch (std::exception e)
	{
		APP_LOG_CRITICAL(e.what());
		return -1;
	}

	return 0;
}