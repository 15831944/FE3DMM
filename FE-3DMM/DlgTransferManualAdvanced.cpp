// DlgTransferManualAdvanced.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgTransferManualAdvanced.h"
#include "afxdialogex.h"


// CDlgTransferManualAdvanced �Ի���

IMPLEMENT_DYNAMIC(CDlgTransferManualAdvanced, CDialogEx)

CDlgTransferManualAdvanced::CDlgTransferManualAdvanced(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTransferManualAdvanced::IDD, pParent)
	, m_pProCore(pProCore)
{
	
}

CDlgTransferManualAdvanced::~CDlgTransferManualAdvanced()
{
}


void CDlgTransferManualAdvanced::Release()
{

}

void CDlgTransferManualAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSFER_M_A_PositivePress_SLIDER, m_cSldPositiveOrF);
	DDX_Control(pDX, IDC_TRANSFER_M_A_PositivePress_EDIT, m_cEditPositiveOrF);
	DDX_Control(pDX, IDC_TRANSFER_M_A_PositivePress_SPIN, m_cSpinPositiveOrF);
	DDX_Control(pDX, IDC_TRANSFER_M_A_NegativePress_SLIDER, m_cSldNegativeOrS);
	DDX_Control(pDX, IDC_TRANSFER_M_A_NegativePress_EDIT, m_cEditNegativeOrS);
	DDX_Control(pDX, IDC_TRANSFER_M_A_NegativePress_SPIN, m_cSpinNegativeOrS);
	DDX_Control(pDX, IDC_TRANSFER_M_A_ZSpeed_SLIDE, m_cSldZSpeed);
	DDX_Control(pDX, IDC_TRANSFER_M_A_ZSpeed_EDIT, m_cEditZSpeed);
	DDX_Control(pDX, IDC_TRANSFER_M_A_ZSpeed_SPIN, m_cSpinZSpeed);
}


BEGIN_MESSAGE_MAP(CDlgTransferManualAdvanced, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_TRANSFER_M_A_OK_BTN, &CDlgTransferManualAdvanced::OnBnClickedTransferMAOkBtn)
	ON_BN_CLICKED(IDC_TRANSFER_M_A_Cancel_BTN, &CDlgTransferManualAdvanced::OnBnClickedTransferMACancelBtn)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_TRANSFER_M_A_PositivePress_SLIDER, &CDlgTransferManualAdvanced::OnNMReleasedcaptureTransferMAPositivepressSlider)
	ON_EN_CHANGE(IDC_TRANSFER_M_A_PositivePress_EDIT, &CDlgTransferManualAdvanced::OnEnChangeTransferMAPositivepressEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRANSFER_M_A_PositivePress_SPIN, &CDlgTransferManualAdvanced::OnDeltaposTransferMAPositivepressSpin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_TRANSFER_M_A_NegativePress_SLIDER, &CDlgTransferManualAdvanced::OnNMReleasedcaptureTransferMANegativepressSlider)
	ON_EN_CHANGE(IDC_TRANSFER_M_A_NegativePress_EDIT, &CDlgTransferManualAdvanced::OnEnChangeTransferMANegativepressEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRANSFER_M_A_NegativePress_SPIN, &CDlgTransferManualAdvanced::OnDeltaposTransferMANegativepressSpin)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_TRANSFER_M_A_ZSpeed_SLIDE, &CDlgTransferManualAdvanced::OnNMReleasedcaptureTransferMAZspeedSlide)
	ON_EN_CHANGE(IDC_TRANSFER_M_A_ZSpeed_EDIT, &CDlgTransferManualAdvanced::OnEnChangeTransferMAZspeedEdit)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TRANSFER_M_A_ZSpeed_SPIN, &CDlgTransferManualAdvanced::OnDeltaposTransferMAZspeedSpin)
END_MESSAGE_MAP()


// CDlgTransferManualNew ��Ϣ�������
HBRUSH CDlgTransferManualAdvanced::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case IDC_TRANSFER_M_CameraTransDown_RADIO:
		case IDC_TRANSFER_M_CameraTransUp_RADIO:
		case IDC_TRANSFER_M_Active_RADIO:
		case IDC_TRANSFER_M_Passivity_RADIO:
		case IDC_TRANSFER_M_A_POSITIVE_STATIC:
		case IDC_TRANSFER_M_A_NEGATIVE_STATIC:

			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgTransferManualAdvanced::OnEraseBkgnd(CDC* pDC)
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


void CDlgTransferManualAdvanced::OnBnClickedTransferMAOkBtn()
{
	char PositiveEdit[256], NegativeEdit[256], ZSpeed[256];
	char * StopString;
	memset(PositiveEdit, 0, 256);
	memset(NegativeEdit, 0, 256);
	memset(ZSpeed, 0, 256);
	GetDlgItemText(IDC_TRANSFER_M_A_PositivePress_EDIT, PositiveEdit, 256);
	GetDlgItemText(IDC_TRANSFER_M_A_NegativePress_EDIT, NegativeEdit, 256);
	GetDlgItemText(IDC_TRANSFER_M_A_ZSpeed_EDIT, ZSpeed, 256);

	if (strcmp(PositiveEdit, "") == 0 || strcmp(NegativeEdit, "") == 0 || strcmp(ZSpeed, "") == 0)
	{
		::MessageBox(NULL, "��������ֵ", "��ʾ", MB_OK);
		return;
	}

	double fPositive = strtod(PositiveEdit, &StopString);
	if (strcmp(StopString, "\0") != 0)
	{
		::MessageBox(NULL, "����������������������", "��ʾ", MB_OK);
		return;
	}

	double fNegative = strtod(NegativeEdit, &StopString);
	if (strcmp(StopString, "\0") != 0)
	{
		::MessageBox(NULL, "����������������������", "��ʾ", MB_OK);
		return;
	}

	double fZSpeed = strtod(ZSpeed, &StopString);
	if (strcmp(StopString, "\0") != 0)
	{
		::MessageBox(NULL, "����������������������", "��ʾ", MB_OK);
		return;
	}

	m_pProCore->GetParamData()->GetParamTransfer()->fStaticF = fPositive;
	m_pProCore->GetParamData()->GetParamTransfer()->fStaticV = fNegative;
	m_pProCore->GetParamData()->GetParamTransfer()->fZSpeed = fZSpeed;

	CDlgTransferManualAdvanced::OnOK();
}


void CDlgTransferManualAdvanced::OnBnClickedTransferMACancelBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgTransferManualAdvanced::OnCancel();
}


BOOL CDlgTransferManualAdvanced::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitCtrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgTransferManualAdvanced::InitCtrl()
{
	m_cSldPositiveOrF.SetRange(0,500,TRUE);
	m_cSldPositiveOrF.SetPos(0);
	m_cSldPositiveOrF.SetTicFreq(5);
	m_cSpinPositiveOrF.SetBuddy(&m_cEditPositiveOrF);
	m_cSpinPositiveOrF.SetRange(0,500);
	m_cSpinPositiveOrF.SetPos(0);
	m_cEditPositiveOrF.SetWindowTextA("50");

	m_cSldNegativeOrS.SetRange(0,500,TRUE);
	m_cSldNegativeOrS.SetPos(0);
	m_cSldNegativeOrS.SetTicFreq(5);
	m_cSpinNegativeOrS.SetBuddy(&m_cEditNegativeOrS);
	m_cSpinNegativeOrS.SetRange(0,500);
	m_cSpinNegativeOrS.SetPos(0);
	m_cEditNegativeOrS.SetWindowTextA("50");

	m_cSldZSpeed.SetRange(0,500,TRUE);
	m_cSldZSpeed.SetPos(0);
	m_cSldZSpeed.SetTicFreq(5);
	m_cSpinZSpeed.SetBuddy(&m_cEditZSpeed);
	m_cSpinZSpeed.SetRange(0,500);
	m_cSpinZSpeed.SetPos(0);
	m_cEditZSpeed.SetWindowTextA("50");
}

void CDlgTransferManualAdvanced::SetTransferType(int Type)
{
     m_iTransferType = Type;
}


void CDlgTransferManualAdvanced::OnNMReleasedcaptureTransferMAPositivepressSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos = m_cSldPositiveOrF.GetPos();
	m_cSldPositiveOrF.SetPos(iPos);
	CString str;
	str.Format(_T("%d"),iPos);
	m_cEditPositiveOrF.SetWindowText(str);
	*pResult = 0;
}


void CDlgTransferManualAdvanced::OnEnChangeTransferMAPositivepressEdit()
{
	CString strTmp;
	int val;

	try
	{
		m_cEditPositiveOrF.GetWindowTextA(strTmp);
		TRACE("enter OnEnChangeEditZ , get str in m_cEditZSpeed\n");
	}
	catch (CException* e)
	{
		throw (e);
		TRACE("test empty str of OnEnChangeEditZ in m_cEditZSpeed\n");
	}

	bool bEmptyOfString;
	bEmptyOfString = strTmp.IsEmpty();

	if(bEmptyOfString) val=0;
	else val =  (int)_tstof(strTmp);

	if ( val > 500 || val < 0 )
	{
		if (val > 0)
		{
			val = 500;
			CString str;
			str.Format(_T("%d"), val);
			m_cEditPositiveOrF.SetWindowText(str);
		}
		else
		{
			val = 0;
			CString str;
			str.Format(_T("%d"), val);
			m_cEditPositiveOrF.SetWindowText(str);
		}
		//AfxMessageBox(_T("������һ������0��500֮�������"));
	}
	m_cSldPositiveOrF.SetPos(val);
	m_cSpinPositiveOrF.SetPos(val);
}


void CDlgTransferManualAdvanced::OnDeltaposTransferMAPositivepressSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTmp;
	int val;
	if(pNMUpDown->iDelta >0)                    //����������Spin�е����ϰ�ť  ,1
	{
		m_cEditPositiveOrF.GetWindowTextA(strTmp);
		val =  (int)_tstof(strTmp) + 1;
		m_cSpinPositiveOrF.SetPos(val);
		m_cSldPositiveOrF.SetPos(val);
		CString str;
		str.Format(_T("%d"),val);
		m_cEditPositiveOrF.SetWindowTextA(str);
	}
	else if(pNMUpDown->iDelta <0)    //����������Spin�����°�ť,  -1
	{
		m_cEditPositiveOrF.GetWindowTextA(strTmp);
		val =  (int)_tstof(strTmp) - 1;
		m_cSpinPositiveOrF.SetPos(val);
		m_cSldPositiveOrF.SetPos(val);
		CString str;
		str.Format(_T("%d"),val);
		m_cEditPositiveOrF.SetWindowTextA(str);
	}
	*pResult = 0;
}


void CDlgTransferManualAdvanced::OnNMReleasedcaptureTransferMANegativepressSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iPos = m_cSldNegativeOrS.GetPos();
	m_cSldNegativeOrS.SetPos(iPos);
	CString str;
	str.Format(_T("%d"),iPos);
	m_cEditNegativeOrS.SetWindowText(str);
	*pResult = 0;
}


void CDlgTransferManualAdvanced::OnEnChangeTransferMANegativepressEdit()
{
	CString strTmp;
	int val;

	try
	{
		m_cEditNegativeOrS.GetWindowTextA(strTmp);
		TRACE("enter OnEnChangeEditZ , get str in m_cEditZSpeed\n");
	}
	catch (CException* e)
	{
		throw (e);
		TRACE("test empty str of OnEnChangeEditZ in m_cEditZSpeed\n");
	}

	bool bEmptyOfString;
	bEmptyOfString = strTmp.IsEmpty();

	if(bEmptyOfString) val=0;
	else val =  (int)_tstof(strTmp);

	if ( val > 500 || val < 0 )
	{
		if (val > 0)
		{
			val = 500;
			CString str;
			str.Format(_T("%d"), val);
			m_cEditNegativeOrS.SetWindowText(str);
		}
		else
		{
			val = 0;
			CString str;
			str.Format(_T("%d"), val);
			m_cEditNegativeOrS.SetWindowText(str);
		}
		//AfxMessageBox(_T("������һ������0��500֮�������"));
	}
	m_cSldNegativeOrS.SetPos(val);
	m_cSpinNegativeOrS.SetPos(val);
}


void CDlgTransferManualAdvanced::OnDeltaposTransferMANegativepressSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString strTmp;
	int val;
	if(pNMUpDown->iDelta >0)                    //����������Spin�е����ϰ�ť  ,1
	{
		m_cEditNegativeOrS.GetWindowTextA(strTmp);
		val =  (int)_tstof(strTmp) + 1;
		m_cSpinNegativeOrS.SetPos(val);
		m_cSldNegativeOrS.SetPos(val);
		CString str;
		str.Format(_T("%d"),val);
		m_cEditNegativeOrS.SetWindowTextA(str);
	}
	else if(pNMUpDown->iDelta <0)    //����������Spin�����°�ť,  -1
	{
		m_cEditNegativeOrS.GetWindowTextA(strTmp);
		val =  (int)_tstof(strTmp) - 1;
		m_cSpinNegativeOrS.SetPos(val);
		m_cSldNegativeOrS.SetPos(val);
		CString str;
		str.Format(_T("%d"),val);
		m_cEditNegativeOrS.SetWindowTextA(str);
	}
	*pResult = 0;
}


void CDlgTransferManualAdvanced::OnNMReleasedcaptureTransferMAZspeedSlide(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iPos = m_cSldZSpeed.GetPos();
	m_cSldZSpeed.SetPos(iPos);
	CString str;
	str.Format(_T("%d"),iPos);
	m_cEditZSpeed.SetWindowText(str);
	*pResult = 0;
}


void CDlgTransferManualAdvanced::OnEnChangeTransferMAZspeedEdit()
{
	CString strTmp;
	int val;

	try
	{
		m_cEditZSpeed.GetWindowTextA(strTmp);
		TRACE("enter OnEnChangeEditZ , get str in m_cEditZSpeed\n");
	}
	catch (CException* e)
	{
		throw (e);
		TRACE("test empty str of OnEnChangeEditZ in m_cEditZSpeed\n");
	}

	bool bEmptyOfString;
	bEmptyOfString = strTmp.IsEmpty();

	if(bEmptyOfString) val=0;
	else val =  (int)_tstof(strTmp);

	if ( val > 500 || val < 0 )
	{
		if (val > 0)
		{
			val = 500;
			CString str;
			str.Format(_T("%d"), val);
			m_cEditZSpeed.SetWindowText(str);
		}
		else
		{
			val = 0;
			CString str;
			str.Format(_T("%d"), val);
			m_cEditZSpeed.SetWindowText(str);
		}
		//AfxMessageBox(_T("������һ������0��500֮�������"));
	}
	m_cSldZSpeed.SetPos(val);
	m_cSpinZSpeed.SetPos(val);
}


void CDlgTransferManualAdvanced::OnDeltaposTransferMAZspeedSpin(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	CString strTmp;
	int val;
	if(pNMUpDown->iDelta >0)                    //����������Spin�е����ϰ�ť  ,1
	{
		m_cEditZSpeed.GetWindowTextA(strTmp);
		val =  (int)_tstof(strTmp) + 1;
		m_cSpinZSpeed.SetPos(val);
		m_cSldZSpeed.SetPos(val);
		CString str;
		str.Format(_T("%d"),val);
		m_cEditZSpeed.SetWindowTextA(str);
	}
	else if(pNMUpDown->iDelta <0)    //����������Spin�����°�ť,  -1
	{
		m_cEditZSpeed.GetWindowTextA(strTmp);
		val =  (int)_tstof(strTmp) - 1;
		m_cSpinZSpeed.SetPos(val);
		m_cSldZSpeed.SetPos(val);
		CString str;
		str.Format(_T("%d"),val);
		m_cEditZSpeed.SetWindowTextA(str);
	}
	*pResult = 0;
}
