#pragma once

class Keyboard : public Singleton<Keyboard>
{
private:
    static const UINT KEY_MAX = 255;

    enum KeyState
    {
        NONE, DOWN, UP, PRESS
    };

public:
    Keyboard();
    ~Keyboard();

    void Update();

    bool Down(UINT key) { return mapState[key] == DOWN; }
    bool Up(UINT key) { return mapState[key] == UP; }
    bool Press(UINT key) { return mapState[key] == PRESS; }

    bool IsAnyKey();
private:
    BYTE curState[KEY_MAX] = {};
    BYTE oldState[KEY_MAX] = {};
    KeyState mapState[KEY_MAX] = {};
};