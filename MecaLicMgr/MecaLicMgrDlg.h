
// MecaLicMgrDlg.h : ��� ����
//

#pragma once
#include "afxmenubutton.h"
#include "afxwin.h"
#include "ATLComTime.h"

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
	afx_msg void OnCbxApptype();
	afx_msg void OnButtReadAll();
	afx_msg void OnButtReadComp();
	afx_msg void OnButtReadUser();
	afx_msg void OnButtLicMake();
	afx_msg void OnButtLicRead();
	afx_msg void OnButtCompSaveAs();
	afx_msg void OnButtUserSaveAs();
	afx_msg void OnButtAllSave();
	afx_msg void OnButtAllSaveAs();
	afx_msg void OnUpdateMac1();
	afx_msg void OnButtCompSave();
private:
	BOOL check_ipv;
	CComboBox m_cApptype;
	CComboBox m_cVersion;
	CString m_strCbxApptype;
	CEdit m_EditCtrMac1;

	CString baseAddress;
	CString apptypeAddress;
	CString compDataAddress;
	CString userDataAddress;
	CString appVerAddresss;

	CString compCode;
	CString compRemarks;
	CString compMngCell;
	CString compMngEmail;
	CString compMngName;
	CString compName;
	CString compPhone;

	CString userDept;
	CString userName;
	CString userPhone;
	CString userCell;
	CString userEmail;
	COleDateTime userEnd;
	CString userRemarks;

	CString macAdd1;
	CString macAdd2;
	CString macAdd3;
	CString macAdd4;
	CString macAdd5;
	CString macAdd6;

	CString compNameOriginal;
	CString compCodeOriginal;
	CString compPhoneOriginal;
	CString compMngNameOriginal;
	CString compMngEmailOriginal;
	CString compMngCellOriginal;
	CString compRemarksOriginal;

	CString filePath;

	CString openOrSave(BOOL isOpen, CString address);
	CString getMacAdd(void);
	void printMacAdd(CString macAddress);
};
