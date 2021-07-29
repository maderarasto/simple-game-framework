#include "sgfpch.h"
#include "SGF.h"

#include "SGF/States/StateStack.h"
#include "SGF/Assets/AssetManager.h"

#include "States/SplashScreen.h"

class Sandbox : public SGF::Application
{
public:
	Sandbox(SGF::AppConfig* config) : SGF::Application(config)
	{
		m_StateStack->RegisterState<States::SplashScreen>("SplashScreen");
		m_FontAssets->Load("Roboto-Regular.ttf", "ROBOTO_REGULAR_10", 10);

		m_StateStack->Push("SplashScreen");
	}
};

int main(int argc, char** argv)
{
	SGF::AppConfig* config = [&]
	{
		SGF::AppConfig* config = new SGF::AppConfig();

		config->title = "Sandbox";
		config->resolution_width = 1024;
		config->resolution_height = 768;

		return config;
	}();

	try {
		Sandbox* sandbox = new Sandbox(config);
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