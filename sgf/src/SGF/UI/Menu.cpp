#include "sgfpch.h"
#include "Menu.h"
#include "Button.h"

#include "SGF/Core/Logger.h"

using namespace SGF::UI;


Menu::Menu(const ComponentProperties* properties) :
	UIComponent(properties),
	m_SelectedItem(0)
{
	auto props = static_cast<const MenuProperties*>(properties);

	m_StateColors[ButtonState::Idle] = props->color;
	m_StateColors[ButtonState::Highlighted] = props->highlightColor;
	m_StateColors[ButtonState::Active] = props->highlightColor;
	m_StateColors[ButtonState::Pressed] = props->pressedColor;
	m_Spacing = props->spacing;

	int width = 0;
	int height = 0;

	for (int i = 0; i < props->items.size(); i++)
	{
		auto buttonProps = [&]()
		{
			ButtonProperties p;

			p.font = props->font;
			p.color = props->color;
			p.highlightColor = props->highlightColor;
			p.pressedColor = props->pressedColor;
			p.text = props->items[i].text;
			p.onClick = props->items[i].action;

			return p;
		}();

		ButtonPtr button = std::make_unique<Button>(&buttonProps);
		Vector2i buttonSize = button->GetSize();
		
		if (i == m_SelectedItem)
			button->SetActive(true);

		if (buttonSize.x > width)
			width = buttonSize.x;

		height += buttonSize.y + m_Spacing;

		m_Buttons.push_back(std::move(button));
	}

	SetSize(width, height);
}


Menu::~Menu()
{

}


void Menu::SetAnchorToCanvas(Canvas& canvas, Anchor anchor)
{
	UIComponent::SetAnchorToCanvas(canvas, anchor);
	_UpdateButtonsPosition();
}


void Menu::SetPosition(int x, int y)
{
	UIComponent::SetPosition(x, y);
	_UpdateButtonsPosition();
}


void Menu::SetPosition(Vector2i position)
{
	UIComponent::SetPosition(position);
	_UpdateButtonsPosition();
}


SDL_Color Menu::GetColor() const
{
	return m_StateColors.at(ButtonState::Idle);
}


void Menu::SetColor(SDL_Color color)
{
	m_StateColors[ButtonState::Idle] = color;
}


SDL_Color Menu::GetHighlightColor() const
{
	return m_StateColors.at(ButtonState::Highlighted);
}


void Menu::SetHighlightColor(SDL_Color color)
{
	m_StateColors[ButtonState::Highlighted] = color;
}


SDL_Color Menu::GetPressedColor() const
{
	return m_StateColors.at(ButtonState::Pressed);
}


void Menu::SetPressedColor(SDL_Color color)
{
	m_StateColors[ButtonState::Pressed] = color;
}


void Menu::HandleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP)
	{
		m_SelectedItem = (m_SelectedItem - 1) >= 0 ? m_SelectedItem - 1 : m_Buttons.size() - 1;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN)
	{
		m_SelectedItem = ++m_SelectedItem % m_Buttons.size();
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		m_Buttons[m_SelectedItem]->Click();
	}

	_UpdateButtonsState();
	
	for (ButtonPtr& button : m_Buttons)
	{
		button->HandleEvent(event);
	}
}


void Menu::Update(double deltaTime)
{
	for (ButtonPtr& button : m_Buttons)
	{
		button->Update(deltaTime);
	}
}


void Menu::Render(SDL_Renderer* renderer)
{
	for (ButtonPtr& button : m_Buttons)
	{
		button->Render(renderer);
	}
}


void Menu::_UpdateButtonsPosition()
{
	Vector2i position = GetPosition();

	for (int i = 0; i < m_Buttons.size(); i++)
	{
		m_Buttons[i]->SetPosition(position.x, position.y + i * (m_Buttons[i]->GetSize().y + m_Spacing));
	}
}


void Menu::_UpdateButtonsState()
{
	for (ButtonPtr& btn : m_Buttons)
	{
		btn->SetActive(false);
	}
	
	m_Buttons[m_SelectedItem]->SetActive(true);
}