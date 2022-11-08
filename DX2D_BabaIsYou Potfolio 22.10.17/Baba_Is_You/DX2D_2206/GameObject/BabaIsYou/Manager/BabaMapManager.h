#pragma once

class BabaMapManager : public Singleton<BabaMapManager>
{
public:
	BabaMapManager();
	~BabaMapManager();

	void SetMapData(BabaTileMap* data);
	vector<Object*> GetMapData() { return maps; }
	Object* GetPositionTile(Vector2 pos);
	Object* GetPositionAndEffectTile(Vector2 pos, string effect);
	Object* GetPositionExceptMyself(Vector2 pos, string tag);
	Object* GetPositionMyself(Transform* transform);

	bool& IsClear() { return isClear; }

	float Left() { return LB.x; }
	float Top() { return RT.y; }
	float Bottom() { return LB.y; }
	float Right() { return RT.x; }
private:
	Vector2 LB, RT;
	vector<Object*> maps;

	bool isClear = false;
};