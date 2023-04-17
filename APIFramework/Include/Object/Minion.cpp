#include "Minion.h"

CMinion::CMinion() :
	m_fFireTime(0.f),
	m_fFireLimitTime(1.1586f)
{
}

CMinion::CMinion(const CMinion& minion) :
	CMoveObj(minion)
{
	m_eDir = minion.m_eDir;
	m_fFireTime = minion.m_fFireTime;
	m_fFireLimitTime = minion.m_fFireLimitTime;
}

CMinion::~CMinion()
{
}
 


bool CMinion::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(280.f);
	SetPivot(0.5f, 0.5f);

	SetTexture("Minion", L"Minion.bmp");

	m_eDir = MD_FRONT;
	return true;
}

int CMinion::Update(float fDeltaTime)
{
	MoveYFromSpeed(fDeltaTime, m_eDir);
	if (m_tPos.y + m_tSize.y >= GET_SINGLE(CCore)->GetResolution().iH) {
		m_tPos.y = GET_SINGLE(CCore)->GetResolution().iH - m_tSize.y;
		m_eDir = MD_BACK;
	}
	else if (m_tPos.y <= 0)
	{
		m_tPos.y = 0;
		m_eDir = MD_FRONT;
	}
	
	m_fFireTime += fDeltaTime;
	if (m_fFireTime >= m_fFireLimitTime)
	{
		m_fFireTime -= m_fFireLimitTime;
		Fire();
	}
	CMoveObj::Update(fDeltaTime);
	return 0;
}

int CMinion::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);
	return 0;
}

void CMinion::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMinion::Render(HDC hDC, float fDeltaTime)
{
	//Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
	CMoveObj::Render(hDC, fDeltaTime);
}

CMinion* CMinion::Clone()
{
	return new CMinion(*this);
}

void CMinion::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj("Bullet", "MinionBullet", m_pLayer);
	((CMoveObj*)pBullet)->SetAngle(PI);
	
	float x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
	float y = GetCenter().y;

	pBullet->SetPos(x, y);
	
	SAFE_RELEASE(pBullet);}