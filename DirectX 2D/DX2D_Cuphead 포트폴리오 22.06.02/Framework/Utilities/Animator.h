#pragma once

class AnimationClip
{
public:
	friend class Animator;

	AnimationClip(wstring clipName, Texture2D* srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bReversed = false);
	void SetAnimationSpeed(float playRate) { this->playRate = playRate; }

private:
	wstring clipName = L"";
	vector<Vector2> keyFrames;
	UINT frameCount = 0;
	ID3D11ShaderResourceView* srv = nullptr;
	Vector2 texelFrameSize = Value::ZeroVec2;
	float playRate = 0.0f;
	bool bReversed = false;
};

class Animator
{
public:
	Animator();
	~Animator();

	void Update();
	bool GetEndAni(wstring path)
	{ 
		if (path == GetClipName())
		{
			if (endAni == true)
			{
				endAni = false;
				return true;
			}
			else
			{
				return false;
			}
		}
		else
			return false;
	}

	void SetCurrentFrameIndex(int index) { currentFrameIndex = index; }

	bool GetFrameAni(wstring path, int Frame)
	{
		if (path == GetClipName() && currentFrameIndex == Frame && returnFrameReady == true)
		{
			returnFrameReady = false;
			return true;
		}
		else
			return false;
	}

	void SetAnimationSpeed(wstring aniName, float playRate);

	Vector2 GetCurrentFrame() { return currentFrame; }
	Vector2 GetTexelFrameSize() { return currentClip->texelFrameSize; }
	ID3D11ShaderResourceView* GetCurrentSRV() { return currentClip->srv; }
	wstring GetClipName() 
	{
		if (currentClip == nullptr)
			return (wstring)L"asd";
		return currentClip->clipName; 
	}


	void AddAnimClips(vector<AnimationClip*> clips);
	void AddAnimClips(AnimationClip* clips);
	void SetCurrentAnimClip(wstring clipName, bool oneAnim = false );
private:
	unordered_map<wstring, AnimationClip*> animClips;
	bool CheckExist(wstring clipName) { return animClips.find(clipName) != animClips.end(); }

	AnimationClip* currentClip = nullptr;
	UINT currentFrameIndex = 0;
	Vector2 currentFrame = Value::ZeroVec2;
	
	float deltaTime = 0.0f;
	bool endAni = false;
	bool returnFrameReady = true;
};