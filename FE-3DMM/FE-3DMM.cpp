
// FE-3DMM.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "FE-3DMMDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFE3DMMApp

BEGIN_MESSAGE_MAP(CFE3DMMApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CFE3DMMApp ����

CFE3DMMApp::CFE3DMMApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_pInitWorkThread	= NULL;
	m_pInitUIThread		= NULL;
	m_bAglientInitState = false;
	m_bHarvardInitState = false;
	m_bWinMainBegin		= false;
	m_bAppExit			= false;
}


// Ψһ��һ�� CFE3DMMApp ����

CFE3DMMApp theApp;


// CFE3DMMApp ��ʼ��

BOOL CFE3DMMApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//���.exe·��
	char cExePath[MAX_PATH];
	GetModuleFileName(NULL, cExePath, MAX_PATH);
	m_gAppExePath.Format("%s", cExePath);

	//�豸��ʼ��////////////////////jsb��ע�ͣ�������Էſ�
// 	m_pInitUIThread = (CInitializeThread*)AfxBeginThread(RUNTIME_CLASS(CInitializeThread));
// 	ASSERT(m_pInitUIThread);
// 	m_pInitWorkThread = AfxBeginThread(InitThreadFunc, this);
// 	ASSERT(m_pInitWorkThread);
// 
// 	while(!m_bWinMainBegin)
// 	{
// 		if (m_bAppExit)
// 		{
// 			return FALSE;
// 		}	
// 	}
	////////////////////////////////

	CFE3DMMDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}


HHOOK hHook;
LRESULT __stdcall CBTHookProc(long nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode == HCBT_ACTIVATE)
	{
		SetDlgItemText((HWND)wParam,IDOK,_T("&���Բ�����"));
		SetDlgItemText((HWND)wParam,IDCANCEL,_T("&�˳�"));
		UnhookWindowsHookEx(hHook);
	}

	return 0;
}

UINT CFE3DMMApp::InitThreadFunc(LPVOID pVoid)
{
	CFE3DMMApp* pThis = (CFE3DMMApp*)pVoid;			
	
	LONG nNum = 0;
	bool bInitState = true;    //��ʼ��״̬(��ǰ�豸��ʼ���ɹ�����Բ��ɹ������ܼ�����ʼ��)

	//������ʼ������
	pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 0, (LPARAM)nNum);

	//��ʼ�����ƿ�
	nNum = 20;
	//Sleep(100);


	//��ʼ������������
	if (bInitState)
	{
// 		nNum = 60;
// 		if (TRUE == pThis->m_JetAglientFunc.Connect())
// 		{
// 			pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 2, (LPARAM)nNum);
// 			pThis->m_bAglientInitState = true;
// 		}
// 		else
// 		{
// 			hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
// 			int nResult = MessageBox(NULL, _T("��ʼ������������ʧ�ܣ�"), _T("����������Error"), MB_OKCANCEL|MB_SYSTEMMODAL);
// 			if (IDCANCEL == nResult)
// 			{
// 				//�˳�
// 				pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 5, (LPARAM)nNum);
// 				Sleep(300);
// 				pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 6, (LPARAM)nNum);
// 				bInitState = false;
// 			}
// 			else if (IDOK == nResult)
// 			{
// 				//���Բ�����
// 				pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 2, (LPARAM)nNum);
// 			}
// 			pThis->m_bAglientInitState = false;
// 		}
// 		Sleep(500);
	}

	//��ʼ������������
	if (bInitState)
	{
// 		nNum = 100;
// 		int nPort = 7;
// 		if (pThis->m_JetHarvardPump.Init(nPort))
// 		{
// 			pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 3, (LPARAM)nNum);
// 			pThis->m_bHarvardInitState = true;
// 		}
// 		else
// 		{
// 			hHook = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTHookProc, NULL, GetCurrentThreadId());
// 			int nResult = MessageBox(NULL, _T("��ʼ������������ʧ�ܣ�"), _T("����������Error"), MB_OKCANCEL|MB_SYSTEMMODAL);
// 			if (IDCANCEL == nResult)
// 			{
// 				//�˳�
// 				pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 5, (LPARAM)nNum);
// 				Sleep(300);
// 				pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 6, (LPARAM)nNum);
// 				bInitState = false;
// 			}
// 			else if (IDOK == nResult)
// 			{
// 				//���Բ�����
// 				pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 3, (LPARAM)nNum);
// 			}
// 			pThis->m_bHarvardInitState = false;
// 		}
//		Sleep(500);
	}

	if (bInitState)
	{
		pThis->m_pInitUIThread->PostThreadMessage(UM_INITIALIZE, 4, (LPARAM)nNum);
	}

	return 0;
}

