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
#include "MainFrm.h"

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

	BOOL brush_check;
	int brush_r;
	int brush_g;
	int brush_b;

	double gamma_v;
	int edge;
};

vector<Draw_info> v;
stack<Draw_info> s;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Capp4View

IMPLEMENT_DYNCREATE(Capp4View, CScrollView)

BEGIN_MESSAGE_MAP(Capp4View, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_COMMAND(ID_EDIT_UNDO, &Capp4View::OnEditUndo)
ON_COMMAND(ID_EDIT_REDO, &Capp4View::OnEditRedo)
ON_COMMAND(ID_FILTER_HISTOGRAM, &Capp4View::OnFilterHistogram)
ON_COMMAND(ID_FILTER_AVG, &Capp4View::OnFilterAvg)
ON_COMMAND(ID_FILTER_CONTRAST, &Capp4View::OnFilterContrast)
ON_COMMAND(ID_FILE_SAVE, &Capp4View::OnFileSave)
ON_COMMAND(ID_FILTER_SHARPENING, &Capp4View::OnFilterSharpening)
ON_WM_VSCROLL()
ON_WM_HSCROLL()
ON_COMMAND(ID_SLIDER2, &Capp4View::OnSlider2)
ON_COMMAND(ID_SLIDER3, &Capp4View::OnSlider3)
ON_COMMAND(ID_SLIDER4, &Capp4View::OnSlider4)
ON_COMMAND(ID_FILTER_MEDIAN, &Capp4View::OnFilterMedian)
ON_COMMAND(ID_EDGE_PREWITT_X, &Capp4View::OnEdgePrewittX)
ON_COMMAND(ID_EDGE_PREWITT_Y, &Capp4View::OnEdgePrewittY)
ON_COMMAND(ID_EDGE_SOBEL_X, &Capp4View::OnEdgeSobelX)
ON_COMMAND(ID_EDGE_SOBEL_Y, &Capp4View::OnEdgeSobelY)
ON_COMMAND(ID_EDGE_EMBOSS_1, &Capp4View::OnEdgeEmboss1)
ON_COMMAND(ID_EDGE_EMBOSS_2, &Capp4View::OnEdgeEmboss2)
ON_COMMAND(ID_EDGE_LAPLAICAN_4, &Capp4View::OnEdgeLaplaican4)
ON_COMMAND(ID_EDGE_LAPLAICAN_8, &Capp4View::OnEdgeLaplaican8)
ON_COMMAND(ID_EDGE_UNSHARP_4, &Capp4View::OnEdgeUnsharp4)
ON_COMMAND(ID_EDGE_UNSHARP_8, &Capp4View::OnEdgeUnsharp8)
ON_COMMAND(ID_BUTTON11, &Capp4View::OnButton11)
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
	m_x = this->GetScrollPos(SB_HORZ);
	m_y = this->GetScrollPos(SB_VERT);
	////////////////////////////////////////////////////////////
	//copy
	BYTE* copy_temp = new BYTE[pDoc->m_imagedata_size];
	BITMAPINFO info_header;
	info_header.bmiHeader = pDoc->m_info_header;
	GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap_ori, 0, pDoc->m_height, copy_temp, &info_header, DIB_RGB_COLORS);
	SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, copy_temp, &info_header, DIB_RGB_COLORS);
	free(copy_temp);
	////////////////////////////////////////////////////////////

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	memDC.SelectObject(&pDoc->m_Cbitmap);

	////
	//그림 그리는 부분
	CPoint point1;
	CPoint point2;

	for (int i = 0; i < v.size(); i++) {
		point1.x = v[i].x1;
		point1.y = v[i].y1;
		point2.x = v[i].x2;
		point2.y = v[i].y2;
		CPen pen;
		CBrush brush(RGB(v[i].brush_r, v[i].brush_g, v[i].brush_b));
		pen.CreatePen(PS_SOLID, v[i].thickness, RGB(v[i].r, v[i].g, v[i].b));
		memDC.SelectObject(pen);
		//채우기 설정
		if (v[i].brush_check) { memDC.SelectObject(brush); }
		else { memDC.SelectStockObject(NULL_BRUSH); }

		//도형그리기 redo undo 때문에 계속 추가
		//1연필 2선분 3사각형 4원 5지우개 6다각형 7색채우기 8히스토그램 필터 9블러링 10엔드인 11감마 12샤프닝 13미디안 14엣지검출
		if(v[i].type==1 || v[i].type==2 || v[i].type==5 || v[i].type==6){
			memDC.MoveTo(point1);
			memDC.LineTo(point2);
		}
		else if(v[i].type==3){
			memDC.Rectangle(point1.x, point1.y, point2.x, point2.y);
		}
		else if (v[i].type == 4) {
			memDC.Ellipse(point1.x, point1.y, point2.x, point2.y);
		}
		else if (v[i].type == 7) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			//pDoc->MyFloodFill(point1.x, point1.y, v[i].brush_r, v[i].brush_g, v[i].brush_b);
			COLORREF color = pDoc->GetRGB(point1.x, point1.y);
			memDC.ExtFloodFill(point1.x, point1.y, color, FLOODFILLSURFACE);
		}
		else if (v[i].type == 8) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->Filter_histogram();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 9) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->Filter_avg();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 10) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->Filter_auto_contrast();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 11) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->m_gamma = v[i].gamma_v;
			pDoc->Filter_gamma();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 12) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->Filter_sharpening();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 13) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->Filter_median();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 14) {
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->m_edge = v[i].edge;
			pDoc->Filter_edge();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		}
		else if (v[i].type == 15) {
			index = 0;
			GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			pDoc->Defect_Stain_inspection();
			SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
			for (int i = 0; i < index; i++) {
				memDC.Rectangle(point_x1[i], pDoc->m_height - point_y1[i], point_x2[i], pDoc->m_height - point_y2[i]);
			}
		}

		pen.DeleteObject();
		brush.DeleteObject();
	}
	if (pDoc->m_bright_check) {
		GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		pDoc->Filter_bright();
		SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
	}
	if (pDoc->m_brightless_check) {
		GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		pDoc->Filter_brightless();
		SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
	}
	if (pDoc->m_binary_check) {
		GetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		pDoc->Filter_binary();
		SetDIBits(pDC->m_hDC, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
	}
	////
	//축소 출력할때 깨짐 현상 제거 모드
	SetStretchBltMode(pDC->m_hDC, COLORONCOLOR);
	//크기를 반으로 줄일때
	/*if (pDoc->m_width > 1920 || pDoc->m_height > 1080) {
		pDC->StretchBlt(0, 0, pDoc->m_width / 2, pDoc->m_height / 2, &memDC, 0, 0, pDoc->m_width, pDoc->m_height, SRCCOPY);
	}*/
	if (pDoc->m_height>1080 && pDoc->m_width>1920) {
		if (pDoc->m_height / 1080 > pDoc->m_width / 1920) {
			pDC->StretchBlt(0, 0, (pDoc->m_width/pDoc->m_height)*1080, 1080, &memDC, 0, 0, pDoc->m_width, pDoc->m_height, SRCCOPY);
		}
		else {
			pDC->StretchBlt(0, 0, 1920, (pDoc->m_height/pDoc->m_width)*1920, &memDC, 0, 0, pDoc->m_width, pDoc->m_height, SRCCOPY);
		}
	}
	else if (pDoc->m_width>1920) {
		pDC->StretchBlt(0, 0, 1920, (pDoc->m_height / pDoc->m_width) * 1920, &memDC, 0, 0, pDoc->m_width, pDoc->m_height, SRCCOPY);
	}
	else if (pDoc->m_height>1080) {
		pDC->StretchBlt(0, 0, (pDoc->m_width / pDoc->m_height) * 1080, 1080, &memDC, 0, 0, pDoc->m_width, pDoc->m_height, SRCCOPY);
	}
	else {
		pDC->BitBlt(0, 0, pDoc->m_width, pDoc->m_height, &memDC, 0, 0, SRCCOPY);
	}
	
	//UI가 갱신이안되는건 이거때문이였음 invalidate 하는역할 보고 넘어가자
	//Invalidate(false);
	
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

void Capp4View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	point.x += m_x;
	point.y += m_y;
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Previous_ = point;
	Start_ = point;
	if (Poly_start.x == -1 && Poly_start.y == -1) {
		Poly_start = point;
		Poly_temp = point;
	}
	if (pDoc->m_state == 7) {
		Draw_info draw;
		draw.x1 = point.x;
		draw.y1 = point.y;
		draw.x2 = point.x;
		draw.y2 = point.y;
		draw.check = pDoc->m_vector_index;
		draw.thickness = pDoc->m_thickness;
		draw.r = pDoc->m_color_r;
		draw.g = pDoc->m_color_g;
		draw.b = pDoc->m_color_b;
		draw.type = pDoc->m_state;
		draw.brush_check = pDoc->m_brush_check;
		draw.brush_r = pDoc->m_brush_color_r;
		draw.brush_g = pDoc->m_brush_color_g;
		draw.brush_b = pDoc->m_brush_color_b;
		if (draw.brush_check) {
			v.push_back(draw);
			pDoc->m_vector_index++;
		}
	}
	Invalidate(false);
	CView::OnLButtonDown(nFlags, point);
}


void Capp4View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	CClientDC dc(this);
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {
		if (pDoc->m_state == 0)return;
		point.x += m_x;
		point.y += m_y;
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
			draw.brush_check = pDoc->m_brush_check;
			draw.brush_r = pDoc->m_brush_color_r;
			draw.brush_g = pDoc->m_brush_color_g;
			draw.brush_b = pDoc->m_brush_color_b;
			v.push_back(draw);
			Previous_ = point;
			Invalidate(false);
		}
		else if (pDoc->m_state == 6) {
			Draw_info draw;
			draw.x1 = Previous_.x;
			draw.y1 = Previous_.y;
			draw.x2 = point.x;
			draw.y2 = point.y;
			draw.check = pDoc->m_vector_index;
			draw.thickness = pDoc->m_thickness*5;
			draw.r = 255;
			draw.g = 255;
			draw.b = 255;
			draw.type = pDoc->m_state;
			draw.brush_check = pDoc->m_brush_check;
			draw.brush_r = 255;
			draw.brush_g = 255;
			draw.brush_b = 255;
			v.push_back(draw);
			Previous_ = point;
			Invalidate(false);
		}
		else if (pDoc->m_state == 5) {
			while (v.size() != 0 && v[v.size() - 1].check == pDoc->m_vector_index) {
				v.pop_back();
			}
			Draw_info draw;
			draw.x1 = Poly_temp.x;
			draw.y1 = Poly_temp.y;
			draw.x2 = point.x;
			draw.y2 = point.y;
			draw.check = pDoc->m_vector_index;
			draw.thickness = pDoc->m_thickness;
			draw.r = pDoc->m_color_r;
			draw.g = pDoc->m_color_g;
			draw.b = pDoc->m_color_b;
			draw.type = pDoc->m_state;
			draw.brush_check = pDoc->m_brush_check;
			draw.brush_r = pDoc->m_brush_color_r;
			draw.brush_g = pDoc->m_brush_color_g;
			draw.brush_b = pDoc->m_brush_color_b;
			v.push_back(draw);
			Invalidate(false);
		}
		else if(pDoc->m_state == 2 || pDoc->m_state == 3 || pDoc->m_state == 4){
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
			draw.brush_check = pDoc->m_brush_check;
			draw.brush_r = pDoc->m_brush_color_r;
			draw.brush_g = pDoc->m_brush_color_g;
			draw.brush_b = pDoc->m_brush_color_b;
			v.push_back(draw);
			Invalidate(false);
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void Capp4View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	if (pDoc->m_state == 0)return;
	point.x += m_x;
	point.y += m_y;
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
		draw.brush_check = pDoc->m_brush_check;
		draw.brush_r = pDoc->m_brush_color_r;
		draw.brush_g = pDoc->m_brush_color_g;
		draw.brush_b = pDoc->m_brush_color_b;
		v.push_back(draw);
		pDoc->m_vector_index++;
	}
	else if (pDoc->m_state == 6) {
		Draw_info draw;
		draw.x1 = Previous_.x;
		draw.y1 = Previous_.y;
		draw.x2 = point.x;
		draw.y2 = point.y;
		draw.check = pDoc->m_vector_index;
		draw.thickness = pDoc->m_thickness*5;
		draw.r = 255;
		draw.g = 255;
		draw.b = 255;
		draw.type = pDoc->m_state;
		draw.brush_check = pDoc->m_brush_check;
		draw.brush_r = 255;
		draw.brush_g = 255;
		draw.brush_b = 255;
		v.push_back(draw);
		pDoc->m_vector_index++;
	}
	else if (pDoc->m_state == 5) {
		if (Poly_start.x-10 < point.x && Poly_start.x+10 >point.x && Poly_start.y-10 < point.y && Poly_start.y+10>point.y) {
			point = Poly_start;
		}
		Draw_info draw;
		draw.x1 = Poly_temp.x;
		draw.y1 = Poly_temp.y;
		draw.x2 = point.x;
		draw.y2 = point.y;
		draw.check = pDoc->m_vector_index;
		draw.thickness = pDoc->m_thickness;
		draw.r = pDoc->m_color_r;
		draw.g = pDoc->m_color_g;
		draw.b = pDoc->m_color_b;
		draw.type = pDoc->m_state;
		draw.brush_check = pDoc->m_brush_check;
		draw.brush_r = pDoc->m_brush_color_r;
		draw.brush_g = pDoc->m_brush_color_g;
		draw.brush_b = pDoc->m_brush_color_b;
		v.push_back(draw);
		Poly_temp = point;
		pDoc->m_vector_index++;
		if (Poly_start.x - 10 < point.x && Poly_start.x + 10 >point.x && Poly_start.y - 10 < point.y && Poly_start.y + 10>point.y) {
			pDoc->m_state = 0;
		}
	}
	else if (pDoc->m_state == 2 || pDoc->m_state == 3 || pDoc->m_state == 4) {
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
		draw.brush_check = pDoc->m_brush_check;
		draw.brush_r = pDoc->m_brush_color_r;
		draw.brush_g = pDoc->m_brush_color_g;
		draw.brush_b = pDoc->m_brush_color_b;
		v.push_back(draw);
		pDoc->m_vector_index++;
	}
	Invalidate(false);

	while (!s.empty()) {
		s.pop();
	}

	CView::OnLButtonUp(nFlags, point);
}


void Capp4View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	this->GetClientRect(m_rectCurHist);
	
	//this->GetWindowRect(m_rectCurHist);
	if (pDoc->m_file_path == "") {
		//헤더초기화 및 비트맵 선언
		pDoc->m_file_header.bfType = 19778;
		pDoc->m_file_header.bfReserved1 = 0;
		pDoc->m_file_header.bfReserved2 = 0;
		pDoc->m_file_header.bfOffBits = 54;

		pDoc->m_info_header.biSize = 40;
		pDoc->m_info_header.biWidth = 1437;
		pDoc->m_info_header.biHeight = 637;
		pDoc->m_info_header.biPlanes = 1;
		pDoc->m_info_header.biBitCount = 24;
		pDoc->m_info_header.biCompression = BI_RGB;
		pDoc->m_info_header.biXPelsPerMeter = 0;
		pDoc->m_info_header.biYPelsPerMeter = 0;
		pDoc->m_info_header.biClrUsed = 0;
		pDoc->m_info_header.biClrImportant = 0;

		pDoc->m_channels = pDoc->m_info_header.biBitCount / 8;
		pDoc->m_height = pDoc->m_info_header.biHeight;
		pDoc->m_width = pDoc->m_info_header.biWidth;
		pDoc->m_step = (pDoc->m_width*pDoc->m_channels + 3)&~3;
		pDoc->m_imagedata_size = pDoc->m_height * pDoc->m_step;
		pDoc->m_info_header.biSizeImage = pDoc->m_imagedata_size;
		pDoc->m_file_header.bfSize = pDoc->m_imagedata_size + 54;

		pDoc->m_imagedata = new BYTE[pDoc->m_imagedata_size];
		pDoc->m_imagedata_temp = new BYTE[pDoc->m_imagedata_size];

		std::fill_n(pDoc->m_imagedata, pDoc->m_imagedata_size*sizeof(BYTE), 255);
		memcpy(pDoc->m_imagedata_temp, pDoc->m_imagedata, pDoc->m_imagedata_size * sizeof(BYTE));

		pDoc->m_bright = 0;
		pDoc->m_brightless = 0;

		pDoc->m_Cbitmap_ori.LoadBitmapW(IDB_BITMAP1);
		pDoc->m_Cbitmap.LoadBitmapW(IDB_BITMAP1);

		pDoc->m_Cbitmap_ori.GetBitmap(&pDoc->m_bmpinfo);

	}
	else {
		//GetParentFrame()->SetWindowPos(NULL, 200, 200, pDoc->m_width<500?500: pDoc->m_width,220+ pDoc->m_height, SWP_NOZORDER);
		v.clear();
		while (!s.empty()) {
			s.pop();
		}
		pDoc->m_vector_index = 1;
	}
	CSize sizeTotal;
	sizeTotal.cx = pDoc->m_width;
	sizeTotal.cy = pDoc->m_height;
	if (pDoc->m_height>1080 && pDoc->m_width>1920) {
		if (pDoc->m_height / 1080 > pDoc->m_width / 1920) {
			sizeTotal.cx *= (1080/pDoc->m_height);
			sizeTotal.cy = 1080;
		}
		else {
			sizeTotal.cx = 1920;
			sizeTotal.cy *= (1920 / pDoc->m_width);
		}
	}
	else if (pDoc->m_width>1920) {
		sizeTotal.cy *= (1920 / pDoc->m_width);
	}
	else if (pDoc->m_height>1080) {
		sizeTotal.cx *= (1080 / pDoc->m_height);
	}
	//크기를 반으로만 줄일때
	/*if (pDoc->m_width > 1920 || pDoc->m_height > 1080) {
		sizeTotal.cx /= 2;
		sizeTotal.cy /= 2;
	}*/
	SetScrollSizes(MM_TEXT, sizeTotal);

	Invalidate();
}


void Capp4View::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	Invalidate(false);
}


void Capp4View::OnEditRedo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	Invalidate(false);
}


void Capp4View::OnFilterHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 8;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnFilterAvg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 9;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnFilterContrast()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 10;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}

void Capp4View::OnFilterGamma(double gamma_v)
{
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 11;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.gamma_v = gamma_v;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnFileSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(L"View");
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	CFile File;
	CFileDialog SaveDlg(FALSE, _T("bmp"), NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		pDoc->m_file_path = SaveDlg.GetPathName();
		File.Open(SaveDlg.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		File.Write(&pDoc->m_file_header, sizeof(BITMAPFILEHEADER));
		File.Write(&pDoc->m_info_header, sizeof(BITMAPINFOHEADER));

		if (pDoc->m_channels == 1) {
			for (int i = 0; i < 256; i++) {
				RGBQUAD GrayPalette = { i,i,i,0 };
				File.Write(&GrayPalette, sizeof(RGBQUAD));
			}
		}

		BITMAPINFO info_header;
		info_header.bmiHeader = pDoc->m_info_header;
		HDC dc = GetDC()->m_hDC;
		GetDIBits(dc, pDoc->m_Cbitmap, 0, pDoc->m_height, pDoc->m_imagedata, &info_header, DIB_RGB_COLORS);
		File.Write(pDoc->m_imagedata, pDoc->m_imagedata_size);
		File.Close();
	}
}


void Capp4View::OnFilterSharpening()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 12;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate(true);
	m_y = this->GetScrollPos(SB_VERT);
	CScrollView::OnVScroll(nSBCode, nPos, pScrollBar);
}


void Capp4View::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	Invalidate(true);
	m_x = this->GetScrollPos(SB_HORZ);
	CScrollView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void Capp4View::OnSlider2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonSlider* pSilder = DYNAMIC_DOWNCAST(CMFCRibbonSlider, pFrame->m_wndRibbonBar.FindByID(ID_SLIDER2));
	int v = pSilder->GetPos();
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	pDoc->m_bright = v;
	Invalidate(false);
	
	// 리본 슬라이더 위치 값 수정
	/*int custPos = 20;
	pSlider->SetPos(custPos);*/
}


void Capp4View::OnSlider3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonSlider* pSilder = DYNAMIC_DOWNCAST(CMFCRibbonSlider, pFrame->m_wndRibbonBar.FindByID(ID_SLIDER3));
	int v = pSilder->GetPos();
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	pDoc->m_brightless = v;
	Invalidate(false);
}


void Capp4View::OnSlider4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CMFCRibbonSlider* pSilder = DYNAMIC_DOWNCAST(CMFCRibbonSlider, pFrame->m_wndRibbonBar.FindByID(ID_SLIDER4));
	int v = pSilder->GetPos();
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	pDoc->m_binary = v;
	Invalidate(false);
}


void Capp4View::OnFilterMedian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 13;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgePrewittX()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 0;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgePrewittY()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 1;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeSobelX()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 2;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeSobelY()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 3;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeEmboss1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 4;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeEmboss2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 5;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeLaplaican4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 6;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeLaplaican8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 7;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeUnsharp4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 8;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnEdgeUnsharp8()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = pDoc->m_thickness;
	draw.r = pDoc->m_color_r;
	draw.g = pDoc->m_color_g;
	draw.b = pDoc->m_color_b;
	draw.type = 14;
	draw.brush_check = pDoc->m_brush_check;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	draw.edge = 9;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}


void Capp4View::OnButton11()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	Capp4Doc* pDoc = (Capp4Doc*)GetDocument();
	pDoc->m_messageBox = false;
	Draw_info draw;
	draw.x1 = 0;
	draw.y1 = 0;
	draw.x2 = 0;
	draw.y2 = 0;
	draw.check = pDoc->m_vector_index;
	draw.thickness = 3;
	draw.r = 255;
	draw.g = 0;
	draw.b = 0;
	draw.type = 15;
	draw.brush_check = false;
	draw.brush_r = pDoc->m_brush_color_r;
	draw.brush_g = pDoc->m_brush_color_g;
	draw.brush_b = pDoc->m_brush_color_b;
	v.push_back(draw);
	pDoc->m_vector_index++;
	while (!s.empty()) {
		s.pop();
	}
	Invalidate(false);
}
