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

#include<vector>
#include<stack>
using namespace std;
struct Draw_info
{
	int x1;
	int y1;
	int x2;
	int y2;
	//CPen pen;
	int check;

	int thickness;
	int r;
	int g;
	int b;

	int type;
};

vector<Draw_info> v;
stack<Draw_info> s;

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
ON_WM_LBUTTONUP()
ON_COMMAND(ID_EDIT_UNDO, &Capp4View::OnEditUndo)
ON_COMMAND(ID_EDIT_REDO, &Capp4View::OnEditRedo)
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
	////////////////////////////////////////////////////////////
	//copy
	BYTE* copy_temp = new BYTE[pDoc->m_imagedata_size];
	BITMAPINFO info_header;
	info_header.bmiHeader = pDoc->m_info_header;
	GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap_ori, 0, pDoc->m_height, copy_temp, &info_header, DIB_RGB_COLORS);
	SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, copy_temp, &info_header, DIB_RGB_COLORS);
	////////////////////////////////////////////////////////////

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&pDoc->m_Cbitmap);

	////
	//�׸� �׸��� �κ�
	CPoint point1;
	CPoint point2;

	for (int i = 0; i < v.size(); i++) {
		point1.x = v[i].x1;
		point1.y = v[i].y1;
		point2.x = v[i].x2;
		point2.y = v[i].y2;
		CPen pen;
		pen.CreatePen(PS_SOLID, v[i].thickness, RGB(v[i].r, v[i].g, v[i].b));
		memDC.SelectObject(pen);
		if(v[i].type==1||v[i].type==2){
			memDC.MoveTo(point1);
			memDC.LineTo(point2);
		}
		else if(v[i].type==3){
			memDC.Rectangle(point1.x, point1.y, point2.x, point2.y);
		}
		else if (v[i].type == 4) {
			CPoint point3;
			point3.x = point1.x;
			point3.y = point2.y;
			CPoint point4;
			point4.x = point2.x;
			point4.y = point1.y;
			memDC.MoveTo(point1);
			memDC.LineTo(point3);
			memDC.LineTo(point4);
			memDC.MoveTo(point2);
			memDC.LineTo(point3);
			memDC.LineTo(point4);
		}
	}
	////
	pDC->BitBlt(0, 0, pDoc->m_bmpinfo.bmWidth, pDoc->m_bmpinfo.bmHeight, &memDC, 0, 0, SRCCOPY);
	ReleaseDC(&memDC);
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

void Capp4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Previous_ = point;
	Start_ = point;
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}


void Capp4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	CClientDC dc(this);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {
		if (pDoc->m_state == 1) {
			Draw_info draw;
			draw.x1 = Previous_.x;
			draw.y1 = Previous_.y;
			draw.x2 = point.x;
			draw.y2 = point.y;
			draw.check = pDoc->m_vector_index;
			draw.thickness = pDoc->m_thickness;
			draw.r = pDoc->m_color_r;
			draw.g = pDoc->m_color_g;
			draw.b = pDoc->m_color_b;
			draw.type = pDoc->m_state;
			v.push_back(draw);
			Previous_ = point;
			Invalidate(false);
		}
		else {
			while (v.size() != 0 && v[v.size() - 1].check == pDoc->m_vector_index) {
				v.pop_back();
			}
			Draw_info draw;
			draw.x1 = Start_.x;
			draw.y1 = Start_.y;
			draw.x2 = point.x;
			draw.y2 = point.y;
			draw.check = pDoc->m_vector_index;
			draw.thickness = pDoc->m_thickness;
			draw.r = pDoc->m_color_r;
			draw.g = pDoc->m_color_g;
			draw.b = pDoc->m_color_b;
			draw.type = pDoc->m_state;
			v.push_back(draw);
			Invalidate(false);
		}
	}
	CView::OnMouseMove(nFlags, point);
}

void Capp4View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	if (pDoc->m_file_path == "") {
		GetParentFrame()->SetWindowPos(NULL, 200, 200, 200 + 500, 200 + 500, SWP_NOZORDER);
	}
	else {
		GetParentFrame()->SetWindowPos(NULL, 200, 200, pDoc->m_width<500?500: pDoc->m_width,220+ pDoc->m_height, SWP_NOZORDER);
		v.clear();
		while (!s.empty()) {
			s.pop();
		}
		pDoc->m_vector_index = 1;
	}

	Invalidate();
}


void Capp4View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	if (pDoc->m_state == 0)return;
	if(pDoc->m_state==1){
		Draw_info draw;
		draw.x1 = Previous_.x;
		draw.y1 = Previous_.y;
		draw.x2 = point.x;
		draw.y2 = point.y;
		draw.check = pDoc->m_vector_index;
		draw.thickness = pDoc->m_thickness;
		draw.r = pDoc->m_color_r;
		draw.g = pDoc->m_color_g;
		draw.b = pDoc->m_color_b;
		draw.type = pDoc->m_state;
		v.push_back(draw);
		pDoc->m_vector_index++;
	}
	else {
		Draw_info draw;
		draw.x1 = Start_.x;
		draw.y1 = Start_.y;
		draw.x2 = point.x;
		draw.y2 = point.y;
		draw.check = pDoc->m_vector_index;
		draw.thickness = pDoc->m_thickness;
		draw.r = pDoc->m_color_r;
		draw.g = pDoc->m_color_g;
		draw.b = pDoc->m_color_b;
		draw.type = pDoc->m_state;
		v.push_back(draw);
		pDoc->m_vector_index++;
	}
	Invalidate(false);

	while (!s.empty()) {
		s.pop();
	}

	CView::OnLButtonUp(nFlags, point);
}


void Capp4View::OnEditUndo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	bool check = false;
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	while (v.size() != 0 && v[v.size() - 1].check == pDoc->m_vector_index-1) {
		check = true;
		s.push(v[v.size() - 1]);
		v.pop_back();
	}
	if (check) {
		pDoc->m_vector_index--;
	}
	Invalidate();
}


void Capp4View::OnEditRedo()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	bool check = false;
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	while (!s.empty() && s.top().check == pDoc->m_vector_index){
		check = true;
		v.push_back(s.top());
		s.pop();
	}
	if (check) {
		pDoc->m_vector_index++;
	}
	Invalidate();
}
