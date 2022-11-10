#include "Framework.h"
#include "BabaScene.h"

BabaScene::BabaScene()
{
	SetSound();
	BabaGameManager::Get()->CallLoad() = false;
	backGround = new Quad(L"Textures/BackGround.png");
	backGround->Position() = { CENTER_X,CENTER_Y };
	backGround->UpdateWorld();

	EventManager::Get();
	EventManager::Get()->Add("SetPropertyHeight", bind(&BabaScene::SetHeightPropertyObject, this, placeholders::_1));
	EventManager::Get()->Add("SetPropertyWidth", bind(&BabaScene::SetWidthPropertyObject, this, placeholders::_1));
	EventManager::Get()->Add("RemoveHeightPropertyObject", bind(&BabaScene::RemoveHeightPropertyObject, this, placeholders::_1));
	EventManager::Get()->Add("RemoveWidthPropertyObject", bind(&BabaScene::RemoveWidthPropertyObject, this, placeholders::_1));
	EventManager::Get()->AddEvent("CheckIs", bind(&BabaScene::CheckIs, this));


	Load(BabaGameManager::Get()->Stage());
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

	if (BabaGameManager::Get()->IsLobby())	
		return;

	tileMap->Update();
	BabaMapManager::Get()->Update();

	if (BabaMapManager::Get()->IsClear())
	{
		BabaMapManager::Get()->IsClear() = false;
		BabaGameManager::Get()->Stage()++;
		Load(BabaGameManager::Get()->Stage());
	}

	if (KEY_DOWN('Q'))
	{
		GetBackObject::Get()->GetBack();
	}
	if (KEY_DOWN('E'))
	{
		Load(BabaGameManager::Get()->Stage());
	}
}

void BabaScene::Render()
{
	backGround->Render();
	tileMap->Render();
}

void BabaScene::PostRender()
{
}

void BabaScene::Load(int curstage)
{
	if (BabaGameManager::Get()->Stage() < 6)
		Audio::Get()->Play("BGM", 0.5f);
	else
		Audio::Get()->Play("GameClear", 0.5f);
	GetBackObject::Get()->ClearData();

	string path = "TextData/Stage" + to_string(curstage);
	path += ".map";
	SetLoad();
	tileMap->Load(path);
	tileMap->SetColliderOff();
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
			IsObject* temp = (IsObject*)object;
			temp->SetHaveObject();
			propertyIs.push_back(temp);

		}
		else if (object->tag.find("PROPERTY") != string::npos)
		{
			SetAction(object, ActionType::PUSH);
			propertys.push_back(object);
		}
		else
			objectImgs[object->tag.substr(0,object->tag.find('_'))].push_back(object);
	}

	EventManager::Get()->PlayEvent("CheckIs");
}

void BabaScene::SetLoad()
{
	if (tileMap != nullptr)
	{
		delete tileMap;
	}
	tileMap = new BabaTileMap(0, 0);

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
		object->effect = "DEFEAT";
		object->SetAction(new Defeat((Transform*)object));
		break;
	case BabaScene::ActionType::PUSH:
		object->effect = "PUSH";
		break;
	case BabaScene::ActionType::HOT:
		if(object->effect != "PUSH")
			object->effect = "HOT";
		object->SetAction(new Hot((Transform*)object,object->tag));
		break;
	case BabaScene::ActionType::MELT:
		object->effect = "MELT";
		break;
	case BabaScene::ActionType::SINK:
		object->effect = "SINK";
		object->SetAction(new Sink((Transform*)object,object->tag));
		break;
	case BabaScene::ActionType::WIN:
		object->effect = "WIN";
		object->SetAction(new Win((Transform*)object));
		break;
	case BabaScene::ActionType::YOU:
		break;
	default:
		break;
	}
	
}

void BabaScene::ChangeImg(Object* object, Object* changeObject)
{
	tileMap->GetInstanceQuads()[changeObject->tag]->AddPushDatas(changeObject);
	tileMap->GetInstanceQuads()[object->tag]->DeleteObject(object);
}

//Is타일 가로 세로의 정보를 갱신하는 함수
void BabaScene::CheckIs()
{
	for (IsObject*& object : propertyIs)
	{
		for (Object*& target : objects)
		{
			if ((target->tag.find("NAME") != string::npos || target->tag.find("PROPERTY") != string::npos )
				&& target->tag.find("IS") == string::npos)
			{
				if (target->Position() == object->Position() - Vector2(48.0f, 0) && target->tag.find("PROPERTY") == string::npos)
				{
					if (object->GetHaveObject().left != target)
						object->RemoveHaveObject();
					object->GetHaveObject().left = target;
				}

				if (target->Position() == object->Position() + Vector2(48.0f, 0))
				{
					if (object->GetHaveObject().right != target)
						object->RemoveHaveObject();
					object->GetHaveObject().right = target;
				}

				if (target->Position() == object->Position() + Vector2(0, 48.0f) && target->tag.find("PROPERTY") == string::npos)
				{
					if (object->GetHaveObject().top != target)
						object->RemoveHaveObject();
					object->GetHaveObject().top = target;
				}

				if (target->Position() == object->Position() - Vector2(0, 48.0f))
				{
					if (object->GetHaveObject().bottom != target)
						object->RemoveHaveObject();
					object->GetHaveObject().bottom = target;
				}
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
		if (object->effect == "HOT")
			SetAction(object, property);

		/*if (temp->GetHaveObject().right->tag.find("NAME") != string::npos)
		{
			ChangeImg(object, temp);
		}*/
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
		if (object->effect == "HOT")
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

void BabaScene::SetSound()
{
	Audio::Get()->Add("BGM", "Sounds/BGM.OGG", true, true);
	Audio::Get()->Add("Broken", "Sounds/Broken.OGG");
	Audio::Get()->Add("Clear", "Sounds/Clear.OGG");
	Audio::Get()->Add("Lobby", "Sounds/map.OGG");
	Audio::Get()->Add("Move", "Sounds/Move.OGG");
	Audio::Get()->Add("GameClear", "Sounds/stars.OGG");

}
