#pragma once


// GetIpDlg 대화 상자입니다.

class GetIpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GetIpDlg)
public:
	//변수
	CString m_ip;

public:
	GetIpDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GetIpDlg();
	CString GetIp() { return m_ip; }
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};
