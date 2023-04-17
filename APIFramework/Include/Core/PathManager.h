#pragma once
#include "../Game.h"

class CPathManager
{
	DECLARE_SINGLE(CPathManager);
private:
	unordered_map<string, wstring> m_mapPath;

public:
	bool CreatePath(const string& strKey, const wchar_t* pPath,
		const string& strBaseKey = ROOT_PATH);
	bool Init();
	const wchar_t* FindPath(const string& strKey);
};

