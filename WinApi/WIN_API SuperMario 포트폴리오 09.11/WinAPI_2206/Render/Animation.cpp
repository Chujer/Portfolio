#include "Framework.h"

Animation::Animation(POINT imageFrame, float frameUpdateTime)
    : imageFrame(imageFrame), frameUpdateTime(frameUpdateTime)
{
    for (int y = 0; y < imageFrame.y; y++)
    {
        for (int x = 0; x < imageFrame.x; x++)
        {
            frames.push_back({ x, y });
        }
    }
}

Animation::~Animation()
{
}

void Animation::Update()
{
    if (!isPlay) return;

    time += DELTA;

    if (time >= frameUpdateTime)
    {
        time -= frameUpdateTime;

        curPlayNum++;

        if (curPlayNum > action.size() - 1)
        {
            if (isLoop)
                curPlayNum = 0;
            else
            {
                curPlayNum--;
                Stop();
            }
        }
    }
}

void Animation::SetDefault(bool loop, bool pingpong)
{
    isLoop = loop;
    
    action.clear();

    for (int i = 0; i < frames.size(); i++)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetArray(int * arr, int arrSize, bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (int i = 0; i < arrSize; i++)
        action.push_back(arr[i]);

    if (pingpong)
        SetPingpong();
}

void Animation::SetPart(int start, int end, bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (int i = start; i <= end; i++)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetReversePart(int start, int end, bool loop, bool pingpong)
{
    isLoop = loop;

    action.clear();

    for (int i = end; i >= start; i--)
        action.push_back(i);

    if (pingpong)
        SetPingpong();
}

void Animation::SetPingpong()
{
    for (int i = action.size() - 2; i >= 0; i--)
        action.push_back(action[i]);
}

void Animation::Stop()
{
    isPlay = false;

    if (EndEvent != nullptr)
        EndEvent();
}
