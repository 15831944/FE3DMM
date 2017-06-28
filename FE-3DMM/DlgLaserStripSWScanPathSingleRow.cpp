// DlgLaserStripSWScanPathSingleRow.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgLaserStripSWScanPathSingleRow.h"
#include "afxdialogex.h"
#include "DlgLaserStripSubWin.h"


// CDlgLaserStripSWScanPathSingleRow �Ի���

IMPLEMENT_DYNAMIC(CDlgLaserStripSWScanPathSingleRow, CDialog)

CDlgLaserStripSWScanPathSingleRow::CDlgLaserStripSWScanPathSingleRow(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLaserStripSWScanPathSingleRow::IDD, pParent)
{
	m_pDlgLaserStripSubWinMain = (CDlgLaserStripSubWin*)pParent;

}

CDlgLaserStripSWScanPathSingleRow::~CDlgLaserStripSWScanPathSingleRow()
{
	Release();
}

void CDlgLaserStripSWScanPathSingleRow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLaserStripSWScanPathSingleRow, CDialog)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_LASERSTRIP_SUB_SP_SR_ScanPathSet_BTN, &CDlgLaserStripSWScanPathSingleRow::OnBnClickedLaserstripSubSpSrScanpathsetBtn)
END_MESSAGE_MAP()


// CDlgLaserStripSWScanPathSingleRow ��Ϣ�������


void CDlgLaserStripSWScanPathSingleRow::OnCancel()
{
	DestroyWindow();
}


void CDlgLaserStripSWScanPathSingleRow::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgLaserStripSWScanPathSingleRow::Cancel()
{
	OnCancel();
}


void CDlgLaserStripSWScanPathSingleRow::Release()
{

}


BOOL CDlgLaserStripSWScanPathSingleRow::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CDlgLaserStripSWScanPathSingleRow::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDlgLaserStripSWScanPathSingleRow::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgLaserStripSWScanPathSingleRow::InitDlgCtrl()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanPathSet_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("����");
}


BOOL CDlgLaserStripSWScanPathSingleRow::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgLaserStripSWScanPathSingleRow::OnBnClickedLaserstripSubSpSrScanpathsetBtn()
{
	if (NULL == m_pDlgLaserStripSubWinMain)	return;
	m_pDlgLaserStripSubWinMain->GetParamScan()->scanmode = SingleROW;

	CString strTemp = _T("");
	double dEditValue = 0.0;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanLen_EDIT)->GetWindowText(strTemp);
	dEditValue = _ttof(strTemp);
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 10000.0)
		dEditValue = 10000.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanLen_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramSingleScan.dScanLen = dEditValue;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanSpeed_EDIT)->GetWindowText(strTemp);
	dEditValue = _ttof(strTemp);
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 1000.0)
		dEditValue = 1000.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanSpeed_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramSingleScan.dScanSpeed = dEditValue;

	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanNum_EDIT)->GetWindowText(strTemp);
	int nEditValue = _ttoi(strTemp);
	if (nEditValue < 0)
		nEditValue = 0;
	else if (nEditValue > 10000)
		nEditValue = 10000;	
	strTemp.Format(_T("%d"), nEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanNum_EDIT)->SetWindowText(strTemp);	
	m_pDlgLaserStripSubWinMain->GetParamScan()->paramSingleScan.nScanNum = nEditValue;

	m_pDlgLaserStripSubWinMain->SetParamInStatic();
}


void CDlgLaserStripSWScanPathSingleRow::ApplyScanParamToSinglePathWin()
{
	ParamScan* pScanParam = NULL;
	pScanParam = m_pDlgLaserStripSubWinMain->GetParamScan();
	if (NULL == pScanParam)	return;

	CString strTemp = _T("");
	double dEditValue = 0.0;

	dEditValue = pScanParam->paramSingleScan.dScanLen;
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanLen_EDIT)->SetWindowText(strTemp);

	dEditValue = pScanParam->paramSingleScan.dScanSpeed;
	strTemp.Format(_T("%.2f"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanSpeed_EDIT)->SetWindowText(strTemp);

	dEditValue = pScanParam->paramSingleScan.nScanNum;
	strTemp.Format(_T("%d"), dEditValue);
	GetDlgItem(IDC_LASERSTRIP_SUB_SP_SR_ScanNum_EDIT)->SetWindowText(strTemp);
}