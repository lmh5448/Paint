#pragma once


// GetIpDlg ��ȭ �����Դϴ�.

class GetIpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GetIpDlg)
public:
	//����
	CString m_ip;

public:
	GetIpDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GetIpDlg();
	CString GetIp() { return m_ip; }
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
