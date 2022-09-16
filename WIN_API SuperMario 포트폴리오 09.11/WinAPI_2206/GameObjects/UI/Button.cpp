#include "Framework.h"

Button::Button(Texture * texture)
    : ImageRect(texture), normalTexture(texture)
{
}

Button::~Button()
{
}

void Button::Update()
{
    if (!isActive) return;

    if (IsCollision(mousePos))
    {
        state = OVER;

        if (KEY_UP(VK_LBUTTON) && isClick)
        {
            if (Event != nullptr)
                Event();

            if (ObjEvent != nullptr)
                ObjEvent(this);

            isClick = false;
        }

        if (KEY_DOWN(VK_LBUTTON))
            isClick = true;

        if (KEY_PRESS(VK_LBUTTON))
            state = DOWN;
    }
    else
    {
        state = NORMAL;

        if (KEY_UP(VK_LBUTTON))
            isClick = false;
    }

    switch (state)
    {
    case Button::NORMAL:
        SetTexture(normalTexture);
        break;
    case Button::OVER:
        if (overTexture != nullptr)
            SetTexture(overTexture);
        break;
    case Button::DOWN:
        if (downTexture != nullptr)
            SetTexture(downTexture);
        break;
    default:
        break;
    }
}

void Button::Render(HDC hdc)
{
    ImageRect::Render(hdc);
    TextRender(hdc);
}

void Button::TextRender(HDC hdc)
{
    if (font != nullptr)
        oldFont = (HFONT)SelectObject(hdc, font);

    COLORREF oldColor = SetTextColor(hdc, fontColor);
        
    RECT rect = { Left(), Top() + fontSize * 0.25f, Right(), Bottom() + fontSize * 0.25f };
    DrawTextA(hdc, text.c_str(), text.length(), &rect, DT_CENTER);

    if (font != nullptr)
        SelectObject(hdc, oldFont);

    SetTextColor(hdc, oldColor);
}

void Button::SetFont(HFONT font, int fontSize, COLORREF fontColor)
{
    this->font = font;
    this->fontSize = fontSize;
    this->fontColor = fontColor;
}
