#pragma once

class BabaGameManager : public Singleton<BabaGameManager>
{
public:
	BabaGameManager();
	~BabaGameManager();
	bool& CallLoad() { return callLoad; }

private:
	bool callLoad = false;
};