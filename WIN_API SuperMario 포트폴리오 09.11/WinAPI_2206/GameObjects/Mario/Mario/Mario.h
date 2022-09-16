#pragma once

class Mario : public ImageRect
{
private:
    const float JUMP_POWER = 980.0f;
    const float GRAVITY = 1980.0f;
    const float MAX_VELOCITY = 500.0f;
    const float ACCEL = 700.0f;
    const float DECEL = 2.0f;
    const float SLOPE = 10.0f;

    const UINT MAX_JUMP_COUNT = 1;

    enum ActionType
    {
        IDLE_R, IDLE_L, DIE, SIT_R, SIT_L,
        RUN_R, JUMP_R,  BRAKE_R,
        RUN_L, JUMP_L,  BRAKE_L, 
        CHANGE_MODE_R, CHANGE_MODE_L,
        FLOWER_CHANGE_MODE_R, FLOWER_CHANGE_MODE_L,
        ATTACK_L, ATTACK_R
    };

    enum Mode
    {
        SMALL, BIG, FLOWER, CHANGE_MODE, CHANGE_FLOWER_MODE
    };

public:
	Mario();
	~Mario();

    void Update();
    void Render(HDC hdc);
    void SetSize()
    {
        size = texture->GetSize() * 3.0f;
        camRect->Size() = size;
    }


    void IsHit();
    void PushEnemy();

    void EatMushroom();
    void EatFlower();

    void EndChangeMushroomAnimation();
    void EndChangeFlowerAnimation();
    void IsOnTheGround(Vector2 Ground);
    
    bool& GetDie() { return isDie; }

    Vector2& GetVelocity()
    {
        return velocity;
    }
    Mode GetMode()
    {
        return mode;
    }

    //void SetBeforMode(Mode beforeMode) { this->beforeMode = beforeMode; }

private:
    void Move();
    void Jump();
    void Shooting();
    void Die();

    void SetAnimation();
    void CreateAnimation();

    void SetAction(ActionType type);

    void ChangeSmallToBig();
    void ChangeBigToSmall();
    void ChangeFlower();
    

private:
    map<ActionType, Animation*> animations;

    Texture* smallMarioAnimation;
    Texture* bigMarioAnimation;
    Texture* FlowerMarioAnimation;
    Texture* changeMarioMushroomAnimation;
    Texture* changeMarioFlowerAnimation;

    ActionType curType = IDLE_R;

    float speed = 500.0f;

    UINT jumpCount = 0;

    Vector2 velocity;

    bool isRight = true;
    bool isRun = false;
    bool isDie = false;

    Mode mode = SMALL;
    Mode beforeMode = SMALL;

    Rect* hitBox;
    Vector2 bodyOffset;
};