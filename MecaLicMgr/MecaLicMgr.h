
// MecaLicMgr.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMecaLicMgrApp:
// �� Ŭ������ ������ ���ؼ��� MecaLicMgr.cpp�� �����Ͻʽÿ�.
//

class CMecaLicMgrApp : public CWinApp
{
public:
	CMecaLicMgrApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMecaLicMgrApp theApp;