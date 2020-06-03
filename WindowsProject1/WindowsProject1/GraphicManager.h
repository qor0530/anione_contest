#pragma once
#include <wincodec.h>
#include <dwrite.h>
#include "GameObject.h"
class GameObject;
class GraphicManager
{
private:
	static ID2D1Factory* pD2DFactory;
	static ID2D1HwndRenderTarget* pRT;
	static IWICImagingFactory* m_pWICFactory;
	static IWICBitmapDecoder *pDecoder;
	static IWICBitmapFrameDecode *pSource;
	static IWICStream *pStream;
	static IWICFormatConverter *pConverter;
	static IWICBitmapScaler *pScaler;
	static ID2D1RenderTarget *pRenderTarget;
	static ID2D1Bitmap *pBitmap;
	static ID2D1BitmapBrush *m_pBitmapBrush;
	static IDWriteFactory* pDWriteFactory_;
	static IDWriteTextFormat* pTextFormat_;
	static ID2D1SolidColorBrush* pBlackBrush_;
	static D2D1_RECT_F layoutRect;
public:

	
	static void Init(HWND hwnd);
	static void SetFontFormat(LPCWSTR fontname, float fontsize, int alignment);
	static void Load_Bitmap(GameObject * obj, LPCWSTR filename);
	static void Render(GameObject * obj);
	static void TextRender(LPCWSTR text, float x, float y);
	static void Release();
	static void BeginDraw();
	static void EndDraw();
};

