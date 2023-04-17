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
    COLORREF m_ColorKey;
    bool     m_bColorKeyEnable;
public :
    void SetColorKey(unsigned char r, unsigned char g,
        unsigned char b);
    void SetColorKey(COLORREF colorKey);
    COLORREF GetColorKey() const { return m_ColorKey; }
    bool GetColorKeyEnable() const { return m_bColorKeyEnable; }

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
