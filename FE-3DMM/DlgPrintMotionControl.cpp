// DlgPrintMotionControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgPrintMotionControl.h"
#include "afxdialogex.h"


// CDlgPrintMotionControl �Ի���

IMPLEMENT_DYNAMIC(CDlgPrintMotionControl, CDialog)

CDlgPrintMotionControl::CDlgPrintMotionControl(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrintMotionControl::IDD, pParent)
{
	m_pProCore									= pProCore;
	m_bContinuousMove					= false;
	m_dContinMoveSpeed				= 0.0;
	m_dInterMoveStep						= 0.0;
	m_bLinkLearn								= false;
	m_pDlgPrintMotionLinkLearn	= NULL;
}

CDlgPrintMotionControl::~CDlgPrintMotionControl()
{
	Release();
}

void CDlgPrintMotionControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRINT_M_GB1_GROUP, m_GB1);
	DDX_Control(pDX, IDC_PRINT_M_GB2_GROUP, m_GB2);
	DDX_Control(pDX, IDC_PRINT_M_GB3_GROUP, m_GB3);
}


BEGIN_MESSAGE_MAP(CDlgPrintMotionControl, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_PRINT_M_ContinuMove_RADIO, &CDlgPrintMotionControl::OnBnClickedPrintMContinuMoveRadio)
	ON_BN_CLICKED(IDC_PRINT_M_InterMove_RADIO, &CDlgPrintMotionControl::OnBnClickedPrintMInterMoveRadio)
	ON_BN_CLICKED(IDC_PRINT_M_XPositive_BTN, &CDlgPrintMotionControl::OnBnClickedPrintMXpositiveBtn)
	ON_BN_CLICKED(IDC_PRINT_M_XNegative_BTN, &CDlgPrintMotionControl::OnBnClickedPrintMXnegativeBtn)
	ON_BN_CLICKED(IDC_PRINT_M_YPositive_BTN, &CDlgPrintMotionControl::OnBnClickedPrintMYpositiveBtn)
	ON_BN_CLICKED(IDC_PRINT_M_YNegative_BTN, &CDlgPrintMotionControl::OnBnClickedPrintMYnegativeBtn)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PRINT_M_ContinuMoveSpeed_SPIN, &CDlgPrintMotionControl::OnDeltaposPrintMContinuMoveSpeedSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PRINT_M_InterMoveStep_SPIN, &CDlgPrintMotionControl::OnDeltaposPrintMInterMoveStepSpin)
	ON_BN_CLICKED(IDC_PRINT_M_LinkLearn_BTN, &CDlgPrintMotionControl::OnBnClickedPrintMLinklearnBtn)
	ON_BN_CLICKED(IDC_PRINT_M_CameraLocate_RADIO, &CDlgPrintMotionControl::OnBnClickedPrintMCameralocateRadio)
END_MESSAGE_MAP()


// CDlgPrintMotionControl ��Ϣ�������
void CDlgPrintMotionControl::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgPrintMotionControl::OnCancel()
{
	DestroyWindow();
}


void CDlgPrintMotionControl::Cancel()
{
	//���Ӵ���Cancel();
	m_pDlgPrintMotionLinkLearn->Cancel();
	OnCancel();
}


void CDlgPrintMotionControl::Release()
{

}


HBRUSH CDlgPrintMotionControl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case IDC_PRINT_M_CameraLocate_RADIO:
		case IDC_PRINT_M_ContinuMove_RADIO:
		case IDC_PRINT_M_InterMove_RADIO:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgPrintMotionControl::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgPrintMotionControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();
	InitSimulatePanel();
	InitWindowHandle();

	CheckRadioButton(IDC_PRINT_M_ContinuMove_RADIO, IDC_PRINT_M_InterMove_RADIO, IDC_PRINT_M_ContinuMove_RADIO);
	m_bContinuousMove = true;
	SetMoveComponentState();

	GetDlgItem(IDC_PRINT_M_XPos_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRINT_M_YPos_EDIT)->EnableWindow(FALSE);

	m_pDlgPrintMotionLinkLearn = new CDlgPrintMotionLinkLearn(m_pProCore, this);
	ASSERT(m_pDlgPrintMotionLinkLearn);
	m_pDlgPrintMotionLinkLearn->Create(IDD_DLG_PRINT_MOTION_LINES);

	return TRUE;  
}


void CDlgPrintMotionControl::InitDlgCtrl()
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

	m_bmpBtn[0].SubclassDlgItem(IDC_PRINT_M_XPositive_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_XR,IDB_BITMAP_XRCLK,IDB_BITMAP_XR,IDB_BITMAP_XRCLK);
	
	m_bmpBtn[1].SubclassDlgItem(IDC_PRINT_M_XNegative_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_XL,IDB_BITMAP_XLCLK,IDB_BITMAP_XL,IDB_BITMAP_XLCLK);

	m_bmpBtn[2].SubclassDlgItem(IDC_PRINT_M_YPositive_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_YF,IDB_BITMAP_YFCLK,IDB_BITMAP_YF,IDB_BITMAP_YFCLK);

	m_bmpBtn[3].SubclassDlgItem(IDC_PRINT_M_YNegative_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_YB,IDB_BITMAP_YBCLK,IDB_BITMAP_YB,IDB_BITMAP_YBCLK);

	m_bmpBtn[4].SubclassDlgItem(IDC_PRINT_M_LinkLearn_BTN, this);
	m_bmpBtn[4].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[4].SetFont(15);
	m_bmpBtn[4].SetTitle("����ѧϰ>>");

	m_bmpBtn[5].SubclassDlgItem(IDC_PRINT_M_SetHomePt_BTN, this);
	m_bmpBtn[5].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[5].SetFont(15);
	m_bmpBtn[5].SetTitle("���궨");

	m_bmpBtn[6].SubclassDlgItem(IDC_PRINT_M_ToHomePt_BTN, this);
	m_bmpBtn[6].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[6].SetFont(15);
	m_bmpBtn[6].SetTitle("�����");
}


void CDlgPrintMotionControl::SetMoveComponentState()
{
	if (m_bContinuousMove)
	{
		m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_XRR,IDB_BITMAP_XRRCLK,IDB_BITMAP_XRR,IDB_BITMAP_XRRCLK);
		m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_XLL,IDB_BITMAP_XLLCLK,IDB_BITMAP_XLL,IDB_BITMAP_XLLCLK);
		m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_YFF,IDB_BITMAP_YFFCLK,IDB_BITMAP_YFF,IDB_BITMAP_YFFCLK);
		m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_YBB,IDB_BITMAP_YBBCLK,IDB_BITMAP_YBB,IDB_BITMAP_YBBCLK);
		GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_SPIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_PRINT_M_InterMoveStep_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_PRINT_M_InterMoveStep_SPIN)->EnableWindow(FALSE);
	}
	else
	{	
		m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_XR,IDB_BITMAP_XRCLK,IDB_BITMAP_XR,IDB_BITMAP_XRCLK);
		m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_XL,IDB_BITMAP_XLCLK,IDB_BITMAP_XL,IDB_BITMAP_XLCLK);
		m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_YF,IDB_BITMAP_YFCLK,IDB_BITMAP_YF,IDB_BITMAP_YFCLK);
		m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_YB,IDB_BITMAP_YBCLK,IDB_BITMAP_YB,IDB_BITMAP_YBCLK);
		GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_SPIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_PRINT_M_InterMoveStep_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_PRINT_M_InterMoveStep_SPIN)->EnableWindow(TRUE);
	}

	//ˢ�°�ť
	CRect rc;
	GetDlgItem(IDC_PRINT_M_YPositive_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);

	GetDlgItem(IDC_PRINT_M_YNegative_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);

	GetDlgItem(IDC_PRINT_M_XPositive_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);

	GetDlgItem(IDC_PRINT_M_XNegative_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);
}


void CDlgPrintMotionControl::InitSimulatePanel()
{
	CRect rcPanel;
	GetDlgItem(IDC_PRINT_M_Simulate_STATIC)->GetClientRect(&rcPanel);
	m_panelwnd.Create(GetDlgItem(IDC_PRINT_M_Simulate_STATIC),rcPanel,IDC_PRINT_M_Simulate_STATIC);
	//m_panelwnd.ShowWindow(SW_SHOW);
}


BOOL CDlgPrintMotionControl::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		CString strTemp = _T("");
		double dEditValue = 0.0;

		if (GetFocus() == GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_EDIT))
		{
			GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_EDIT)->GetWindowText(strTemp);
			dEditValue = _ttof(strTemp);
			if (dEditValue < 0.0)
				dEditValue = 0.0;
			else if (dEditValue > 500.0)
				dEditValue = 500.0;	
			strTemp.Format(_T("%.2f"), dEditValue);
			GetDlgItem(IDC_PRINT_M_ContinuMoveSpeed_EDIT)->SetWindowText(strTemp);	

			m_dContinMoveSpeed = dEditValue;
		}

		if (GetFocus() == GetDlgItem(IDC_PRINT_M_InterMoveStep_EDIT))
		{
			GetDlgItem(IDC_PRINT_M_InterMoveStep_EDIT)->GetWindowText(strTemp);
			dEditValue = _ttof(strTemp);
			if (dEditValue < 0.0)
				dEditValue = 0.0;
			else if (dEditValue > 500.0)
				dEditValue = 500.0;
			strTemp.Format(_T("%.2f"), dEditValue);
			GetDlgItem(IDC_PRINT_M_InterMoveStep_EDIT)->SetWindowText(strTemp);

			m_dInterMoveStep = dEditValue;
		}

		return TRUE;
	}

	//���Ƶ�������˶�
	if (WM_LBUTTONDOWN == pMsg->message)
	{
		if (m_bContinuousMove)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_PRINT_M_XPositive_BTN)->m_hWnd)
			{
				//m_pProCore->GetProPrint()->GetMotorX()->Jog(1);
			}
			if (pMsg->hwnd == GetDlgItem(IDC_PRINT_M_XNegative_BTN)->m_hWnd)
			{
				//m_pProCore->GetProPrint()->GetMotorX()->Jog(0);
			}
			if (pMsg->hwnd == GetDlgItem(IDC_PRINT_M_YPositive_BTN)->m_hWnd)
			{
				//m_pProCore->GetProPrint()->GetMotorY()->Jog(1);
			}
			if (pMsg->hwnd == GetDlgItem(IDC_PRINT_M_YNegative_BTN)->m_hWnd)
			{
				//m_pProCore->GetProPrint()->GetMotorY()->Jog(0);
			}
		}
	}

	if (WM_LBUTTONUP == pMsg->message)
	{
		if (m_bContinuousMove)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_PRINT_M_XPositive_BTN)->m_hWnd
				|| pMsg->hwnd == GetDlgItem(IDC_PRINT_M_XNegative_BTN)->m_hWnd)
			{
				//m_pProCore->GetProPrint()->GetMotorX()->JogStop();
			}

			if (pMsg->hwnd == GetDlgItem(IDC_PRINT_M_YPositive_BTN)->m_hWnd
				|| pMsg->hwnd == GetDlgItem(IDC_PRINT_M_YNegative_BTN)->m_hWnd)
			{
				//m_pProCore->GetProPrint()->GetMotorY()->JogStop();
			}
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgPrintMotionControl::OnBnClickedPrintMContinuMoveRadio()
{
	m_bContinuousMove = true;
	SetMoveComponentState();
}


void CDlgPrintMotionControl::OnBnClickedPrintMInterMoveRadio()
{
	m_bContinuousMove = false;
	SetMoveComponentState();
}


void CDlgPrintMotionControl::OnBnClickedPrintMXpositiveBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProPrint()->GetMotorX()->Move(m_dInterMoveStep);
}


void CDlgPrintMotionControl::OnBnClickedPrintMXnegativeBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProPrint()->GetMotorX()->Move(m_dInterMoveStep*(-1.0f));
}


void CDlgPrintMotionControl::OnBnClickedPrintMYpositiveBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProPrint()->GetMotorY()->Move(m_dInterMoveStep);

}


void CDlgPrintMotionControl::OnBnClickedPrintMYnegativeBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProPrint()->GetMotorY()->Move(m_dInterMoveStep*(-1.0f));
}


void CDlgPrintMotionControl::OnDeltaposPrintMContinuMoveSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp = _T("");
	double dEditValue = 0.0;
	GetDlgItemText(IDC_PRINT_M_ContinuMoveSpeed_EDIT, strTemp);
	dEditValue = _ttof(strTemp);
	dEditValue -= (double)pNMUpDown->iDelta * 0.1f;
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 500.0)
		dEditValue = 500.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	SetDlgItemText(IDC_PRINT_M_ContinuMoveSpeed_EDIT, strTemp);	

	m_dContinMoveSpeed = dEditValue;

	*pResult = 0;
}


void CDlgPrintMotionControl::OnDeltaposPrintMInterMoveStepSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp = _T("");
	double dEditValue = 0.0;
	GetDlgItemText(IDC_PRINT_M_InterMoveStep_EDIT, strTemp);
	dEditValue = _ttof(strTemp);
	dEditValue -= (double)pNMUpDown->iDelta * 0.1f;
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 500.0)
		dEditValue = 500.0;
	strTemp.Format(_T("%.2f"), dEditValue);
	SetDlgItemText(IDC_PRINT_M_InterMoveStep_EDIT, strTemp);

	m_dInterMoveStep = dEditValue;

	*pResult = 0;
}


void CDlgPrintMotionControl::OnBnClickedPrintMLinklearnBtn()
{
	if (!m_bLinkLearn)
	{
		m_bLinkLearn = true;
		m_bmpBtn[4].SetTitle("����ѧϰ<<");

		CRect rcMain, rcSub;
		GetDlgItem(IDC_PRINT_M_GB3_GROUP)->GetWindowRect(&rcMain);
		m_pDlgPrintMotionLinkLearn->GetWindowRect(&rcSub);	
		m_pDlgPrintMotionLinkLearn->MoveWindow(rcMain.left+150, rcMain.bottom-rcSub.Height(), rcSub.Width(), rcSub.Height());
		m_pDlgPrintMotionLinkLearn->ShowWindow(SW_SHOW);
	}
	else
	{
		m_bLinkLearn = false;
		m_bmpBtn[4].SetTitle("����ѧϰ>>");

		m_pDlgPrintMotionLinkLearn->ShowWindow(SW_HIDE);
	}

	//ˢ�°�ť
	CRect rc;
	GetDlgItem(IDC_PRINT_M_LinkLearn_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);
}


void CDlgPrintMotionControl::InitWindowHandle()
{
	SetCheck("~father");
	Hlong hlWnd;
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_PRINT_M_PicShow_STATIC);
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


void CDlgPrintMotionControl::OnBnClickedPrintMCameralocateRadio()
{
	if (NULL == m_pProCore) return;
	m_pProCore->SwitchCamera(PRINT_LOCAL);
	m_pProCore->SetShowInfo(PRINT_LOCAL, m_windowHandle_Pic, m_winSize_Pic);
}
