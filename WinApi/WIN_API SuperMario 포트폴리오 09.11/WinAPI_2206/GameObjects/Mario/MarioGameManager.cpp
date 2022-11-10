#include "Framework.h"
#include "MarioGameManager.h"

MarioGameManager::MarioGameManager()
{
	Audio::Get()->Add("stage1BGM", "Sounds/stage1.mp3", true, true);
	Audio::Get()->Add("stage2BGM", "Sounds/stage2.mp3", true, true);
	stageTime[1] = 400;
	stageTime[2] = 400;
	stageTime[3] = 400;
}

MarioGameManager::~MarioGameManager()
{
}

void MarioGameManager::SetStageInfo(int life, int score, int stageNum)
{
	this->life = life;
	this->score = score;
	this->stageNum = stageNum;
}

void MarioGameManager::ClearStage()
{

}

void MarioGameManager::ChangeScene(string sceneName)
{
	if (stageNum == 2)
	{
		Audio::Get()->Stop("stage1BGM");
	}
	else if (stageNum == 1)
	{
		Audio::Get()->Stop("stage2BGM");
	}
	if (life == 0)
	{
		stageNum = 1;
		life = 3;
		score = 0;
	}
	RemoveStage();
	SCENE->ChangeScene(sceneName);
}

void MarioGameManager::SetStage()
{
	StartScene((void*)stageNum);
	if (stageNum == 1)
	{
		Audio::Get()->Play("stage1BGM",0.2f);
	}
	else if (stageNum == 2)
	{
		Audio::Get()->Play("stage2BGM",0.2f);
	}
}

void MarioGameManager::RemoveStage()
{
	EndStage();
	time = 0;
}

void MarioGameManager::StageClear()
{
	if (stageNum == 1)
	{
		Audio::Get()->Add("stage1BGM", "Sounds/stage1.mp3", true, true);
		Audio::Get()->Play("stage1BGM", 0.2f);
	}
	else
	{
		Audio::Get()->Add("stage2BGM", "Sounds/stage2.mp3", true, true);
		Audio::Get()->Play("stage2BGM", 0.2f);
	}
	stageNum++;
	ChangeScene("UIScene");
}

void MarioGameManager::Update()
{
	if (playGame)
	{
		time += DELTA;
		gameTime = stageTime[stageNum] - time;
		if (gameTime < 1)
			playGame = false;
	}
}
