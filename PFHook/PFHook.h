
// PFHook.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPFHookApp: 
// �йش����ʵ�֣������ PFHook.cpp
//

class CPFHookApp : public CWinApp
{
public:
	CPFHookApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPFHookApp theApp;