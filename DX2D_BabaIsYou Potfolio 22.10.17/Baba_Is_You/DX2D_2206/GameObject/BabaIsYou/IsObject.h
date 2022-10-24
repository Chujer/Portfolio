#pragma once

class IsObject : public Object
{
public:
	struct HaveObject
	{
		Object* left = nullptr;
		Object* right = nullptr;
		Object* top = nullptr;
		Object* bottom = nullptr;
	};
public:
	IsObject(string key);
	~IsObject();

	HaveObject& GetHaveObject() { return haveObject; }
	int GetWidthProperty();
	int GetHeightProperty();

	void RemoveHaveObject();
private:
	HaveObject haveObject;
};