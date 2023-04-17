#include "Texture.h"
#include "../Core/PathManager.h"

CTexture::CTexture()
{
}

CTexture::~CTexture()
{
	SelectObject(m_hMemDC, m_hOldBitMap);
	DeleteObject(m_hBitMap);
	DeleteDC(m_hMemDC);
}

bool CTexture::LoadTexture(HINSTANCE hInst, HDC hDC, const wchar_t* pFileName, const string& strPathKey)
{
	// 메모리 DC를 만들어준다.
	m_hMemDC = CreateCompatibleDC(hDC);

	const wchar_t* pPath = GET_SINGLE(CPathManager)->FindPath(strPathKey);

	wstring strPath;
	if (pPath)
		strPath = pPath;
	strPath += pFileName;

	m_hBitMap = (HBITMAP)LoadImage(hInst, strPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_hOldBitMap = (HBITMAP)SelectObject(m_hMemDC, m_hBitMap);

	GetObject(m_hBitMap, sizeof(m_tInfo), &m_tInfo);
	return true;
}
