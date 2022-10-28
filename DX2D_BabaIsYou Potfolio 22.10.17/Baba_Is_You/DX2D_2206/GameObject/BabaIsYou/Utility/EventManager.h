#pragma once

class EventManager : public Singleton<EventManager>
{
public:
	EventManager();
	~EventManager();

	void Adda(string key, function<void()> event) { nomalEvents[key] = event; }
	void Add(string key, function<void(void*)> event) { objEvents[key] = event; }

	//void PlayEvent(string key) { events[key]; }
	void PlayObjEvent(string key,void* obj) { objEvents[key](obj); }

private:
	map<string, function<void()>> nomalEvents;
	map <string, function<void(void*)>> objEvents;
};