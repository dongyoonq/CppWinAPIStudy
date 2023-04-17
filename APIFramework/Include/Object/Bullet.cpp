#include "Bullet.h"
#include "../Resource/Texture.h"

CBullet::CBullet() :
	m_fDist(0.f),
	m_fLimitDist(500.f)
{
}

CBullet::CBullet(const CBullet& bullet) :
	CMoveObj(bullet)
{
	m_fDist = bullet.m_fDist;
	m_fLimitDist = bullet.m_fLimitDist;
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
	SetSize(50.f, 50.f);
	SetSpeed(500.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Bullet", L"Bullet.bmp");

	m_pTexture->SetColorKey(255, 255, 255);

	return true;
}

int CBullet::Update(float fDeltaTime)
{
	MoveAngle(fDeltaTime);
	m_fDist += GetSpeed() * fDeltaTime;
	if (m_fDist >= m_fLimitDist) {
		Die();
		//m_tPos = POSITION(0.f, 0.f);
	}
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CBullet::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CBullet::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CBullet::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);
}

CBullet* CBullet::Clone()
{
	return new CBullet(*this);
}
