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

#define CLIP(x) ((x>255 )? 255 : (x<0 ? 0 : x))

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Capp4Doc

IMPLEMENT_DYNCREATE(Capp4Doc, CDocument)

BEGIN_MESSAGE_MAP(Capp4Doc, CDocument)
	ON_COMMAND(ID_BUTTON3, &Capp4Doc::OnButtonR)
	ON_COMMAND(ID_BUTTON4, &Capp4Doc::OnButtonG)
	ON_COMMAND(ID_BUTTON5, &Capp4Doc::OnButtonB)
	ON_COMMAND(ID_BUTTON6, &Capp4Doc::OnButtonSave)
	ON_COMMAND(ID_avg_filter, &Capp4Doc::Onavgfilter)
	ON_UPDATE_COMMAND_UI(ID_avg_filter, &Capp4Doc::OnUpdateavgfilter)
	ON_COMMAND(ID_auto_contrast, &Capp4Doc::Onautocontrast)
	ON_UPDATE_COMMAND_UI(ID_auto_contrast, &Capp4Doc::OnUpdateautocontrast)
	ON_COMMAND(ID_bright, &Capp4Doc::Onbright)
	ON_UPDATE_COMMAND_UI(ID_bright, &Capp4Doc::OnUpdatebright)
	ON_COMMAND(ID_brightless, &Capp4Doc::Onbrightless)
	ON_UPDATE_COMMAND_UI(ID_brightless, &Capp4Doc::OnUpdatebrightless)
	ON_COMMAND(ID_paint_line, &Capp4Doc::Onpaintline)
	ON_UPDATE_COMMAND_UI(ID_paint_line, &Capp4Doc::OnUpdatepaintline)
	ON_COMMAND(ID_paint_segment, &Capp4Doc::Onpaintsegment)
	ON_UPDATE_COMMAND_UI(ID_paint_segment, &Capp4Doc::OnUpdatepaintsegment)
	ON_COMMAND(ID_CHECK2, &Capp4Doc::OnCheck2)
	ON_UPDATE_COMMAND_UI(ID_CHECK2, &Capp4Doc::OnUpdateCheck2)
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
	m_size = File.GetLength();
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
	m_imagedata = new BYTE[m_imagedata_size];
	m_imagedata_temp = new BYTE[m_imagedata_size];
	int r;
	for (r = m_height - 1; r >= 0; r--) {
		File.Read(&m_imagedata[r*m_step], m_step);
	}

	m_imagedata_ori = new BYTE[m_imagedata_size];
	memcpy(m_imagedata_ori, m_imagedata, m_imagedata_size);
	File.Close();
	for (int i = 0; i < m_filter_size; i++) {
		m_filter_check[i] = false;
	}
	m_bright = 0;
	m_brightless = 0;

	return TRUE;
}


BOOL Capp4Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (m_file_path == "")return false;
	CFile File;
	CFileDialog SaveDlg(FALSE, _T("BMP"), NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeWrite | CFile::modeCreate);
		File.Write(&m_file_header, sizeof(BITMAPFILEHEADER));
		File.Write(&m_info_header, sizeof(BITMAPINFOHEADER));
		
		if (m_channels == 1) {
			for (int i = 0; i < 256; i++) {
				RGBQUAD GrayPalette = { i,i,i,0 };
				File.Write(&GrayPalette, sizeof(RGBQUAD));
			}
		}

		int r;
		for (r = m_height - 1; r >= 0; r--) {
			File.Write(&m_imagedata[r*m_step], m_step);
		}
		File.Close();
	}

	return TRUE;
}


void Capp4Doc::OnButtonR()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	memcpy(m_imagedata_temp, m_imagedata_ori, m_imagedata_size);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_imagedata_temp[(i*m_step + j * m_channels) + 0] = 0;
			m_imagedata_temp[(i*m_step + j * m_channels) + 1] = 0;
		}
	}

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	int r;
	for (r = m_height - 1; r >= 0; r--) {
		File.Write(&m_imagedata_temp[r*m_step], m_step);
	}
	File.Close();
	return;
}


void Capp4Doc::OnButtonG()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	memcpy(m_imagedata_temp, m_imagedata_ori, m_imagedata_size);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_imagedata_temp[(i*m_step + j * m_channels) + 0] = 0;
			m_imagedata_temp[(i*m_step + j * m_channels) + 2] = 0;
		}
	}

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	int r;
	for (r = m_height - 1; r >= 0; r--) {
		File.Write(&m_imagedata_temp[r*m_step], m_step);
	}
	File.Close();
	return;
}


void Capp4Doc::OnButtonB()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	memcpy(m_imagedata_temp, m_imagedata_ori, m_imagedata_size);

	for (int i = 0; i < m_height; i++) {
		for (int j = 0; j < m_width; j++) {
			m_imagedata_temp[(i*m_step + j * m_channels) + 1] = 0;
			m_imagedata_temp[(i*m_step + j * m_channels) + 2] = 0;
		}
	}

	if (m_channels == 1) {
		for (int i = 0; i < 256; i++) {
			RGBQUAD GrayPalette = { i,i,i,0 };
			File.Write(&GrayPalette, sizeof(RGBQUAD));
		}
	}

	int r;
	for (r = m_height - 1; r >= 0; r--) {
		File.Write(&m_imagedata_temp[r*m_step], m_step);
	}
	File.Close();
	return;
}


void Capp4Doc::OnButtonSave()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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

	int r;
	for (r = m_height - 1; r >= 0; r--) {
		File.Write(&m_imagedata[r*m_step], m_step);
	}
	File.Close();
	return;
}

void Capp4Doc::Filter() {
	if (m_file_path == "")return;
	memcpy(m_imagedata, m_imagedata_ori, m_imagedata_size);
	
	if (m_filter_check[0]) {
		Filter_avg();
		memcpy(m_imagedata, m_imagedata_temp, m_imagedata_size);
	}
	if (m_filter_check[1]) {
		Filter_auto_contrast();
	}
	if (m_filter_check[2]) {
		Filter_bright();
	}
	if (m_filter_check[3]) {
		Filter_brightless();
	}
	if (m_filter_check[4]) {
		Filter_gamma();
	}
	if (m_filter_check[5]) {
		Filter_histogram();
	}


	UpdateAllViews(NULL);
	return;
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
					sum_temp_b += array[m][n] * m_imagedata[(i*m_step + j * m_channels) + 0];
				}
			}
			m_imagedata_temp[i*m_step + j * m_channels + 2] = CLIP( sum_temp_r / count_temp);
			m_imagedata_temp[i*m_step + j * m_channels + 1] = CLIP( sum_temp_g / count_temp);
			m_imagedata_temp[i*m_step + j * m_channels + 0] = CLIP( sum_temp_b / count_temp);
		}
	}
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
				m_imagedata[i*m_step + j*m_channels + k] = CLIP((m_imagedata[i*m_step + j*m_channels + k] - m_bright)*m_brightless);
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
			int gray_value = (int)((m_imagedata[index + 0] * 114 + m_imagedata[index + 1] * 578 + m_imagedata[index + 0] * 308) / 1000);
			int v = histogram_gray[gray_value] - gray_value;
			m_imagedata[index + 0] = CLIP(m_imagedata[index + 0] + v);
			m_imagedata[index + 1] = CLIP(m_imagedata[index + 1] + v);
			m_imagedata[index + 2] = CLIP(m_imagedata[index + 2] + v);
		}
	}
}

void Capp4Doc::Onavgfilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_filter_check[0] = !m_filter_check[0];
	Filter();
}


void Capp4Doc::OnUpdateavgfilter(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_filter_check[0]);
}


void Capp4Doc::Onautocontrast()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_filter_check[1] = !m_filter_check[1];
	Filter();
}


void Capp4Doc::OnUpdateautocontrast(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_filter_check[1]);
}


void Capp4Doc::Onbright()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_filter_check[2] = !m_filter_check[2];
	Filter();
}


void Capp4Doc::OnUpdatebright(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_filter_check[2]);
}


void Capp4Doc::Onbrightless()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_filter_check[3] = !m_filter_check[3];
	Filter();
}


void Capp4Doc::OnUpdatebrightless(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_filter_check[3]);
}


void Capp4Doc::Onpaintline()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_state = 1;
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
	m_state = 2;
}


void Capp4Doc::OnUpdatepaintsegment(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	if (m_state == 2) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
		m_line_x = -1;
		m_line_y = -1;
	}
}


void Capp4Doc::OnCheck2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_filter_check[5] = !m_filter_check[5];
	Filter();
}


void Capp4Doc::OnUpdateCheck2(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_filter_check[5]);
}
