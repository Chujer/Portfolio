#pragma once

class MarioEventManager : public Singleton<MarioEventManager>
{
public:
	MarioEventManager();
	~MarioEventManager();

	void AddEvent(string key, function<void()> Event);
	function<void()> GetEvent(string key) { return Events[key]; }

private:
	map<string, function<void()>> Events;
};