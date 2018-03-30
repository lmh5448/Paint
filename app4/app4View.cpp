// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// app4View.cpp : Capp4View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "app4.h"
#endif

#include "app4Doc.h"
#include "app4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Capp4View

IMPLEMENT_DYNCREATE(Capp4View, CView)

BEGIN_MESSAGE_MAP(Capp4View, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//	ON_WM_MBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// Capp4View 생성/소멸

Capp4View::Capp4View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

Capp4View::~Capp4View()
{
}

BOOL Capp4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// Capp4View 그리기

void Capp4View::OnDraw(CDC* pDC)
{
	Capp4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	//bitmapinfo 구조체부터 만들기
	SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
	pDoc->m_info_header.biHeight = pDoc->m_height*(-1);
	::StretchDIBits(pDC->m_hDC, 0, 0, pDoc->m_width, pDoc->m_height,
		0, 0, pDoc->m_width, pDoc->m_height,
		pDoc->m_imagedata, (LPBITMAPINFO)&pDoc->m_info_header,
		DIB_RGB_COLORS, SRCCOPY);
	pDoc->m_info_header.biHeight = pDoc->m_height;


	/////////////////////////////////
	if(pDoc->m_draw_check){
		CBitmap* pBmSrc = pDC->GetCurrentBitmap();
		LPBITMAPINFO bitmap_info = NULL;
		bitmap_info->bmiHeader = pDoc->m_info_header;
		int v = GetDIBits(pDC->m_hDC, *pBmSrc, 0, 0, pDoc->m_imagedata_ori, bitmap_info, DIB_RGB_COLORS);
		AfxMessageBox(v);
		pDoc->m_draw_check = false;
	}
	/////////////////////////////////


}

void Capp4View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Capp4View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Capp4View 진단

#ifdef _DEBUG
void Capp4View::AssertValid() const
{
	CView::AssertValid();
}

void Capp4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Capp4Doc* Capp4View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Capp4Doc)));
	return (Capp4Doc*)m_pDocument;
}
#endif //_DEBUG


// Capp4View 메시지 처리기


int Capp4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}


void Capp4View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


//void Capp4View::OnMButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnMButtonDown(nFlags, point);
//}

void Capp4View::bitmap_paint(Capp4Doc* pDoc, CPoint point) {
	if (pDoc->m_file_path != "" && point.y < pDoc->m_height && point.x < pDoc->m_width) {
		int px, py, nx, ny;
		int dist_x, dist_y;
		dist_x = abs(Previous_.x - point.x);
		dist_y = abs(Previous_.y - point.y);
		if (dist_x > dist_y) {
			if (Previous_.x < point.x) {
				px = Previous_.x;
				py = Previous_.y;
				nx = point.x;
				ny = point.y;
			}
			else {
				px = point.x;
				py = point.y;
				nx = Previous_.x;
				ny = Previous_.y;
			}
			for (int x = px; x <= nx && x <= pDoc->m_width; x++) {
				int y = (int)(((double)(ny - py) / (nx - px))*(x - px) + py);
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 0] = pDoc->m_color_b;
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 1] = pDoc->m_color_g;
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 2] = pDoc->m_color_r;
			}
		}
		else {
			if (Previous_.y < point.y) {
				px = Previous_.x;
				py = Previous_.y;
				nx = point.x;
				ny = point.y;
			}
			else {
				px = point.x;
				py = point.y;
				nx = Previous_.x;
				ny = Previous_.y;
			}
			for (int y = py; y <= ny; y++) {
				int x = (((y - py)*(nx - px)) / (ny - py)) + px;
				pDoc->m_imagedata_ori[y*pDoc->m_step + x*pDoc->m_channels + 0] = pDoc->m_color_b;
				pDoc->m_imagedata_ori[y*pDoc->m_step + x*pDoc->m_channels + 1] = pDoc->m_color_g;
				pDoc->m_imagedata_ori[y*pDoc->m_step + x*pDoc->m_channels + 2] = pDoc->m_color_r;
			}
		}
	}
}

void Capp4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	CClientDC dc(this);
	if (pDoc->m_line_x == -1 && pDoc->m_line_y == -1) {
		pDoc->m_line_x = point.x;
		pDoc->m_line_y = point.y;
	}
	else {
		CPoint temp;
		temp.x = pDoc->m_line_x;
		temp.y = pDoc->m_line_y;
		dc.MoveTo(temp);
		dc.LineTo(point);
		pDoc->m_line_x = -1;
		pDoc->m_line_y = -1;
		//bitmap_paint(pDoc, point);
	}
	Previous_ = point;
	pDoc->m_draw_check = true;
	CView::OnLButtonDown(nFlags, point);
}


void Capp4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	if (pDoc->m_state == 1) {
		if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {
			CClientDC dc(this);
			CPen pen;
			pen.CreatePen(PS_SOLID, 5, RGB(pDoc->m_color_r, pDoc->m_color_g, pDoc->m_color_b));
			CPen* oldPen = dc.SelectObject(&pen);
			dc.MoveTo(Previous_);
			dc.LineTo(point);
			//bitmap_paint(pDoc, point);
			Previous_ = point;
			pDoc->m_draw_check = true;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


//void Capp4View::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	AfxMessageBox(_T("더블클릭이지"));
//	CView::OnLButtonDblClk(nFlags, point);
//}

void Capp4View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	if (pDoc->m_file_path == "") {
		GetParentFrame()->SetWindowPos(NULL, 200, 200, 200 + 500, 200 + 500, SWP_NOZORDER);
	}
	else {
		GetParentFrame()->SetWindowPos(NULL, 200, 200, pDoc->m_width<500?500: pDoc->m_width,220+ pDoc->m_height, SWP_NOZORDER);
	}

	Invalidate();
}
