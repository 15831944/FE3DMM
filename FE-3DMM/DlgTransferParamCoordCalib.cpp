// DlgTransferParamCoordCalib.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "FE-3DMMDlg.h"
#include "DlgTransferParamCoordCalib.h"
#include "DlgTransfer.h"
#include "afxdialogex.h"


// CDlgTransferParamCoordCalib �Ի���

IMPLEMENT_DYNAMIC(CDlgTransferParamCoordCalib, CDialogEx)

int CDlgTransferParamCoordCalib::m_iPressCount = 0;

CDlgTransferParamCoordCalib::CDlgTransferParamCoordCalib(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTransferParamCoordCalib::IDD, pParent)
{
	ASSERT(pProCore);
	m_pProCore = pProCore;
	SetParentWnd();
}

CDlgTransferParamCoordCalib::~CDlgTransferParamCoordCalib()
{
	Release();
}

void CDlgTransferParamCoordCalib::Release()
{

}

void CDlgTransferParamCoordCalib::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgTransferParamCoordCalib, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_TRANSFER_P_C_SaveCenter_BTN, &CDlgTransferParamCoordCalib::OnBnClickedTransferPCSavecenterBtn)
	ON_BN_CLICKED(IDC_TRANSFER_P_C_SaveCam_BTN, &CDlgTransferParamCoordCalib::OnBnClickedTransferPCClibBtn)
	ON_BN_CLICKED(IDC_TRANSFER_P_C_CalibPickerCam_BTN, &CDlgTransferParamCoordCalib::OnBnClickedTransferPCCalibpickercamBtn)
END_MESSAGE_MAP()


// CDlgTransferParamCoordCalib ��Ϣ�������
void CDlgTransferParamCoordCalib::Cancel()
{
	OnCancel();
}

void CDlgTransferParamCoordCalib::OnCancel()
{
	//CWnd* pParent = ((CFE3DMMDlg*)AfxGetMainWnd())->m_pDlgTransfer->m_pDlgTransferParaLearn;
    CWnd* pBtnWnd = (static_cast<CWnd*>(m_pParent))->GetDlgItem(IDC_TRANSFER_P_CoordCalib_BTN);
	pBtnWnd->EnableWindow(TRUE);
	DestroyWindow();
}

void CDlgTransferParamCoordCalib::PostNcDestroy()
{
	CDialogEx::PostNcDestroy();	
	delete this;
}

BOOL CDlgTransferParamCoordCalib::OnEraseBkgnd(CDC* pDC)
{
	CDC MemDC;
	CBitmap Bitmap, *pOldBitmap;
	BITMAP bm;
	Bitmap.LoadBitmap(IDB_BITMAP_BACKGROUND);
	Bitmap.GetObject(sizeof(BITMAP),&bm); 
	MemDC.CreateCompatibleDC(pDC);
	pOldBitmap = (CBitmap*)(MemDC.SelectObject(&Bitmap));

	CRect rcClient;
	GetClientRect(&rcClient);

	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),&MemDC,0,0,SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	MemDC.DeleteDC(); 
	return TRUE;
}


HBRUSH CDlgTransferParamCoordCalib::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
			case IDC_STATIC:
			{
				CFont font;
				font.CreatePointFont( 120, _T("����") );
				pDC->SetBkMode(TRANSPARENT); 
				pDC->SetTextColor(RGB(0,0,0)); 
				pDC->SelectObject(&font);
				return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
			}
		case IDC_TRANSFER_P_C_NOTE_STATIC:
			{
				CFont font;
				font.CreatePointFont( 120, _T("����") );
				pDC->SetBkMode(TRANSPARENT); 
				pDC->SetTextColor(RGB(0,0,0)); 
				pDC->SelectObject(&font);
				return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
			}
		default: 
			break; 
		} 
	}
	return hbr;
}

void CDlgTransferParamCoordCalib::SetParentWnd()
{
	m_pParent = ((CFE3DMMDlg*)AfxGetMainWnd())->m_pDlgTransfer->m_pDlgTransferParaLearn;
	ASSERT(m_pParent);
}


BOOL CDlgTransferParamCoordCalib::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgTransferParamCoordCalib::InitCtrl()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_TRANSFER_P_C_SaveCenter_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("�����е������");

	m_bmpBtn[1].SubclassDlgItem(IDC_TRANSFER_P_C_SaveCam_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(15);
	m_bmpBtn[1].SetTitle("�������λ��");
	m_bmpBtn[1].EnableWindow(FALSE);

	m_bmpBtn[2].SubclassDlgItem(IDC_TRANSFER_P_C_CalibPickerCam_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(15);
	m_bmpBtn[2].SetTitle("��ɱ궨");
	m_bmpBtn[2].EnableWindow(FALSE);

	m_bmpBtn[3].SubclassDlgItem(IDC_TRANSFER_P_C_SaveX_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[3].SetFont(15);
	m_bmpBtn[3].SetTitle("����X����ֵ");

	m_bmpBtn[4].SubclassDlgItem(IDC_TRANSFER_P_C_SaveY_BTN, this);
	m_bmpBtn[4].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[4].SetFont(15);
	m_bmpBtn[4].SetTitle("����Y����ֵ");

	m_bmpBtn[5].SubclassDlgItem(IDC_TRANSFER_P_C_SaveZ_BTN, this);
	m_bmpBtn[5].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[5].SetFont(15);
	m_bmpBtn[5].SetTitle("����Z����ֵ");
}


void CDlgTransferParamCoordCalib::OnBnClickedTransferPCSavecenterBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#ifndef FE_DEBUG_OFFLINE
	CCtrlMotor *pMotorX;
	pMotorX = m_pProCore->GetProTransfer()->GetMotorTransferX();
	ASSERT(pMotorX);
	m_fTransferPickPosX = pMotorX->GetMotorPostion();
#endif
	MessageBox(_T("����ɹ�"), _T("��ʾ"), MB_OK);
	m_bmpBtn[1].EnableWindow(TRUE);
}


void CDlgTransferParamCoordCalib::OnBnClickedTransferPCClibBtn()
{
	//��ȡ��ͼʱ�����λ��
	CCtrlMotor *pMotorX;
	pMotorX = m_pProCore->GetProTransfer()->GetMotorTransferX();
	ASSERT(pMotorX);
	m_fTransCamPosX = pMotorX->GetMotorPostion();

	//תӡ��������ɼ�һ��ͼ��
	PylonCamera  * TransCam = m_pProCore->GetCameraTransDown();
		
	//��λԲ��λ����������ĵ�ƫ��
	double fOffsetX, fOffsetY;   
	//��е���������������ƫ��
	double fDisPickCamX, fDisPickCamY;
	
	if (LocateCircle(TransCam->GetSingleLocal(), fOffsetX, fOffsetY))
	{
		fDisPickCamX = (m_fTransCamPosX - m_fTransferPickPosX) + fOffsetX;
		fDisPickCamY = fOffsetY;

		PickCamOffset tempOffset;
		tempOffset.fOffsetX = fDisPickCamX;
		tempOffset.fOffsetY = fDisPickCamY;
		m_vecOffset.push_back(tempOffset);

		MessageBox(_T("����ɹ�"), _T("��ʾ"), MB_OK);

		if ( ++m_iPressCount == 3)
		{
			m_bmpBtn[2].EnableWindow(TRUE);
		}
	}
}


void CDlgTransferParamCoordCalib::OnBnClickedTransferPCCalibpickercamBtn()
{
	double sumX = 0.0, sumY = 0.0;
	std::vector<PickCamOffset>::iterator beg = m_vecOffset.begin();
	for (; beg != m_vecOffset.end(); ++beg)
	{
		sumX += (*beg).fOffsetX;
		sumY += (*beg).fOffsetY;
	}
	m_fOffsetX = sumX / m_vecOffset.size();
	m_fOffsetY = sumY / m_vecOffset.size();
	//������
	m_pProCore->GetParamData()->GetParamTransfer()->fDisPickerCamX = m_fOffsetX;
	m_pProCore->GetParamData()->GetParamTransfer()->fDisPickerCamY = m_fOffsetY;
	m_iPressCount = 0;
	m_bmpBtn[2].EnableWindow(FALSE);
}


BOOL CDlgTransferParamCoordCalib::LocateCircle(const HObject* hoImage, const double &fOffsetX, const double&fOffsetY)
{
	return TRUE;
}