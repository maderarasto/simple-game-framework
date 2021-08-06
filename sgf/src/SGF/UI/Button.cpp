#include "sgfpch.h"
#include "Button.h"
#include "Text.h"

#include "SGF/Core/Logger.h"

using namespace SGF::UI;


Button::Button(const ComponentProperties* properties) :
	UIComponent(properties),
	m_State(ButtonState::Idle),
	m_Active(false)
{
	auto props = static_cast<const ButtonProperties*>(properties);

	m_Text = std::make_unique<Text>(properties);
	m_OnClick = props->onClick;
	
	m_StateColors[ButtonState::Idle] = props->color;
	m_StateColors[ButtonState::Highlighted] = props->highlightColor;
	m_StateColors[ButtonState::Pressed] = props->pressedColor;
	m_StateColors[ButtonState::Active] = props->highlightColor;

	SetSize(m_Text->GetSize());
}


Button::~Button()
{

}


void Button::SetAnchorToCanvas(Canvas& canvas, Anchor anchor)
{
	UIComponent::SetAnchorToCanvas(canvas, anchor);
	m_Text->SetPosition(GetPosition());
}


void Button::SetPosition(Vector2i position)
{
	UIComponent::SetPosition(position);
	m_Text->SetPosition(position);
}


void Button::SetPosition(int x, int y)
{
	UIComponent::SetPosition(x, y);
	m_Text->SetPosition(x, y);
}


SDL_Color Button::GetColor() const
{
	return m_StateColors.at(ButtonState::Idle);
}


void Button::SetColor(SDL_Color color)
{
	m_StateColors[ButtonState::Idle] = color;
}


SDL_Color Button::GetHighlightedColor() const
{
	return m_StateColors.at(ButtonState::Highlighted);
}


void Button::SetHighlightedColor(SDL_Color color)
{
	m_StateColors[ButtonState::Highlighted] = color;
}


SDL_Color Button::GetPressedColor() const
{
	return m_StateColors.at(ButtonState::Pressed);
}


void Button::SetPressedColor(SDL_Color color)
{
	m_StateColors[ButtonState::Pressed] = color;
}


std::string Button::GetText() const
{
	return m_Text->GetText();
}


void Button::SetText(std::string text)
{
	m_Text->SetText(text);
}


bool Button::IsActive() const
{
	return m_Active;
}


void Button::SetActive(bool active)
{
	m_Active = active;
}


void Button::SetOnClick(ButtonAction onClick)
{
	m_OnClick = onClick;
}


void Button::Click()
{
	if (m_OnClick == NULL)
		throw std::runtime_error("Button does not have any onClick method to execure!");

	m_OnClick();
}


void Button::HandleEvent(SDL_Event& event)
{
	
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (_ResolveClick(event.button) && m_OnClick != NULL)
		{
			m_State = ButtonState::Pressed;
		}
	}
	else if (m_State != ButtonState::Highlighted && _ResolveHighlight())
	{
		m_State = ButtonState::Highlighted;
	}
	else if (m_State == ButtonState::Highlighted && !_ResolveHighlight())
	{
		m_State = ButtonState::Idle;
	}
	else
	{
		m_State = m_Active ? ButtonState::Active : ButtonState::Idle;
	}

}


void Button::Update(double deltaTime)
{
	SDL_Color color = m_StateColors[m_State];

	m_Text->SetColor(color);
}


void Button::Render(SDL_Renderer* renderer)
{
	SDL_Rect border = GetBorder();

	m_Text->Render(renderer);
}


bool Button::_ResolveClick(SDL_MouseButtonEvent& event)
{
	SDL_Rect mouseRect = { event.x, event.y, 1, 1 };
	SDL_Rect border = GetBorder();

	return SDL_HasIntersection(&border, &mouseRect);
}


bool Button::_ResolveHighlight()
{
	int mouseX, mouseY;

	SDL_GetMouseState(&mouseX, &mouseY);

	SDL_Rect mouseRect = { mouseX, mouseY, 1, 1 };
	SDL_Rect border = GetBorder();

	return SDL_HasIntersection(&border, &mouseRect);

}