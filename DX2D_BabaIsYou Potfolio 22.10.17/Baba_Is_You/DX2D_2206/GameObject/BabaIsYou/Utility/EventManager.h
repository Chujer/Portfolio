#pragma once

class EventManager : public Singleton<EventManager>
{
public:
	EventManager();
	~EventManager();

	void Add(string key, function<void()> event) { events[key] = event; }
	void Add(string key, function<void(void*)> event) { objEvents[key] = event; }

	void PlayEvent(string key) { events[key]; }
	void PlayObjEvent(string key) { objEvents[key]; }

private:
	map<string, function<void()>> events;
	map < string, function<void(void*)>> objEvents;
};