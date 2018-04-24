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

// app4View.h : Capp4View Ŭ������ �������̽�
//

#pragma once

#define MAX_CLIENT_COUNT	10

class Capp4View : public CScrollView
{
protected: // serialization������ ��������ϴ�.
	Capp4View();
	DECLARE_DYNCREATE(Capp4View)

// Ư���Դϴ�.
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
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~Capp4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // app4View.cpp�� ����� ����
inline Capp4Doc* Capp4View::GetDocument() const
   { return reinterpret_cast<Capp4Doc*>(m_pDocument); }
#endif

