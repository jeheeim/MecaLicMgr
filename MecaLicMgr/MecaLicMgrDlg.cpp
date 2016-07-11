
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

0710 app type 탭 기능 구현
1. 프로그램이 실행되면 apptype.txt파일을 자동으로 읽어 프로그램의 종류를 파악하고

2. app version 에 자동으로 버전들을 추가한다.
*/

/*
0711
1. 파일 입출력시 파일주소 위치 변수화
apptype, appversion, 회사 정보, 사용자 정보 파일의 위치를 CString 변수화.
2. 회사 정보파일 불러오기
3. 사용자 정보파일 불러오기
4. 열기/저장을 단일 메소드화함.(openOrSave 메소드)
5. 전체 정보 읽기 구현.
6. mac address 출력
7. 회사, 사용자 정보 save as 기능 추가
8. mac address 길이에 따라 ipv6 체크
9. 전체 save as 기능 추가

to do
회사, 사용자 save 기능 추가
license type 물어볼것
tab 순서 설정
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
	
	// 주소의 공통부분인 배열 baseAddress 설정,
	// apptype.txt, appversion.txt가 위치한 폴더,
	// 회사 정보파일 폴더, 사용자 정보파일 폴더
	baseAddress = "C:\\Users\\Jay\\Desktop\\data\\";
	apptypeAddress = baseAddress + "application\\apptype.txt";
	appVerAddresss = baseAddress + "application\\version\\";
	compDataAddress = baseAddress + "license\\comp";
	userDataAddress = baseAddress + "license\\user";

	// app type 콤보박스를 위해 apptype.txt파일 읽어오기.
	CStdioFile src_file;

	// 파일경로는 기본 변수로 따로 만들것
	src_file.Open(apptypeAddress, CFile::modeRead);

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

	// 화면에 출력하기
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

// 회사 정보 읽기 버튼. 회사정보 파일에서 정보를 읽어와 앞부분을 잘라낸 뒤에
// 불필요한 부분을 trim하고 화면에 띄운다.
void CMecaLicMgrDlg::OnButtReadComp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		
	// 파일에서 입력받을 정보배열
	CString compInfo[7];

	int i = 0;

	CStdioFile compFile;

	// openOrSave 함수는 true 값을 입력받았을때 열기창을 실행하고 선택한 파일의 주소를 리턴한다.
	compFile.Open(openOrSave(true, compDataAddress), CFile::modeRead);

	while (i<7)
	{
		compFile.ReadString(compInfo[i]);

		i++;
	}

	compFile.Close();

	// 화면에 출력하기
	compName = compInfo[0].Mid(14);
	compCode = compInfo[1].Mid(14);
	compPhone = compInfo[2].Mid(14);
	compMngName = compInfo[3].Mid(14);
	compMngEmail = compInfo[4].Mid(14);
	compMngCell = compInfo[5].Mid(14);
	compRemarks = compInfo[6].Mid(14);

	UpdateData(FALSE);
}

//사용자 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadUser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	// 파일에서 입력받을 정보배열
	CString userInfo[9];

	int i = 0;

	CStdioFile userFile;

	// openOrSave 함수는 true 값을 입력받았을때 열기창을 실행하고 선택한 파일의 주소를 리턴한다.
	userFile.Open(openOrSave(true, userDataAddress), CFile::modeRead);

	while (i<9)
	{
		userFile.ReadString(userInfo[i]);

		i++;
	}

	userFile.Close();

	// 화면에 출력하기
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MessageBox("라이센스를 발급합니다.", "발급", NULL);
}


void CMecaLicMgrDlg::OnButtLicRead()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MessageBox("라이센스를 불러옵니다.", "읽기", NULL);
}

// 열기 혹은 저장을 수행하는 메소드. isOpen의 값이 true면 열기, false면 저장한다.
CString CMecaLicMgrDlg::openOrSave(BOOL isOpen, CString address)
{
	// 열기 / 저장창. txt파일과 모든파일중에 선택할 수 있다.
	// true면 열기, false 면 저장한다.
	CFileDialog dlgFileOpen(isOpen, "TXT", NULL, OFN_FILEMUSTEXIST, "메모장(*.txt)|*.txt|모든파일(*.*)|*.*||", NULL);

	// 유저폴더.
	dlgFileOpen.m_ofn.lpstrInitialDir = address;

	if (dlgFileOpen.DoModal() != IDOK)
	{
		MessageBox("사용자 파일을 여는데 실패했습니다!", "실패", NULL);

		return NULL;
	}

	return dlgFileOpen.GetPathName();
}


// 어플리케이션 종류를 선택하면 실행되는 함수
// 매번 앱 버젼을 초기화하고 선택한 어플리케이션의 버전 목록파일을 읽어들여
// 버전을 선택할 수 있는 콤보박스에 저장한다.
void CMecaLicMgrDlg::OnCbxApptype()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cVersion.ResetContent();
	
	UpdateData(TRUE);

	CStdioFile src_file;
	
	CString fileAddress = appVerAddresss + m_strCbxApptype + ".txt";

	// 파일경로는 기본 변수로 따로 만들것
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

	MessageBox("저장에 성공했습니다!", "알림", NULL);
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

	MessageBox("저장에 성공했습니다!", "알림", NULL);
}


void CMecaLicMgrDlg::OnButtAllSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MessageBox("전체 save를 실시합니다.","알림",NULL);
}


void CMecaLicMgrDlg::OnButtAllSaveAs()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

	MessageBox("저장에 성공했습니다!", "알림", NULL);
}
