
// MecaLicMgrDlg.cpp : ���� ����
//

/*
1. OnInitDialog �޼ҵ�

2. ��ü ���� �б� ��ư, ȸ�� ���� �б� �޼ҵ�, ����� ���� �б� �޼ҵ� ����.
OnButtReadAll, OnButtReadComp, OnButtReadUser �޼ҵ�

3. ���̼��� �б�, �߱�, ���� �޼ҵ�
���̼��� �б�, �߱� �޼ҵ�� �޽����ڽ�, ����� ���α׷� ����.

4. ipv6 üũ�ڽ� �޼ҵ�
üũ�ϸ� 12�ڸ� 6�ڽ�, �����ϸ� 8�ڸ� 4�ڽ�.

0710 app type �� ��� ����
1. ���α׷��� ����Ǹ� apptype.txt������ �ڵ����� �о� ���α׷��� ������ �ľ��ϰ�

2. app version �� �ڵ����� �������� �߰��Ѵ�.
*/

/*
0711
1. ���� ����½� �����ּ� ��ġ ����ȭ
apptype, appversion, ȸ�� ����, ����� ���� ������ ��ġ�� CString ����ȭ.
2. ȸ�� �������� �ҷ�����
3. ����� �������� �ҷ�����
4. ����/������ ���� �޼ҵ�ȭ��.(openOrSave �޼ҵ�)
5. ��ü ���� �б� ����.
6. mac address ���
7. ȸ��, ����� ���� save as ��� �߰�
8. mac address ���̿� ���� ipv6 üũ
9. ��ü save as ��� �߰�

to do
ȸ��, ����� save ��� �߰�
license type �����
tab ���� ����
*/

#include "stdafx.h"
#include "MecaLicMgr.h"
#include "MecaLicMgrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	, check_ipv(FALSE)
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
}

void CMecaLicMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_IPV6, check_ipv);
	DDX_Control(pDX, IDC_COMBO_APPTYPE, m_cApptype);
	//  DDX_CBString(pDX, IDC_COMBO_APPTYPE, apptypeSel);
	DDX_Control(pDX, IDC_COMBO_VERSION, m_cVersion);
	DDX_CBString(pDX, IDC_COMBO_APPTYPE, m_strCbxApptype);
	DDX_Text(pDX, IDC_EDIT_COMP_CODE, compCode);
	DDX_Text(pDX, IDC_EDIT_COMP_EXTRA, compRemarks);
	DDX_Text(pDX, IDC_EDIT_COMP_MNG_CELL, compMngCell);
	DDX_Text(pDX, IDC_EDIT_COMP_MNG_EMAIL, compMngEmail);
	DDX_Text(pDX, IDC_EDIT_COMP_MNG_NAME, compMngName);
	DDX_Text(pDX, IDC_EDIT_COMP_NAME, compName);
	DDX_Text(pDX, IDC_EDIT_COMP_PHONE, compPhone);
	DDX_Text(pDX, IDC_EDIT_USER_CELL, userCell);
	DDX_Text(pDX, IDC_EDIT_USER_DEPT, userDept);
	DDX_Text(pDX, IDC_EDIT_USER_EMAIL, userEmail);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, userName);
	DDX_Text(pDX, IDC_EDIT_USER_PHONE, userPhone);
	DDX_Text(pDX, IDC_EDIT_USER_REMARKS, userRemarks);
	//  DDX_DateTimeCtrl(pDX, IDC_DATE_USER_LIC_END, userStart);
	DDX_DateTimeCtrl(pDX, IDC_DATE_USER_LIC_END, userEnd);
	//  DDX_DateTimeCtrl(pDX, IDC_DATE_USER_LIC_START, userStart);
	DDX_Text(pDX, IDC_EDIT_MAC1, macAdd1);
	DDV_MaxChars(pDX, macAdd1, 2);
	DDX_Text(pDX, IDC_EDIT_MAC2, macAdd2);
	DDV_MaxChars(pDX, macAdd2, 2);
	DDX_Text(pDX, IDC_EDIT_MAC3, macAdd3);
	DDV_MaxChars(pDX, macAdd3, 2);
	DDX_Text(pDX, IDC_EDIT_MAC4, macAdd4);
	DDV_MaxChars(pDX, macAdd4, 2);
	DDX_Text(pDX, IDC_EDIT_MAC5, macAdd5);
	DDV_MaxChars(pDX, macAdd5, 2);
	DDX_Text(pDX, IDC_EDIT_MAC6, macAdd6);
	DDV_MaxChars(pDX, macAdd6, 2);
	//  DDX_Control(pDX, IDC_CHECK_IPV6, idc_check_ipv);
}

BEGIN_MESSAGE_MAP(CMecaLicMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_EXIT, &CMecaLicMgrDlg::OnButtExit)
	ON_BN_CLICKED(IDC_CHECK_IPV6, &CMecaLicMgrDlg::OnClickIpv6)
	ON_BN_CLICKED(IDC_BUTT_READ_ALL, &CMecaLicMgrDlg::OnButtReadAll)
	ON_BN_CLICKED(IDC_BUTT_READ_COMP, &CMecaLicMgrDlg::OnButtReadComp)
	ON_BN_CLICKED(IDC_BUTT_READ_USER, &CMecaLicMgrDlg::OnButtReadUser)
	ON_BN_CLICKED(IDC_BUTT_LIC_MAKE, &CMecaLicMgrDlg::OnButtLicMake)
	ON_BN_CLICKED(IDC_BUTT_LIC_READ, &CMecaLicMgrDlg::OnButtLicRead)
	ON_CBN_SELCHANGE(IDC_COMBO_APPTYPE, &CMecaLicMgrDlg::OnCbxApptype)
	ON_BN_CLICKED(IDC_BUTT_COMP_SAVE_AS, &CMecaLicMgrDlg::OnButtCompSaveAs)
	ON_BN_CLICKED(IDC_BUTT_USER_SAVE_AS, &CMecaLicMgrDlg::OnButtUserSaveAs)
	ON_BN_CLICKED(IDC_BUTT_SAVE_ALL, &CMecaLicMgrDlg::OnButtAllSave)
	ON_BN_CLICKED(IDC_BUTT_SAVE_AS_ALL, &CMecaLicMgrDlg::OnButtAllSaveAs)
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
	baseAddress = "C:\\Users\\Jay\\Desktop\\data\\";
	apptypeAddress = baseAddress + "application\\apptype.txt";
	appVerAddresss = baseAddress + "application\\version\\";
	compDataAddress = baseAddress + "license\\comp";
	userDataAddress = baseAddress + "license\\user";

	// app type �޺��ڽ��� ���� apptype.txt���� �о����.
	CStdioFile src_file;

	// ���ϰ�δ� �⺻ ������ ���� �����
	src_file.Open(apptypeAddress, CFile::modeRead);

	CString str;

	while (src_file.ReadString(str))
	{
		m_cApptype.AddString(str);
	}

	src_file.Close();
	
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


//���⼭���� �۾����� �޼ҵ�.

// ���α׷� ���� ��ư
void CMecaLicMgrDlg::OnButtExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	OnOK();
}

// üũ�ϸ� ipv6, �����ϸ� ipv4. ip�Է�ĭ�� ���̰� ����ȴ�.
void CMecaLicMgrDlg::OnClickIpv6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	UpdateData(TRUE);
	
	if (check_ipv)
	{
		GetDlgItem(IDC_EDIT_MAC5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAC6)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_MAC_BAR4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_MAC_BAR5)->ShowWindow(TRUE);
	}

	else
	{
		GetDlgItem(IDC_EDIT_MAC5)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_MAC6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MAC_BAR4)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_MAC_BAR5)->ShowWindow(FALSE);
	}
}

// ��ü ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadAll()
{
	CString allInfo[15];

	int i = 0;

	CStdioFile allFile;
	
	allFile.Open(openOrSave(true, compDataAddress), CFile::modeRead);

	while (i<7)
	{
		allFile.ReadString(allInfo[i]);

		i++;
	}

	allFile.Close();

	allFile.Open(openOrSave(true, userDataAddress), CFile::modeRead);

	while (i<15)
	{
		allFile.ReadString(allInfo[i]);

		i++;
	}

	allFile.Close();

	// ȭ�鿡 ����ϱ�
	compName = allInfo[0].Mid(14);
	compCode = allInfo[1].Mid(14);
	compPhone = allInfo[2].Mid(14);
	compMngName = allInfo[3].Mid(14);
	compMngEmail = allInfo[4].Mid(14);
	compMngCell = allInfo[5].Mid(14);
	compRemarks = allInfo[6].Mid(14);

	userDept = allInfo[7].Mid(14);
	userName = allInfo[8].Mid(14);
	userPhone = allInfo[9].Mid(14);
	userCell = allInfo[10].Mid(14);
	userEmail = allInfo[11].Mid(14);
	userEnd.ParseDateTime(allInfo[12].Mid(14));
	userRemarks = allInfo[13].Mid(14);

	printMacAdd(allInfo[14].Mid(14));

	UpdateData(FALSE);
}

// ȸ�� ���� �б� ��ư. ȸ������ ���Ͽ��� ������ �о�� �պκ��� �߶� �ڿ�
// ���ʿ��� �κ��� trim�ϰ� ȭ�鿡 ����.
void CMecaLicMgrDlg::OnButtReadComp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
		
	// ���Ͽ��� �Է¹��� �����迭
	CString compInfo[7];

	int i = 0;

	CStdioFile compFile;

	// openOrSave �Լ��� true ���� �Է¹޾����� ����â�� �����ϰ� ������ ������ �ּҸ� �����Ѵ�.
	compFile.Open(openOrSave(true, compDataAddress), CFile::modeRead);

	while (i<7)
	{
		compFile.ReadString(compInfo[i]);

		i++;
	}

	compFile.Close();

	// ȭ�鿡 ����ϱ�
	compName = compInfo[0].Mid(14);
	compCode = compInfo[1].Mid(14);
	compPhone = compInfo[2].Mid(14);
	compMngName = compInfo[3].Mid(14);
	compMngEmail = compInfo[4].Mid(14);
	compMngCell = compInfo[5].Mid(14);
	compRemarks = compInfo[6].Mid(14);

	UpdateData(FALSE);
}

//����� ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadUser()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	// ���Ͽ��� �Է¹��� �����迭
	CString userInfo[9];

	int i = 0;

	CStdioFile userFile;

	// openOrSave �Լ��� true ���� �Է¹޾����� ����â�� �����ϰ� ������ ������ �ּҸ� �����Ѵ�.
	userFile.Open(openOrSave(true, userDataAddress), CFile::modeRead);

	while (i<9)
	{
		userFile.ReadString(userInfo[i]);

		i++;
	}

	userFile.Close();

	// ȭ�鿡 ����ϱ�
	userDept = userInfo[0].Mid(14);
	userName = userInfo[1].Mid(14);
	userPhone = userInfo[2].Mid(14);
	userCell = userInfo[3].Mid(14);
	userEmail = userInfo[4].Mid(14);
	userEnd.ParseDateTime(userInfo[5].Mid(14));
	userRemarks = userInfo[6].Mid(14);

	printMacAdd(userInfo[7].Mid(14));

	UpdateData(FALSE);
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

// ���� Ȥ�� ������ �����ϴ� �޼ҵ�. isOpen�� ���� true�� ����, false�� �����Ѵ�.
CString CMecaLicMgrDlg::openOrSave(BOOL isOpen, CString address)
{
	// ���� / ����â. txt���ϰ� ��������߿� ������ �� �ִ�.
	// true�� ����, false �� �����Ѵ�.
	CFileDialog dlgFileOpen(isOpen, "TXT", NULL, OFN_FILEMUSTEXIST, "�޸���(*.txt)|*.txt|�������(*.*)|*.*||", NULL);

	// ��������.
	dlgFileOpen.m_ofn.lpstrInitialDir = address;

	if (dlgFileOpen.DoModal() != IDOK)
	{
		MessageBox("����� ������ ���µ� �����߽��ϴ�!", "����", NULL);

		return NULL;
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
	
	UpdateData(TRUE);

	CStdioFile src_file;
	
	CString fileAddress = appVerAddresss + m_strCbxApptype + ".txt";

	// ���ϰ�δ� �⺻ ������ ���� �����
	src_file.Open(fileAddress, CFile::modeRead);

	CString str;

	while (src_file.ReadString(str))
	{
		m_cVersion.AddString(str);
	}

	src_file.Close();
}

void CMecaLicMgrDlg::printMacAdd(CString macAddress)
{
	if(macAddress.GetLength() >= 17)
	{
		macAdd1 = macAddress.Left(2);
		macAdd2 = macAddress.Mid(3, 2);
		macAdd3 = macAddress.Mid(6, 2);
		macAdd4 = macAddress.Mid(9, 2);
		macAdd5 = macAddress.Mid(12, 2);
		macAdd6 = macAddress.Mid(15, 2);

		check_ipv = true;
	}
	else
	{
		macAdd1 = macAddress.Left(2);
		macAdd2 = macAddress.Mid(3, 2);
		macAdd3 = macAddress.Mid(6, 2);
		macAdd4 = macAddress.Mid(9, 2);

		check_ipv = false;
	}

	UpdateData(FALSE);

	UpdateData(TRUE);

	if (check_ipv)
	{
		GetDlgItem(IDC_EDIT_MAC5)->ShowWindow(TRUE);
		GetDlgItem(IDC_EDIT_MAC6)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_MAC_BAR4)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_MAC_BAR5)->ShowWindow(TRUE);
	}
}

CString CMecaLicMgrDlg::getMacAdd(void)
{
	CString result;

	UpdateData(TRUE);

	result = macAdd1 + "-" + macAdd2 + "-" + macAdd3 + "-" + macAdd4 + "-" + macAdd5 + "-" + macAdd6;

	return result;
}

void CMecaLicMgrDlg::OnButtCompSaveAs()
{
	CString compDataPath;
	CFileException ex;
	CString writeStr[7];

	compDataPath = openOrSave(FALSE, compDataAddress);

	if (!compDataPath)
	{
		return;
	}

	CStdioFile compFile;
	
	compFile.Open(compDataPath, CFile::modeCreate | CFile::modeReadWrite, &ex);

	UpdateData(true);

	writeStr[0] = "Company Name: " + compName + "\n";
	writeStr[1] = "Company Code: " + compCode + "\n";
	writeStr[2] = "Company  TEL: " + compPhone + "\n";
	writeStr[3] = "Admin   Name: " + compMngName + "\n";
	writeStr[4] = "Admin e-mail: " + compMngEmail + "\n";
	writeStr[5] = "Admin Mobile: " + compMngCell + "\n";
	writeStr[6] = "Comp.Remarks: " + compRemarks + "\n";

	for (int i = 0; i < 7; i++)
	{
		compFile.WriteString(writeStr[i]);
	}

	compFile.Close();

	MessageBox("���忡 �����߽��ϴ�!", "�˸�", NULL);
}


void CMecaLicMgrDlg::OnButtUserSaveAs()
{
	CString userDataPath;
	CFileException ex;
	CString writeStr[9];

	CString userMacAdd = getMacAdd();
	CString userLicType;

	userDataPath = openOrSave(FALSE, userDataAddress);

	if (!userDataPath)
	{
		return;
	}

	UpdateData(true);

	writeStr[0] = "User   Dept.: " + userDept + "\n";
	writeStr[1] = "User   Name : " + userName + "\n";
	writeStr[2] = "User   Phone: " + userPhone + "\n";
	writeStr[3] = "User  Mobile: " + userCell + "\n";
	writeStr[4] = "User  e-mail: " + userEmail + "\n";
	writeStr[5] = "Lic. Enddate: " + userEnd.Format(_T("%Y/%m/%d")) + "\n";
	writeStr[6] = "User Remarks: " + userRemarks + "\n";
	writeStr[7] = "MAC  Address: " + userMacAdd + "\n";
	writeStr[8] = "License Type: " + userLicType + "\n";

	CStdioFile userFile;

	userFile.Open(userDataPath, CFile::modeCreate | CFile::modeReadWrite, &ex);

	for (int i = 0; i < 8; i++)
	{
		userFile.WriteString(writeStr[i]);
	}

	userFile.Close();

	MessageBox("���忡 �����߽��ϴ�!", "�˸�", NULL);
}


void CMecaLicMgrDlg::OnButtAllSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	MessageBox("��ü save�� �ǽ��մϴ�.","�˸�",NULL);
}


void CMecaLicMgrDlg::OnButtAllSaveAs()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString allDataPath;
	CFileException ex;
	CString writeStr[9];
	CStdioFile allFile;

	allDataPath = openOrSave(FALSE, compDataAddress);

	if (!allDataPath)
	{
		return;
	}

	allFile.Open(allDataPath, CFile::modeCreate | CFile::modeReadWrite, &ex);

	UpdateData(true);

	writeStr[0] = "Company Name: " + compName + "\n";
	writeStr[1] = "Company Code: " + compCode + "\n";
	writeStr[2] = "Company  TEL: " + compPhone + "\n";
	writeStr[3] = "Admin   Name: " + compMngName + "\n";
	writeStr[4] = "Admin e-mail: " + compMngEmail + "\n";
	writeStr[5] = "Admin Mobile: " + compMngCell + "\n";
	writeStr[6] = "Comp.Remarks: " + compRemarks + "\n";

	for (int i = 0; i < 7; i++)
	{
		allFile.WriteString(writeStr[i]);
	}

	allFile.Close();

	CString userMacAdd = getMacAdd();
	CString userLicType;

	allDataPath = openOrSave(FALSE, userDataAddress);

	if (!allDataPath)
	{
		return;
	}

	UpdateData(true);

	writeStr[0] = "User   Dept.: " + userDept + "\n";
	writeStr[1] = "User   Name : " + userName + "\n";
	writeStr[2] = "User   Phone: " + userPhone + "\n";
	writeStr[3] = "User  Mobile: " + userCell + "\n";
	writeStr[4] = "User  e-mail: " + userEmail + "\n";
	writeStr[5] = "Lic. Enddate: " + userEnd.Format(_T("%Y/%m/%d")) + "\n";
	writeStr[6] = "User Remarks: " + userRemarks + "\n";
	writeStr[7] = "MAC  Address: " + userMacAdd + "\n";
	writeStr[8] = "License Type: " + userLicType + "\n";

	allFile.Open(allDataPath, CFile::modeCreate | CFile::modeReadWrite, &ex);

	for (int i = 0; i < 8; i++)
	{
		allFile.WriteString(writeStr[i]);
	}

	allFile.Close();

	MessageBox("���忡 �����߽��ϴ�!", "�˸�", NULL);
}
