#pragma once
#include "MoveObj.h"

class CBullet :
	public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;
private:
	CBullet();
	CBullet(const CBullet& bullet);
	~CBullet();
private:
	float m_fDist;
	float m_fLimitDist;
public:
	void SetBulletDisatance(float fDist)
	{
		m_fLimitDist = fDist;
	}
public:
	virtual bool Init();
	virtual int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CBullet* Clone();
};

