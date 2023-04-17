#include "Player.h"
#include "../Core/Input.h"

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& player) :
    CMoveObj(player)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    SetPos(50.f, 50.f);
    SetSize(100.f, 100.f);
    SetPivot(0.5f, 0.5f);
    SetSpeed(400.f);

    SetTexture("Player", L"SpongeBob.bmp");
    return true;
}

void CPlayer::Input(float fDeltaTime)
{
    if (KEYPRESS("MoveLeft"))
    {
        MoveXFromSpeed(fDeltaTime, MD_BACK);
    }
    if (KEYPRESS("MoveRight"))
    {
        MoveXFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (KEYPRESS("MoveFront"))
    {
        MoveYFromSpeed(fDeltaTime, MD_BACK);
    }
    if (KEYPRESS("MoveBack"))
    {
        MoveYFromSpeed(fDeltaTime, MD_FRONT);
    }
    if (KEYDOWN("Fire"))
    {
        Fire();
    }
    if (KEYDOWN("Skill1"))
    {
        MessageBox(NULL, L"Skill1", L"Skill1", MB_OK);
    }
    
    CMoveObj::Input(fDeltaTime);
    
}

int CPlayer::Update(float fDeltaTime)
{
    CMoveObj::Update(fDeltaTime);
    return 0;
}

int CPlayer::LateUpdate(float fDeltaTime)
{
    CMoveObj::LateUpdate(fDeltaTime);
    return 0;
}

void CPlayer::Collision(float fDeltaTime)
{
    CMoveObj::Collision(fDeltaTime);
}

void CPlayer::Render(HDC hDC, float fDeltaTime)
{

    //Rectangle(hDC, m_tPos.x, m_tPos.y, m_tPos.x + m_tSize.x, m_tPos.y + m_tSize.y);
    CMoveObj::Render(hDC, fDeltaTime);
}

CPlayer* CPlayer::Clone()
{
    return new CPlayer(*this);
}

void CPlayer::Fire()
{
    CObj* pBullet = CObj::CreateCloneObj("Bullet", "PlayerBullet", m_pLayer);

    //GET_SINGLE(CCamera)->SetTarget(pBullet);
    // 오른쪽 가운데를 구한다.
    POSITION tPos;
    tPos.x = GetRight() + pBullet->GetSize().x * pBullet->GetPivot().x;
    tPos.y = GetCenter().y;

    pBullet->SetPos(tPos);
    SAFE_RELEASE(pBullet);
}