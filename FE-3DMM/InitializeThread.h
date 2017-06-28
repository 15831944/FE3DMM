#pragma once
#include "DlgInitialize.h"


// CInitializeThread

class CInitializeThread : public CWinThread
{
	DECLARE_DYNCREATE(CInitializeThread)

protected:
	CInitializeThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CInitializeThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnUIThreadMessage(WPARAM wParam,LPARAM lParam);    //�û������߳���Ϣ��Ӧ����

private:
	BOOL CreateInitDialog();

private:
	CDlgInitialize*  m_pDlgInitialize;
};


