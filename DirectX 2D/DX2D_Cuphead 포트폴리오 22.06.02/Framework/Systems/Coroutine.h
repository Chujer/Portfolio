#pragma once
class Coroutine : public SingletonBase<Graphics>
{
public:
	friend class SingletonBase<Coroutine>;

	template<typename T>
	void PlayCoroutin(float delayTime, T(*fp));
	void Update();

private:
	bool onCoroutine = false;
	float coroutineTime = 0.0f;
};

template<typename T>
inline void Coroutine::PlayCoroutin(float delayTime, T(*fp))
{
	if (coroutineTime >= delayTime)
	{
		T(*fp);
		onCoroutine = false;
		coroutineTime = 0.0f;
	}
}
