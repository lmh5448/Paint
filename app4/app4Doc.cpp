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

// app4Doc.cpp : Capp4Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "app4.h"
#endif

#include "app4Doc.h"

#include <propkey.h>
#include <cmath>
#include <queue>
#include <locale.h>
#include <time.h>
#include<string>
#include"app4View.h"
#include"MainFrm.h"

#define CLIP(x) ((x>255 )? 255 : (x<0 ? 0 : x))

using namespace std;

struct Pair
{
	int x;
	int y;
	double v;
	Pair(int x1, int y1) {
		x = x1;
		y = y1;
	}
	Pair(int x1, int y1, int v1) {
		x = x1;
		y = y1;
		v = v1;
	}
};

bool compare(Pair a, Pair b) { return a.v < b.v; }

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Capp4Doc

IMPLEMENT_DYNCREATE(Capp4Doc, CDocument)

BEGIN_MESSAGE_MAP(Capp4Doc, CDocument)
	ON_COMMAND(ID_bright, &Capp4Doc::Onbright)
	ON_UPDATE_COMMAND_UI(ID_bright, &Capp4Doc::OnUpdatebright)
	ON_COMMAND(ID_brightless, &Capp4Doc::Onbrightless)
	ON_UPDATE_COMMAND_UI(ID_brightless, &Capp4Doc::OnUpdatebrightless)
	ON_COMMAND(ID_paint_line, &Capp4Doc::Onpaintline)
	ON_UPDATE_COMMAND_UI(ID_paint_line, &Capp4Doc::OnUpdatepaintline)
	ON_COMMAND(ID_paint_segment, &Capp4Doc::Onpaintsegment)
	ON_UPDATE_COMMAND_UI(ID_paint_segment, &Capp4Doc::OnUpdatepaintsegment)
	ON_COMMAND(ID_BUTTON12, &Capp4Doc::OnButton12)
	ON_UPDATE_COMMAND_UI(ID_BUTTON12, &Capp4Doc::OnUpdateButton12)
	ON_COMMAND(ID_BUTTON13, &Capp4Doc::OnButton13)
	ON_UPDATE_COMMAND_UI(ID_BUTTON13, &Capp4Doc::OnUpdateButton13)
	ON_COMMAND(ID_BUTTON14, &Capp4Doc::OnButton14)
	ON_UPDATE_COMMAND_UI(ID_BUTTON14, &Capp4Doc::OnUpdateButton14)
	ON_COMMAND(ID_BUTTON15, &Capp4Doc::OnButton15)
	ON_UPDATE_COMMAND_UI(ID_BUTTON15, &Capp4Doc::OnUpdateButton15)
	ON_COMMAND(ID_BUTTON16, &Capp4Doc::OnButton16)
	ON_UPDATE_COMMAND_UI(ID_BUTTON16, &Capp4Doc::OnUpdateButton16)
	ON_COMMAND(ID_SAVE_R, &Capp4Doc::OnSaveR)
	ON_COMMAND(ID_SAVE_G, &Capp4Doc::OnSaveG)
	ON_COMMAND(ID_SAVE_B, &Capp4Doc::OnSaveB)
	ON_COMMAND(ID_SAVE_ONFILE, &Capp4Doc::OnSaveOnfile)
	ON_COMMAND(ID_BINARY_CHECK, &Capp4Doc::OnBinaryCheck)
	ON_UPDATE_COMMAND_UI(ID_BINARY_CHECK, &Capp4Doc::OnUpdateBinaryCheck)
END_MESSAGE_MAP()


// Capp4Doc 생성/소멸

Capp4Doc::Capp4Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

Capp4Doc::~Capp4Doc()
{
}

BOOL Capp4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}


// Capp4Doc serialization

void Capp4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void Capp4Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void Capp4Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void Capp4Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Capp4Doc 진단

#ifdef _DEBUG
void Capp4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Capp4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Capp4Doc 명령


BOOL Capp4Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CFile File;
	m_file_path = lpszPathName;
	File.Open(m_file_path, CFile::modeRead | CFile::typeBinary);
	File.Read(&m_file_header, sizeof(BITMAPFILEHEADER));
	if (m_file_header.bfType != 0x4D42) {
		File.Close();
		return false;
	}
	File.Read(&m_info_header, sizeof(BITMAPINFOHEADER));
	
	m_channels = m_info_header.biBitCount / 8;
	m_height = abs(m_info_header.biHeight);
	m_width = m_info_header.biWidth;
	m_step = (m_width*m_channels + 3)&~3;
	m_imagedata_size = m_height * m_step;
	free(m_imagedata);
	free(m_imagedata_temp);
	m_imagedata = new BYTE[m_imagedata_size];
	m_imagedata_temp = new BYTE[m_imagedata_size];

	File.Read(m_imagedata, m_imagedata_size);

	File.Close();
	m_bright = 0;
	m_brightless = 0;

	//////////////////////////////////
	HANDLE handle = ::LoadImage(AfxGetInstanceHandle(), lpszPathName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADMAP3DCOLORS);
	if (!handle) {
		return false;
	}
	m_Cbitmap.DeleteObject();
	m_Cbitmap.Attach((HBITMAP)handle);
	m_Cbitmap.GetBitmap(&m_bmpinfo);
	HANDLE handle2 = ::LoadImage(AfxGetInstanceHandle(), lpszPathName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADMAP3DCOLORS);
	if (!handle2) {
		return false;
	}
	m_Cbitmap_ori.DeleteObject();
	m_Cbitmap_ori.Attach((HBITMAP)handle2);
	m_Cbitmap_ori.GetBitmap(&m_bmpinfo);
	//////////////////////////////////

	m_state = 0;
	m_bright = 0;
	m_brightless = 1;
	m_vector_index = 1;
	m_thickness = 5;
	m_gamma = 1.0;
	m_binary = 127;
	m_edge = 0;
	m_brush_check = false;
	m_gamma_check = false;
	m_binary_check = false;
	m_messageBox = false;
	return TRUE;
}


void Capp4Doc::Filter_avg() {
	int array_size = 3;
	double array[3][3] = {
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};
	double sum = 0;
	for (int i = 0; i < array_size; i++) {
		for (int j = 0; j < array_size; j++) {
			sum += array[i][j];
		}
	}
	memcpy(m_imagedata_temp, m_imagedata, m_imagedata_size);
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			double count_temp = 0;
			double sum_temp_r = 0;
			double sum_temp_g = 0;
			double sum_temp_b = 0;
			for (int m = 0; m < array_size; m++) {
				for (int n = 0; n < array_size; n++) {
					if ((m == 0 && i == 0) || (n == 0 && j == 0) || (m == 2 && i == m_height - 1) || (n == 2 && j == m_width - 1)) continue;
					count_temp+=array[m][n];
					sum_temp_r += array[m][n] * m_imagedata[((i+m-1)*m_step + (j+n-1) * m_channels) + 2];
					sum_temp_g += array[m][n] * m_imagedata[((i+m-1)*m_step + (j+n-1) * m_channels) + 1];
					sum_temp_b += array[m][n] * m_imagedata[((i+m-1)*m_step + (j+n-1) * m_channels) + 0];
				}
			}
			m_imagedata_temp[i*m_step + j * m_channels + 2] = CLIP( sum_temp_r / count_temp);
			m_imagedata_temp[i*m_step + j * m_channels + 1] = CLIP( sum_temp_g / count_temp);
			m_imagedata_temp[i*m_step + j * m_channels + 0] = CLIP( sum_temp_b / count_temp);
		}
	}
	memcpy(m_imagedata, m_imagedata_temp, m_imagedata_size);
	return;
}


void Capp4Doc::Filter_auto_contrast()
{
	int min_value = 255;
	int max_value = 0;
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			for (int k = 0; k < 3; k++) {
				min_value = min(min_value, m_imagedata[i*m_step + j*m_channels + k]);
				max_value = max(max_value, m_imagedata[i*m_step + j*m_channels + k]);
			}
		}
	}
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			for (int k = 0; k < 3; k++) {
				m_imagedata[i*m_step + j*m_channels + k] = ((((double)(m_imagedata[i*m_step + j*m_channels + k] - min_value)) / (max_value - min_value)) * 255);
			}
		}
	}
	return;
}


void Capp4Doc::Filter_bright()
{
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++){
			for (int k = 0; k < 3; k++) {
				m_imagedata[i*m_step + j*m_channels + k] = CLIP(m_imagedata[i*m_step + j*m_channels + k] + m_bright);
			}
		}
	}
	return;
}

void Capp4Doc::Filter_brightless()
{
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			for (int k = 0; k < 3; k++) {
				m_imagedata[i*m_step + j*m_channels + k] = CLIP((m_imagedata[i*m_step + j*m_channels + k] - (m_bright_check==true ? m_bright:0))*m_brightless);
			}
		}
	}
	return;
}

void Capp4Doc::Filter_gamma()
{
	BYTE arrPow[255];
	for (int i = 0; i < 255; i++) {
		arrPow[i] = (BYTE)(pow(i / 255.0, m_gamma) * 255 + 0.5);
	}
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			for (int k = 0; k < 3; k++) {
				m_imagedata[i*m_step + j*m_channels + k] = arrPow[m_imagedata[i*m_step + j*m_channels + k]];
			}
		}
	}
	return;
}

void Capp4Doc::Filter_histogram()
{
	int image_size = m_width * m_height;
	int histogram_gray[256] = { 0 };
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			histogram_gray[(int)(
				(m_imagedata[i*m_step + j*m_channels + 0] * 114 +
					m_imagedata[i*m_step + j*m_channels + 1] * 578 +
					m_imagedata[i*m_step + j*m_channels + 2] * 308) / 1000)]++;
		}
	}
	for (int i = 1; i < 256; i++) {
		histogram_gray[i] = histogram_gray[i] + histogram_gray[i - 1];
	}
	for (int i = 0; i < 256; i++) {
		histogram_gray[i] = (BYTE)(histogram_gray[i] * 255 / image_size + 0.5);
	}
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			int index = i*m_step + j*m_channels;
			int gray_value = (int)((m_imagedata[index + 0] * 114 + m_imagedata[index + 1] * 578 + m_imagedata[index + 2] * 308) / 1000);
			int v = histogram_gray[gray_value] - gray_value;
			m_imagedata[index + 0] = CLIP(m_imagedata[index + 0] + v);
			m_imagedata[index + 1] = CLIP(m_imagedata[index + 1] + v);
			m_imagedata[index + 2] = CLIP(m_imagedata[index + 2] + v);
		}
	}
}

void Capp4Doc::Filter_sharpening()
{
	int array_size = 3;
	double array[3][3] = {
		{ -1,-1,-1 },
		{ -1, 8,-1 },
		{ -1,-1,-1 }
	};
	double sum = 9.0;
	memcpy(m_imagedata_temp, m_imagedata, m_imagedata_size);
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			double count_temp = 0;
			double sum_temp_r = 0;
			double sum_temp_g = 0;
			double sum_temp_b = 0;
			for (int m = 0; m < array_size; m++) {
				for (int n = 0; n < array_size; n++) {
					if ((m == 0 && i == 0) || (n == 0 && j == 0) || (m == 2 && i == m_height - 1) || (n == 2 && j == m_width - 1)) continue;
					count_temp += array[m][n];
					sum_temp_r += array[m][n] * m_imagedata[((i + m - 1)*m_step + (j + n - 1) * m_channels) + 2];
					sum_temp_g += array[m][n] * m_imagedata[((i + m - 1)*m_step + (j + n - 1) * m_channels) + 1];
					sum_temp_b += array[m][n] * m_imagedata[((i + m - 1)*m_step + (j + n - 1) * m_channels) + 0];
				}
			}
			m_imagedata_temp[i*m_step + j * m_channels + 2] = CLIP(sum_temp_r / count_temp);
			m_imagedata_temp[i*m_step + j * m_channels + 1] = CLIP(sum_temp_g / count_temp);
			m_imagedata_temp[i*m_step + j * m_channels + 0] = CLIP(sum_temp_b / count_temp);
		}
	}
	memcpy(m_imagedata, m_imagedata_temp, m_imagedata_size);
	return;
}

void Capp4Doc::Filter_binary()
{
	int index;
	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			index = i*m_step + j*m_channels;
			int gray_value = (int)((m_imagedata[index + 0] * 114 + m_imagedata[index + 1] * 578 + m_imagedata[index + 2] * 308) / 1000);
			if (gray_value>m_binary) {
				m_imagedata[index + 0] = 255;
				m_imagedata[index + 1] = 255;
				m_imagedata[index + 2] = 255;
			}
			else {
				m_imagedata[index + 0] = 0;
				m_imagedata[index + 1] = 0;
				m_imagedata[index + 2] = 0;
			}
		}
	}
	return;
}

void Capp4Doc::Filter_median()
{
	int index;
	int size;
	int i, j, n, m, k;
	double temp;
	vector<Pair> v;
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			size = 0;
			v.clear();
			for (n = -1; n < 2; n++) {
				for (m = -1; m < 2; m++) {
					if (i + n < 0 || i + n >= m_height || j + m < 0 || j + m >= m_width)continue;
					size++;
					index = (i + n)*m_step + (j + m)*m_channels;
					temp = (m_imagedata[index + 0]*114 + m_imagedata[index + 1]*578 + m_imagedata[index + 2]*308)/1000;
					v.push_back(Pair(i+n,j+m,temp));
				}
			}
			sort(v.begin(), v.end(), compare);
			n = v[size / 2].x;
			m = v[size / 2].y;
			m_imagedata_temp[i*m_step + j*m_channels + 0] = m_imagedata[n*m_step + m*m_channels + 0];
			m_imagedata_temp[i*m_step + j*m_channels + 1] = m_imagedata[n*m_step + m*m_channels + 1];
			m_imagedata_temp[i*m_step + j*m_channels + 2] = m_imagedata[n*m_step + m*m_channels + 2];
		}
	}
	memcpy(m_imagedata, m_imagedata_temp, m_imagedata_size);
	return;
}

void Capp4Doc::Filter_edge()
{
	int mask[10][3][3] = {
		//0
		{{ 1, 1, 1},
		{ 0, 0, 0},
		{-1,-1,-1}},
		//1
		{ { 1, 0, -1 },
		{ 1, 0, -1 },
		{ 1, 0, -1 } },
		//2
		{ { 1, 2, 1 },
		{ 0, 0, 0 },
		{ -1,-2,-1 } },
		//3
		{ { 1, 0,-1 },
		{ 2, 0, -2 },
		{ 1, 0,-1 } },
		//4
		{ { 1, 0, 0 },
		{ 0, 0, 0 },
		{ 0, 0,-1 } },
		//5
		{ { 0, 0, 1 },
		{ 0, 0, 0 },
		{ -1, 0, 0 } },
		//6
		{ { 0, 1, 0 },
		{ 1, -4, 1 },
		{  0, 1, 0 } },
		//7
		{ { 1, 1, 1 },
		{ 1, -8, 1 },
		{  1, 1, 1 } },
		//8
		{ { 0, -1, 0 },
		{ -1, 5, -1 },
		{ 0,-1, 0 } },
		//9
		{ { -1, -1, -1},
		{ -1, 9, -1 },
		{ -1,-1, -1 } }
	};
	int i, j, n, m;
	int size, index1,index2;
	int sum1,sum2;
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			size = 0;
			index1 = i*m_step + j*m_channels;
			sum1 = (int)((m_imagedata[index1 + 0]*114 + m_imagedata[index1 + 1]*578 + m_imagedata[index1 + 2]*308)/1000);
			sum2 = 0;
			for (n = -1; n < 2; n++) {
				for (m = -1; m < 2; m++) {
					if ((i + n) < 0 || (i + n) >= m_height || (j + m) < 0 || (j + m) >= m_width)continue;
					index2 = (i + n)*m_step + (j + m)*m_channels;
					sum2 += (int)((m_imagedata[index2 + 0]*114 + m_imagedata[index2 + 1]*578 + m_imagedata[index2 + 2]*308) / 1000) * (mask[m_edge][n+1][m+1]);
				}
			}
			sum2 -= sum1;
			m_imagedata_temp[index1 + 0] = CLIP(m_imagedata[index1 + 0] + sum2);
			m_imagedata_temp[index1 + 1] = CLIP(m_imagedata[index1 + 1] + sum2);
			m_imagedata_temp[index1 + 2] = CLIP(m_imagedata[index1 + 2] + sum2);
		}
	}
	memcpy(m_imagedata, m_imagedata_temp, m_imagedata_size);
}

void Capp4Doc::Defect_inspection()
{
	Capp4View* pView = (Capp4View*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
	
	int i, j, n, m;
	int index;
	double sum = 0;
	double sum_temp = 0;
	double avg = 0;
	double sdev = 0;
	int size = m_height * m_width;
	int** ar = new int*[m_height];
	bool** ar_bool = new bool*[m_height];
	for (i = 0; i < m_height; i++) {
		ar[i] = new int[m_width];
		ar_bool[i] = new bool[m_width];
		ZeroMemory(ar_bool[i], m_width * sizeof(bool));
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			index = i*m_step + j*m_channels;
			ar[i][j] = (m_imagedata[index + 0] + m_imagedata[index + 1] + m_imagedata[index + 2]) / 3;
			if (j != 0 && (abs(ar[i][j] - ar[i][j - 1]) > 40)) {
				if (ar_bool[i][j] == false) {
					pView->point_x1[pView->index] = j - 15;
					pView->point_y1[pView->index] = i - 15;
					pView->point_x2[pView->index] = j + 15;
					pView->point_y2[pView->index] = i + 15;
					pView->index++;
				}
				if (ar_bool[i][j] == true)continue;
				for (n = -15; n <= 15; n++) {
					for (m = -15; m <= 15; m++) {
						if (i + n < 0 || i + n >= m_height || j + m < 0 || j + m >= m_width)continue;
						ar_bool[i + n][j + m] = true;
					}
				}
			}
		}
	}
	for (i = 0; i < m_height; i++) {
		free(ar[i]);
		free(ar_bool[i]);
	}
	free(ar);
	free(ar_bool);
	//for (i = 0; i < m_height; i += 24) {
	//	for (j = 0; j < m_width; j += 24) {
	//		//평균
	//		sum = 0;
	//		size = 0;
	//		for (n = 0; n <= 96; n++) {
	//			for (m = 0; m <= 96; m++) {
	//				if (i + n >= m_height || j + m >= m_width)continue;
	//				size++;
	//				sum += ar[i+n][j+m];
	//			}
	//		}
	//		avg = sum / size;
	//		//표준편차
	//		sdev = 0;
	//		for (n = 0; n <= 96; n++) {
	//			for (m = 0; m <= 96; m++) {
	//				if (i + n >= m_height || j + m >= m_width)continue;
	//				sdev += pow(ar[i + n][j + m]-avg, 2.0);
	//			}
	//		}
	//		sdev /= size;
	//		sdev = sqrt(sdev);

	//		for (n = 0; n < 96; n += 3) {
	//			for (m = 0; m < 96; m += 3) {
	//				sum_temp = 0;
	//				size = 0;
	//				for (int x = 0; x <  3; x++) {
	//					for (int y = 0; y < 3; y++) {
	//						if (i + n + x >= m_height || j + m + y >= m_width)continue;
	//						size++;
	//						sum_temp += ar[i + n + x][j + m + y];
	//					}
	//				}
	//				sum_temp /= size;
	//				if (sum_temp < avg - sdev || sum_temp > avg + sdev) {
	//					v.push_back(Pair(i+n+1,j+m+1));
	//				}
	//			}
	//		}
	//	}
	//}
	/*for(Point temp : v){
		TRACE("x : %d, y : %d\n",temp.y, temp.x);
	}*/
	if (m_messageBox==false && pView->index != 0) {
		AfxMessageBox(L"defect 감지");
		m_messageBox=true;
		TRACE("path : %s\n", m_file_path);
		TRACE("length : %d\n", m_file_path.GetLength());
		
		//CFile File;
		//int index = 0;
		//for (int i = m_file_path.GetLength() - 1; i >= 0; i--) {
		//	if (m_file_path[i] == '\\') {
		//		index = i;
		//		break;
		//	}
		//}
		//File.Open(m_file_path.Left(index) + "\\log.csv", CFile::modeWrite | CFile::modeCreate);
		//char buf[20] = { NULL };
		//
		//for (int i = 0; i < pView->index; i++) {
		//	ZeroMemory(buf, 20);
		//	sprintf_s(buf,"%d, %d \r\n",pView->point_x1[i]+15,pView->point_y1[i]+15);
		//	/*TRACE("%s\n", m_file_path);*/
		//	File.Write(buf, 20);
		//}
		//File.Close();
		int index = 0;
		for (int i = m_file_path.GetLength() - 1; i >= 0; i--) {
			if (m_file_path[i] == '\\') {
				index = i;
				break;
			}
		}
		FILE* fp;
		char* char_str;
		time_t timer;
		struct tm* t;
		timer = time(NULL);
		t = NULL;
		localtime_s(t,&timer);
		string s;
		CString cs;

		/*s += to_string(t->tm_year + 1900);
		s += " ";
		s += to_string(t->tm_mon + 1);
		s += " ";
		s += to_string(t->tm_mday);

		cs += to_string(t->tm_year + 1900);
		cs += " ";
		cs += to_string(t->tm_mon + 1);
		cs += " ";
		cs += to_string(t->tm_mday);*/

		fopen_s(&fp, m_file_path.Left(index) + "\\log.csv", "w+");
		_wsetlocale(LC_ALL, L"korean");
		for (int i = 0; i < pView->index; i++) {
			fwprintf(fp, _T("%s, %d, %d,\n"),m_file_path, pView->point_x1[i] + 15, pView->point_y1[i] + 15);
		}
		
		fclose(fp);
		fp = NULL;
	}
}

//void Capp4Doc::MyFloodFill(int x, int y, BYTE nr, BYTE ng, BYTE nb)
//{
//	int dx[8] = {-1,0,1,1,1,0,-1,-1};
//	int dy[8] = {1,1,1,0,-1,-1,-1,0};
//	BOOL* check = new BOOL[m_imagedata_size];
//	ZeroMemory(check, m_imagedata_size * sizeof(BOOL));
//	queue<Pair> q;
//	q.push(Pair(x, y));
//	BYTE r, g, b;
//	r = m_imagedata[(m_height - y - 1)*m_step + x*m_channels + 2];
//	g = m_imagedata[(m_height - y - 1)*m_step + x*m_channels + 1];
//	b = m_imagedata[(m_height - y - 1)*m_step + x*m_channels + 0];
//	while (!q.empty()) {
//		Pair p = q.front();
//		q.pop();
//		for (int i = 0; i < 8; i++) {
//			int nx = p.x + dx[i];
//			int ny = p.y + dy[i];
//			int index = (m_height - ny - 1)*m_step + nx*m_channels;
//			if (nx<0 || ny<0 || nx>=m_width || ny>=m_height)continue;
//			if (check[index + 0] == true && check[index + 1] == true && check[index + 2] == true) {
//				continue;
//			}
//			if (m_imagedata[index + 0] == b && m_imagedata[index + 1] == g && m_imagedata[index + 2] == r) {
//				m_imagedata[index + 0] = nb;
//				m_imagedata[index + 1] = ng;
//				m_imagedata[index + 2] = nr;
//				check[index + 0] = true;
//				check[index + 1] = true;
//				check[index + 2] = true;
//				q.push(Pair(nx,ny));
//			}
//		}
//	}
//	free(check);
//}

COLORREF Capp4Doc::GetRGB(int x, int y)
{
	BYTE r, g, b;
	r = m_imagedata[(m_height - y - 1)*m_step + x*m_channels + 2];
	g = m_imagedata[(m_height - y - 1)*m_step + x*m_channels + 1];
	b = m_imagedata[(m_height - y - 1)*m_step + x*m_channels + 0];
	return RGB(r,g,b);
}


void Capp4Doc::Onbright()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_bright_check = !m_bright_check;
	UpdateAllViews(NULL);
}


void Capp4Doc::OnUpdatebright(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_bright_check);
}


void Capp4Doc::Onbrightless()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_brightless_check = !m_brightless_check;
	UpdateAllViews(NULL);
}


void Capp4Doc::OnUpdatebrightless(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_brightless_check);
}


void Capp4Doc::Onpaintline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state==1? 0 : 1;
}


void Capp4Doc::OnUpdatepaintline(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 1) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::Onpaintsegment()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state==2? 0 : 2;
}


void Capp4Doc::OnUpdatepaintsegment(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 2) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::OnButton12()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state == 3 ? 0 : 3;
}


void Capp4Doc::OnUpdateButton12(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 3) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::OnButton13()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state == 4 ? 0 : 4;
}


void Capp4Doc::OnUpdateButton13(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 4) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::OnButton14()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state == 5 ? 0 : 5;
	if (m_state == 5) {
		Capp4View* pView = (Capp4View*)((CMainFrame*)AfxGetMainWnd())->GetActiveView();
		pView->Poly_start.x = -1;
		pView->Poly_start.y = -1;
		pView->Poly_temp.x = -1;
		pView->Poly_temp.y = -1;
	}
}


void Capp4Doc::OnUpdateButton14(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 5) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::OnButton15()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state == 6 ? 0 : 6;
}


void Capp4Doc::OnUpdateButton15(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 6) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::OnButton16()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = m_state == 7 ? 0 : 7;
}


void Capp4Doc::OnUpdateButton16(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 7) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::OnSaveR()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(L"R");
	if (m_file_path == "")return;
	CFile File;
	int index = 0;
	for (int i = m_file_path.GetLength() - 1; i >= 0; i--) {
		if (m_file_path[i] == '.') {
			index = i;
			break;
		}
	}
	CString filename = m_file_path.Mid(index);
	File.Open(m_file_path.Left(index) + "_r" + filename, CFile::modeWrite | CFile::modeCreate);
	File.Write(&m_file_header, sizeof(BITMAPFILEHEADER));
	File.Write(&m_info_header, sizeof(BITMAPINFOHEADER));

	BITMAPINFO info_header;
	info_header.bmiHeader = m_info_header;
	HDC dc = GetDC(NULL);
	GetDIBits(dc, m_Cbitmap, 0, m_height, m_imagedata, &info_header, DIB_RGB_COLORS);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_imagedata[(i*m_step + j * m_channels) + 0] = 0;
			m_imagedata[(i*m_step + j * m_channels) + 1] = 0;
		}
	}

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	File.Write(m_imagedata, m_imagedata_size);
	File.Close();
	return;
}


void Capp4Doc::OnSaveG()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(L"G");
	if (m_file_path == "")return;
	CFile File;
	int index = 0;
	for (int i = m_file_path.GetLength() - 1; i >= 0; i--) {
		if (m_file_path[i] == '.') {
			index = i;
			break;
		}
	}
	CString filename = m_file_path.Mid(index);
	File.Open(m_file_path.Left(index) + "_g" + filename, CFile::modeWrite | CFile::modeCreate);
	File.Write(&m_file_header, sizeof(BITMAPFILEHEADER));
	File.Write(&m_info_header, sizeof(BITMAPINFOHEADER));

	BITMAPINFO info_header;
	info_header.bmiHeader = m_info_header;
	HDC dc = GetDC(NULL);
	GetDIBits(dc, m_Cbitmap, 0, m_height, m_imagedata, &info_header, DIB_RGB_COLORS);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_imagedata[(i*m_step + j * m_channels) + 0] = 0;
			m_imagedata[(i*m_step + j * m_channels) + 2] = 0;
		}
	}

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	File.Write(m_imagedata, m_imagedata_size);
	File.Close();
	return;
}


void Capp4Doc::OnSaveB()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(L"B");
	if (m_file_path == "")return;
	CFile File;
	int index = 0;
	for (int i = m_file_path.GetLength() - 1; i >= 0; i--) {
		if (m_file_path[i] == '.') {
			index = i;
			break;
		}
	}
	CString filename = m_file_path.Mid(index);
	File.Open(m_file_path.Left(index) + "_b" + filename, CFile::modeWrite | CFile::modeCreate);
	File.Write(&m_file_header, sizeof(BITMAPFILEHEADER));
	File.Write(&m_info_header, sizeof(BITMAPINFOHEADER));

	BITMAPINFO info_header;
	info_header.bmiHeader = m_info_header;
	HDC dc = GetDC(NULL);
	GetDIBits(dc, m_Cbitmap, 0, m_height, m_imagedata, &info_header, DIB_RGB_COLORS);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_imagedata[(i*m_step + j * m_channels) + 2] = 0;
			m_imagedata[(i*m_step + j * m_channels) + 1] = 0;
		}
	}

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	File.Write(m_imagedata, m_imagedata_size);
	File.Close();
	return;
}


void Capp4Doc::OnSaveOnfile()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	//AfxMessageBox(L"ALL");
	if (m_file_path == "")return;
	CFile File;
	File.Open(m_file_path, CFile::modeWrite | CFile::modeCreate);
	File.Write(&m_file_header, sizeof(BITMAPFILEHEADER));
	File.Write(&m_info_header, sizeof(BITMAPINFOHEADER));

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	BITMAPINFO info_header;
	info_header.bmiHeader = m_info_header;
	HDC dc = GetDC(NULL);
	GetDIBits(dc, m_Cbitmap, 0, m_height, m_imagedata, &info_header, DIB_RGB_COLORS);
	File.Write(m_imagedata, m_imagedata_size);

	File.Close();
	return;
}



void Capp4Doc::OnBinaryCheck()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_binary_check = !m_binary_check;
	UpdateAllViews(NULL);
}


void Capp4Doc::OnUpdateBinaryCheck(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_binary_check);
}
