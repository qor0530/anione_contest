#include "GraphicManager.h"
#include <d2d1.h>


ID2D1Factory* GraphicManager::pD2DFactory = NULL;
ID2D1HwndRenderTarget* GraphicManager::pRT = NULL;
IWICImagingFactory * GraphicManager::m_pWICFactory = NULL;
IWICBitmapDecoder *GraphicManager::pDecoder = NULL;
IWICBitmapFrameDecode *GraphicManager::pSource = NULL;
IWICStream *GraphicManager::pStream = NULL;
IWICFormatConverter *GraphicManager::pConverter = NULL;
IWICBitmapScaler *GraphicManager::pScaler = NULL;
ID2D1RenderTarget *GraphicManager::pRenderTarget = NULL;
ID2D1Bitmap *GraphicManager::pBitmap = NULL;
ID2D1BitmapBrush * GraphicManager::m_pBitmapBrush = NULL;
IDWriteFactory* GraphicManager::pDWriteFactory_ = NULL;
IDWriteTextFormat* GraphicManager::pTextFormat_ = NULL;
ID2D1SolidColorBrush* GraphicManager::pBlackBrush_ = NULL;
D2D1_RECT_F GraphicManager::layoutRect;
void GraphicManager::Init(HWND hwnd)
{
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory
	);
	DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory_)
	);
	// Obtain the size of the drawing area.
	RECT rc;
	GetClientRect(hwnd, &rc);

	// Create a Direct2D render target
	pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			hwnd,
			D2D1::SizeU(
				rc.right - rc.left,
				rc.bottom - rc.top)
		),
		&pRT
	);

	layoutRect = D2D1::RectF(
		static_cast<FLOAT>(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN))
	);
	SetFontFormat(L"GULIME", 32, 0);
	CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pWICFactory)
	);
}

void GraphicManager::SetFontFormat(LPCWSTR fontname, float fontsize, int alignment)
{
	pDWriteFactory_->CreateTextFormat(
		fontname,                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontsize,
		L"en-us",
		&pTextFormat_
	);
	pTextFormat_->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)alignment);
	pTextFormat_->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)alignment);
}

void GraphicManager::Load_Bitmap(GameObject * obj , LPCWSTR name)
{
	m_pWICFactory->CreateDecoderFromFilename(
		name,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	pDecoder->GetFrame(0, &pSource);
	m_pWICFactory->CreateFormatConverter(&pConverter);
	pConverter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
	);
	pRT->CreateBitmapFromWicBitmap(
		pConverter,
		NULL,
		&obj->pBitmap
	);
}

void GraphicManager::Render(GameObject * obj)
{
	if (obj->exist)
	{
		pRT->CreateBitmapBrush(
			obj->pBitmap,
			&m_pBitmapBrush
		);
		float width = obj->pBitmap->GetPixelSize().width;
		float height = obj->pBitmap->GetPixelSize().height;
		pRT->SetTransform(D2D1::Matrix3x2F::Scale(obj->scale.x, obj->scale.y,
			D2D1::Point2F(width / 2, height / 2)) *
			D2D1::Matrix3x2F::Rotation(obj->angle,
				D2D1::Point2F(width / 2, height / 2)) *
			D2D1::Matrix3x2F::Translation(obj->position.x - width / 2, obj->position.y - height / 2));
		pRT->FillRectangle(D2D1::RectF(0, 0, width, height), m_pBitmapBrush);
	}
}

void GraphicManager::TextRender(LPCWSTR text, float x, float y)
{
	pRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::YellowGreen),
		&pBlackBrush_
	);
	pRT->SetTransform(D2D1::Matrix3x2F::Translation(x,y));
	pRT->DrawText(
		text,        // The string to render.
		(UINT32)wcslen(text),    // The string's length.
		pTextFormat_,    // The text format.
		layoutRect,       // The region of the window where the text will be rendered.
		pBlackBrush_     // The brush used to draw the text.
	);
}

void GraphicManager::Release()
{
}

void GraphicManager::BeginDraw()
{
	pRT->BeginDraw();
	pRT->Clear();
}

void GraphicManager::EndDraw()
{
	pRT->EndDraw();
}
