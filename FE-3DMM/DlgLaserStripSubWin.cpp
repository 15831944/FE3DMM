// DlgLaserStripSubWin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgLaserStripSubWin.h"
#include "afxdialogex.h"


// CDlgLaserStripSubWin �Ի���


IMPLEMENT_DYNAMIC(CDlgLaserStripSubWin, CDialog)

CDlgLaserStripSubWin::CDlgLaserStripSubWin(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLaserStripSubWin::IDD, pParent)
{
	m_pProCore			= pProCore;
	m_bScanPathSet		= false;
	m_bPathParamSave	= false;
	m_bContinuousMove	= false;
	m_dContinMoveSpeed	= 0.0;
	m_dInterMoveStep	= 0.0;
	m_dFastMoveXPos		= 0.0;
	m_dFastMoveYPos		= 0.0;

	m_pDlgLaserStripSWScanPath	  = NULL;
	m_pDlgLaserStripSWParamRecord = NULL;
}

CDlgLaserStripSubWin::~CDlgLaserStripSubWin()
{
	Release();
}

void CDlgLaserStripSubWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LASERSTRIP_S_GB1_GROUP, m_GB1);
	DDX_Control(pDX, IDC_LASERSTRIP_S_GB2_GROUP, m_GB2);
	DDX_Control(pDX, IDC_LASERSTRIP_S_GB3_GROUP, m_GB3);
}


BEGIN_MESSAGE_MAP(CDlgLaserStripSubWin, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_LASERSTRIP_S_ContiMove_RADIO, &CDlgLaserStripSubWin::OnBnClickedLaserstripSContiMoveRadio)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_InterMove_RADIO, &CDlgLaserStripSubWin::OnBnClickedLaserstripSInterMoveRadio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_LASERSTRIP_S_ContiMoveSpeed_SPIN, &CDlgLaserStripSubWin::OnDeltaposLaserstripSContiMoveSpeedSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_LASERSTRIP_S_InterMoveStep_SPIN, &CDlgLaserStripSubWin::OnDeltaposLaserstripSInterMoveStepSpin)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_XL_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSubwinXLBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_XR_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSubwinXRBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_YB_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSubwinYBBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_YF_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSubwinYFBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_FastMove_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSFastMoveBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_StartStrip_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSStartStripBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_ToHome_BTN, &CDlgLaserStripSubWin::OnClickedLaserstripSToHomeBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_ScanPathSet_BTN, &CDlgLaserStripSubWin::OnBnClickedLaserstripSScanPathSetBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_PathParamSave_BTN, &CDlgLaserStripSubWin::OnBnClickedLaserstripSPathParamSaveBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_LaserConfig_BTN, &CDlgLaserStripSubWin::OnBnClickedLaserstripSLaserConfigBtn)
	ON_BN_CLICKED(IDC_LASERSTRIP_S_Camera_RADIO, &CDlgLaserStripSubWin::OnBnClickedLaserstripSCameraRadio)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgLaserStripSubWin ��Ϣ�������
void CDlgLaserStripSubWin::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgLaserStripSubWin::OnCancel()
{
	DestroyWindow();
}


void CDlgLaserStripSubWin::Cancel()
{
	KillTimer(1);        //�رն�ʱ��
	//���Ӵ���Cancel();
	m_pDlgLaserStripSWScanPath->Cancel();
	m_pDlgLaserStripSWParamRecord->Cancel();
	OnCancel();
}


void CDlgLaserStripSubWin::Release()
{

}


HBRUSH CDlgLaserStripSubWin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case IDC_LASERSTRIP_S_ParamView_STATIC:
		case IDC_LASERSTRIP_S_Camera_RADIO:
		case IDC_LASERSTRIP_S_ContiMove_RADIO:
		case IDC_LASERSTRIP_S_InterMove_RADIO:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgLaserStripSubWin::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgLaserStripSubWin::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();
	InitWindowHandle();

	CheckRadioButton(IDC_LASERSTRIP_S_ContiMove_RADIO,IDC_LASERSTRIP_S_InterMove_RADIO,IDC_LASERSTRIP_S_ContiMove_RADIO);
	m_bContinuousMove = true;
	SetMoveComponentState();

	m_pDlgLaserStripSWScanPath = new CDlgLaserStripSWScanPath(this);
	ASSERT(m_pDlgLaserStripSWScanPath);
	m_pDlgLaserStripSWScanPath->Create(IDD_DLG_LASERSTRIP_SUB_SCANPATH);

	m_pDlgLaserStripSWParamRecord = new CDlgLaserStripSWParamRecord(this);
	ASSERT(m_pDlgLaserStripSWParamRecord);
	m_pDlgLaserStripSWParamRecord->Create(IDD_DLG_LASERSTRIP_SUB_PARAMRECODE);

	SetTimer(1, 100, NULL);

	return TRUE;  
}


void CDlgLaserStripSubWin::InitDlgCtrl()
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

	m_bmpBtn[0].SubclassDlgItem(IDC_LASERSTRIP_S_XL_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_XL,IDB_BITMAP_XLCLK,IDB_BITMAP_XL,IDB_BITMAP_XLCLK);

	m_bmpBtn[1].SubclassDlgItem(IDC_LASERSTRIP_S_XR_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_XR,IDB_BITMAP_XRCLK,IDB_BITMAP_XR,IDB_BITMAP_XRCLK);

	m_bmpBtn[2].SubclassDlgItem(IDC_LASERSTRIP_S_YF_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_YF,IDB_BITMAP_YFCLK,IDB_BITMAP_YF,IDB_BITMAP_YFCLK);

	m_bmpBtn[3].SubclassDlgItem(IDC_LASERSTRIP_S_YB_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_YB,IDB_BITMAP_YBCLK,IDB_BITMAP_YB,IDB_BITMAP_YBCLK);

	m_bmpBtn[4].SubclassDlgItem(IDC_LASERSTRIP_S_FastMove_BTN, this);
	m_bmpBtn[4].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[4].SetFont(15);
	m_bmpBtn[4].SetTitle("�����ƶ�");

	m_bmpBtn[5].SubclassDlgItem(IDC_LASERSTRIP_S_ToHome_BTN, this);
	m_bmpBtn[5].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[5].SetFont(15);
	m_bmpBtn[5].SetTitle("ƽ̨����");

	m_bmpBtn[6].SubclassDlgItem(IDC_LASERSTRIP_S_StartStrip_BTN, this);
	m_bmpBtn[6].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[6].SetFont(15);
	m_bmpBtn[6].SetTitle("��ʼ����");

	m_bmpBtn[7].SubclassDlgItem(IDC_LASERSTRIP_S_LaserConfig_BTN, this);
	m_bmpBtn[7].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[7].SetFont(15);
	m_bmpBtn[7].SetTitle("����������..");

	m_bmpBtn[8].SubclassDlgItem(IDC_LASERSTRIP_S_ScanPathSet_BTN, this);
	m_bmpBtn[8].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[8].SetFont(15);
	m_bmpBtn[8].SetTitle("·���滮>>");

	m_bmpBtn[9].SubclassDlgItem(IDC_LASERSTRIP_S_PathParamSave_BTN, this);
	m_bmpBtn[9].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[9].SetFont(15);
	m_bmpBtn[9].SetTitle("������¼>>");
}


void CDlgLaserStripSubWin::SetMoveComponentState()
{
	if (m_bContinuousMove)
	{
		m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_XLL,IDB_BITMAP_XLLCLK,IDB_BITMAP_XLL,IDB_BITMAP_XLLCLK);
		m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_XRR,IDB_BITMAP_XRRCLK,IDB_BITMAP_XRR,IDB_BITMAP_XRRCLK);
		m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_YFF,IDB_BITMAP_YFFCLK,IDB_BITMAP_YFF,IDB_BITMAP_YFFCLK);
		m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_YBB,IDB_BITMAP_YBBCLK,IDB_BITMAP_YBB,IDB_BITMAP_YBBCLK);
		GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_SPIN)->EnableWindow(TRUE);
		GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_SPIN)->EnableWindow(FALSE);
	}
	else
	{
		m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_XL,IDB_BITMAP_XLCLK,IDB_BITMAP_XL,IDB_BITMAP_XLCLK);
		m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_XR,IDB_BITMAP_XRCLK,IDB_BITMAP_XR,IDB_BITMAP_XRCLK);
		m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_YF,IDB_BITMAP_YFCLK,IDB_BITMAP_YF,IDB_BITMAP_YFCLK);
		m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_YB,IDB_BITMAP_YBCLK,IDB_BITMAP_YB,IDB_BITMAP_YBCLK);
		GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_SPIN)->EnableWindow(FALSE);
		GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_EDIT)->EnableWindow(TRUE);
		GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_SPIN)->EnableWindow(TRUE);
	}

	//ˢ�°�ť
	CRect rc;
	GetDlgItem(IDC_LASERSTRIP_S_XL_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);

	GetDlgItem(IDC_LASERSTRIP_S_XR_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);

	GetDlgItem(IDC_LASERSTRIP_S_YF_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);

	GetDlgItem(IDC_LASERSTRIP_S_YB_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);
}


void CDlgLaserStripSubWin::OnBnClickedLaserstripSContiMoveRadio()
{
	m_bContinuousMove = true;
	SetMoveComponentState();
}


void CDlgLaserStripSubWin::OnBnClickedLaserstripSInterMoveRadio()
{
	m_bContinuousMove = false;
	SetMoveComponentState();
}


BOOL CDlgLaserStripSubWin::PreTranslateMessage(MSG* pMsg)
{
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		CString strTemp = _T("");
		double dEditValue = 0.0;

		if (GetFocus() == GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT))
		{
			GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT)->GetWindowText(strTemp);
			dEditValue = _ttof(strTemp);
			if (dEditValue < 0.0)
				dEditValue = 0.0;
			else if (dEditValue > 500.0)
				dEditValue = 500.0;	
			strTemp.Format(_T("%.2f"), dEditValue);
			GetDlgItem(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT)->SetWindowText(strTemp);	

			m_dContinMoveSpeed = dEditValue;
		}

		if (GetFocus() == GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_EDIT))
		{
			GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_EDIT)->GetWindowText(strTemp);
			dEditValue = _ttof(strTemp);
			if (dEditValue < 0.0)
				dEditValue = 0.0;
			else if (dEditValue > 500.0)
				dEditValue = 500.0;
			strTemp.Format(_T("%.2f"), dEditValue);
			GetDlgItem(IDC_LASERSTRIP_S_InterMoveStep_EDIT)->SetWindowText(strTemp);

			m_dInterMoveStep = dEditValue;
		}

		if (GetFocus() == GetDlgItem(IDC_LASERSTRIP_S_FastMoveXPos_EDIT))
		{
			GetDlgItem(IDC_LASERSTRIP_S_FastMoveXPos_EDIT)->GetWindowText(strTemp);		
			dEditValue = _ttof(strTemp);
			if (dEditValue < 0.0)
				dEditValue = 0.0;
			else if (dEditValue > 1000.0)
				dEditValue = 1000.0;
			strTemp.Format(_T("%.2f"), dEditValue);
			GetDlgItem(IDC_LASERSTRIP_S_FastMoveXPos_EDIT)->SetWindowText(strTemp);

			m_dFastMoveXPos = dEditValue;
		}

		if (GetFocus() == GetDlgItem(IDC_LASERSTRIP_S_FastMoveYPos_EDIT))
		{
			GetDlgItem(IDC_LASERSTRIP_S_FastMoveYPos_EDIT)->GetWindowText(strTemp);
			dEditValue = _ttof(strTemp);
			if (dEditValue < 0.0)
				dEditValue = 0.0;
			else if (dEditValue > 1000.0)
				dEditValue = 1000.0;
			strTemp.Format(_T("%.2f"), dEditValue);
			GetDlgItem(IDC_LASERSTRIP_S_FastMoveYPos_EDIT)->SetWindowText(strTemp);

			m_dFastMoveYPos = dEditValue;
		}

		return TRUE;
	}

	//���Ƶ�������˶�
	if (WM_LBUTTONDOWN == pMsg->message)
	{
		if (m_bContinuousMove)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_XL_BTN)->m_hWnd)
			{
				//m_pProCore->GetProLaserStrip()->GetMotorLaserStripX()->Jog(0);
			}
			if (pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_XR_BTN)->m_hWnd)
			{
				//m_pProCore->GetProLaserStrip()->GetMotorLaserStripX()->Jog(1);
			}
			
			if (pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_YF_BTN)->m_hWnd)
			{
				//m_pProCore->GetProLaserStrip()->GetMotorLaserStripY()->Jog(0);
			}
			if (pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_YB_BTN)->m_hWnd)
			{
				//m_pProCore->GetProLaserStrip()->GetMotorLaserStripY()->Jog(1);
			}
		}
	}

	if (WM_LBUTTONUP == pMsg->message)
	{
		if (m_bContinuousMove)
		{
			if (pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_XL_BTN)->m_hWnd
				|| pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_XR_BTN)->m_hWnd)
			{
				//m_pProCore->GetProLaserStrip()->GetMotorLaserStripX()->JogStop();
			}
			
			if (pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_YF_BTN)->m_hWnd
				|| pMsg->hwnd == GetDlgItem(IDC_LASERSTRIP_S_YB_BTN)->m_hWnd)
			{
				//m_pProCore->GetProLaserStrip()->GetMotorLaserStripY()->JogStop();
			}
		}
	}


	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgLaserStripSubWin::OnDeltaposLaserstripSContiMoveSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp = _T("");
	double dEditValue = 0.0;
	GetDlgItemText(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT, strTemp);
	dEditValue = _ttof(strTemp);
	dEditValue -= (double)pNMUpDown->iDelta * 0.1f;
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 500.0)
		dEditValue = 500.0;	
	strTemp.Format(_T("%.2f"), dEditValue);
	SetDlgItemText(IDC_LASERSTRIP_S_ContiMoveSpeed_EDIT, strTemp);	

	m_dContinMoveSpeed = dEditValue;

	*pResult = 0;
}


void CDlgLaserStripSubWin::OnDeltaposLaserstripSInterMoveStepSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp = _T("");
	double dEditValue = 0.0;
	GetDlgItemText(IDC_LASERSTRIP_S_InterMoveStep_EDIT, strTemp);
	dEditValue = _ttof(strTemp);
	dEditValue -= (double)pNMUpDown->iDelta * 0.1f;
	if (dEditValue < 0.0)
		dEditValue = 0.0;
	else if (dEditValue > 500.0)
		dEditValue = 500.0;
	strTemp.Format(_T("%.2f"), dEditValue);
	SetDlgItemText(IDC_LASERSTRIP_S_InterMoveStep_EDIT, strTemp);

	m_dInterMoveStep = dEditValue;

	*pResult = 0;
}


void CDlgLaserStripSubWin::OnClickedLaserstripSubwinXLBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProLaserStrip()->GetMotorLaserStripX()->Move(m_dInterMoveStep*(-1.0f));
}


void CDlgLaserStripSubWin::OnClickedLaserstripSubwinXRBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProLaserStrip()->GetMotorLaserStripX()->Move(m_dInterMoveStep);
}


void CDlgLaserStripSubWin::OnClickedLaserstripSubwinYFBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProLaserStrip()->GetMotorLaserStripY()->Move(m_dInterMoveStep);
}


void CDlgLaserStripSubWin::OnClickedLaserstripSubwinYBBtn()
{
	if (m_bContinuousMove)
	{
		return;
	}

	//���Ƶ���㶯
	//m_pProCore->GetProLaserStrip()->GetMotorLaserStripY()->Move(m_dInterMoveStep*(-1.0f));
}


void CDlgLaserStripSubWin::OnClickedLaserstripSFastMoveBtn()
{
	//�����ƶ�
// 	m_pProCore->GetProLaserStrip()->GetMotorLaserStripX()->MoveTo(m_dFastMoveXPos);
// 	m_pProCore->GetProLaserStrip()->GetMotorLaserStripY()->MoveTo(m_dFastMoveYPos);
}


void CDlgLaserStripSubWin::OnClickedLaserstripSStartStripBtn()
{
	double ScanLen = 0.0;
	double ScanSpace = 0.0;
	double ScanSpeed = 0.0;
	double TransRowSpeed = 0.0;
	int    ScanNum = 0;

	switch(GetParamScan()->scanmode) //�ж�ɨ��·��
	{
		case SingleROW:  
		{
			//���ݵ���ɨ�����		
			ScanLen       = GetParamScan()->paramSingleScan.dScanLen;				
			ScanSpace     = 0.0;
			ScanSpeed     = GetParamScan()->paramSingleScan.dScanSpeed;
			TransRowSpeed = 0.0;
			ScanNum       = GetParamScan()->paramSingleScan.nScanNum;
			m_pProCore->GetProLaserStrip()->TransferPara(ScanLen,ScanSpace,ScanSpeed,TransRowSpeed,ScanNum);
			break;
		}
		case MultiROW:  
		{
			//���ݶ���ɨ�����
			ScanLen       = GetParamScan()->paramMultiScan.dScanLen;			
			ScanSpace     = GetParamScan()->paramMultiScan.dScanSpace;
			ScanSpeed     = GetParamScan()->paramMultiScan.dScanSpeed;
			TransRowSpeed = GetParamScan()->paramMultiScan.dTransRowSpeed;
			ScanNum       = GetParamScan()->paramMultiScan.nScanNum;
			m_pProCore->GetProLaserStrip()->TransferPara(ScanLen,ScanSpace,ScanSpeed,TransRowSpeed,ScanNum);
			break;
		}
		default:
		{
			MessageBox("·�������쳣����������ɨ��·������!");
			break;
		}
	}

	if((m_pProCore->GetProLaserStrip()->GetProgStatus() == FALSE) && (GetParamScan()->scanmode != EMPTY))
		m_pProCore->GetProLaserStrip()->RunProgram();
	
	GetDlgItem(IDC_LASERSTRIP_S_StartStrip_BTN)->EnableWindow(FALSE);	//ɨ���ڼ��ֹ�ظ�����������ť
	MessageBox("����������,�����ʾ����ǰ�����޸Ĳ��������������!");
	
	SetTimer(2,1000,NULL);	//��������״̬��ѯ��ʱ��
}


void CDlgLaserStripSubWin::OnClickedLaserstripSToHomeBtn()
{
	//m_pProCore->GetProLaserStrip()->Home();
}


void CDlgLaserStripSubWin::OnBnClickedLaserstripSScanPathSetBtn()
{
	if (!m_bScanPathSet)
	{
		m_bScanPathSet = true;
		m_bmpBtn[8].SetTitle("·���滮<<");

		CRect rcMain, rcSub;
		GetDlgItem(IDC_LASERSTRIP_S_GB1_GROUP)->GetWindowRect(&rcMain);
		m_pDlgLaserStripSWScanPath->GetWindowRect(&rcSub);
		m_pDlgLaserStripSWScanPath->MoveWindow(rcMain.left, 
			rcMain.bottom-rcSub.Height(), rcSub.Width(), rcSub.Height());
		m_pDlgLaserStripSWScanPath->ShowWindow(SW_SHOW);
	}
	else
	{
		m_bScanPathSet = false;
		m_bmpBtn[8].SetTitle("·���滮>>");

		m_pDlgLaserStripSWScanPath->ShowWindow(SW_HIDE);
	}

	//ˢ�°�ť
	CRect rc;
	GetDlgItem(IDC_LASERSTRIP_S_ScanPathSet_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);
}


void CDlgLaserStripSubWin::OnBnClickedLaserstripSPathParamSaveBtn()
{
	if (!m_bPathParamSave)
	{
		m_bPathParamSave = true;
		m_bmpBtn[9].SetTitle("������¼<<");

		CRect rcMain, rcSub;
		GetDlgItem(IDC_LASERSTRIP_S_GB2_GROUP)->GetWindowRect(&rcMain);
		m_pDlgLaserStripSWParamRecord->GetWindowRect(&rcSub);
		m_pDlgLaserStripSWParamRecord->MoveWindow(rcMain.right-rcSub.Width(), 
			rcMain.bottom-rcSub.Height(), rcSub.Width(), rcSub.Height());
		m_pDlgLaserStripSWParamRecord->ShowWindow(SW_SHOW);
	}
	else
	{
		m_bPathParamSave = false;
		m_bmpBtn[9].SetTitle("������¼>>");

		m_pDlgLaserStripSWParamRecord->ShowWindow(SW_HIDE);
	}

	//ˢ�°�ť
	CRect rc;
	GetDlgItem(IDC_LASERSTRIP_S_PathParamSave_BTN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);
}


void CDlgLaserStripSubWin::OnBnClickedLaserstripSLaserConfigBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CDlgLaserStripSubWin::ShowBmpInStatic()
{
	CBitmap Bitmap,*pOldBitmap; 
	BITMAP bm; 
	if (m_paramscan.scanmode == SingleROW)
	{
		Bitmap.LoadBitmap(IDB_BITMAP_SINGLESCAN); 
	}
	else if (m_paramscan.scanmode == MultiROW)
	{
		Bitmap.LoadBitmap(IDB_BITMAP_MULTISCAN); 
	}
	else
	{
		return;
	}
	Bitmap.GetObject(sizeof(BITMAP), &bm);   //��λͼ��Դ������

	CDC dcMem; 
	dcMem.CreateCompatibleDC(GetDC()); 
	pOldBitmap=(CBitmap*)(dcMem.SelectObject(&Bitmap)); 

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_LASERSTRIP_S_ScanPathShow_STATIC);
	CRect rect;
	pStatic->GetClientRect(&rect);
	pStatic->GetDC()->StretchBlt(rect.left, rect.top, rect.Width(), rect.Height(),
		&dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	dcMem.SelectObject(&pOldBitmap);
	dcMem.DeleteDC();
}


ParamScan* CDlgLaserStripSubWin::GetParamScan()
{
	return &m_paramscan;
}


void CDlgLaserStripSubWin::SetParamInStatic()
{
	CString strView = _T("");
	CString strTemp = _T("");
	if (m_paramscan.scanmode == SingleROW)
	{
		strView = _T("ɨ�跽ʽ������ɨ��\n");
		strView += _T("ɨ�賤�ȣ�");
		strTemp.Format(_T("%.2f\n"), m_paramscan.paramSingleScan.dScanLen);
		strView += strTemp;
		strView += _T("ɨ���ٶȣ�");
		strTemp.Format(_T("%.2f\n"), m_paramscan.paramSingleScan.dScanSpeed);
		strView += strTemp;
		strView += _T("ɨ�������");
		strTemp.Format(_T("%d\n"), m_paramscan.paramSingleScan.nScanNum);
		strView += strTemp;
		GetDlgItem(IDC_LASERSTRIP_S_ParamView_STATIC)->SetWindowText(strView);
	}
	else if (m_paramscan.scanmode == MultiROW)
	{
		strView = _T("ɨ�跽ʽ������ɨ��\n");
		strView += _T("ɨ�賤�ȣ�");
		strTemp.Format(_T("%.2f\n"), m_paramscan.paramMultiScan.dScanLen);
		strView += strTemp;
		strView += _T("ɨ���ࣺ");
		strTemp.Format(_T("%.2f\n"), m_paramscan.paramMultiScan.dScanSpace);
		strView += strTemp;
		strView += _T("ɨ���ٶȣ�");
		strTemp.Format(_T("%.2f\n"), m_paramscan.paramMultiScan.dScanSpeed);
		strView += strTemp;
		strView += _T("�����ٶȣ�");
		strTemp.Format(_T("%.2f\n"), m_paramscan.paramMultiScan.dTransRowSpeed);
		strView += strTemp;
		strView += _T("ɨ�������");
		strTemp.Format(_T("%d\n"), m_paramscan.paramMultiScan.nScanNum);
		strView += strTemp;
		GetDlgItem(IDC_LASERSTRIP_S_ParamView_STATIC)->SetWindowText(strView);
	}

	CRect rc;
	GetDlgItem(IDC_LASERSTRIP_S_ParamView_STATIC)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	RedrawWindow(&rc);
}


CDlgLaserStripSWScanPath* CDlgLaserStripSubWin::GetDlgLaserStripSWScanPath()
{
	return m_pDlgLaserStripSWScanPath;
}


void CDlgLaserStripSubWin::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
		case 1:	
			ShowBmpInStatic();	
			break;

		case 2:	
			if(m_pProCore->GetProLaserStrip()->GetProgStatus() == FALSE)
			{
				MessageBox("�������!");
				GetDlgItem(IDC_LASERSTRIP_S_StartStrip_BTN)->EnableWindow(TRUE);
				KillTimer(2);
			}
			break;
	}
	
	CDialog::OnTimer(nIDEvent);
}


void CDlgLaserStripSubWin::InitWindowHandle()
{
	SetCheck("~father");
	Hlong hlWnd;
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_LASERSTRIP_S_PicShow_STATIC);
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


void CDlgLaserStripSubWin::OnBnClickedLaserstripSCameraRadio()
{
	if (NULL == m_pProCore) return;
	m_pProCore->SwitchCamera(LASER_VIEW);
	m_pProCore->SetShowInfo(LASER_VIEW, m_windowHandle_Pic, m_winSize_Pic);
}
