// Dlg3DMeasureScan.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "Dlg3DMeasureScan.h"
#include "afxdialogex.h"


// CDlg3DMeasureScan �Ի���
ISD_LaserCOMPtr oLaserCom = NULL;
int NumofProbes = 0;
IMPLEMENT_DYNAMIC(CDlg3DMeasureScan, CDialog)

CDlg3DMeasureScan::CDlg3DMeasureScan(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlg3DMeasureScan::IDD, pParent)
{
	m_pProCore = pProCore;
}

CDlg3DMeasureScan::~CDlg3DMeasureScan()
{
	Release();
}

void CDlg3DMeasureScan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_3DMEASURE_S_GB1_GROUP, m_GB1);
	DDX_Control(pDX, IDC_3DMEASURE_S_LensMaxDis_COMBOX, m_cbLens);
	DDX_Control(pDX, IDC_3DMEASURE_S_LensDis_SLIDER, m_sliderPower);
	DDX_Control(pDX, IDC_3DMEASURE_S_ProbeType_COMBOX, m_CBProbeType);
	DDX_Text(pDX, IDC_3DMEASURE_S_LensDis_EDIT, m_sSliderPower);
	DDX_Text(pDX, IDC_3DMEASURE_S_LensMinDis_EDIT, m_sDisMin);
	DDX_Text(pDX, IDC_3DMEASURE_S_LensMaxDis_EDIT, m_sDisMax);
	DDX_Text(pDX, IDC_3DMEASURE_S_PointDis_EDIT, m_sDistance);
	DDX_Text(pDX, IDC_3DMEASURE_S_PointSNR_EDIT, m_sSNR);
//	DDX_Text(pDX, IDC_3DMEASURE_S_PointFreq_EDIT, m_Freq);
//	DDX_Text(pDX, IDC_3DMEASURE_S_PointQuality_EDIT, m_sQuality);

}


BEGIN_MESSAGE_MAP(CDlg3DMeasureScan, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_HSCROLL()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_3DMEASURE_S_Connect_BTN, &CDlg3DMeasureScan::OnBnClicked3dmeasureSConnectBtn)
	ON_BN_CLICKED(IDC_3DMEASURE_S_Start_BTN, &CDlg3DMeasureScan::OnBnClicked3dmeasureSStartBtn)
	ON_BN_CLICKED(IDC_3DMEASURE_S_Stop_BTN, &CDlg3DMeasureScan::OnBnClicked3dmeasureSStopBtn)
	ON_CBN_SELCHANGE(IDC_3DMEASURE_S_LensMaxDis_COMBOX, &CDlg3DMeasureScan::OnCbnSelchange3dmeasureSLensmaxdisCombox)
//	ON_EN_CHANGE(IDC_3DMEASURE_S_PointFreq_EDIT, &CDlg3DMeasureScan::OnEnChange3dmeasureSPointfreqEdit)
END_MESSAGE_MAP()


// CDlg3DMeasureScan ��Ϣ�������
void CDlg3DMeasureScan::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlg3DMeasureScan::OnCancel()
{
//	DestroyWindow();
}


void CDlg3DMeasureScan::Cancel()
{
	OnCancel();
}


void CDlg3DMeasureScan::Release()
{

}


HBRUSH CDlg3DMeasureScan::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDlg3DMeasureScan::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlg3DMeasureScan::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();
	CoInitialize(NULL);

	oLaserCom.CreateInstance(__uuidof(SD_LaserCOM));



	m_CBProbeType.SetCurSel(1);
	m_sliderPower.SetRange(0, 63, TRUE);
	m_sliderPower.SetPos(20);
	return TRUE;  
}


void CDlg3DMeasureScan::InitDlgCtrl()
{
	m_GB1.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetAlignment(SS_CENTER);

	m_bmpBtn[0].SubclassDlgItem(IDC_3DMEASURE_S_Connect_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(16);
	m_bmpBtn[0].SetTitle("���Ӳ�ͷ");

	m_bmpBtn[1].SubclassDlgItem(IDC_3DMEASURE_S_Start_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(16);
	m_bmpBtn[1].SetTitle("��ʼ����");

	m_bmpBtn[2].SubclassDlgItem(IDC_3DMEASURE_S_Stop_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(16);
	m_bmpBtn[2].SetTitle("ֹͣ����");
}

void CDlg3DMeasureScan::OnBnClicked3dmeasureSConnectBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//����Ҫ��ʾ������
	byte Res = 0;

	unsigned short port = 0;
	byte bRes = 0;
	long SN = 0;

	int nCurSel = 1;
	oLaserCom->SetProbeType(nCurSel,&bRes);//ѡ��Ҫ���ĸ�probe
	oLaserCom->ProbeDetect(&port);//������ӵ�ϵͳ��probe������Ϊ��ע��IP
	NumofProbes = port;

	for (int i = 0; i < NumofProbes; i++)
	{
		oLaserCom->SetActiveProbe(i, &bRes);//���ûprobe������
		oLaserCom->ProbeGetHeadSN(&SN);//��ȡprobe�����к�
		CString sSN;
		sSN.Format("%ld",SN);
//		m_CBProbes.AddString(sSN);

		oLaserCom->ProbeInit(i, &Res);
		if (Res == 0)
		{
			//MessageBox.Show("Can't initialize Probe", "Probe Laser COM", MessageBoxButtons.OK, MessageBoxIcon.Error);
			oLaserCom->ProbeTerminate();//����뻻�Probe,����ֹ��ǰ��probe
		}

	}
	int val = m_sliderPower.GetPos();

	oLaserCom->ProbeSetPower(2, val, &Res);//���ü���ǿ��

	unsigned short power = 0;
	oLaserCom->ProbeGetPower(2, &power);//����ʵ�ʼ���ǿ��ֵ
//	GetDlgItem(IDC_3DMEASURE_S_LensDis_SLIDER)->SetWindowText(pp);
	m_sSliderPower.Format("%ld",power); 
	UpdateData(FALSE);
//	m_CBProbes.SetCurSel(0);
	OnChangeProbes();
	OnChangeLens();

}


void CDlg3DMeasureScan::OnBnClicked3dmeasureSStartBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//SD_LaserCOMLib.PrbMeasurementInt Meas = new PrbMeasurementInt();
	byte Res = 0;
	timer1 = SetTimer(1,100,0);
	for (int t = 0; t < NumofProbes; t++)
	{
		oLaserCom->SetActiveProbe(t, &Res);
		oLaserCom->ProbeBeginReadMeasurementStream(10,(TPrbMode)0,0, &Res);//ת��������ģʽ
	}


//	timer1 = SetTimer(1,100,0);


}


void CDlg3DMeasureScan::OnBnClicked3dmeasureSStopBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	KillTimer(timer1);
}
void CDlg3DMeasureScan::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (pScrollBar == (CScrollBar *) &m_sliderPower)
	{
		int val = m_sliderPower.GetPos();

		byte Res = 0;
		oLaserCom->ProbeSetPower(2, val, &Res);//���ü���ǿ��

		unsigned short power = 0;
		oLaserCom->ProbeGetPower(2, &power);//����ʵ�ʼ���ǿ��ֵ

		m_sSliderPower.Format("%ld",power); 
		UpdateData(FALSE);
	}
	else
	{
		CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}

void CDlg3DMeasureScan::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	IPrbMeasurementIntPtr Meas = NULL;  

	if (nIDEvent == timer1)
	{
		byte Res = 0;

		for (int t = 0; t < NumofProbes; t++)
		{
			oLaserCom->SetActiveProbe(t, &Res);
			oLaserCom->ProbeGetMeasurementStream(&Meas, &Res);//

			if (Res != 0)
			{
				float f = 0;
				Meas->Distance(&f);
				m_sDistance.Format("%f",f);
				long SNR = 0, Total = 0;
				Meas->Snr(&SNR);
				SNR = SNR * 100 / 1024;
				m_sSNR.Format("%ld",SNR);                
// 				Meas->Total(&Total);
// 				m_sQuality.Format("%ld",Total);
			}
		}
	}
	else if (nIDEvent == timer2)
	{
		byte Res = 0;

		oLaserCom->ProbeReadMeasurement(&Meas, &Res);//��ʾһ��ͼ�񣬲����Ի�ɨ���ǲ���
		if (Res != 0)
		{
			float f = 0;
			Meas->Distance(&f);
			m_sDistance.Format("%f",f);
			long SNR = 0, Total = 0;
			Meas->Snr(&SNR);
			SNR = SNR * 100 / 1024;
			m_sSNR.Format("%ld",SNR);
// 			Meas->Total(&Total);
// 			m_sQuality.Format("%ld",Total);
		}
	}

	UpdateData(FALSE);

	CDialog::OnTimer(nIDEvent);
}

void CDlg3DMeasureScan::OnCbnSelchange3dmeasureSLensmaxdisCombox()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnChangeLens();
}
void CDlg3DMeasureScan::OnChangeProbes()
{
	unsigned short power = 0;

    byte res = 0;
    oLaserCom->SetActiveProbe(30745, &res);
    //Fill in Lens Dialog

    oLaserCom->ProbeGetPower(2, &power);

    byte Cnt = 0;
    oLaserCom->ProbeGetLensCount(&Cnt);//����ɨ�����Ѿ�У׼�õľ�ͷ����
    IPrbLensIntPtr Lens = NULL;
	Lens.CreateInstance(__uuidof(PrbLensInt));
    long Val = 0;
	CString sdis; 
    for (byte ii = 1; ii <= Cnt; ii++)
    {
        oLaserCom->ProbeGetLens(ii, &Lens, &res);//���¾�ͷ����
		if (res == 1)
		{
			Lens->FocalDistance(&Val);//��ͷ�����伤��������ľ���
			sdis.Format("%ld",Val);
			m_cbLens.AddString(sdis);
		}

    }
    oLaserCom->ProbeGetActiveLensIndex(&Cnt);//��ǰ��ͷ������
	m_cbLens.SetCurSel(Cnt-1);


	UpdateData(FALSE);
}
void CDlg3DMeasureScan::OnChangeLens()
{
	byte Res = 0;
	byte idx = (byte)(m_cbLens.GetCurSel() + 1);
	oLaserCom->ProbeSetActiveLensIndex(idx, &Res);//����ɨ������У׼�仯��ľ������
	IPrbLensIntPtr Lens = NULL;
	Lens.CreateInstance(__uuidof(PrbLensInt));
	oLaserCom->ProbeGetLens(idx, &Lens, &Res);
	float val =0;
	Lens->DistanceMin(&val);
	m_sDisMin.Format("%f",val);
	Lens->DistanceMax(&val);
	m_sDisMax.Format("%f",val);

	UpdateData(FALSE);
}

