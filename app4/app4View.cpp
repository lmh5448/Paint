// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// app4View.cpp : Capp4View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
END_MESSAGE_MAP()

// Capp4View ����/�Ҹ�

Capp4View::Capp4View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Capp4View::~Capp4View()
{
}

BOOL Capp4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Capp4View �׸���

void Capp4View::OnDraw(CDC* pDC)
{
	Capp4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	//bitmapinfo ����ü���� �����
	SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
	pDoc->m_info_header.biHeight = pDoc->m_height*(-1);
	::StretchDIBits(pDC->m_hDC, 0, 0, pDoc->m_width, pDoc->m_height,
		0, 0, pDoc->m_width, pDoc->m_height,
		pDoc->m_imagedata,(LPBITMAPINFO)&pDoc->m_info_header,
		DIB_RGB_COLORS,SRCCOPY);
	pDoc->m_info_header.biHeight = pDoc->m_height;
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


// Capp4View ����

#ifdef _DEBUG
void Capp4View::AssertValid() const
{
	CView::AssertValid();
}

void Capp4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Capp4Doc* Capp4View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Capp4Doc)));
	return (Capp4Doc*)m_pDocument;
}
#endif //_DEBUG


// Capp4View �޽��� ó����


int Capp4View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	return 0;
}


void Capp4View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


//void Capp4View::OnMButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//
//	CView::OnMButtonDown(nFlags, point);
//}


void Capp4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Previous_ = point;
	CView::OnLButtonDown(nFlags, point);
}


void Capp4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {
		CClientDC dc(this);
		dc.MoveTo(Previous_);
		dc.LineTo(point);
		if (pDoc->m_file_path != "" && point.y < pDoc->m_height && point.x < pDoc->m_width) {
			int px, py, nx, ny;
			if(Previous_.x<point.x){
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
			for (int x = px; x <= nx; x++) {
				int y = (int)(((double)(ny - py) / (nx - px))*(x - px) + py);
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 0] = 0;
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 1] = 0;
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 2] = 0;
			}
			if (ny < py) {
				int temp = ny;
				ny = py;
				py = temp;
				temp = nx;
				nx = px;
				px = temp;
			}
			for (int y = py; y <= ny; y++) {
				int x = (int)(((double)(nx - px) / (ny - py))*(y - py) + px);
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 0] = 0;
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 1] = 0;
				pDoc->m_imagedata_ori[y * pDoc->m_step + x*pDoc->m_channels + 2] = 0;
			}
		}
		Previous_ = point;
	}
	CView::OnMouseMove(nFlags, point);
}
