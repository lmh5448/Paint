// GetIpDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "app4.h"
#include "GetIpDlg.h"
#include "afxdialogex.h"


// GetIpDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GetIpDlg, CDialogEx)

GetIpDlg::GetIpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

GetIpDlg::~GetIpDlg()
{
}

void GetIpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GetIpDlg, CDialogEx)
END_MESSAGE_MAP()


// GetIpDlg 메시지 처리기입니다.


void GetIpDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	GetDlgItemText(IDC_IP_EDIT, m_ip);
	CDialogEx::OnOK();
}
