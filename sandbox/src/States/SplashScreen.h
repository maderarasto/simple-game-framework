#pragma once

#include <SGF/States/AbstractState.h>
#include <SGF/UI/Text.h>

namespace States
{
	class SplashScreen : public SGF::States::AbstractState
	{
	public:
		SplashScreen(SGF::States::StateStack& stack, SGF::States::Context context);
		~SplashScreen();

		bool HandleEvent(SDL_Event& event) override;
		bool Update(double deltaTime) override;
		void Render() override;

	private:
		SGF::UI::TextPtr m_Title;
	};
}