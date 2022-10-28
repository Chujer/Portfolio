#include "Framework.h"

IsObject::IsObject(string key)
	:Object(key)
{
}


IsObject::~IsObject()
{
}

int IsObject::GetWidthProperty()
{
	if (haveObject.left != nullptr && haveObject.right != nullptr && haveObject.left->Active() && haveObject.right->Active())
	{
		if (haveObject.right->tag.find("YOU") != string::npos)
			return 1;
		else if (haveObject.right->tag.find("STOP") != string::npos)
			return 2;
		else if (haveObject.right->tag.find("PUSH") != string::npos)
			return 3;
	}
	return 0;
}

int IsObject::GetHeightProperty()
{
	if (haveObject.top != nullptr && haveObject.bottom != nullptr && haveObject.top->Active() && haveObject.bottom->Active())
	{
		if (haveObject.bottom->tag.find("YOU") != string::npos)
			return 1;
		else if (haveObject.bottom->tag.find("STOP") != string::npos)
			return 2;
		else if (haveObject.right->tag.find("PUSH") != string::npos)
			return 3;
	}
	return 0;
}

void IsObject::RemoveHaveObject()
{
	if (haveObject.left != nullptr)
	{
		if (haveObject.left->Position() != Position() - Vector2(48.0f, 0) || !haveObject.left->Active())
		{
			EventManager::Get()->PlayObjEvent("RemoveWidthPropertyObject", this);
			haveObject.left = nullptr;
		}
	}
	if (haveObject.right != nullptr)
	{
		if (haveObject.right->Position() != Position() + Vector2(48.0f, 0) || !haveObject.right->Active())
		{
			EventManager::Get()->PlayObjEvent("RemoveWidthPropertyObject", this);
			haveObject.right = nullptr;
		}
	}
	if (haveObject.top != nullptr)
	{
		if (haveObject.top != nullptr && haveObject.top->Position() != Position() + Vector2(0, 48.0f) || !haveObject.top->Active())
		{
			EventManager::Get()->PlayObjEvent("RemoveHeightPropertyObject", this);
			haveObject.top = nullptr;
		}
	}
	if (haveObject.bottom != nullptr)
	{
		if (haveObject.bottom != nullptr && haveObject.bottom->Position() != Position() - Vector2(0, 48.0f) || !haveObject.bottom->Active())
		{
			EventManager::Get()->PlayObjEvent("RemoveHeightPropertyObject", this);
			haveObject.bottom = nullptr;
		}
	}

	EventManager::Get()->PlayObjEvent("SetPropertyHeight", this);
	EventManager::Get()->PlayObjEvent("SetPropertyWidth", this);
}
