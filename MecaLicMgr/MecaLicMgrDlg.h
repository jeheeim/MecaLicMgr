
// MecaLicMgrDlg.h : ��� ����
//

#pragma once
#include "afxmenubutton.h"
#include "afxwin.h"

// CMecaLicMgrDlg ��ȭ ����
class CMecaLicMgrDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMecaLicMgrDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MECALICMGR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtExit();
	afx_msg void OnClickIpv6();
private:
	BOOL check_ipv;
public:
	afx_msg void OnButtReadAll();
	afx_msg void OnButtReadComp();
	afx_msg void OnButtReadUser();
	afx_msg void OnButtLicMake();
	afx_msg void OnButtLicRead();
private:
//	CMFCMenuButton m_cApptype;
//	CSplitButton m_cApptype;
	CComboBox m_cApptype;
};
