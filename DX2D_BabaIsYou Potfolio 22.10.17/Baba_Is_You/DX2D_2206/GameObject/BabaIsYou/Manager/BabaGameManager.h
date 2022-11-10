#pragma once

class BabaGameManager : public Singleton<BabaGameManager>
{
public:
	BabaGameManager();
	~BabaGameManager();
	bool& CallLoad() { return callLoad; }
	bool& IsLobby() { return isLobby; }
	bool& FadeEnd() { return fadeEnd; }
	int& Stage() { return stage; }

private:
	bool callLoad = false;
	int stage = 0;
	bool isLobby = true;
	bool fadeEnd = false;
};