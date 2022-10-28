#include "Framework.h"
#include "BabaScene.h"

BabaScene::BabaScene()
{
	backGround = new Quad(L"Textures/BackGround.png");
	backGround->Position() = { CENTER_X,CENTER_Y };
	backGround->UpdateWorld();

	EventManager::Get();
	//EventManager  관련
	// EventManager를 이용해 propertys변수안의 값을 추가 제거할수 있도록 사용 사용처(IsObject클래스)
	EventManager::Get()->Add("SetPropertyHeight", bind(&BabaScene::SetHeightPropertyObject, this, placeholders::_1));
	EventManager::Get()->Add("SetPropertyWidth", bind(&BabaScene::SetWidthPropertyObject, this, placeholders::_1));
	EventManager::Get()->Add("RemoveHeightPropertyObject", bind(&BabaScene::RemoveHeightPropertyObject, this, placeholders::_1));
	EventManager::Get()->Add("RemoveWidthPropertyObject", bind(&BabaScene::RemoveWidthPropertyObject, this, placeholders::_1));
	EventManager::Get()->Adda("Check", bind(&BabaScene::CheckIs, this));


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

	if (KEY_DOWN(VK_SPACE))
	{
		objectNames.front()->SetActive(false);
	}
	if (KEY_DOWN('W'))
	{
		objectNames.front()->SetActive(true);
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
	BabaMapManager::Get()->SetMapData(tileMap);

	objectNames.clear();
	propertyIs.clear();
	propertys.clear();
	objectImgs.clear();

	//각 역할에 해당하는 Object에 담아 개별적으로 사용
	for (Object* object : objects)
	{
		if (object->tag.find("NAME") != string::npos)
		{
			SetAction(object, ActionType::PUSH);
			objectNames.push_back(object);
		}
		else if (object->tag.find("IS") != string::npos)
		{
			SetAction(object, ActionType::PUSH);
			propertyIs.push_back((IsObject*)object);
		}
		else if (object->tag.find("PROPERTY") != string::npos)
		{
			SetAction(object, ActionType::PUSH);
			propertys.push_back(object);
		}
		else
			objectImgs[object->tag.substr(0,object->tag.find('_'))].push_back(object);
	}

}

//실질적 기능을하는 Action클래스를 설정하는 함수
void BabaScene::SetAction(Object* object, ActionType action)
{
	switch (action)
	{
	case BabaScene::ActionType::NONE:
		if (object->GetAction() != nullptr)
		{
			delete object->GetAction();
			object->GetAction() = nullptr;
		}
		object->effect = "NONE";
		break;
	case BabaScene::ActionType::MOVE:
		if (object->tag.find("NAME") == string::npos)
		{
			if (object->tag.find("BABA") != string::npos)
			{
				object->SetAction(new Move((Transform*)object, &object->GetInstanceData().curFrame));
				object->effect = "MOVE";
				return;
			}
			object->SetAction(new Move((Transform*)object));
			object->effect = "MOVE";
		}
		break;
	case BabaScene::ActionType::STOP:
		object->effect = "STOP";
		break;
	case BabaScene::ActionType::DEFEAT:
		break;
	case BabaScene::ActionType::HOT:
		break;
	case BabaScene::ActionType::MELT:
		break;
	case BabaScene::ActionType::PUSH:
		object->effect = "PUSH";
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

//Is타일 가로 세로의 정보를 갱신하는 함수
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

//Check Is이후 설정된 기능의 Action을 설정하는 역할
void BabaScene::SetWidthPropertyObject(void* object)
{
	IsObject* temp = (IsObject*)object;

	if (temp->GetHaveObject().left == nullptr || temp->GetHaveObject().right == nullptr)
		return;

	string tag = temp->GetHaveObject().left->tag.substr(0, temp->GetHaveObject().left->tag.find('_'));
	ActionType property = (ActionType)temp->GetWidthProperty();

	for (Object* object : objectImgs[tag])
	{
		if (object->GetAction() == nullptr)
			SetAction(object, property);
	}
}

void BabaScene::SetHeightPropertyObject(void* object)
{
	IsObject* temp = (IsObject*)object;

	if (temp->GetHaveObject().top == nullptr || temp->GetHaveObject().bottom == nullptr)
		return;

	string tag = temp->GetHaveObject().top->tag.substr(0, temp->GetHaveObject().top->tag.find('_'));
	ActionType property = (ActionType)temp->GetHeightProperty();

	for (Object* object : objectImgs[tag])
	{
		if(object->GetAction() == nullptr)
			SetAction(object, property);
	}
}

void BabaScene::RemoveWidthPropertyObject(void* object)
{
	IsObject* temp = (IsObject*)object;

	if (temp->GetHaveObject().left == nullptr || temp->GetHaveObject().right == nullptr)
		return;

	string tag = temp->GetHaveObject().left->tag.substr(0, temp->GetHaveObject().left->tag.find('_'));
	ActionType property = (ActionType)temp->GetWidthProperty();

	for (Object* object : objectImgs[tag])
	{
		SetAction(object, ActionType::NONE);
	}
}

void BabaScene::RemoveHeightPropertyObject(void* object)
{
	IsObject* temp = (IsObject*)object;

	if (temp->GetHaveObject().top == nullptr || temp->GetHaveObject().bottom == nullptr)
		return;

	string tag = temp->GetHaveObject().top->tag.substr(0, temp->GetHaveObject().top->tag.find('_'));
	ActionType property = (ActionType)temp->GetWidthProperty();

	for (Object* object : objectImgs[tag])
	{
		SetAction(object, ActionType::NONE);
	}
}
