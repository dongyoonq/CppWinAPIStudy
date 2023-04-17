#pragma once
#include "../Game.h"

class CScene
{
private:
	static unordered_map<string, class CObj*> m_mapPrototype;
protected:
	friend class CSceneManager;
protected:
	CScene();
	virtual ~CScene() = 0;
protected:
	list<class CLayer*> m_LayerList;
public:
	static void ErasePrototype();
	static void ErasePrototype(const string& strTag);
	static CObj* FindPrototype(const string& strTag);
public:
	template <typename T>
	static T* CreatePrototype(const string& strTag)
	{
		T* pObj = new T;
		pObj->SetTag(strTag);
		if (!pObj->Init())
		{
			SAFE_RELEASE(pObj);
			return NULL;
		}
		pObj->AddRef();
		m_mapPrototype.insert(make_pair(strTag, pObj));
		return pObj;
	}
public:
	class CLayer* CreateLayer(const string& strTag,
		int iZOrder = 0);
	class CLayer* FindLayer(const string& strTag);
public:
	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual	int Update(float fDeltaTime);
	virtual int LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
public:
	static bool LayerSort(class CLayer* pL1, class CLayer* pL2);
};