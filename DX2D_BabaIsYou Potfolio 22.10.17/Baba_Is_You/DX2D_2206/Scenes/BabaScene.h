#pragma once

class BabaScene : public Scene
{
public:
	enum class ActionType
	{
		NONE = 0, MOVE, STOP, PUSH, WIN, DEFEAT, HOT, MELT, SINK, YOU
	};
public:
	BabaScene();
	~BabaScene();

	// Scene을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Load(int curstage);
	void SetLoad();

	void SetAction(Object* object, ActionType action);

	void CheckIs();

	void SetWidthPropertyObject(void* object);
	void SetHeightPropertyObject(void* object);
	void RemoveWidthPropertyObject(void* object);
	void RemoveHeightPropertyObject(void* object);

private:
	map<string, InstanceQuad*> instanceQuads;

	BabaTileMap* tileMap;
	vector<Object*> objects;

	vector<Object*> objectNames;
	map<string,vector<Object*>> objectImgs;
	vector<Object*> propertys;

	vector<IsObject*> propertyIs;		//IS블럭을 담는 객체
	
	int stage = 0;


	//map<ActionType, vector<Object*>> propertyObject;

	Quad* backGround;
};