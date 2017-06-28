// DlgTransferAuto.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgTransferAuto.h"
#include "afxdialogex.h"


// CDlgTransferAuto �Ի���

IMPLEMENT_DYNAMIC(CDlgTransferAuto, CDialog)

CDlgTransferAuto::CDlgTransferAuto(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransferAuto::IDD, pParent)
{
	m_pProCore = pProCore;
}

CDlgTransferAuto::~CDlgTransferAuto()
{
	Release();
}

void CDlgTransferAuto::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSFER_A_GB1_GROUP, m_GB1);
	DDX_Control(pDX, IDC_TRANSFER_A_GB2_GROUP, m_GB2);
	DDX_Control(pDX, IDC_TRANSFER_A_GB3_GROUP, m_GB3);
}


BEGIN_MESSAGE_MAP(CDlgTransferAuto, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_TRANSFER_A_CameraTransUp_RADIO, &CDlgTransferAuto::OnBnClickedTransferACameraTransUpRadio)
END_MESSAGE_MAP()


// CDlgTransferAuto ��Ϣ�������
void CDlgTransferAuto::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgTransferAuto::OnCancel()
{
	DestroyWindow();
}


void CDlgTransferAuto::Cancel()
{
	OnCancel();
}


void CDlgTransferAuto::Release()
{

}


HBRUSH CDlgTransferAuto::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case IDC_TRANSFER_A_OffsetAngle_STATIC:
		case IDC_TRANSFER_A_YOffset_STATIC:
		case IDC_TRANSFER_A_ActiveMode_RADIO:
		case IDC_TRANSFER_A_PassiveMode_RADIO:
		case IDC_TRANSFER_A_LowSpeed_RADIO:
		case IDC_TRANSFER_A_MediumSpeed_RADIO:
		case IDC_TRANSFER_A_HighSpeed_RADIO:
		case IDC_TRANSFER_A_CameraTransUp_RADIO:
		case IDC_TRANSFER_A_CameraTransDown_RADIO:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgTransferAuto::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgTransferAuto::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();
	InitWindowHandle();

	return TRUE;  
}

void CDlgTransferAuto::InitDlgCtrl()
{
	m_GB1.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetAlignment(SS_CENTER);

	m_GB2.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetAlignment(SS_CENTER);

	m_GB3.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetAlignment(SS_CENTER);

	m_bmpBtn[0].SubclassDlgItem(IDC_TRANSFER_A_OK_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(16);
	m_bmpBtn[0].SetTitle("ȷ��");

	m_bmpBtn[1].SubclassDlgItem(IDC_TRANSFER_A_Start_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(16);
	m_bmpBtn[1].SetTitle("��ʼ");

	m_bmpBtn[2].SubclassDlgItem(IDC_TRANSFER_A_Pause_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(16);
	m_bmpBtn[2].SetTitle("��ͣ");

	m_bmpBtn[3].SubclassDlgItem(IDC_TRANSFER_A_Stop_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[3].SetFont(16);
	m_bmpBtn[3].SetTitle("ֹͣ");
}

BOOL CDlgTransferAuto::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgTransferAuto::InitWindowHandle()
{
	SetCheck("~father");
	Hlong hlWnd;
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_TRANSFER_A_PicShow_STATIC);
	hlWnd = (Hlong)(pWnd ->GetSafeHwnd());
	CRect rc; 
	pWnd->GetClientRect(&rc);
	m_winSize_Pic.width = rc.Width();
	m_winSize_Pic.height = rc.Height();

	OpenWindow(0, 0, rc.Width(), rc.Height(), hlWnd, "", "", &m_windowHandle_Pic);
	SetPart(m_windowHandle_Pic, 0, 0, rc.Height()-1, rc.Width()-1);
	SetColor(m_windowHandle_Pic, "yellow");
	SetWindowAttr("background_color", "black");
	SetCheck("father");
}


void CDlgTransferAuto::OnBnClickedTransferACameraTransUpRadio()
{
	if (NULL == m_pProCore) return;
	m_pProCore->SwitchCamera(TRANS_UP);
	m_pProCore->SetShowInfo(TRANS_UP, m_windowHandle_Pic, m_winSize_Pic);
}
