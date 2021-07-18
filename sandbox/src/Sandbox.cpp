#include "SGF/Application.h"

class Sandbox : SGF::Application
{
	
};

int main(int argc, char** argv)
{
	Sandbox* sandbox = new Sandbox();

	delete sandbox;
	system("pause");

	return 0;
}