#pragma once
#include "../Core/Ref.h"

class CTexture :
    public CRef
{
private:
    friend class CResourceManager;
private:
    HDC m_hMemDC;
    HBITMAP m_hBitMap;
    HBITMAP m_hOldBitMap;
    BITMAP m_tInfo;
private:
    CTexture();
    ~CTexture();
public:
    bool LoadTexture(HINSTANCE hInst, HDC hDC,
        const wchar_t* pFileName, const string& strPathKey = TEXTURE_PATH);
    HDC GetDC() const
    {
        return m_hMemDC;
    }
};

