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
	if (haveObject.left != nullptr && haveObject.right != nullptr)
	{
		if (haveObject.right->tag.find("YOU") != string::npos)
			return 1;
	}
	return 0;
}

int IsObject::GetHeightProperty()
{
	if (haveObject.top != nullptr && haveObject.left != nullptr)
	{
		if (haveObject.bottom->tag.find("YOU") != string::npos)
			return 1;
	}
	return 0;
}

void IsObject::RemoveHaveObject()
{
	if (haveObject.left != nullptr && haveObject.left->Position() != Position() - Vector2(48.0f, 0))
	{
		haveObject.left = nullptr;
	}
	else if (haveObject.right != nullptr && haveObject.right->Position() != Position() + Vector2(48.0f, 0) )
	{
		haveObject.right = nullptr;
	}
	else if (haveObject.top != nullptr && haveObject.top->Position() != Position() + Vector2(0, 48.0f))
	{
		haveObject.top = nullptr;
	}
	else if (haveObject.bottom != nullptr && haveObject.bottom->Position() != Position() - Vector2(0, 48.0f))
	{
		haveObject.bottom = nullptr;
	}
}
