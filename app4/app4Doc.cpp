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

// app4Doc.cpp : Capp4Doc Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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


// Capp4Doc ����/�Ҹ�

Capp4Doc::Capp4Doc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

Capp4Doc::~Capp4Doc()
{
}

BOOL Capp4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// Capp4Doc serialization

void Capp4Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void Capp4Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
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

// �˻� ó���⸦ �����մϴ�.
void Capp4Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
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

// Capp4Doc ����

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


// Capp4Doc ���


BOOL Capp4Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_filter_check[0] = !m_filter_check[0];
	Filter();
}


void Capp4Doc::OnUpdateavgfilter(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_filter_check[0]);
}


void Capp4Doc::Onautocontrast()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_filter_check[1] = !m_filter_check[1];
	Filter();
}


void Capp4Doc::OnUpdateautocontrast(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_filter_check[1]);
}


void Capp4Doc::Onbright()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_filter_check[2] = !m_filter_check[2];
	Filter();
}


void Capp4Doc::OnUpdatebright(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_filter_check[2]);
}


void Capp4Doc::Onbrightless()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_filter_check[3] = !m_filter_check[3];
	Filter();
}


void Capp4Doc::OnUpdatebrightless(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_filter_check[3]);
}


void Capp4Doc::Onpaintline()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_state = 1;
}


void Capp4Doc::OnUpdatepaintline(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	if (m_state == 1) {
		pCmdUI->SetCheck(true);
	}
	else {
		pCmdUI->SetCheck(false);
	}
}


void Capp4Doc::Onpaintsegment()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_state = 2;
}


void Capp4Doc::OnUpdatepaintsegment(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	m_filter_check[5] = !m_filter_check[5];
	Filter();
}


void Capp4Doc::OnUpdateCheck2(CCmdUI *pCmdUI)
{
	// TODO: ���⿡ ��� ������Ʈ UI ó���� �ڵ带 �߰��մϴ�.
	pCmdUI->SetCheck(m_filter_check[5]);
}
