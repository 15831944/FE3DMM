// DlgPrint.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgPrint.h"
#include "afxdialogex.h"


// CDlgPrint �Ի���

IMPLEMENT_DYNAMIC(CDlgPrint, CDialog)

CDlgPrint::CDlgPrint(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrint::IDD, pParent)
{
	m_pProCore								= pProCore;
	m_pCustomeTab						= NULL;
	m_pDlgPrintParamAdjust		= NULL;
	m_pDlgPrintMotionControl	= NULL;
	m_pDlgPrintPrintOperate		= NULL;
}

CDlgPrint::~CDlgPrint()
{
	Release();
}

void CDlgPrint::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPrint, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_PRINT_TABCTRL, &CDlgPrint::OnCustomeTabChange)
END_MESSAGE_MAP()


// CDlgPrint ��Ϣ�������


void CDlgPrint::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}

void CDlgPrint::OnCancel()
{
	DestroyWindow();
}


void CDlgPrint::Cancel()
{
	//���˳���ӡ�߳�
	if (NULL != m_pProCore)
	{
		m_pProCore->GetProPrint()->ExitPrintThread();
	}

	Sleep(500);    //�ȴ��߳��˳�

	//�ر��Ӵ���Cancel();
	m_pDlgPrintParamAdjust->Cancel();
	m_pDlgPrintMotionControl->Cancel();
	m_pDlgPrintPrintOperate->Cancel();

	OnCancel();
}


void CDlgPrint::Release()
{
	if (NULL != m_pCustomeTab)
	{
		delete m_pCustomeTab;
		m_pCustomeTab = NULL;
	}
}


HBRUSH CDlgPrint::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_PRINT_TAB_STATIC:
		case IDC_PRINT_SUWIN_STATIC:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgPrint::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC; 
	//CBitmap����
	CBitmap Bitmap,*pOldBitmap; 
	//BITMAP���
	BITMAP bm; 
	//����λͼ
	Bitmap.LoadBitmap(IDB_BITMAP_SUBDLG_BG); 
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


BOOL CDlgPrint::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCustomeTab();
	CreateSubWindow();
	ShowSubWindow(0);

	return TRUE;
}


bool CDlgPrint::InitCustomeTab()
{
	bool bResult = false;
	m_pCustomeTab = new CD2DCustomeTable();
	if (NULL != m_pCustomeTab)
	{
		m_pCustomeTab->InitializeButtonSize(3);
		CRect rect;
		GetDlgItem(IDC_PRINT_TAB_STATIC)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.top = 0;
		rect.left = 0;
		m_pCustomeTab->Create(this, rect, IDC_PRINT_TABCTRL);

		CStringArray nameArray;
		nameArray.Add(_T("�˶�����"));
		nameArray.Add(_T("��������"));
		nameArray.Add(_T("��ӡ����"));

		m_pCustomeTab->InitializeButtonName(nameArray);
		m_pCustomeTab->ShowWindow(SW_SHOW);
		bResult = true;
	}

	return bResult;
}


void CDlgPrint::OnCustomeTabChange(NMHDR *pNMHDR,LRESULT * pResult)
{
	TBNOTIFY *pNotify = (TBNOTIFY*)(pNMHDR);
	int nChioce = pNotify->iItem;

	ShowSubWindow(nChioce);
}


void CDlgPrint::CreateSubWindow()
{
	m_pDlgPrintMotionControl = new CDlgPrintMotionControl(m_pProCore);
	ASSERT(m_pDlgPrintMotionControl);
	m_pDlgPrintMotionControl->Create(IDD_DLG_PRINT_MOTION, GetDlgItem(IDC_PRINT_SUWIN_STATIC));

	m_pDlgPrintParamAdjust = new CDlgPrintParamAdjust(m_pProCore);
	ASSERT(m_pDlgPrintParamAdjust);
	m_pDlgPrintParamAdjust->Create(IDD_DLG_PRINT_PARAM, GetDlgItem(IDC_PRINT_SUWIN_STATIC));

	m_pDlgPrintPrintOperate = new CDlgPrintPrintOperate(m_pProCore);
	ASSERT(m_pDlgPrintPrintOperate);
	m_pDlgPrintPrintOperate->Create(IDD_DLG_PRINT_PRINTING, GetDlgItem(IDC_PRINT_SUWIN_STATIC));

	m_listSubWindow.AddTail(m_pDlgPrintMotionControl);
	m_listSubWindow.AddTail(m_pDlgPrintParamAdjust);
	m_listSubWindow.AddTail(m_pDlgPrintPrintOperate);
}

void CDlgPrint::ShowSubWindow(int iIndex)
{
	int iCount = m_listSubWindow.GetSize();
	if (!m_listSubWindow.IsEmpty())
	{
		for (int i = 0; i < iCount; i++)
		{
			POSITION pos = m_listSubWindow.FindIndex(i);
			CDialog *pDlgTemp = m_listSubWindow.GetAt(pos);

			if (i == iIndex)
				pDlgTemp->ShowWindow(SW_SHOW);
			else
				pDlgTemp->ShowWindow(SW_HIDE);		
		}
	}
}

BOOL CDlgPrint::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
