/////////////////////////////////////////////////////////////////////////
// TimerClass.h
/////////////////////////////////////////////////////////////////////////
#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class TimerClass
{
public:
	TimerClass(void);
	TimerClass(TimerClass& other);
	~TimerClass(void);

public:
	bool Initialize();
	void Update();
	float GetDeltaTimer();

private:
	__int64 m_prevFrame;
	__int64 m_currentFrame;
	__int64 m_frequency;
	__int64 m_deltaTime;
};