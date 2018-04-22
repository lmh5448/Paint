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

// app4Doc.h : Capp4Doc Ŭ������ �������̽�
//


#pragma once

class Capp4Doc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	Capp4Doc();
	DECLARE_DYNCREATE(Capp4Doc)

// Ư���Դϴ�.
public:
	CBitmap m_Cbitmap;
	CBitmap m_Cbitmap_ori;
	BITMAP m_bmpinfo;
	////////////////////////////////
	CString m_file_path;
	BITMAPFILEHEADER m_file_header;
	BITMAPINFOHEADER m_info_header;
	BYTE* m_imagedata;
	BYTE* m_imagedata_temp;
	int m_imagedata_size;
	int m_channels;
	int m_width;
	int m_height;
	int m_step;
	BOOL m_bright_check = false;
	BOOL m_brightless_check = false;
	int m_bright=0;
	int m_brightless=1;
	//1���� 2���� 3�簢�� 4�� 5���찳 6�ٰ��� 7��ä��� 8������׷� ���� 9���� 10������ 11���� 12������ 13�̵�� 14��������
	int m_state = 0;
	int m_vector_index = 1;
	int m_color_r=0;
	int m_color_g=0;
	int m_color_b=0;
	BOOL m_brush_check = false;
	int m_brush_color_r = 0;
	int m_brush_color_g = 0;
	int m_brush_color_b = 0;
	int m_thickness = 5;
	BOOL m_gamma_check = false;
	double m_gamma = 1.0;
	BOOL m_binary_check = false;
	int m_binary = 127;
	int m_edge = 0;
	BOOL m_messageBox = false;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	//virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~Capp4Doc();
	BOOL OnNewDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	afx_msg void Filter_avg();
	afx_msg void Filter_auto_contrast();
	afx_msg void Filter_bright();
	afx_msg void Filter_brightless();
	afx_msg void Filter_gamma();
	afx_msg void Filter_histogram();
	afx_msg void Filter_sharpening();
	afx_msg void Filter_binary();
	afx_msg void Filter_median();
	afx_msg void Filter_edge();
	afx_msg void Defect_inspection();
	//�����Ѵ� ����� �Ȱ����� �ӵ����̰� ���� -> ExtFloodFill FLOODFILLSURFACE
	//afx_msg void MyFloodFill(int x, int y, BYTE nr, BYTE ng, BYTE nb);
	COLORREF GetRGB(int x,int y);
	afx_msg void Onbright();
	afx_msg void OnUpdatebright(CCmdUI *pCmdUI);
	afx_msg void Onbrightless();
	afx_msg void OnUpdatebrightless(CCmdUI *pCmdUI);
	afx_msg void Onpaintline();
	afx_msg void OnUpdatepaintline(CCmdUI *pCmdUI);
	afx_msg void Onpaintsegment();
	afx_msg void OnUpdatepaintsegment(CCmdUI *pCmdUI);
	afx_msg void OnButton12();
	afx_msg void OnUpdateButton12(CCmdUI *pCmdUI);
	afx_msg void OnButton13();
	afx_msg void OnUpdateButton13(CCmdUI *pCmdUI);
	afx_msg void OnButton14();
	afx_msg void OnUpdateButton14(CCmdUI *pCmdUI);
	afx_msg void OnButton15();
	afx_msg void OnUpdateButton15(CCmdUI *pCmdUI);
	afx_msg void OnButton16();
	afx_msg void OnUpdateButton16(CCmdUI *pCmdUI);
	afx_msg void OnSaveR();
	afx_msg void OnSaveG();
	afx_msg void OnSaveB();
	afx_msg void OnSaveOnfile();
	afx_msg void OnBinaryCheck();
	afx_msg void OnUpdateBinaryCheck(CCmdUI *pCmdUI);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
