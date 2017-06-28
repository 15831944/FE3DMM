// DlgLaserStripSWScanPath.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgLaserStripSWScanPath.h"
#include "afxdialogex.h"
#include "DlgLaserStripSubWin.h"


// CDlgLaserStripSWScanPath �Ի���

IMPLEMENT_DYNAMIC(CDlgLaserStripSWScanPath, CDialog)

CDlgLaserStripSWScanPath::CDlgLaserStripSWScanPath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLaserStripSWScanPath::IDD, pParent)
{
	m_pDlgLaserStripSubWinMain = (CDlgLaserStripSubWin*)pParent;
	m_pDlgLaserStripSingleRow = NULL;
	m_pDlgLaserStripMultiRow = NULL;
}

CDlgLaserStripSWScanPath::~CDlgLaserStripSWScanPath()
{
	Release();
}

void CDlgLaserStripSWScanPath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLaserStripSWScanPath, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_LASERSTRIP_SUB_SP_SingleRow_RADIO, &CDlgLaserStripSWScanPath::OnBnClickedLaserstripSubSpSinglerowRadio)
	ON_BN_CLICKED(IDC_LASERSTRIP_SUB_SP_MultiRow_RADIO, &CDlgLaserStripSWScanPath::OnBnClickedLaserstripSubSpMultirowRadio)
END_MESSAGE_MAP()


// CDlgLaserStripSWScanPath ��Ϣ�������


void CDlgLaserStripSWScanPath::OnCancel()
{
	DestroyWindow();
}


void CDlgLaserStripSWScanPath::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgLaserStripSWScanPath::Cancel()
{
	//���Ӵ���Cancel();
	m_pDlgLaserStripSingleRow->Cancel();
	m_pDlgLaserStripMultiRow->Cancel();
	OnCancel();
}


void CDlgLaserStripSWScanPath::Release()
{

}


BOOL CDlgLaserStripSWScanPath::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CDlgLaserStripSWScanPath::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case IDC_LASERSTRIP_SUB_SP_PathWin_STATIC:
		case IDC_LASERSTRIP_SUB_SP_SingleRow_RADIO:
		case IDC_LASERSTRIP_SUB_SP_MultiRow_RADIO:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgLaserStripSWScanPath::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_pDlgLaserStripSingleRow = new CDlgLaserStripSWScanPathSingleRow(m_pDlgLaserStripSubWinMain);
	ASSERT(m_pDlgLaserStripSingleRow);
	m_pDlgLaserStripSingleRow->Create(IDD_DLG_LASERSTRIP_SUB_SCANPATH_SingleRow, GetDlgItem(IDC_LASERSTRIP_SUB_SP_PathWin_STATIC));
	
	m_pDlgLaserStripMultiRow = new CDlgLaserStripSWScanPathMultiRow(m_pDlgLaserStripSubWinMain);
	ASSERT(m_pDlgLaserStripMultiRow);
	m_pDlgLaserStripMultiRow->Create(IDD_DLG_LASERSTRIP_SUB_SCANPATH_MultiRow, GetDlgItem(IDC_LASERSTRIP_SUB_SP_PathWin_STATIC));

	CheckRadioButton(IDC_LASERSTRIP_SUB_SP_SingleRow_RADIO,IDC_LASERSTRIP_SUB_SP_MultiRow_RADIO,IDC_LASERSTRIP_SUB_SP_SingleRow_RADIO);
	ShowSubDlg(SW_SHOW, SW_HIDE);

	return TRUE;
}


void CDlgLaserStripSWScanPath::OnClose()
{
	if (NULL != m_pDlgLaserStripSubWinMain)
	{
		m_pDlgLaserStripSubWinMain->OnBnClickedLaserstripSScanPathSetBtn();
	}
}

void CDlgLaserStripSWScanPath::OnBnClickedLaserstripSubSpSinglerowRadio()
{
	ShowSubDlg(SW_SHOW, SW_HIDE);
}


void CDlgLaserStripSWScanPath::OnBnClickedLaserstripSubSpMultirowRadio()
{
	ShowSubDlg(SW_HIDE, SW_SHOW);
}


void CDlgLaserStripSWScanPath::ShowSubDlg(INT singlerow, INT multirow)
{
	m_pDlgLaserStripSingleRow->ShowWindow(singlerow);
	m_pDlgLaserStripMultiRow->ShowWindow(multirow);
}


BOOL CDlgLaserStripSWScanPath::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgLaserStripSWScanPath::ApplyScanParamToPathWin()
{
	if (NULL == m_pDlgLaserStripSubWinMain) return;

	ParamScan* pScanParam = NULL;
	pScanParam = m_pDlgLaserStripSubWinMain->GetParamScan();
	if (NULL == pScanParam)	return;

	if (pScanParam->scanmode == SingleROW)
	{
		if (NULL != m_pDlgLaserStripSingleRow)
			m_pDlgLaserStripSingleRow->ApplyScanParamToSinglePathWin();
	}
	else if (pScanParam->scanmode == MultiROW)
	{
		if (NULL != m_pDlgLaserStripMultiRow)
			m_pDlgLaserStripMultiRow->ApplyScanParamToMultiPathWin();
	}
}