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

// app4Doc.h : Capp4Doc 클래스의 인터페이스
//


#pragma once

class Capp4Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	Capp4Doc();
	DECLARE_DYNCREATE(Capp4Doc)

// 특성입니다.
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
	//1연필 2선분 3사각형 4원 5지우개 6다각형 7색채우기 8히스토그램 필터 9블러링 10엔드인 11감마 12샤프닝 13미디안 14엣지검출
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
// 작업입니다.
public:

// 재정의입니다.
public:
	//virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~Capp4Doc();
	BOOL OnNewDocument();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
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
	//사용안한다 기능은 똑같지만 속도차이가 어마어마함 -> ExtFloodFill FLOODFILLSURFACE
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
