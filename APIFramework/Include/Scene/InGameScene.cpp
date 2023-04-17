#include "InGameScene.h"
#include "../Object/Player.h"
#include "../Object/Minion.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
#include "Layer.h" 
#include "../Core/Camera.h"

CInGameScene::CInGameScene()
{

}
CInGameScene::~CInGameScene()
{

}

bool CInGameScene::Init()
{
	// �θ��� Scene Ŭ������ �ʱ�ȭ �Լ��� ȣ�����ش�.
	if (!CScene::Init())
		return false;
	CLayer* pLayer = FindLayer("Default");
	CMinion* pMinion = CObj::CreateObj<CMinion>("Minion", pLayer);
	CPlayer* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);

	GET_SINGLE(CCamera)->SetTarget(pPlayer);

	SAFE_RELEASE(pPlayer);
	SAFE_RELEASE(pMinion);
	// �Ѿ��� ������ Ÿ���� ������ش�.
	CBullet* pBullet = CScene::CreatePrototype<CBullet>("Bullet");
	
	SAFE_RELEASE(pBullet);

	CLayer* pStageLayer = FindLayer("Stage");

	CStage* pStage = CObj::CreateObj<CStage>("Stage", pStageLayer);
	SAFE_RELEASE(pStage);
	return true;
}
