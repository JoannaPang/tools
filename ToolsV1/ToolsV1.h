
// ToolsV1.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CToolsV1App: 
// �йش����ʵ�֣������ ToolsV1.cpp
//

class CToolsV1App : public CWinApp
{
public:
	CToolsV1App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CToolsV1App theApp;