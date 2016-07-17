
// MecaLicMgrDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "MecaLicMgr.h"
#include "MecaLicMgrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
onInitDialog() �Լ����� �ǵ帮���.
�ű⿡ todo �� �����ϴ� �ּ��ؿ��� ���� return TRUE ������ �ʱ�ȭ�ϴ� �κ�

�� �ؿ� ���⼭ ���� �۾����� �޼ҵ� ��� �ּ�����.

�޼ҵ� ���
OnButtExit()		: ���α׷� ����

OnButtLicMake()		: ���̼����߱� ��ư
OnButtLicRead()		: ���̼����б� ��ư

OnButtReadAll()		: ��ü�����б� ��ư reading �Լ� ȣ��
OnButtReadComp()	: ȸ�������б� ��ư reading �Լ� ȣ��
OnButtReadUser()	: ����������б� ��ư reading �Լ� ȣ��

OnButtAllSaveAs()	: ��ü Save As ��ư. ���� ��ȭ���ڸ� �������� openOrSaveDlg() �Լ���
						���� ������ �����ϴ� saving() �Լ��� ȣ���Ѵ�.
OnButtCompSaveAs()	: ȸ�� ���� save as ��ư
onButtUserSaveAs()	: ����� ���� save as ��ư

OnButtAllSave()		: ��ü save ��ư. �Էµ� ���� ������ ���� �������� ������ ������ ���� �������� �����.
openOrSaveDlg() �Լ��� saving() �Լ��� ȣ���Ѵ�.
OnButtCompSave()	: ȸ�� save ��ư
OnButtUserSave()	: ����� save ��ư

openOrSaveDlg()		: ����/���� ��ȭ���ڸ� ���� �޼ҵ�

OnCbxApptype()		: apptype �޺��ڽ����� ���������� ����. addAppversion() �Լ� ȣ��
addAppversion()		: apptype �޺��ڽ����� ���õ� �������� appversion ������ �о���δ�.

printMacAdd()		: mac address �� ��ȭ���ڿ� ���
getMacAdd()			: edit control�� ���� �������ִ� mac address �� CString ���� ���


saving()			: ���� ������ �����ϴ� �Լ�. saveType, �����Ͱ� ����� �迭, ���� ��θ� �Է¹޴´�.
						saveType �� 0�϶� ��ü����, 1�϶� ȸ�� ����, 2�϶� ����� ������ �����Ѵ�.
reading()			: ���� �б⸦ �����ϴ� �Լ�. readType, ���� ��θ� �Է¹޴´�.
						readType�� 0�϶� ��ü����, 1�϶� ȸ�� ����, 2�϶� ����� ������ �����Ѵ�.

OnUpdateMac1~6		: mac address �Է�ĭ�� ����Ǹ� ����. macAddControl()�� �����Ѵ�.
macAddControl()		: ���� boxNum�� �Է¹޾� 16������(������ �빮��) ����Ѵ�.
*/

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMecaLicMgrDlg ��ȭ ����



CMecaLicMgrDlg::CMecaLicMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MECALICMGR_DIALOG, pParent)
	, m_strCbxApptype(_T(""))
	, compCode(_T(""))
	, compRemarks(_T(""))
	, compMngCell(_T(""))
	, compMngEmail(_T(""))
	, compMngName(_T(""))
	, compName(_T(""))
	, compPhone(_T(""))
	, userCell(_T(""))
	, userDept(_T(""))
	, userEmail(_T(""))
	, userName(_T(""))
	, userPhone(_T(""))
	, userRemarks(_T(""))
	, userEnd(COleDateTime::GetCurrentTime())
	, macAdd1(_T(""))
	, macAdd2(_T(""))
	, macAdd3(_T(""))
	, macAdd4(_T(""))
	, macAdd5(_T(""))
	, macAdd6(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	baseAddress = _T("");
	apptypeAddress = _T("");
	compDataAddress = _T("");
	userDataAddress = _T("");
	appVerAddresss = _T("");
	compFilePathOriginal = _T("");
	userFilePathOriginal = _T("");
	allFilePathOriginal = _T("");
	userEndDate = _T("");
	userMacAdd = _T("");
	allDataAddress = _T("");
}

void CMecaLicMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_APPTYPE, m_cApptype);
	DDX_CBString(pDX, IDC_COMBO_APPTYPE, m_strCbxApptype);

	DDX_Control(pDX, IDC_COMBO_VERSION, m_cVersion);

	DDX_Text(pDX, IDC_EDIT_COMP_NAME, compName);
	DDX_Text(pDX, IDC_EDIT_COMP_CODE, compCode);
	DDX_Text(pDX, IDC_EDIT_COMP_PHONE, compPhone);
	DDX_Text(pDX, IDC_EDIT_COMP_MNG_CELL, compMngCell);
	DDX_Text(pDX, IDC_EDIT_COMP_MNG_EMAIL, compMngEmail);
	DDX_Text(pDX, IDC_EDIT_COMP_MNG_NAME, compMngName);
	DDX_Text(pDX, IDC_EDIT_COMP_EXTRA, compRemarks);

	DDX_Text(pDX, IDC_EDIT_USER_DEPT, userDept);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, userName);
	DDX_Text(pDX, IDC_EDIT_USER_PHONE, userPhone);
	DDX_Text(pDX, IDC_EDIT_USER_CELL, userCell);
	DDX_Text(pDX, IDC_EDIT_USER_EMAIL, userEmail);
	DDX_DateTimeCtrl(pDX, IDC_DATE_USER_LIC_END, userEnd);
	DDX_Text(pDX, IDC_EDIT_USER_REMARKS, userRemarks);

	DDX_Text(pDX, IDC_EDIT_MAC1, macAdd1);
	DDX_Text(pDX, IDC_EDIT_MAC2, macAdd2);
	DDX_Text(pDX, IDC_EDIT_MAC3, macAdd3);
	DDX_Text(pDX, IDC_EDIT_MAC4, macAdd4);
	DDX_Text(pDX, IDC_EDIT_MAC5, macAdd5);
	DDX_Text(pDX, IDC_EDIT_MAC6, macAdd6);

	DDX_Control(pDX, IDC_EDIT_MAC1, m_EditCtrMac1);
	DDX_Control(pDX, IDC_EDIT_MAC2, m_EditCtrMac2);
	DDX_Control(pDX, IDC_EDIT_MAC3, m_EditCtrMac3);
	DDX_Control(pDX, IDC_EDIT_MAC4, m_EditCtrMac4);
	DDX_Control(pDX, IDC_EDIT_MAC5, m_EditCtrMac5);
	DDX_Control(pDX, IDC_EDIT_MAC6, m_EditCtrMac6);

	DDV_MaxChars(pDX, macAdd1, 2);
	DDV_MaxChars(pDX, macAdd2, 2);
	DDV_MaxChars(pDX, macAdd3, 2);
	DDV_MaxChars(pDX, macAdd4, 2);
	DDV_MaxChars(pDX, macAdd5, 2);
	DDV_MaxChars(pDX, macAdd6, 2);

}

BEGIN_MESSAGE_MAP(CMecaLicMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_BUTT_EXIT, &CMecaLicMgrDlg::OnButtExit)

	ON_BN_CLICKED(IDC_BUTT_READ_ALL, &CMecaLicMgrDlg::OnButtReadAll)
	ON_BN_CLICKED(IDC_BUTT_READ_COMP, &CMecaLicMgrDlg::OnButtReadComp)
	ON_BN_CLICKED(IDC_BUTT_READ_USER, &CMecaLicMgrDlg::OnButtReadUser)

	ON_BN_CLICKED(IDC_BUTT_LIC_MAKE, &CMecaLicMgrDlg::OnButtLicMake)
	ON_BN_CLICKED(IDC_BUTT_LIC_READ, &CMecaLicMgrDlg::OnButtLicRead)

	ON_CBN_SELCHANGE(IDC_COMBO_APPTYPE, &CMecaLicMgrDlg::OnCbxApptype)

	ON_BN_CLICKED(IDC_BUTT_SAVE_AS_ALL, &CMecaLicMgrDlg::OnButtAllSaveAs)
	ON_BN_CLICKED(IDC_BUTT_COMP_SAVE_AS, &CMecaLicMgrDlg::OnButtCompSaveAs)
	ON_BN_CLICKED(IDC_BUTT_USER_SAVE_AS, &CMecaLicMgrDlg::OnButtUserSaveAs)

	ON_BN_CLICKED(IDC_BUTT_SAVE_ALL, &CMecaLicMgrDlg::OnButtAllSave)
	ON_BN_CLICKED(IDC_BUTT_COMP_SAVE, &CMecaLicMgrDlg::OnButtCompSave)
	ON_BN_CLICKED(IDC_BUTT_USER_SAVE, &CMecaLicMgrDlg::OnButtUserSave)

	ON_EN_UPDATE(IDC_EDIT_MAC1, &CMecaLicMgrDlg::OnUpdateMac1)
	ON_EN_UPDATE(IDC_EDIT_MAC2, &CMecaLicMgrDlg::OnUpdateMac2)
	ON_EN_UPDATE(IDC_EDIT_MAC3, &CMecaLicMgrDlg::OnUpdateMac3)
	ON_EN_UPDATE(IDC_EDIT_MAC4, &CMecaLicMgrDlg::OnUpdateMac4)
	ON_EN_UPDATE(IDC_EDIT_MAC5, &CMecaLicMgrDlg::OnUpdateMac5)
	ON_EN_UPDATE(IDC_EDIT_MAC6, &CMecaLicMgrDlg::OnUpdateMac6)
END_MESSAGE_MAP()


// CMecaLicMgrDlg �޽��� ó����

BOOL CMecaLicMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	
	// �ּ��� ����κ��� �迭 baseAddress ����,
	// apptype.txt, appversion.txt�� ��ġ�� ����,
	// ȸ�� �������� ����, ����� �������� ����
	char badd[512];
	memset(badd, 0, 512);
	SHGetSpecialFolderPath(NULL, badd, CSIDL_PERSONAL, FALSE);
	
	baseAddress.Format("%s",badd);
	baseAddress += "\\LicenseManagerData\\data\\";
	apptypeAddress = baseAddress + (CString)"application\\apptype.txt";
	appVerAddresss = baseAddress + (CString)"application\\version\\";
	compDataAddress = baseAddress + (CString)"license\\comp";
	userDataAddress = baseAddress + (CString)"license\\user";
	allDataAddress = baseAddress + (CString)"license\\comp.user";

	// app type �޺��ڽ��� ���� apptype.txt���� �а� ù��° �׸� �����ϱ�
	CStdioFile src_file;
	
	src_file.Open(apptypeAddress, CFile::modeRead);

	CString str;

	while (src_file.ReadString(str))
	{
		m_cApptype.AddString(str);
	}

	src_file.Close();

	m_cApptype.SetCurSel(0);

	// ���õ� apptype �׸� �´� appversion ������ �а� ù��° �׸� �����ϱ�
	addAppversion();

	m_cVersion.SetCurSel(0);

	// *data[]�� edit �ڽ� ����
	data[0] = &compName;
	data[1] = &compCode;
	data[2] = &compPhone;
	data[3] = &compMngName;
	data[4] = &compMngEmail;
	data[5] = &compMngCell;
	data[6] = &compRemarks;
	data[7] = &userDept;
	data[8] = &userName;
	data[9] = &userCell;
	data[10] = &userPhone;
	data[11] = &userEmail;
	data[12] = &userEndDate;
	data[13] = &userRemarks;
	data[14] = &userMacAdd;

	// *macAdd[]�� mac address �ڽ��� ����
	macAdd[0] = &macAdd1;
	macAdd[1] = &macAdd2;
	macAdd[2] = &macAdd3;
	macAdd[3] = &macAdd4;
	macAdd[4] = &macAdd5;
	macAdd[5] = &macAdd6;

	// *macAddCtrl[]�� mac address control ������ ����
	macAddCtrl[0] = &m_EditCtrMac1;
	macAddCtrl[1] = &m_EditCtrMac2;
	macAddCtrl[2] = &m_EditCtrMac3;
	macAddCtrl[3] = &m_EditCtrMac4;
	macAddCtrl[4] = &m_EditCtrMac5;
	macAddCtrl[5] = &m_EditCtrMac6;

	// ���� ���ϰ�� �ʱ�ȭ
	allFilePathOriginal = "";
	userFilePathOriginal = "";
	compFilePathOriginal = "";

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CMecaLicMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CMecaLicMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CMecaLicMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/*

���⼭���� �۾����� �޼ҵ�

*/

// ���α׷� ���� ��ư
void CMecaLicMgrDlg::OnButtExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	OnOK();
}

void CMecaLicMgrDlg::OnButtLicMake()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	MessageBox("���̼����� �߱��մϴ�.", "�߱�", NULL);
}


void CMecaLicMgrDlg::OnButtLicRead()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	MessageBox("���̼����� �ҷ��ɴϴ�.", "�б�", NULL);
}

// read

// ��ü ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadAll()
{
	reading(0, allDataAddress);
}

// ȸ�� ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadComp()
{
	reading(1, compDataAddress);
}

//����� ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadUser()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	reading(2, userDataAddress);
}

// save as

void CMecaLicMgrDlg::OnButtAllSaveAs()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString allDataPath;
	CString writeStr[15];

	allDataPath = openOrSaveDlg(FALSE, allDataAddress);

	if (allDataPath == "f") { return; }

	saving(0, writeStr, allDataPath);

	MessageBox("���忡 �����߽��ϴ�!", "�˸�", NULL);
}

void CMecaLicMgrDlg::OnButtCompSaveAs()
{
	CString writeStr[7];
	CString compDataPath;

	compDataPath = openOrSaveDlg(FALSE, compDataAddress);

	// ����ϸ� ����!
	if (compDataPath == "f") { return; }

	saving(1, writeStr, compDataPath);

	for (int i = 0; i < 7; i++)
	{
		originalData[i] = writeStr[i];
	}

	compFilePathOriginal = compDataPath;

	MessageBox("���忡 �����߽��ϴ�!", "�˸�", NULL);
}

void CMecaLicMgrDlg::OnButtUserSaveAs()
{
	CString userDataPath;
	CString writeStr[8];

	userDataPath = openOrSaveDlg(FALSE, userDataAddress);

	if (userDataPath == "f") { return; }

	saving(2, writeStr, userDataPath);

	for (int i = 0; i < 8; i++)
	{
		originalData[i + 7] = writeStr[i];
	}

	userFilePathOriginal = userDataPath;

	MessageBox("���忡 �����߽��ϴ�!", "�˸�", NULL);
}

// save

void CMecaLicMgrDlg::OnButtAllSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CString allDataPath;
	CString writeStr[15];

	if (allFilePathOriginal.GetLength() > 3)
	{
		int choice = MessageBox("���� �����Ͻðڽ��ϱ�?", "����", MB_YESNOCANCEL);

		// MB_YESNOCANCEL ���� yes �� 6, no�� 7, cancel�� 2
		switch (choice)
		{
		case 6:
			allDataPath = openOrSaveDlg(FALSE, allDataAddress);
			break;
		case 7:
			allDataPath = allFilePathOriginal;
			break;
		case 2:
			return;
			break;
		}
	}
	else
	{
		allDataPath = openOrSaveDlg(FALSE, allDataAddress);
	}

	// ����ϸ� ����!
	if (allDataPath == "f") { return; }

	saving(0, writeStr, allDataPath);

	MessageBox("������ �Ϸ�Ǿ����ϴ�!", "�˸�", NULL);
}

// �б�, Ȥ�� ����ÿ� �Էµ� �ʱ�ȸ�� ������ ���� ����� ������ ��, ���忩�θ� �����Ѵ�.
// ��������� ���ٸ� �׳� �����ߴٰ� �߰��Ѵ�
// ��������� �ִٸ� �������� �����Ѵ�.
// 1. ������ �Էµ� ���� ��η� �����Ѵ�.
// 2. ���� �����Ѵ�.
// 3. ���
void CMecaLicMgrDlg::OnButtCompSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CString compDataPath;
	CString writeStr[7];

	if (compFilePathOriginal.GetLength() > 2)
	{
		int choice = MessageBox("���� �����Ͻðڽ��ϱ�?", "����", MB_YESNOCANCEL);

		// MB_YESNOCANCEL ���� yes �� 6, no�� 7, cancel�� 2
		switch (choice)
		{
		case 6:
			compDataPath = openOrSaveDlg(FALSE, compDataAddress);
			break;
		case 7:
			compDataPath = compFilePathOriginal;
			break;
		case 2:
			return;
			break;
		}
	}
	else
	{
		compDataPath = openOrSaveDlg(FALSE, compDataAddress);
	}

	if (compDataPath == "f") { return; }

	saving(1, writeStr, compDataPath);

	MessageBox("������ �Ϸ�Ǿ����ϴ�!", "�˸�", NULL);
}

void CMecaLicMgrDlg::OnButtUserSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	CString userDataPath;
	CString writeStr[8];

	if (userFilePathOriginal.GetLength() > 2)
	{
		int choice = MessageBox("���� �����Ͻðڽ��ϱ�?", "����", MB_YESNOCANCEL);

		// MB_YESNOCANCEL ���� yes �� 6, no�� 7, cancel�� 2
		switch (choice)
		{
		case 6:
			userDataPath = openOrSaveDlg(FALSE, userDataAddress);
			break;
		case 7:
			userDataPath = userFilePathOriginal;
			break;
		case 2:
			return;
			break;
		}
	}
	else
	{
		userDataPath = openOrSaveDlg(FALSE, userDataAddress);
	}

	if (userDataPath == "f") { return; }

	saving(2, writeStr, userDataPath);

	userFilePathOriginal = userDataPath;

	MessageBox("������ �Ϸ�Ǿ����ϴ�!", "�˸�", NULL);
}


// ���� Ȥ�� ���� ��ȭ���ڸ� ���� �޼ҵ�. isOpen�� ���� true�� ����, false�� �����Ѵ�.
// ��ҹ�ư�� ������ f�� ������ �˼��ֵ��� �Ѵ�.
CString CMecaLicMgrDlg::openOrSaveDlg(BOOL isOpen, CString address)
{
	// ���� / ����â. txt���ϰ� ��������߿� ������ �� �ִ�.
	// true�� ����, false �� �����Ѵ�.
	CFileDialog dlgFileOpen(isOpen, "TXT", NULL, OFN_FILEMUSTEXIST, "�޸���(*.txt)|*.txt|�������(*.*)|*.*||", NULL);

	// ��������.
	dlgFileOpen.m_ofn.lpstrInitialDir = address;

	if (dlgFileOpen.DoModal() == IDCANCEL)
	{
		return (CString)"f";
	}

	return dlgFileOpen.GetPathName();
}


// ���ø����̼� ������ �����ϸ� ����Ǵ� �Լ�
// �Ź� �� ������ �ʱ�ȭ�ϰ� ������ ���ø����̼��� ���� ��������� �о�鿩
// ������ ������ �� �ִ� �޺��ڽ��� �����Ѵ�.
void CMecaLicMgrDlg::OnCbxApptype()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cVersion.ResetContent();
	
	addAppversion();
}

void CMecaLicMgrDlg::addAppversion()
{
	CStdioFile src_file;
	CString str;

	UpdateData(TRUE);

	// ���õ� apptype �׸� �´� appversion ������ �а� ù��° �׸� �����ϱ�
	CString fileAddress = appVerAddresss + m_strCbxApptype + ".txt";

	src_file.Open(fileAddress, CFile::modeRead);

	while (src_file.ReadString(str))
	{
		m_cVersion.AddString(str);
	}

	src_file.Close();

}


void CMecaLicMgrDlg::printMacAdd(CString macAddress)
{
	macAdd1 = macAddress.Left(2);
	macAdd2 = macAddress.Mid(3, 2);
	macAdd3 = macAddress.Mid(6, 2);
	macAdd4 = macAddress.Mid(9, 2);
	macAdd5 = macAddress.Mid(12, 2);
	macAdd6 = macAddress.Mid(15, 2);

	UpdateData(FALSE);
}


CString CMecaLicMgrDlg::getMacAdd(void)
{
	CString result;

	UpdateData(TRUE);

	result = macAdd1 + "-" + macAdd2 + "-" + macAdd3 + "-" + macAdd4 + "-" + macAdd5 + "-" + macAdd6;

	return result;
}


// ��ü / ȸ�� / ����� ������ �����͸� �Է��Ѵ�.
// 0�̸� ��ü ����, 1�̸� ȸ������ ����, 2�̸� ����� ����
void CMecaLicMgrDlg::saving(int saveType, CString * writeStr, CString dataPath)
{
	CFileException ex;
	CStdioFile textFile;

	int start, finish;

	switch(saveType)
	{
	case 0:
		start = 0;
		finish = 15;
		break;
	case 1:
		start = 0;
		finish = 7;
		break;
	case 2:
		start = 7;
		finish = 15;
		break;
	}

	UpdateData(TRUE);

	userMacAdd = getMacAdd();
	userEndDate = userEnd.Format(_T("%Y/%m/%d"));

	for (int i = start; i < finish; i++)
	{
		writeStr[i - start] = (*data[i]) + "\n";
	}

	textFile.Open(dataPath, CFile::modeCreate | CFile::modeReadWrite, &ex);

	for (int i = 0; i < finish-start; i++)
	{
		textFile.WriteString(writeStr[i]);
	}

	textFile.Close();
}

// ��ü / ȸ�� / ����� ������ �����͸� �ҷ��´�.
// 0�̸� ��ü �б�, 1�̸� ȸ������ �б�, 2�̸� ����� �б�
void CMecaLicMgrDlg::reading(int readType, CString dataPath)
{
	CString filePath;
	CString alert;
	CStdioFile txtFile;
	int start, finish;

	filePath = openOrSaveDlg(TRUE, dataPath);

	switch (readType)
	{
	case 0:
		start = 0;
		finish = 15;
		alert = "��ü";
		allFilePathOriginal = filePath;
		break;
	case 1:
		start = 0;
		finish = 8;
		alert = "ȸ��";
		compFilePathOriginal = filePath;
		break;
	case 2:
		start = 7;
		finish = 15;
		alert = "�����";
		userFilePathOriginal = filePath;
		break;
	}

	if (filePath == "f")
	{
		MessageBox(alert + " ���� �б⸦ �����߽��ϴ�.", "�˸�", NULL);

		return;
	}

	// openOrSave �Լ��� true ���� �Է¹޾����� ����â�� �����ϰ� ������ ������ �ּҸ� �����Ѵ�.
	txtFile.Open(filePath, CFile::modeRead);

	for(int i=start; i<finish;i++)
	{
		txtFile.ReadString(*data[i]);
	}

	if (readType != 1)
	{
		userEnd.ParseDateTime(*data[12]);
		printMacAdd(*data[14]);
	}

	txtFile.Close();

	UpdateData(FALSE);

	for (int i = start; i < finish; i++)
	{
		originalData[i] = *data[i];
	}

	MessageBox(alert + " ���� �б⸦ �����߽��ϴ�.", "�˸�", NULL);
}

void CMecaLicMgrDlg::OnUpdateMac1()
{
	macAddControl(0);
}

void CMecaLicMgrDlg::OnUpdateMac2()
{
	macAddControl(1);
}


void CMecaLicMgrDlg::OnUpdateMac3()
{
	macAddControl(2);
}


void CMecaLicMgrDlg::OnUpdateMac4()
{
	macAddControl(3);
}


void CMecaLicMgrDlg::OnUpdateMac5()
{
	macAddControl(4);
}


void CMecaLicMgrDlg::OnUpdateMac6()
{
	macAddControl(5);
}

void CMecaLicMgrDlg::macAddControl(int boxNum)
{
	UpdateData(TRUE);

	TCHAR * tchar;
	CString str = _T("");
	int i;
	int asc;

	for (i = 0; i < (*macAdd[boxNum]).GetLength(); i++)
	{
		str = (*macAdd[boxNum]).Mid(i, 1);

		tchar = (TCHAR*)(LPCTSTR)str;

		asc = __toascii(*tchar);

		// �빮�� A-F, ���ڸ� �޴´�. �� �ܿ��� ������.
		if (!((asc >= 65 && asc <= 70) || (asc > 47 && asc < 58) || (asc > 96 && asc < 103)))
		{
			(*macAdd[boxNum]).Remove(*tchar);
		}

		(*macAdd[boxNum]).MakeUpper();
	}
	
	UpdateData(FALSE);

	(*macAddCtrl[boxNum]).SetSel(0, -1);
	(*macAddCtrl[boxNum]).SetSel(-1, -1);
}