#pragma once

class Button : public ImageRect
{
public:
    enum State
    {
        NORMAL, OVER, DOWN
    };

public:
    Button(Texture* texture);
    ~Button();

    void Update();
    void Render(HDC hdc);
    void TextRender(HDC hdc);

    void SetFont(HFONT font, int fontSize = 20, COLORREF fontColor = BLACK);

    void SetEvent(function<void()> Event) { this->Event = Event; }
    void SetObjEvent(function<void(void*)> Event) { ObjEvent = Event; }

    void SetOverTexture(Texture * texture) { overTexture = texture; }
    void SetDownTexture(Texture * texture) { downTexture = texture; }

    void SetText(string text) { this->text = text; }
    string GetText() { return text; }

protected:
    State state = NORMAL;

    bool isClick = false;

    function<void()> Event = nullptr;
    function<void(void *)> ObjEvent = nullptr;

    Texture * normalTexture = nullptr;
    Texture * overTexture = nullptr;
    Texture * downTexture = nullptr;

    string text;

    HFONT font = nullptr, oldFont = nullptr;
    int fontSize = 20;
    COLORREF fontColor = BLACK;
};