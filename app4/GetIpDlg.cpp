// GetIpDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "app4.h"
#include "GetIpDlg.h"
#include "afxdialogex.h"


// GetIpDlg ��ȭ �����Դϴ�.

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


// GetIpDlg �޽��� ó�����Դϴ�.


void GetIpDlg::OnOK()
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	GetDlgItemText(IDC_IP_EDIT, m_ip);
	CDialogEx::OnOK();
}
