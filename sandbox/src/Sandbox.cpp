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
	Sandbox* sandbox = new Sandbox();

	delete sandbox;
	system("pause");

	return 0;
}