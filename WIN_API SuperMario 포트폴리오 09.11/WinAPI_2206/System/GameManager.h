#pragma once

class GameManager : public Singleton<GameManager>
{
private:
    friend class Singleton;

    GameManager();
    ~GameManager();

public:    
    void Update();
    void Render();

    void SetInit();

    void Stop() { isStop = true; }
    void Play() { isStop = false; }

private:
    void Create();
    void Destory();

private:    
    HDC hdc;

    HDC backBuffer;
    HBITMAP bitmap;

    bool isStop = false;
};