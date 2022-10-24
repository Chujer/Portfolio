#pragma once

class BabaScene : public Scene
{
public:
	enum class ActionType
	{
		NONE = 0, MOVE, STOP, DEFEAT, HOT, MELT, PUSH, SINK, WIN, YOU
	};
public:
	BabaScene();
	~BabaScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Load();

	void SetAction(Object* object, ActionType action);

	void CheckIs();

	void SetPropertyObject(void* object);

private:
	map<string, InstanceQuad*> instanceQuads;

	BabaTileMap* tileMap;
	vector<Object*> objects;

	vector<Object*> objectNames;
	vector<Object*> objectImgs;
	vector<Object*> propertys;

	vector<IsObject*> propertyIs;
	
	map<ActionType, vector<Object*>> propertyObject;

	Quad* backGround;
};