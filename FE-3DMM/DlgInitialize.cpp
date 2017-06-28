// DlgInitialize.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgInitialize.h"
#include "afxdialogex.h"


// CDlgInitialize �Ի���

IMPLEMENT_DYNAMIC(CDlgInitialize, CDialog)

CDlgInitialize::CDlgInitialize(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInitialize::IDD, pParent)
{

}

CDlgInitialize::~CDlgInitialize()
{
	Release();
}

void CDlgInitialize::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INIT_PROGRESS, m_progressInit);
	DDX_Control(pDX, IDC_INIT_EDIT, m_editInit);
}


BEGIN_MESSAGE_MAP(CDlgInitialize, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDlgInitialize ��Ϣ�������


BOOL CDlgInitialize::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC; 
	//CBitmap����
	CBitmap Bitmap,*pOldBitmap; 
	//BITMAP���
	BITMAP bm; 
	//����λͼ
	Bitmap.LoadBitmap(IDB_BITMAP_BACKGROUND); 
	//��λͼ��Դ������
	Bitmap.GetObject(sizeof(BITMAP),&bm); 
	//�������ڴ���ݵ�DC
	MemDC.CreateCompatibleDC(pDC); 
	//�滻ԭλͼ
	pOldBitmap=(CBitmap*)(MemDC.SelectObject(&Bitmap)); 

	//��ȡ���Ƶ�����
	CRect rcClient;
	GetClientRect(&rcClient); 

	//���Ƶ��ͻ���
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC(); 
	return TRUE;
}


HBRUSH CDlgInitialize::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case IDC_INIT_ControlCard_CHECK:
		case IDC_INIT_AglientFunc_CHECK:
		case IDC_INIT_HarvardPump_CHECK:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgInitialize::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitProgress();
	InitEdit();
	GetDlgItem(IDC_INIT_ControlCard_CHECK)->EnableWindow(FALSE);
	GetDlgItem(IDC_INIT_AglientFunc_CHECK)->EnableWindow(FALSE);
	GetDlgItem(IDC_INIT_HarvardPump_CHECK)->EnableWindow(FALSE);

	return TRUE;  
}


void CDlgInitialize::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgInitialize::OnCancel()
{
	DestroyWindow();
}


void CDlgInitialize::Cancel()
{
	OnCancel();
}


void CDlgInitialize::Release()
{
	if (NULL != theApp.m_pInitUIThread)
	{
		theApp.m_pInitUIThread->ExitInstance();
		theApp.m_pInitUIThread = NULL;
	}
}


void CDlgInitialize::InitProgress()
{
	m_progressInit.SetRange(0, 100);
	m_progressInit.ShowPercent(false);
	m_progressInit.SetPos(0);
}


void CDlgInitialize::InitEdit()
{
	COLORREF textColor = RGB(0, 0, 0);
	COLORREF backColor = RGB(180, 255, 255);
	COLORREF backColorFocus = RGB(180, 255, 255);
	m_editInit.SetBkClr(backColor);
	m_editInit.SetBkClrFocus(backColorFocus);
	m_editInit.SetTextFont(12, true, false, _T("Arial"));
	m_editInit.SetTextClr(textColor);
	m_editInit.SetWindowText(_T(""));
}


BOOL CDlgInitialize::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgInitialize::InitFinish()
{
	Cancel();
	theApp.m_bWinMainBegin = true;
}


void CDlgInitialize::InitExit()
{
	//�رպ���������
// 	if (theApp.m_JetAglientFunc.IsDeviceConnect())
// 	{
// 		theApp.m_JetAglientFunc.Disconnect();
// 	}

	//�ر�������
// 	if (theApp.m_JetHarvardPump.IsHarvardOpen())
// 	{
// 		theApp.m_JetHarvardPump.CloseHarvardPump();
// 	}	

	//�ر���ѹ����
//	theApp.m_JetAirPress.UnInit();

	Cancel();
	theApp.m_bAppExit = true;
}