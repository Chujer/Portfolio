#pragma once

class BabaMapManager : public Singleton<BabaMapManager>
{
private:
	const float MAX_SHAKE_POWER = 24.0f;
	const float SHAKE_TIME = 0.05f;
	enum Mode
	{
		MOVE, REVERSE_MOVE, Stop
	};
public:
	BabaMapManager();
	~BabaMapManager();

	void SetMapData(BabaTileMap* data);
	vector<Object*> GetMapData() { return maps; }
	Object* GetPositionTile(Vector2 pos);
	Object* GetPositionAndEffectTile(Vector2 pos, string effect);
	Object* GetPositionExceptMyself(Vector2 pos, string tag);
	Object* GetPositionMyself(Transform* transform);

	void ShakeMap();
	void Update();

	bool& IsClear() { return isClear; }

	float Left() { return LB.x; }
	float Top() { return RT.y; }
	float Bottom() { return LB.y; }
	float Right() { return RT.x; }
private:
	Vector2 LB, RT;
	vector<Object*> maps;

	bool isClear = false;

	Vector2 shakePos = { 0.0f,0.0f };
	Vector2 shakeDirection;
	Vector2 shakeEndPos;
	Vector2 shakeStartPos;
	float shakeTime = 0.0f;

	bool isShacke = false;

	Mode mode;

	BabaTileMap* sample;
};