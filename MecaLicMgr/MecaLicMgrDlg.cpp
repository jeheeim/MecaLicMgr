
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
*/

/*
0710 app type �� ��� ����
1. ���α׷��� ����Ǹ� apptype.txt������ �ڵ����� �о� ���α׷��� ������ �ľ��ϰ�

2. app version �� �ڵ����� �������� �߰��Ѵ�.
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMecaLicMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_IPV6, check_ipv);
	//  DDX_Control(pDX, IDC_MENU_APPTYPE, m_cApptype);
	//  DDX_Control(pDX, IDC_SPLIT_APPTYPE, m_cApptype);
	DDX_Control(pDX, IDC_COMBO_APPTYPE, m_cApptype);
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

	m_cApptype.SetWindowText("App Type");
	
	CStdioFile src_file;

	// ""�� apptype.txt �� ��θ� ������.
	src_file.Open("", CFile::modeRead);

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
	BOOL bTrue = FALSE;
	CString strTemp;

	// txt����. ���̼��� ���Ϸ� �����ʿ�
	CFileDialog dlgFileOpen(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "�޸���(*.txt)|*.txt|�������(*.*)|*.*||", NULL);

	if (dlgFileOpen.DoModal() == IDOK)
	{
		MessageBox("��ü ������ ���µ� �����߽��ϴ�!", "����", NULL);
	}
	else
	{
		MessageBox("��ü ������ ���µ� �����߽��ϴ�!", "����", NULL);
	}
}

// ȸ�� ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadComp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	BOOL bTrue = FALSE;
	CString strTemp;

	// ����â. txt���ϰ� ��������߿� ������ �� �ִ�.
	CFileDialog dlgFileOpen(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "�޸���(*.txt)|*.txt|�������(*.*)|*.*||", NULL);

	dlgFileOpen.m_ofn.lpstrInitialDir = (LPSTR)("C:\\Users\\jay\\Desktop\\MecaLicMgr\\data\\license\\comp");

	if (dlgFileOpen.DoModal() == IDOK)
	{
		MessageBox("��ü ������ ���µ� �����߽��ϴ�!", "����", NULL);
	}
	else
	{
		MessageBox("��ü ������ ���µ� �����߽��ϴ�!", "����", NULL);
	}
}

//����� ���� �б� ��ư.
void CMecaLicMgrDlg::OnButtReadUser()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	BOOL bTrue = FALSE;
	CString strTemp;

	// ����â. txt���ϰ� ��������߿� ������ �� �ִ�.
	CFileDialog dlgFileOpen(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "�޸���(*.txt)|*.txt|�������(*.*)|*.*||", NULL);

	// ��������.
	dlgFileOpen.m_ofn.lpstrInitialDir = (LPSTR)("C:\\Users\\jay\\Desktop\\MecaLicMgr\\data\\license\\user");

	if (dlgFileOpen.DoModal() == IDOK)
	{
		MessageBox("��ü ������ ���µ� �����߽��ϴ�!", "����", NULL);
	}
	else
	{
		MessageBox("��ü ������ ���µ� �����߽��ϴ�!", "����", NULL);
	}
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
