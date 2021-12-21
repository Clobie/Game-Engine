/////////////////////////////////////////////////////////////////////////
// TimerClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "TimerClass.h"

TimerClass::TimerClass(void)
{
	m_prevFrame = 0;
	m_currentFrame = 0;
	m_frequency = 0;
	m_deltaTime = 0;
}

TimerClass::TimerClass(TimerClass& other)
{

}

TimerClass::~TimerClass(void)
{

}

bool TimerClass::Initialize()
{
	m_deltaTime = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentFrame);
	m_prevFrame = m_currentFrame;
	return true;
}

void TimerClass::Update()
{
	//QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentFrame);
	int deltaTicks = (int)(m_currentFrame - m_prevFrame);
	m_deltaTime = (__int64)((float)deltaTicks/(float)m_frequency);
	m_prevFrame = m_currentFrame;
}

float TimerClass::GetDeltaTimer()
{
	float dt = (float)m_deltaTime;
	if(dt <= 0.0f || dt > 1.0f)
	{
		dt = 0.025f;
	}
	
	return dt;
}