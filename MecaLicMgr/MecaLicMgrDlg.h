
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
	afx_msg void OnCbxApptype();

	afx_msg void OnButtReadAll();
	afx_msg void OnButtReadComp();
	afx_msg void OnButtReadUser();

	afx_msg void OnButtLicMake();
	afx_msg void OnButtLicRead();

	afx_msg void OnButtAllSaveAs();
	afx_msg void OnButtCompSaveAs();
	afx_msg void OnButtUserSaveAs();

	afx_msg void OnButtAllSave();
	afx_msg void OnButtCompSave();
	afx_msg void OnButtUserSave();

	afx_msg void OnUpdateMac1();
	afx_msg void OnUpdateMac2();
	afx_msg void OnUpdateMac3();
	afx_msg void OnUpdateMac4();
	afx_msg void OnUpdateMac5();
	afx_msg void OnUpdateMac6();

private:
	CComboBox m_cApptype;
	CComboBox m_cVersion;
	CString m_strCbxApptype;

	CString baseAddress;
	CString apptypeAddress;
	CString compDataAddress;
	CString userDataAddress;
	CString appVerAddresss;
	CString allDataAddress;

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
	CString userEndDate;
	COleDateTime userEnd;
	CString userRemarks;
	CString userMacAdd;

	CString macAdd1;
	CString macAdd2;
	CString macAdd3;
	CString macAdd4;
	CString macAdd5;
	CString macAdd6;

	CString * macAdd[6];

	CEdit m_EditCtrMac1;
	CEdit m_EditCtrMac2;
	CEdit m_EditCtrMac3;
	CEdit m_EditCtrMac4;
	CEdit m_EditCtrMac5;
	CEdit m_EditCtrMac6;

	CEdit * macAddCtrl[6];

	CString compFilePathOriginal;
	CString userFilePathOriginal;
	CString allFilePathOriginal;

	CString * data[15];
	CString originalData[15];

	CString openOrSaveDlg(BOOL isOpen, CString address);
	CString getMacAdd(void);
	void printMacAdd(CString macAddress);
	void saving(int saveType, CString *writeStr, CString dataPath);
	void reading(int readType, CString dataPath);
	void addAppversion();
	void macAddControl(int boxNum);
};
