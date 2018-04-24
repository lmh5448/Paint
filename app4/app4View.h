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

// app4View.h : Capp4View 클래스의 인터페이스
//

#pragma once

#define MAX_CLIENT_COUNT	10

class Capp4View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	Capp4View();
	DECLARE_DYNCREATE(Capp4View)

// 특성입니다.
public:
	Capp4Doc* GetDocument() const;
	CPoint Previous_;
	CPoint Previous_check;
	CPoint Start_;
	CPoint Poly_start;
	CPoint Poly_temp;
	CRect m_rectCurHist;
	int m_x = 0;
	int m_y = 0;
	int point_x1[100];
	int point_y1[100];
	int point_x2[100];
	int point_y2[100];
	int index = 0;

	int stain_point_x1[10000];
	int stain_point_y1[10000];
	int stain_point_x2[10000];
	int stain_point_y2[10000];
	int stain_index = 0;

	SOCKET m_listen_socket;
	CString m_ip;
	SOCKET m_client_list[MAX_CLIENT_COUNT];
	int m_client_count;
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~Capp4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnFilterHistogram();
	afx_msg void OnFilterAvg();
	afx_msg void OnFilterContrast();
	afx_msg void OnFilterGamma(double gamma_v);
	afx_msg void OnFileSave();
	afx_msg void OnFilterSharpening();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSlider2();
	afx_msg void OnSlider3();
	afx_msg void OnSlider4();
	afx_msg void OnFilterMedian();
	afx_msg void OnEdgePrewittX();
	afx_msg void OnEdgePrewittY();
	afx_msg void OnEdgeSobelX();
	afx_msg void OnEdgeSobelY();
	afx_msg void OnEdgeEmboss1();
	afx_msg void OnEdgeEmboss2();
	afx_msg void OnEdgeLaplaican4();
	afx_msg void OnEdgeLaplaican8();
	afx_msg void OnEdgeUnsharp4();
	afx_msg void OnEdgeUnsharp8();
	afx_msg void OnButton11();
	afx_msg void OnSocketOpen();
	void AcceptProcess(SOCKET parm_h_socket);
	void ClientCloseProcess(SOCKET parm_h_socket, char parm_force_flag);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton19();
	void Capp4View::SendOK(SOCKET temp_socket);
	void Capp4View::SendNO(SOCKET temp_socket);
	void Capp4View::InitQueue();
};

#ifndef _DEBUG  // app4View.cpp의 디버그 버전
inline Capp4Doc* Capp4View::GetDocument() const
   { return reinterpret_cast<Capp4Doc*>(m_pDocument); }
#endif

