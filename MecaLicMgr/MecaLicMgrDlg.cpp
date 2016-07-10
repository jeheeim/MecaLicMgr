
// MecaLicMgrDlg.cpp : 구현 파일
//

/*
1. OnInitDialog 메소드

2. 전체 정보 읽기 버튼, 회사 정보 읽기 메소드, 사용자 정보 읽기 메소드 구현.
OnButtReadAll, OnButtReadComp, OnButtReadUser 메소드

3. 라이센스 읽기, 발급, 종료 메소드
라이센스 읽기, 발급 메소드는 메시지박스, 종료는 프로그램 종료.

4. ipv6 체크박스 메소드
체크하면 12자리 6박스, 해제하면 8자리 4박스.
*/

/*
0710 app type 탭 기능 구현
1. 프로그램이 실행되면 apptype.txt파일을 자동으로 읽어 프로그램의 종류를 파악하고

2. app version 에 자동으로 버전들을 추가한다.
*/

#include "stdafx.h"
#include "MecaLicMgr.h"
#include "MecaLicMgrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMecaLicMgrDlg 대화 상자



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


// CMecaLicMgrDlg 메시지 처리기

BOOL CMecaLicMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_cApptype.SetWindowText("App Type");
	
	CStdioFile src_file;

	// ""에 apptype.txt 의 경로를 넣을것.
	src_file.Open("", CFile::modeRead);

	CString str;

	while (src_file.ReadString(str))
	{
		m_cApptype.AddString(str);
	}

	src_file.Close();
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMecaLicMgrDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMecaLicMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//여기서부터 작업중인 메소드.

// 프로그램 종료 버튼
void CMecaLicMgrDlg::OnButtExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	OnOK();
}

// 체크하면 ipv6, 해제하면 ipv4. ip입력칸의 길이가 변경된다.
void CMecaLicMgrDlg::OnClickIpv6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
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

// 전체 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadAll()
{
	BOOL bTrue = FALSE;
	CString strTemp;

	// txt파일. 라이센스 파일로 수정필요
	CFileDialog dlgFileOpen(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "메모장(*.txt)|*.txt|모든파일(*.*)|*.*||", NULL);

	if (dlgFileOpen.DoModal() == IDOK)
	{
		MessageBox("전체 파일을 여는데 성공했습니다!", "성공", NULL);
	}
	else
	{
		MessageBox("전체 파일을 여는데 실패했습니다!", "실패", NULL);
	}
}

// 회사 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadComp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BOOL bTrue = FALSE;
	CString strTemp;

	// 열기창. txt파일과 모든파일중에 선택할 수 있다.
	CFileDialog dlgFileOpen(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "메모장(*.txt)|*.txt|모든파일(*.*)|*.*||", NULL);

	dlgFileOpen.m_ofn.lpstrInitialDir = (LPSTR)("C:\\Users\\jay\\Desktop\\MecaLicMgr\\data\\license\\comp");

	if (dlgFileOpen.DoModal() == IDOK)
	{
		MessageBox("전체 파일을 여는데 성공했습니다!", "성공", NULL);
	}
	else
	{
		MessageBox("전체 파일을 여는데 실패했습니다!", "실패", NULL);
	}
}

//사용자 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadUser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	BOOL bTrue = FALSE;
	CString strTemp;

	// 열기창. txt파일과 모든파일중에 선택할 수 있다.
	CFileDialog dlgFileOpen(TRUE, "TXT", NULL, OFN_FILEMUSTEXIST, "메모장(*.txt)|*.txt|모든파일(*.*)|*.*||", NULL);

	// 유저폴더.
	dlgFileOpen.m_ofn.lpstrInitialDir = (LPSTR)("C:\\Users\\jay\\Desktop\\MecaLicMgr\\data\\license\\user");

	if (dlgFileOpen.DoModal() == IDOK)
	{
		MessageBox("전체 파일을 여는데 성공했습니다!", "성공", NULL);
	}
	else
	{
		MessageBox("전체 파일을 여는데 실패했습니다!", "실패", NULL);
	}
}


void CMecaLicMgrDlg::OnButtLicMake()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MessageBox("라이센스를 발급합니다.", "발급", NULL);
}


void CMecaLicMgrDlg::OnButtLicRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MessageBox("라이센스를 불러옵니다.", "읽기", NULL);
}
