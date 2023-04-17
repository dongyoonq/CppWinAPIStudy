#pragma once
#include "../Game.h"
class CTimer
{
	DECLARE_SINGLE(CTimer);
private:
	LARGE_INTEGER m_tSecond;
	LARGE_INTEGER m_tTime;
	float m_fDeltaTime;
	float m_fTimeScale;
	float m_fFPS;
	float m_fFPSTime;
	int m_iFrameMax;
	int m_iFrame;
public:
	float GetDeltaTime() const;
	float GetFPS() const;
	float GetTimmeScale() const;
public:
	bool Init();
	void Update();
public:
	void SetTimeScale(float fTimeScale);
};

