
// IPATTRC.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIPATTRCApp:
// �йش����ʵ�֣������ IPATTRC.cpp
//

class CIPATTRCApp : public CWinApp
{
public:
	CIPATTRCApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIPATTRCApp theApp;