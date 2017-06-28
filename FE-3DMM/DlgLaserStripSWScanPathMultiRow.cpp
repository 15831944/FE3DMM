// DlgLaserStripSWScanPathMultiRow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgLaserStripSWScanPathMultiRow.h"
#include "afxdialogex.h"
#include "DlgLaserStripSubWin.h"


// CDlgLaserStripSWScanPathMultiRow �Ի���

IMPLEMENT_DYNAMIC(CDlgLaserStripSWScanPathMultiRow, CDialog)

CDlgLaserStripSWScanPathMultiRow::CDlgLaserStripSWScanPathMultiRow(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLaserStripSWScanPathMultiRow::IDD, pParent)
{
	m_pDlgLaserStripSubWinMain = (CDlgLaserStripSubWin*)pParent;
	
}

CDlgLaserStripSWScanPathMultiRow::~CDlgLaserStripSWScanPathMultiRow()
{
	Release();
}

void CDlgLaserStripSWScanPathMultiRow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLaserStripSWScanPathMultiRow, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_LASERSTRIP_SUB_SP_MR_ScanPathSet_BTN, &CDlgLaserStripSWScanPathMultiRow::OnBnClickedLaserstripSubSpMrScanpathsetBtn)
END_MESSAGE_MAP()


// CDlgLaserStripSWScanPathMultiRow ��Ϣ�������


void CDlgLaserStripSWScanPathMultiRow::OnCancel()
{
	DestroyWindow();
}


void CDlgLaserStripSWScanPathMultiRow::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgLaserStripSWScanPathMultiRow::Cancel()
{
	OnCancel();
}


void CDlgLaserStripSWScanPathMultiRow::Release()
{

}


BOOL CDlgLaserStripSWScanPathMultiRow::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CDlgLaserStripSWScanPathMultiRow::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgLaserStripSWScanPathMultiRow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgLaserStripSWScanPathMultiRow::InitDlgCtrl()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanPathSet_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("����");
}

BOOL CDlgLaserStripSWScanPathMultiRow::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgLaserStripSWScanPathMultiRow::OnBnClickedLaserstripSubSpMrScanpathsetBtn()
{
	if (NULL == m_pDlgLaserStripSubWinMain)	return;
	m_pDlgLaserStripSubWinMain->GetParamScan()->scanmode = MultiROW;

	CString strTemp = _T("");
	double dEditValue = 0.0;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanLen_EDIT)->GetWindowText(strTemp);
	dEditValue = _ttof(strTemp);
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 10000.0)
		dEditValue = 10000.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanLen_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramMultiScan.dScanLen = dEditValue;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanSpace_EDIT)->GetWindowText(strTemp);
	dEditValue = _ttof(strTemp);
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 5000.0)
		dEditValue = 5000.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanSpace_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramMultiScan.dScanSpace = dEditValue;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanSpeed_EDIT)->GetWindowText(strTemp);
	dEditValue = _ttof(strTemp);
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 1000.0)
		dEditValue = 1000.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanSpeed_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramMultiScan.dScanSpeed = dEditValue;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_TransRowSpeed_EDIT)->GetWindowText(strTemp);
	dEditValue = _ttof(strTemp);
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 1000.0)
		dEditValue = 1000.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_TransRowSpeed_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramMultiScan.dTransRowSpeed = dEditValue;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanNum_EDIT)->GetWindowText(strTemp);
	int nEditValue = _ttoi(strTemp);
	if (nEditValue < 0)
		nEditValue = 0;
	else if (nEditValue > 10000)
		nEditValue = 10000;	
	strTemp.Format(_T("%d"), nEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanNum_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramMultiScan.nScanNum = nEditValue;

	m_pDlgLaserStripSubWinMain->SetParamInStatic();
}


void CDlgLaserStripSWScanPathMultiRow::ApplyScanParamToMultiPathWin()
{
	ParamScan* pScanParam = NULL;
	pScanParam = m_pDlgLaserStripSubWinMain->GetParamScan();
	if (NULL == pScanParam)	return;

	CString strTemp = _T("");
	double dEditValue = 0.0;

	dEditValue = pScanParam->paramMultiScan.dScanLen;
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanLen_EDIT)->SetWindowText(strTemp);

	dEditValue = pScanParam->paramMultiScan.dScanSpace;
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanSpace_EDIT)->SetWindowText(strTemp);

	dEditValue = pScanParam->paramMultiScan.dScanSpeed;
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanSpeed_EDIT)->SetWindowText(strTemp);

	dEditValue = pScanParam->paramMultiScan.dTransRowSpeed;
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_TransRowSpeed_EDIT)->SetWindowText(strTemp);

	dEditValue = pScanParam->paramMultiScan.nScanNum;
	strTemp.Format(_T("%d"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_MR_ScanNum_EDIT)->SetWindowText(strTemp);
}