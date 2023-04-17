#include "Texture.h"
#include "../Core/PathManager.h"

CTexture::CTexture() :
	m_hMemDC(NULL),
	m_bColorKeyEnable(false),
	m_ColorKey(RGB(255, 0, 255))
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

void CTexture::SetColorKey(unsigned char r, unsigned char g, unsigned char b)
{
	m_ColorKey = RGB(r, g, b);
	m_bColorKeyEnable = true;
}

void CTexture::SetColorKey(COLORREF colorKey)
{
	m_ColorKey = colorKey;
	m_bColorKeyEnable = true;
}

