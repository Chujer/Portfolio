#include "Framework.h"
#include "Animator.h"

using namespace std;

AnimationClip::AnimationClip(wstring clipName, Texture2D * srcTex, UINT frameCount, Vector2 startPos, Vector2 endPos, float playRate, bool bReversed)
	:clipName(clipName), frameCount(frameCount), playRate(playRate), bReversed(bReversed)
{
	srv = srcTex->GetSRV();

	float imageWidth = srcTex->GetWidth();
	float imageHeight = srcTex->GetHeight();

	Vector2 clipSize = endPos - startPos;
	Vector2 frameSize;
	frameSize.x = clipSize.x / frameCount; // 순차재생
	frameSize.y = clipSize.y;

	texelFrameSize.x = frameSize.x / imageWidth;
	texelFrameSize.y = frameSize.y / imageHeight;

	Vector2 texelStartPos;
	texelStartPos.x = startPos.x / imageWidth;
	texelStartPos.y = startPos.y / imageHeight;

	Vector2 keyframe;

	for (UINT i = 0; i < frameCount; i++)
	{
		keyframe.x = texelStartPos.x + (texelFrameSize.x * i);
		keyframe.y = texelStartPos.y;
		keyFrames.push_back(keyframe);
	}
}

Animator::Animator()
{
}

Animator::~Animator()
{
	for (auto clip : animClips)
	{
		SAFE_DELETE(clip.second);
	}
}

void Animator::Update()
{
	if (deltaTime > currentClip->playRate)
	{
		if (currentClip->bReversed == false)
		{
			currentFrameIndex++;
			if (currentFrameIndex == currentClip->frameCount-1)
			{
				endAni = true;
				returnFrameReady = true;
			}
			if (currentFrameIndex == currentClip->frameCount)
			{
				currentFrameIndex = 0;
			}

			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		else
		{
			currentFrameIndex--;
			if (currentFrameIndex == 0)
			{
				endAni = true;
				returnFrameReady = true;
			}
			if (currentFrameIndex == -1)
			{
				currentFrameIndex = currentClip->frameCount - 1;
			}
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
		deltaTime = 0.0f;
	}
	else
	{
		deltaTime += Time::Delta();
	}
}

void Animator::SetAnimationSpeed(wstring aniName, float playRate)
{
	animClips.find(aniName)->second->SetAnimationSpeed(playRate);
}

void Animator::AddAnimClips(vector<AnimationClip*> clips)
{
	for (AnimationClip* c : clips)
	{
		animClips.insert(make_pair(c->clipName, c));
	}
	
}

void Animator::AddAnimClips(AnimationClip* clips)
{
	animClips.insert(make_pair(clips->clipName, clips));
}

void Animator::SetCurrentAnimClip(wstring clipName, bool oneAnim)
{
	endAni = false;
	/*if (oneAnim == true)
	{
		if (currentClip == nullptr && CheckExist(clipName) == true)
		{
			currentClip = animClips.find(clipName)->second;
		}
		else if (currentClip != nullptr && currentClip->clipName == clipName)
		{
			return;
		}

		if (CheckExist(clipName))
		{
			currentClip = animClips.find(clipName)->second;
			deltaTime = 0.0f;

			if (currentClip->bReversed == true)
			{
				currentFrameIndex = currentClip->frameCount - 1;
			}
			else
			{
				currentFrameIndex = 0;
			}
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
	}*/
	if (clipName != GetClipName())
	{
		if(currentClip!=nullptr)
			std::wcout << GetClipName() << endl;

		if (currentClip == nullptr && CheckExist(clipName) == true)
		{
			currentClip = animClips.find(clipName)->second;
		}
		else if (currentClip != nullptr && currentClip->clipName == clipName)
		{
			return;
		}

		if (CheckExist(clipName))
		{
			currentClip = animClips.find(clipName)->second;
			deltaTime = 0.0f;

			if (currentClip->bReversed == true)
			{
				currentFrameIndex = currentClip->frameCount - 1;
			}
			else
			{
				currentFrameIndex = 0;
			}
			currentFrame = currentClip->keyFrames[currentFrameIndex];
		}
	}
}