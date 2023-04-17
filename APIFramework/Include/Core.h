#pragma once

#include "Game.h"

class CCore
{
	DECLARE_SINGLE(CCore);
private:
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HDC m_hDC;
	RESOLUTION m_tRS;
	static bool m_bLoop;
private:
	ATOM MyRegisterClass();
	BOOL Create();
public:
	RESOLUTION GetResolution() const
	{
		return m_tRS;
	}
public:
	bool Init(HINSTANCE hInst);
	int Run();
private:
	void Logic();
	void Input(float fDeltaTime);
	int Update(float fDeltaTime);
	int LateUpdate(float fDeltaTime);
	void Collision(float fDeltaTime);
	void Render(float fDeltaTime);
public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

