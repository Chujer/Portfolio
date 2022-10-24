#include "Framework.h"
#include "BabaScene.h"

BabaScene::BabaScene()
{
	backGround = new Quad(L"Textures/BackGround.png");
	backGround->Position() = { CENTER_X,CENTER_Y };
	backGround->UpdateWorld();


	//EventManager  관련
	// EventManager를 이용해 propertys변수안의 값을 추가 제거할수 있도록 사용 사용처(IsObject클래스)
	EventManager::Get()->Add("SetPropertyObject", bind(&SetPropertyObject, 1, std::placeholders::_1));

	Load();
}

BabaScene::~BabaScene()
{
	delete backGround;
	for (pair<string, InstanceQuad*> instanceQuad : instanceQuads)
	{
		delete instanceQuad.second;
	}
}

void BabaScene::Update()
{
	tileMap->Update();

	CheckIs();

	for (pair<string, InstanceQuad*> instanceQuad : instanceQuads)
	{
		instanceQuad.second->Update();
	}
}

void BabaScene::Render()
{
	backGround->Render();
	tileMap->Render();

	for (pair<string, InstanceQuad*> instanceQuad : instanceQuads)
		instanceQuad.second->Render();
}

void BabaScene::PostRender()
{
}

void BabaScene::Load()
{
	if (tileMap == nullptr)
		tileMap = new BabaTileMap(0, 0);
	tileMap->Load("TextData/test.map");
	objects.clear();
	objects = tileMap->GetTiles();

	objectNames.clear();
	propertyIs.clear();
	propertys.clear();
	objectImgs.clear();

	for (Object* object : objects)
	{
		if (object->tag.find("NAME") != string::npos)
			objectNames.push_back(object);
		else if (object->tag.find("IS") != string::npos)
			propertyIs.push_back((IsObject*)object);
		else if (object->tag.find("PROPERTY") != string::npos)
			propertys.push_back(object);
		else
			objectImgs.push_back(object);
	}

}

void BabaScene::SetAction(Object* object, ActionType action)
{
	switch (action)
	{
	case BabaScene::ActionType::MOVE:
		if (object->tag.find("NAME") == string::npos)
		{
			if (object->tag.find("BABA") != string::npos)
			{
				object->SetAction(new Move((Transform*)object, &object->GetInstanceData().curFrame));
				return;
			}
			object->SetAction(new Move((Transform*)object));
		}
		break;
	case BabaScene::ActionType::STOP:
		break;
	case BabaScene::ActionType::DEFEAT:
		break;
	case BabaScene::ActionType::HOT:
		break;
	case BabaScene::ActionType::MELT:
		break;
	case BabaScene::ActionType::PUSH:
		break;
	case BabaScene::ActionType::SINK:
		break;
	case BabaScene::ActionType::WIN:
		break;
	case BabaScene::ActionType::YOU:
		break;
	default:
		break;
	}
	
}

void BabaScene::CheckIs()
{
	for (IsObject* object : propertyIs)
	{
		for (Object* target : objects)
		{
			if ((target->tag.find("NAME") != string::npos || target->tag.find("PROPERTY") != string::npos )
				&& target->tag.find("IS") == string::npos)
			{
				if (target->Position() == object->Position() - Vector2(48.0f, 0) && target->tag.find("PROPERTY") == string::npos)
					object->GetHaveObject().left = target;

				if (target->Position() == object->Position() + Vector2(48.0f, 0))
					object->GetHaveObject().right = target;

				if (target->Position() == object->Position() + Vector2(0, 48.0f) && target->tag.find("PROPERTY") == string::npos)
					object->GetHaveObject().top = target;

				if (target->Position() == object->Position() - Vector2(0, 48.0f))
					object->GetHaveObject().bottom = target;
			}
		}
		object->RemoveHaveObject();

		
	}

}

void BabaScene::SetPropertyObject(void* object)
{
	string tag = object->GetHaveObject().top->tag.substr(0, object->GetHaveObject().top->tag.find('_'));
	ActionType property = (ActionType)object->GetHeightProperty();

	for (Object* target : objects)
	{
		if (target->tag.find(tag) != string::npos)
		{
			if (find(propertyObject[property].begin(), propertyObject[property].end(), target) == propertyObject[property].end())
			{
				propertyObject[(ActionType)object->GetHeightProperty()].push_back(target);
				SetAction(target, property);
			}
		}
	}
}
