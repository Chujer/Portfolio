#pragma once

class Item : public ImageRect
{
public:
	Item();
	~Item();
	void Update();
	virtual void Render(HDC hdc);

	bool GetArrivalDestination() { return arrivalDestination; }

	virtual void Move() {};
	virtual void SetItemTexture();

	float& Speed() { return speed; }

	void SetEvent(function<void()> Event) { this->Event = Event; }
	void StartEvent() 
	{
		if (Event == nullptr) return;
		Event();
	}
	virtual void IsOnTheGround(Vector2 Ground);

	void CreateItem(Vector2 pos, Vector2 destination);
	void SetSize()
	{
		size = texture->GetSize() * 3.0f;
		camRect->Size() = size;
	}
	virtual void StartSound() {};

protected:
	float speed = 200.0f;
	Vector2 destination;

	bool arrivalDestination = false;
	float gravity = 0;

	function<void()> Event = nullptr;
};