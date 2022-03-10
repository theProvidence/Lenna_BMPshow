
// Lenna_BMPshowView.cpp : implementation of the CLennaBMPshowView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lenna_BMPshow.h"
#endif

#include "Lenna_BMPshowDoc.h"
#include "Lenna_BMPshowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B') // BM marker for BMP file

// CLennaBMPshowView

IMPLEMENT_DYNCREATE(CLennaBMPshowView, CView)

BEGIN_MESSAGE_MAP(CLennaBMPshowView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CLennaBMPshowView construction/destruction

CLennaBMPshowView::CLennaBMPshowView() noexcept
{
	// TODO: add construction code here

}

CLennaBMPshowView::~CLennaBMPshowView()
{
}

BOOL CLennaBMPshowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLennaBMPshowView drawing

void CLennaBMPshowView::OnDraw(CDC* /*pDC*/)
{
	CLennaBMPshowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CLennaBMPshowView printing

BOOL CLennaBMPshowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLennaBMPshowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLennaBMPshowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLennaBMPshowView diagnostics

#ifdef _DEBUG
void CLennaBMPshowView::AssertValid() const
{
	CView::AssertValid();
}

void CLennaBMPshowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLennaBMPshowDoc* CLennaBMPshowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLennaBMPshowDoc)));
	return (CLennaBMPshowDoc*)m_pDocument;
}
#endif //_DEBUG


// CLennaBMPshowView message handlers


void CLennaBMPshowView::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: Add your message handler code here and/or call default

    FILE* fp = NULL;
    fopen_s(&fp, "lenna.bmp", "rb");
    if (!fp)
        return;

    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;

    // Read BITMAP FILE HEADER 
    if (fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, fp) != 1)
    {
        fclose(fp); return;
    }

    // Check 'BM' marker whether the file is BMP
    if (bmfh.bfType != DIB_HEADER_MARKER)
    {
        fclose(fp); return;
    }

    // Read BITMAP INFO HEADER
    if (fread(&bmih, sizeof(BITMAPINFOHEADER), 1, fp) != 1)
    {
        fclose(fp); return;
    }

    LONG nWidth = bmih.biWidth;
    LONG nHeight = bmih.biHeight;
    WORD nBitCount = bmih.biBitCount;

    DWORD dwWidthStep = (DWORD)((nWidth * nBitCount / 8 + 3) & ~3);
    DWORD dwSizeImage = nHeight * dwWidthStep;

    // Size of DIB structure (BITMAP INFO HEADER + Color table + Pixel data)
    DWORD dwDibSize;
    if (nBitCount == 24) // Color
        dwDibSize = sizeof(BITMAPINFOHEADER) + dwSizeImage;
    else // Black & white
        dwDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (static_cast<unsigned long long>(1) << nBitCount) + dwSizeImage;

    // Memory allocation for DIB file
    BYTE* pDib = new BYTE[dwDibSize];

    if (pDib == NULL)
    {
        fclose(fp); return;
    }

    // Read Packed-DIB size from lenna.bmp
    fseek(fp, sizeof(BITMAPFILEHEADER), SEEK_SET);
    if (fread(pDib, sizeof(BYTE), dwDibSize, fp) != dwDibSize)
    {
        delete[] pDib;
        pDib = NULL;
        fclose(fp);
        return;
    }

    // Starting location of pixel data
    LPVOID lpvBits;
    if (nBitCount == 24) // Color
        lpvBits = pDib + sizeof(BITMAPINFOHEADER);
    else // Black & white
        lpvBits = pDib + sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (static_cast<unsigned long long>(1) << nBitCount);

    // Print DIB on the window
    CClientDC dc(this);
    ::SetDIBitsToDevice(dc.m_hDC, point.x, point.y, nWidth, nHeight, 0, 0, 0,
        nHeight, lpvBits, (BITMAPINFO*)pDib, DIB_RGB_COLORS);

    // Memory de-allocation & file closing
    delete[] pDib;
    fclose(fp);

    CView::OnLButtonDown(nFlags, point);
}
