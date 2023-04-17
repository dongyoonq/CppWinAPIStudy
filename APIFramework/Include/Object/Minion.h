#pragma once
#include "MoveObj.h"
#include "../Core.h"

class CMinion :
	public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;
private:
	MOVE_DIR m_eDir;
	float m_fFireTime;
	float m_fFireLimitTime;
private:
	CMinion();
	CMinion(const CMinion& minion);
	~CMinion();
private:
	void Fire();
public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMinion* Clone();
};

