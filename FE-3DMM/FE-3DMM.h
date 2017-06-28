
// FE-3DMM.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

 #include "./JetPrint/JetAglientFunction.h"
 #include "./JetPrint/JetHarvardPump.h"
 #include "./JetPrint/JetAirPressureSet.h"
#include "InitializeThread.h"


// CFE3DMMApp:
// �йش����ʵ�֣������ FE-3DMM.cpp
//

class CFE3DMMApp : public CWinApp
{
public:
	CFE3DMMApp();

// ��д
public:
	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
	
	static UINT InitThreadFunc(LPVOID pVoid);


public:
	CWinThread*				m_pInitWorkThread;		//��ʼ���������߳�
	CInitializeThread*			m_pInitUIThread;				//��ʼ���û������߳�
    CJetAglientFunction   m_JetAglientFunc;			//����������
// 	CJetHarvardPump		m_JetHarvardPump;		//������
// 	CJetAirPressureSet		m_JetAirPress;					//��ѹ����

	bool					m_bAglientInitState;
	bool					m_bHarvardInitState;
	bool					m_bWinMainBegin;    
	bool					m_bAppExit;
	
};

extern CFE3DMMApp theApp;