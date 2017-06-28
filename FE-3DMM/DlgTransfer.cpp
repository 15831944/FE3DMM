// DlgTransfer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgTransfer.h"
#include "afxdialogex.h"


// CDlgTransfer �Ի���

IMPLEMENT_DYNAMIC(CDlgTransfer, CDialog)

CDlgTransfer::CDlgTransfer(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransfer::IDD, pParent)
{
	m_pProCore							= pProCore;
	m_pCustomeTab					= NULL;
	m_pDlgTransferAuto			= NULL;
	m_pDlgTransferManual		= NULL;
	m_pDlgTransferParaLearn	= NULL;
	m_pDlgTransferVisTrain		= NULL;
}

CDlgTransfer::~CDlgTransfer()
{
	Release();
}

void CDlgTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTransfer, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_CLICK, IDC_TRANSFER_TABCTRL, &CDlgTransfer::OnCustomeTabChange)
END_MESSAGE_MAP()


// CDlgTransfer ��Ϣ�������

void CDlgTransfer::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgTransfer::OnCancel()
{
	DestroyWindow();
}


void CDlgTransfer::Cancel()
{
	//���Ӵ���Cancel();
	m_pDlgTransferAuto->Cancel();
	m_pDlgTransferManual->Cancel();
	m_pDlgTransferParaLearn->Cancel();
	m_pDlgTransferVisTrain->Cancel();
	OnCancel();
}


void CDlgTransfer::Release()
{
	if (NULL != m_pCustomeTab)
	{
		delete m_pCustomeTab;
		m_pCustomeTab = NULL;
	}
}


HBRUSH CDlgTransfer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_TRANSFER_TAB_STATIC:
		case IDC_TRANSFER_SUWIN_STATIC:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgTransfer::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgTransfer::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitCustomeTab();
	CreateSubWindow();
	ShowSubWindow(0);

	return TRUE;
}

bool CDlgTransfer::InitCustomeTab()
{
	bool bResult = false;
	m_pCustomeTab = new CD2DCustomeTable();
	if (NULL != m_pCustomeTab)
	{
		m_pCustomeTab->InitializeButtonSize(4);
		CRect rect;
		GetDlgItem(IDC_TRANSFER_TAB_STATIC)->GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.top = 0;
		rect.left = 0;
		m_pCustomeTab->Create(this, rect, IDC_TRANSFER_TABCTRL);

		CStringArray nameArray;
		nameArray.Add(_T("�ֶ�ʵ��"));
		nameArray.Add(_T("����ѧϰ"));
		nameArray.Add(_T("�Ӿ�ѵ��"));
		nameArray.Add(_T("�Զ���ʾ"));
		m_pCustomeTab->InitializeButtonName(nameArray);
		m_pCustomeTab->ShowWindow(SW_SHOW);
		bResult = true;
	}

	return bResult;
}

void CDlgTransfer::OnCustomeTabChange(NMHDR *pNMHDR,LRESULT * pResult)
{
	TBNOTIFY *pNotify = (TBNOTIFY*)(pNMHDR);
	int nChioce = pNotify->iItem;

	ShowSubWindow(nChioce);
}

void CDlgTransfer::CreateSubWindow()
{
	m_pDlgTransferManual = new CDlgTransferManual(m_pProCore);
	ASSERT(m_pDlgTransferManual);
	m_pDlgTransferManual->Create(IDD_DLG_TRANSFER_MANUAL, GetDlgItem(IDC_TRANSFER_SUWIN_STATIC));

	m_pDlgTransferParaLearn = new CDlgTransferParamLearn(m_pProCore);
	ASSERT(m_pDlgTransferParaLearn);
	m_pDlgTransferParaLearn->Create(IDD_DLG_TRANSFER_PARAM, GetDlgItem(IDC_TRANSFER_SUWIN_STATIC));

	m_pDlgTransferVisTrain = new CDlgTransferVisionTrain(m_pProCore);
	ASSERT(m_pDlgTransferVisTrain);
	m_pDlgTransferVisTrain->Create(IDD_DLG_TRANSFER_VISION, GetDlgItem(IDC_TRANSFER_SUWIN_STATIC));

	m_pDlgTransferAuto = new CDlgTransferAuto(m_pProCore);
	ASSERT(m_pDlgTransferAuto);
	m_pDlgTransferAuto->Create(IDD_DLG_TRANSFER_AUTO, GetDlgItem(IDC_TRANSFER_SUWIN_STATIC));

	m_listSubWindow.AddTail(m_pDlgTransferManual);
	m_listSubWindow.AddTail(m_pDlgTransferParaLearn);
	m_listSubWindow.AddTail(m_pDlgTransferVisTrain);
	m_listSubWindow.AddTail(m_pDlgTransferAuto);
}

void CDlgTransfer::ShowSubWindow(int iIndex)
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

BOOL CDlgTransfer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
