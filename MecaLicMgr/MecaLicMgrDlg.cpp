
// MecaLicMgrDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "MecaLicMgr.h"
#include "MecaLicMgrDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
onInitDialog() 함수부터 건드리면됨.
거기에 todo 로 시작하는 주석밑에서 부터 return TRUE 전까지 초기화하는 부분

그 밑에 여기서 부터 작업중인 메소드 라는 주석부터.

메소드 목록
OnButtExit()		: 프로그램 종료

OnButtLicMake()		: 라이센스발급 버튼
OnButtLicRead()		: 라이센스읽기 버튼

OnButtReadAll()		: 전체정보읽기 버튼 reading 함수 호출
OnButtReadComp()	: 회사정보읽기 버튼 reading 함수 호출
OnButtReadUser()	: 사용자정보읽기 버튼 reading 함수 호출

OnButtAllSaveAs()	: 전체 Save As 버튼. 저장 대화상자를 열기위해 openOrSaveDlg() 함수와
						실제 저장을 수행하는 saving() 함수를 호출한다.
OnButtCompSaveAs()	: 회사 정보 save as 버튼
onButtUserSaveAs()	: 사용자 정보 save as 버튼

OnButtAllSave()		: 전체 save 버튼. 입력된 것이 있을때 새로 저장할지 기존에 저장한 곳에 저장할지 물어본다.
openOrSaveDlg() 함수와 saving() 함수를 호출한다.
OnButtCompSave()	: 회사 save 버튼
OnButtUserSave()	: 사용자 save 버튼

openOrSaveDlg()		: 열기/저장 대화상자를 여는 메소드

OnCbxApptype()		: apptype 콤보박스에서 선택했을때 수행. addAppversion() 함수 호출
addAppversion()		: apptype 콤보박스에서 선택된 내용으로 appversion 파일을 읽어들인다.

printMacAdd()		: mac address 를 대화상자에 출력
getMacAdd()			: edit control에 각각 떨어져있는 mac address 를 CString 으로 출력


saving()			: 실제 저장을 수행하는 함수. saveType, 데이터가 저장된 배열, 파일 경로를 입력받는다.
						saveType 은 0일때 전체정보, 1일때 회사 정보, 2일때 사용자 정보를 저장한다.
reading()			: 실제 읽기를 수행하는 함수. readType, 파일 경로를 입력받는다.
						readType은 0일때 전체정보, 1일때 회사 정보, 2일때 사용자 정보를 저장한다.

OnUpdateMac1~6		: mac address 입력칸이 변경되면 실행. macAddControl()을 실행한다.
macAddControl()		: 정수 boxNum을 입력받아 16진수만(영문은 대문자) 출력한다.
*/

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

	// app type 콤보박스를 위해 apptype.txt파일 읽고 첫번째 항목 선택하기
	CStdioFile src_file;
	
	src_file.Open(apptypeAddress, CFile::modeRead);

	CString str;

	while (src_file.ReadString(str))
	{
		m_cApptype.AddString(str);
	}

	src_file.Close();

	m_cApptype.SetCurSel(0);

	// 선택된 apptype 항목에 맞는 appversion 파일을 읽고 첫번째 항목 선택하기
	addAppversion();

	m_cVersion.SetCurSel(0);

	// *data[]와 edit 박스 연결
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

	// *macAdd[]와 mac address 박스와 연결
	macAdd[0] = &macAdd1;
	macAdd[1] = &macAdd2;
	macAdd[2] = &macAdd3;
	macAdd[3] = &macAdd4;
	macAdd[4] = &macAdd5;
	macAdd[5] = &macAdd6;

	// *macAddCtrl[]과 mac address control 변수와 연결
	macAddCtrl[0] = &m_EditCtrMac1;
	macAddCtrl[1] = &m_EditCtrMac2;
	macAddCtrl[2] = &m_EditCtrMac3;
	macAddCtrl[3] = &m_EditCtrMac4;
	macAddCtrl[4] = &m_EditCtrMac5;
	macAddCtrl[5] = &m_EditCtrMac6;

	// 비교할 파일경로 초기화
	allFilePathOriginal = "";
	userFilePathOriginal = "";
	compFilePathOriginal = "";

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

/*

여기서부터 작업중인 메소드

*/

// 프로그램 종료 버튼
void CMecaLicMgrDlg::OnButtExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	OnOK();
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

// read

// 전체 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadAll()
{
	reading(0, allDataAddress);
}

// 회사 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadComp()
{
	reading(1, compDataAddress);
}

//사용자 정보 읽기 버튼.
void CMecaLicMgrDlg::OnButtReadUser()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	reading(2, userDataAddress);
}

// save as

void CMecaLicMgrDlg::OnButtAllSaveAs()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString allDataPath;
	CString writeStr[15];

	allDataPath = openOrSaveDlg(FALSE, allDataAddress);

	if (allDataPath == "f") { return; }

	saving(0, writeStr, allDataPath);

	MessageBox("저장에 성공했습니다!", "알림", NULL);
}

void CMecaLicMgrDlg::OnButtCompSaveAs()
{
	CString writeStr[7];
	CString compDataPath;

	compDataPath = openOrSaveDlg(FALSE, compDataAddress);

	// 취소하면 종료!
	if (compDataPath == "f") { return; }

	saving(1, writeStr, compDataPath);

	for (int i = 0; i < 7; i++)
	{
		originalData[i] = writeStr[i];
	}

	compFilePathOriginal = compDataPath;

	MessageBox("저장에 성공했습니다!", "알림", NULL);
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

	MessageBox("저장에 성공했습니다!", "알림", NULL);
}

// save

void CMecaLicMgrDlg::OnButtAllSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString allDataPath;
	CString writeStr[15];

	if (allFilePathOriginal.GetLength() > 3)
	{
		int choice = MessageBox("새로 저장하시겠습니까?", "저장", MB_YESNOCANCEL);

		// MB_YESNOCANCEL 에서 yes 는 6, no는 7, cancel은 2
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

	// 취소하면 종료!
	if (allDataPath == "f") { return; }

	saving(0, writeStr, allDataPath);

	MessageBox("저장이 완료되었습니다!", "알림", NULL);
}

// 읽기, 혹은 저장시에 입력된 초기회사 정보와 지금 변경된 사항을 비교, 저장여부를 결정한다.
// 변경사항이 없다면 그냥 저장했다고 뜨게한다
// 변경사항이 있다면 선택지를 제공한다.
// 1. 기존에 입력된 파일 경로로 저장한다.
// 2. 새로 저장한다.
// 3. 취소
void CMecaLicMgrDlg::OnButtCompSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString compDataPath;
	CString writeStr[7];

	if (compFilePathOriginal.GetLength() > 2)
	{
		int choice = MessageBox("새로 저장하시겠습니까?", "저장", MB_YESNOCANCEL);

		// MB_YESNOCANCEL 에서 yes 는 6, no는 7, cancel은 2
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

	MessageBox("저장이 완료되었습니다!", "알림", NULL);
}

void CMecaLicMgrDlg::OnButtUserSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString userDataPath;
	CString writeStr[8];

	if (userFilePathOriginal.GetLength() > 2)
	{
		int choice = MessageBox("새로 저장하시겠습니까?", "저장", MB_YESNOCANCEL);

		// MB_YESNOCANCEL 에서 yes 는 6, no는 7, cancel은 2
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

	MessageBox("저장이 완료되었습니다!", "알림", NULL);
}


// 열기 혹은 저장 대화상자를 여는 메소드. isOpen의 값이 true면 열기, false면 저장한다.
// 취소버튼을 누르면 f를 리턴해 알수있도록 한다.
CString CMecaLicMgrDlg::openOrSaveDlg(BOOL isOpen, CString address)
{
	// 열기 / 저장창. txt파일과 모든파일중에 선택할 수 있다.
	// true면 열기, false 면 저장한다.
	CFileDialog dlgFileOpen(isOpen, "TXT", NULL, OFN_FILEMUSTEXIST, "메모장(*.txt)|*.txt|모든파일(*.*)|*.*||", NULL);

	// 유저폴더.
	dlgFileOpen.m_ofn.lpstrInitialDir = address;

	if (dlgFileOpen.DoModal() == IDCANCEL)
	{
		return (CString)"f";
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
	
	addAppversion();
}

void CMecaLicMgrDlg::addAppversion()
{
	CStdioFile src_file;
	CString str;

	UpdateData(TRUE);

	// 선택된 apptype 항목에 맞는 appversion 파일을 읽고 첫번째 항목 선택하기
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


// 전체 / 회사 / 사용자 정보에 데이터를 입력한다.
// 0이면 전체 저장, 1이면 회사정보 저장, 2이면 사용자 저장
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

// 전체 / 회사 / 사용자 정보에 데이터를 불러온다.
// 0이면 전체 읽기, 1이면 회사정보 읽기, 2이면 사용자 읽기
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
		alert = "전체";
		allFilePathOriginal = filePath;
		break;
	case 1:
		start = 0;
		finish = 8;
		alert = "회사";
		compFilePathOriginal = filePath;
		break;
	case 2:
		start = 7;
		finish = 15;
		alert = "사용자";
		userFilePathOriginal = filePath;
		break;
	}

	if (filePath == "f")
	{
		MessageBox(alert + " 파일 읽기를 중지했습니다.", "알림", NULL);

		return;
	}

	// openOrSave 함수는 true 값을 입력받았을때 열기창을 실행하고 선택한 파일의 주소를 리턴한다.
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

	MessageBox(alert + " 파일 읽기를 성공했습니다.", "알림", NULL);
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

		// 대문자 A-F, 숫자만 받는다. 그 외에는 삭제함.
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