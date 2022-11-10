#pragma once

class MarioGameManager : public Singleton<MarioGameManager>
{
public:
	MarioGameManager();
	~MarioGameManager();

	void SetStageInfo(int life, int score, int stageNum);

	int& PlayerLife() { return life; }
	int& StageNum() { return stageNum; }
	bool& PlayGame() { return playGame; }
	int& Score() { return score; }
	int& GameTime() { return gameTime; }
	int& Coin() { return coin; }
	int GetStageTime() { return stageTime[stageNum]; }

	void ClearStage();
	void ChangeScene(string sceneName);

	void SetStage();
	void RemoveStage();

	void SetStartStage(function<void(void*)> Event) { StartScene = Event; }
	void SetEndStage(function<void()> Event) { EndStage = Event; }

	void StageClear();

	void Update();
private:
	map<int, int> stageTime;
	float time = 0;
	int gameTime;
	
	int life = 3;
	int score;
	string stage;
	int stageNum;
	int coin;

	bool playGame = false;
	bool UIScene = false;

	function<void(void*)> StartScene;
	function<void()> EndStage;
};