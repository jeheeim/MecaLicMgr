
// MecaLicMgrDlg.h : 헤더 파일
//

#pragma once
#include "afxmenubutton.h"
#include "afxwin.h"
#include "ATLComTime.h"

// CMecaLicMgrDlg 대화 상자
class CMecaLicMgrDlg : public CDialogEx
{
// 생성입니다.
public:
	CMecaLicMgrDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MECALICMGR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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
private:
	BOOL check_ipv;
	CComboBox m_cApptype;
	CComboBox m_cVersion;
	CString m_strCbxApptype;

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
	
	CString openOrSave(BOOL isOpen, CString address);
	CString getMacAdd(void);
	void printMacAdd(CString macAddress);
//	CButton idc_check_ipv;
public:
	afx_msg void OnButtAllSave();
	afx_msg void OnButtAllSaveAs();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnUpdateMac1();
private:
	CEdit m_EditCtrMac1;
};
