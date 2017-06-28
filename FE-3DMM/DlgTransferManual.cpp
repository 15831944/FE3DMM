// DlgTransferManual.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgTransferManual.h"
#include "afxdialogex.h"

using HalconCpp::HObject;
using HalconCpp::HTuple;
// CDlgTransferManual �Ի���

IMPLEMENT_DYNAMIC(CDlgTransferManual, CDialog)

//��̬��Ա����
int CDlgTransferManual::m_NextBtnCount = 0;     
int CDlgTransferManual::m_iClickNum = 0;

CDlgTransferManual::CDlgTransferManual(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransferManual::IDD, pParent)
	, m_cTransTypeRadio(0)
	, m_cCamNum(0)
{
	m_pProCore = pProCore;
}

CDlgTransferManual::~CDlgTransferManual()
{
	Release();
}

void CDlgTransferManual::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSFER_M_GB1_GROUP, m_GB1);
	DDX_Control(pDX, IDC_TRANSFER_M_GB2_GROUP, m_GB2);
	DDX_Control(pDX, IDC_TRANSFER_M_GB3_GROUP, m_GB3);
	DDX_Control(pDX, IDC_TRANSFER_M_GB4_GROUP, m_GB4);
	DDX_Radio(pDX, IDC_TRANSFER_M_Active_RADIO, m_cTransTypeRadio);
	DDX_Radio(pDX, IDC_TRANSFER_M_CameraTransDown_RADIO, m_cCamNum);
	DDX_Control(pDX, IDC_TRANSFER_M_Object_LIST, m_cListObject);
	//DDX_Text(pDX, IDC_TRANSFER_M_TIPS_STATIC, m_strTips);
}


BEGIN_MESSAGE_MAP(CDlgTransferManual, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_TRANSFER_M_New_BTN, &CDlgTransferManual::OnBnClickedTransferMNewBtn)
	ON_BN_CLICKED(IDC_TRANSFER_M_Advanced_BTN, &CDlgTransferManual::OnBnClickedTransferMAdvancedBtn)
	ON_BN_CLICKED(IDC_TRANSFER_M_Delete_BTN, &CDlgTransferManual::OnBnClickedTransferMDeleteBtn)
	ON_BN_CLICKED(IDC_TRANSFER_M_Start_BTN, &CDlgTransferManual::OnBnClickedTransferMStartBtn)
	ON_BN_CLICKED(IDC_TRANSFER_M_Next_BTN, &CDlgTransferManual::OnBnClickedTransferMNextBtn)
	ON_BN_CLICKED(IDC_TRANSFER_M_StepDebug_BTN, &CDlgTransferManual::OnBnClickedTransferMStepdebugBtn)
	ON_MESSAGE(WM_CHANGETIPS, OnChangeTips)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TRANSFER_M_CameraTransDown_RADIO, &CDlgTransferManual::OnBnClickedTransferMCameraTransDownRadio)
	ON_BN_CLICKED(IDC_TRANSFER_M_CameraTransUp_RADIO, &CDlgTransferManual::OnBnClickedTransferMCameraTransUpRadio)
END_MESSAGE_MAP()


// CDlgTransferManual ��Ϣ�������
void CDlgTransferManual::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgTransferManual::OnCancel()
{
	DestroyWindow();
}


void CDlgTransferManual::Cancel()
{
	m_pProCore->GetProTransfer()->ThreadExit();
	Sleep(500);
	OnCancel();
}


void CDlgTransferManual::Release()
{
	
}


HBRUSH CDlgTransferManual::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		CFont font;
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_TRANSFER_M_TIPS_STATIC:			
			font.CreatePointFont( 120, "����");
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			pDC->SelectObject(&font);
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 

		case IDC_STATIC:
		case IDC_TRANSFER_M_CameraTransDown_RADIO:
		case IDC_TRANSFER_M_CameraTransUp_RADIO:
		case IDC_TRANSFER_M_Active_RADIO:
		case IDC_TRANSFER_M_Passivity_RADIO:		
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgTransferManual::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgTransferManual::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitDlgCtrl();
	InitWindowHandle();	

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgTransferManual::InitDlgCtrl()
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

	m_GB4.SetXPGroupStyle(CXPGroupBox::XPGB_WINDOW)
		.SetFontBold(TRUE)
		.SetFontSize(16)
		.SetAlignment(SS_CENTER);

	m_bmpBtn[0].SubclassDlgItem(IDC_TRANSFER_M_New_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(16);
	m_bmpBtn[0].SetTitle("�½�");

	m_bmpBtn[1].SubclassDlgItem(IDC_TRANSFER_M_Delete_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(16);
	m_bmpBtn[1].SetTitle("ɾ��");

	m_bmpBtn[2].SubclassDlgItem(IDC_TRANSFER_M_Advanced_BTN , this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(16);
	m_bmpBtn[2].SetTitle("�߼�����");

	m_bmpBtn[3].SubclassDlgItem(IDC_TRANSFER_M_Start_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[3].SetFont(16);
	m_bmpBtn[3].SetTitle("��ʼ");

	m_bmpBtn[4].SubclassDlgItem(IDC_TRANSFER_M_Stop_BTN, this);
	m_bmpBtn[4].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[4].SetFont(16);
	m_bmpBtn[4].SetTitle("ֹͣ");

	m_bmpBtn[5].SubclassDlgItem(IDC_TRANSFER_M_PAUSE_BTN, this);
	m_bmpBtn[5].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[5].SetFont(16);
	m_bmpBtn[5].SetTitle("��ͣ");

	m_bmpBtn[6].SubclassDlgItem(IDC_TRANSFER_M_Next_BTN, this);
	m_bmpBtn[6].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[6].SetFont(16);
	m_bmpBtn[6].SetTitle("��һ��");

	m_bmpBtn[7].SubclassDlgItem(IDC_TRANSFER_M_StepDebug_BTN, this);
	m_bmpBtn[7].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[7].SetFont(16);
	m_bmpBtn[7].SetTitle("��������");

	m_bmpBtn[8].SubclassDlgItem(IDC_TRANSFER_M_Fix_BTN, this);
	m_bmpBtn[8].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[8].SetFont(16);
	m_bmpBtn[8].SetTitle("�޸�");

	//��ʼ���б�ؼ�
	m_cListObject.ModifyStyle(NULL,LVS_REPORT);
	m_cListObject.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_MULTIWORKAREAS);

	m_cListObject.SetHeaderBKColor(0x00,0xB2,0xEE, 3);
	LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|WS_CHILD|WS_BORDER|WS_GROUP|LVS_REPORT/*|LVS_EDITLABELS*/;
	lvColumn.fmt = LVCFMT_CENTER;

	CRect rect;
	m_cListObject.GetWindowRect(&rect);
	int nWidth = rect.Width()/2;

	m_cListObject.InsertColumn(0, "��������", LVCFMT_CENTER);
	m_cListObject.InsertColumn(1, "����ʱ��", LVCFMT_CENTER);

	m_cListObject.SetColumnWidth(0, (int)(nWidth*1.17));
	m_cListObject.SetColumnWidth(1, (int)(nWidth*0.84));

	//��ʼ���༭��ؼ�
	SetDlgItemText(IDC_TRANSFER_M_PositionX_EDIT, "0");
	SetDlgItemText(IDC_TRANSFER_M_PositionY_EDIT, "0");
	SetDlgItemText(IDC_TRANSFER_M_PositionAngle_EDIT, "0");
	SetDlgItemText(IDC_TRANSFER_M_Angle_EDIT, "0");
	SetDlgItemText(IDC_TRANSFER_M_YOffset_EDIT, "0");
	SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, "0");

	UpdateList();

	//�ؼ�ʹ��
	GetDlgItem(IDC_TRANSFER_M_PAUSE_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_TRANSFER_M_Stop_BTN)->EnableWindow(FALSE);
	GetDlgItem(IDC_TRANSFER_M_Next_BTN)->EnableWindow(FALSE);

	//��ʾ���ʼ��
	m_strTips = "�������ò���Ȼ������ʼ�������飡";
	SetDlgItemText(IDC_TRANSFER_M_TIPS_STATIC, m_strTips);
}

void CDlgTransferManual::InitWindowHandle()
{
	SetCheck("~father");
	Hlong hlWnd;
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_TRANSFER_M_Image_STATIC);
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

void CDlgTransferManual::UpdateList()
{
	//���list
	m_cListObject.DeleteAllItems();
	ASSERT(m_cListObject.GetItemCount() == 0);
	//����һ���ļ��У����ļ����ؽ�ȥ
	int iItem = 0;
	CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);
	CString strFilePath = strDebugPath + "Storage\\Config\\TransferObject\\";	
	CString strTemp = strFilePath + "*.*";   
	CString lpFileName("");             //ȫ·�����������ļ���
	CString strFileName("");            //�ļ�����������·��
	char strValue[256];
	CFileFind FileFind;
	BOOL bFind = FileFind.FindFile(strTemp);
	while (bFind)
	{
		//������һ���ļ�
		bFind = FileFind.FindNextFile();
		//�ж��Ƿ�Ϊ�ļ���
		if(FileFind.IsDots())
			continue;
		strFileName = FileFind.GetFileName();
		m_cListObject.InsertItem(iItem,_T(""));
		m_cListObject.SetItemText(iItem, 0, strFileName);
		CString lpAppName = "Transfer_Object_File";
		lpFileName = strFilePath + strFileName;
		GetPrivateProfileString(lpAppName, "CreatedTime", "READ_FAIL", strValue, 256, lpFileName);
		m_cListObject.SetItemText(iItem, 1, (CString)strValue);
		iItem++;
	}
}

void CDlgTransferManual::OnBnClickedTransferMNewBtn()
{
	CDlgTransferManualNew dlg(m_pProCore);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDOK == dlg.DoModal())
	{
		//�����б�ؼ�
		UpdateList();
	}
}


void CDlgTransferManual::OnBnClickedTransferMDeleteBtn()
{
	int Item = GetSelProduct();
	if(0 > GetSelProduct())
	{
		MessageBox("δѡ���κ��ļ�!",_T("��ʾ"),MB_ICONWARNING+MB_OK);
		return;
	}
	int	iRet = MessageBox("ȷ��ɾ�����ļ���\n�����ȷ������ťȷ��ɾ�����ļ�ɾ�����޷��ָ���","Warning",MB_ICONWARNING+MB_OKCANCEL);
	if( iRet == IDOK)
	{
		//ִ��ɾ������
		CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);
		CString strFilePath = strDebugPath + "Config\\TransferObject\\";	
		CString strFileName = strFilePath + m_cListObject.GetItemText(Item,0);
		DeleteFileA(strFileName);
		m_cListObject.DeleteAllItems();
		UpdateList();
	}
	else
		return;
}


int CDlgTransferManual::GetSelProduct()
{
	CString str;
	for(int i=0; i<m_cListObject.GetItemCount(); i++)
	{
		if( m_cListObject.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )
		{
			return i;
		}
	}	
	return -1;
}


void CDlgTransferManual::OnBnClickedTransferMAdvancedBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgTransferManualAdvanced dlg(m_pProCore);
	dlg.DoModal();
}



void CDlgTransferManual::OnBnClickedTransferMStartBtn()
{
	UpdateData(TRUE);

	//����ѡ�ŵ����Ͷ���ѡ����صĲ����ļ�
	if (m_cListObject.GetSelectedCount() < 1)
	{
		MessageBox("��ѡ��һ����Ҫתӡ�Ķ���", "��ʾ", IDOK | MB_ICONERROR );
		return;
	}
	else if (m_cListObject.GetSelectedCount() > 1)
	{
		MessageBox("ѡ��Ķ��󳬹�һ��\n������ȷ��ѡ��", "��ʾ", IDOK | MB_ICONERROR );
		return;
	}

	int Item = GetSelProduct();
	CString strObjectName = m_cListObject.GetItemText(Item, 0);

	//�жϳߴ�����
	CString strSize = strObjectName.Left(strObjectName.Find("_"));
	if (_T("6mm X 6mm") == strSize)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferSize = SIZE66;
	}
	else if (_T("5mm X 5mm") == strSize)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferSize = SIZE55;
	}
	else if (_T("4mm X 4mm") == strSize)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferSize = SIZE44;
	}
	else if (_T("3mm X 3mm") == strSize)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferSize = SIZE33;
	}
	else if (_T("2mm X 2mm") == strSize)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferSize = SIZE22;
	}
	else if (_T("1mm X 1mm") == strSize)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferSize = SIZE11;
	}

	//�ж�תӡ����
	if (m_cTransTypeRadio == 0)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferType = INITIATIVE;
	}
	else if (m_cTransTypeRadio == 1)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferType = PASSITIVITY;
	}
	else
	{
		MessageBox("��ѡ��תӡ��ʽ", "��ʾ", MB_ICONERROR);
	}
	
	//��ȡʣ��ؼ�����
	ReadCtrlValue();
	
    //�ؼ�ʹ��
	GetDlgItem(IDC_TRANSFER_M_Start_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANSFER_M_PAUSE_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANSFER_M_Stop_BTN)->EnableWindow(TRUE);
	GetDlgItem(IDC_TRANSFER_M_Next_BTN)->EnableWindow(TRUE);

	m_NextBtnCount = 0;
	//����
	m_pProCore->GetProTransfer()->Run();
}

void CDlgTransferManual::ReadCtrlValue()
{
	UpdateData(TRUE);
	char PosX[256], PosY[256], PosAngle[256];
	char * StopString;
	memset(PosX, 0, 256);
	memset(PosY, 0, 256);
	memset(PosAngle, 0, 256);
	GetDlgItemText(IDC_TRANSFER_M_A_PositivePress_EDIT, PosX, 256);
	GetDlgItemText(IDC_TRANSFER_M_A_NegativePress_EDIT, PosY, 256);
	GetDlgItemText(IDC_TRANSFER_M_A_ZSpeed_EDIT, PosAngle, 256);

	if (strcmp(PosX, "") == 0 || strcmp(PosY, "") == 0 || strcmp(PosAngle, "") == 0)
	{
		MessageBox("��������ֵ", "��ʾ", MB_OK);
		return;
	}

	double fPosX = strtod(PosX, &StopString);
	if (strcmp(StopString, "\0") != 0)
	{
		MessageBox("����������������������", "��ʾ", MB_OK);
		return;
	}

	double fPosY = strtod(PosY, &StopString);
	if (strcmp(StopString, "\0") != 0)
	{
		MessageBox("����������������������", "��ʾ", MB_OK);
		return;
	}

	double fPosAngle = strtod(PosAngle, &StopString);
	if (strcmp(StopString, "\0") != 0)
	{
		MessageBox("����������������������", "��ʾ", MB_OK);
		return;
	}

	m_pProCore->GetParamData()->GetParamTransfer()->iPlacePos.fPosX = fPosX;
	m_pProCore->GetParamData()->GetParamTransfer()->iPlacePos.fPosY = fPosY;
	m_pProCore->GetParamData()->GetParamTransfer()->iPlacePos.fPosA = fPosAngle;

	if (0 == m_cTransTypeRadio)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferType = INITIATIVE;
	} 
	else if (1 == m_cTransTypeRadio)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->TransferType = PASSITIVITY;
	}
	else
	{
		MessageBox("��ѡ��תӡ��ʽ��", "��ʾ", MB_OK | MB_ICONERROR);
	}
}


void CDlgTransferManual::OnBnClickedTransferMNextBtn()
{
	// ����Ĵ�����1
	++m_NextBtnCount;
	switch(m_NextBtnCount)
	{
	case 1:
		//m_pProCore->GetProTransfer()->m_BeAdjustAngle = true;
		break;
	default:
		break;
	}
}


LRESULT CDlgTransferManual::OnChangeTips(WPARAM wParam, LPARAM lParam)
{
	//��һ����û�б����¹����Ƕȵ�����ϱ�־��δ��1
	if (0 == m_NextBtnCount && wParam == 1)
	{		
		m_strTips.Format("%f", m_pProCore->GetParamData()->GetParamTransfer()->fAngleOffsetPick);
		SetDlgItemText(IDC_TRANSFER_M_Angle_EDIT, m_strTips);
		m_strTips = "�Ƕ�ƫ��ֵΪ��" + m_strTips;
		m_strTips = "\n��ת���ֶ���̨�����Ƕ����";		
	} 
	else if(1 == m_NextBtnCount && wParam == 2)
	{
		m_strTips.Format("%f", m_pProCore->GetParamData()->GetParamTransfer()->fYOffsetPick);
		SetDlgItemText(IDC_TRANSFER_M_YOffset_EDIT, m_strTips);
		m_strTips = "Y�᷽��ƫ��ֵΪ��" + m_strTips;
		m_strTips = "\n��ת���ֶ���̨�����Ƕ����";
	}
	else if (3 == wParam)
	{
		m_strTips = "תӡ�����λ���";
	}

	RefreshStatic();

	CWnd* pTmpWnd = GetDlgItem(IDC_TRANSFER_M_TIPS_STATIC);
	ASSERT(pTmpWnd);

	pTmpWnd->SetWindowText(m_strTips);
	return TRUE;

	return 0;
}



void CDlgTransferManual::OnBnClickedTransferMStepdebugBtn()
{
	StepRun();
}


/*
** @name: StepRun
** @Function: ������������µ������к���
** @Input: NULL
** @Output: NULL
*/
void CDlgTransferManual::StepRun()
{	
	if (m_cTransTypeRadio == 0)
	{
		PositiveStepRun();
	}
	else if(m_cTransTypeRadio == 1)
	{
		//NegtiveStepRun();
	}
	else
	{		
		/*NULL*/
	}
}



/*
** @name: StepRunEnableCtrl
** @Function: ������������£�ʹ�ܿؼ�
** @Input: bool������true��ʾʹ��ʹ�ã�false��ʾʹ����ʹ��
** @Output: NULL
*/
void CDlgTransferManual::StepRunEnableCtrl(bool bEnable)
{
	GetDlgItem(IDC_TRANSFER_M_Start_BTN)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_TRANSFER_M_Active_RADIO)->EnableWindow(bEnable);

	GetDlgItem(IDC_TRANSFER_M_Passivity_RADIO)->EnableWindow(bEnable);
}


/*
** @name: PositiveStepRun
** @Function: ������������µ������к���
** @Input: NULL
** @Output: NULL
*/
void CDlgTransferManual::PositiveStepRun()
{
	++m_iClickNum;

	switch (m_iClickNum)
	{
	case STEP1:
		{
			StepRunEnableCtrl(false);

			/* �޸ĵ������԰�ť���� */
			m_bmpBtn[7].SetTitle("��һ��");
			CRect rc;
			GetDlgItem(IDC_TRANSFER_M_StepDebug_BTN)->GetWindowRect(&rc);
			ScreenToClient(&rc);
			RedrawWindow(&rc);


			/* ��ʼ�����������У��������*/
			PositiveStep1();
			SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("1"));
			break;
		}


	case STEP2:
		/* ����˶���תӡ�����ͼλ��*/
		PositiveStep2();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("2"));
		break;

	case STEP3:
		/* ��ʼ�����ͼ��ʵʱ�����������Ƕ�*/
		PositiveStep3();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("3"));
		break;

	case STEP4:
		/* �����Ƕȵ����� ��ʼY����λ*/
		PositiveStep4();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("4"));
		break;

	case STEP5:
		/* ����Y�����������ͼ��λX������е���ƶ���PI�Ϸ�*/
		PositiveStep5();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("5"));
		break;

	case STEP6:
		/* Z���������˶� */
		PositiveStep6();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("6"));
		break;

	case STEP7:
		/* ��������������ﵽָ��ֵ��Z�������˶� */
		PositiveStep7();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("7"));
		break;

	case STEP8:
		/* �Ƹ˱��Σ� �����˶�����ͼλ�� */
		PositiveStep8();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("8"));
		break;

	case STEP9:
		/* ���Ӷ�λ�������������װ��̬ */
		PositiveStep9();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("9"));
		break;

	case STEP10:
		/* תӡZ�������˶�����װλ�� */
		PositiveStep10();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("10"));
		break;

	case STEP11:
		/* �ر���������ʼ����,�ﵽָ��ֵ��رմ����� Z������ */
		PositiveStep11();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("11"));
		break;

	case STEP12:
		/* �ر���������ʼ����,�ﵽָ��ֵ��رմ����� Z������ */
		PositiveStep12();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("12"));
		break;

	case STEP13:
		/* �ر���������ʼ����,�ﵽָ��ֵ��رմ����� Z������ */
		PositiveStep13();
		SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("13"));
		break;

	case STEP14:
		{
			/* ���� */
			PositiveStep14();

			m_bmpBtn[7].SetTitle("��ʼ��������");
			CRect rc;
			GetDlgItem(IDC_TRANSFER_M_StepDebug_BTN)->GetWindowRect(&rc);
			ScreenToClient(&rc);
			RedrawWindow(&rc);

			StepRunEnableCtrl(true);

			SetDlgItemText(IDC_TRANSFER_M_StepNum_EDIT, _T("0"));
			break;
		}

	default:
		break;
	}

	if (m_iClickNum == STEP14)
	{
		m_iClickNum = 0;
	}
}


BOOL CDlgTransferManual::PositiveStep1()
{

#ifndef FE_DEBUG_OFFLINE

	//��������ģʽ���ò�����ִ�ж�Ӧ�Ĵ���
	m_pProCore->GetProTransfer()->SetRunMode(STEP);
	//�������
	//GoHome();
	//�������ģ��
	m_pProCore->GetProTransfer()->LoadModel();
	//��ʼ��
	m_pProCore->GetProTransfer()->StepRunInit();
	//����֧��ƽ̨���
	m_pProCore->GetProTransfer()->GetIoPickPlatform()->On();
#endif

	//������ʾ��
	UpDateTips(TO_TRANSCAM_VIEW);

	return TRUE;
}

BOOL CDlgTransferManual::PositiveStep2()
{
#ifndef FE_DEBUG_OFFLINE

	//�˶�����ͼλ��
	double fPosition;

	//X����˶�����ͼλ��
	fPosition = m_pProCore->GetParamData()->GetParamTransfer()->fXPosPickCamera;
	m_pProCore->GetProTransfer()->GetMotorTransferX()->MoveTo(fPosition);

	//Z�����˶�����ͼλ��
	fPosition = m_pProCore->GetParamData()->GetParamTransfer()->fZPosPickCamera;
	m_pProCore->GetProTransfer()->GetMotorTransferZ()->MoveTo(fPosition);

	//�Ӷ�ʱ����ѯ�Ƿ񵽴�ѧϰλ��
#endif

	UpDateTips(ANGLE_LOCA);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep3()
{
#ifndef FE_DEBUG_OFFLINE

	//����תӡX��Z�����ʹ��
	m_pProCore->GetProTransfer()->EnableTransMotor(false);

	//��תӡ���ץͼ������ʵʱ�Ƕȶ�λ
	m_pProCore->GetProTransfer()->StartAngleAdjust();

#endif
	UpDateTips(POSY_LOCA);
	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep4()
{

#ifndef FE_DEBUG_OFFLINE

	//�����Ƕȵ�����ѭ��
	m_pProCore->GetProTransfer()->EndAngleAdjust();

	//��ʼ��ͼ������ʵʱY����λ
	m_pProCore->GetProTransfer()->StartYAdjust();

#endif

	UpDateTips(TO_PICK_POS);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep5()
{

#ifndef FE_DEBUG_OFFLINE

	//ʹ�ܵ��
	m_pProCore->GetProTransfer()->EnableTransMotor(true);

	//����Y�������
	m_pProCore->GetProTransfer()->EndYAdjust();

	//�˳������߳�
	m_pProCore->GetProTransfer()->ExitStepAdjustThread();

	//��ʼ��ͼ��X����λ
	m_pProCore->GetProTransfer()->PickPosXLocation();

	Sleep(100);

	//�ƶ�X������PI�Ϸ�
	double fDis = m_pProCore->GetParamData()->GetParamTransfer()->fDisPickerCamX;
	double fOffset = m_pProCore->GetParamData()->GetParamTransfer()->fXOffsetPick;
	double des =  fDis + fOffset;
	m_pProCore->GetProTransfer()->GetMotorTransferX()->MoveTo(des);

#endif

	UpDateTips(PICK);

	return TRUE;
}

BOOL CDlgTransferManual::PositiveStep6()
{
#ifndef FE_DEBUG_OFFLINE

	//�ƶ�Z������ʰȡλ��
	double des = m_pProCore->GetParamData()->GetParamTransfer()->fZPosPickPicker;
	m_pProCore->GetProTransfer()->GetMotorTransferZ()->MoveTo(des);

#endif

	UpDateTips(SUCTION);

	return TRUE;
}

BOOL CDlgTransferManual::PositiveStep7()
{
#ifndef FE_DEBUG_OFFLINE

	//�����Ÿ����������
	m_pProCore->GetProTransfer()->GetIoRodAttach()->On();
	//����Ĥ�������
	m_pProCore->GetProTransfer()->GetIoVacAttach()->On();

	//����ʱ����ѯ���Ƿ񵽴�ָ����ѹֵ��Ȼ��ر�Ĥ��տ��أ�������ʱ��Ȼ������Z�ᣬ�������������
	//SetTimer(1, 10, NULL);
#endif
	
	UpDateTips(ROD_RUN);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep8()
{
#ifndef FE_DEBUG_OFFLINE

	//������ת��Ϣ
	m_pProCore->GetProTransfer()->CalRotateInfo();

	//�Ƹ��˶�
	double fDis 

	fDis= m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod11;
	m_pProCore->GetProTransfer()->GetMotorRod11()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod12;
	m_pProCore->GetProTransfer()->GetMotorRod12()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod13;
	m_pProCore->GetProTransfer()->GetMotorRod13()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod21;
	m_pProCore->GetProTransfer()->GetMotorRod21()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod22;
	m_pProCore->GetProTransfer()->GetMotorRod22()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod23;
	m_pProCore->GetProTransfer()->GetMotorRod23()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod31;
	m_pProCore->GetProTransfer()->GetMotorRod31()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod32;
	m_pProCore->GetProTransfer()->GetMotorRod32()->MoveTo(fDis);

	fDis = m_pProCore->GetParamData()->GetParamTransfer()->RodStransform.fRod33;
	m_pProCore->GetProTransfer()->GetMotorRod33()->MoveTo(fDis);	

#endif

	UpDateTips(TO_UPCAM_VIEW);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep9()
{
#ifndef FE_DEBUG_OFFLINE

	//X��Z���˶������������ͼλ��
	double des(0.0);
	des = m_pProCore->GetParamData()->GetParamTransfer()->fXPosPlaceCamera;
	m_pProCore->GetProTransfer()->GetMotorTransferX()->MoveTo(des);
	des = m_pProCore->GetParamData()->GetParamTransfer()->fZPosPlaceCamera;
	m_pProCore->GetProTransfer()->GetMotorTransferZ()->MoveTo(des);

	//�����˶������Ӳ�ͼλ��
	des = m_pProCore->GetParamData()->GetParamTransfer()->fXPosViewFourAxle;
	m_pProCore->GetProTransfer()->GetMotorFourX()->MoveTo(des);
	des = m_pProCore->GetParamData()->GetParamTransfer()->fYPosViewFourAxle;
	m_pProCore->GetProTransfer()->GetMotorFourY()->MoveTo(des);

	
#endif

	UpDateTips(PLACE_LOCA);

	return TRUE;
}



BOOL CDlgTransferManual::PositiveStep10()
{
#ifndef FE_DEBUG_OFFLINE
	
	//�������ץһ��ͼ
	CVisionPart* pCamera;
	pCamera = m_pProCore->GetProTransfer()->GetCameraUp();
	pCamera->SingleGrab();
	pCamera->Match();

	//�����˶�
	double des = m_pProCore->GetParamData()->GetParamTransfer()->fZPosAfterSurfaceLoc;
	m_pProCore->GetProTransfer()->GetMotorTransferZ()->MoveTo(des);

#endif

	UpDateTips(SURFACE_ROTATE);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep11()
{
#ifndef FE_DEBUG_OFFLINE

	//�����XY�ߵ���װ��λ��
	double des;
	des = m_pProCore->GetParamData()->GetParamTransfer()->fXPosPlaceFourAxle + 
		       m_pProCore->GetParamData()->GetParamTransfer()->fXOffsetPlace;

	m_pProCore->GetProTransfer()->GetMotorFourX()->MoveTo(des);

	des = m_pProCore->GetParamData()->GetParamTransfer()->fYPosPlaceFourAxle + 
		       m_pProCore->GetParamData()->GetParamTransfer()->fYOffsetPlace;

	m_pProCore->GetProTransfer()->GetMotorFourY()->MoveTo(des);

	//�����Ƕ�ƫ��
	des = m_pProCore->GetParamData()->GetParamTransfer()->fAngleOffsetPlace;

	m_pProCore->GetProTransfer()->GetMotorFourAngleC()->MoveTo(des);

	//������ת
	des = m_pProCore->GetParamData()->GetParamTransfer()->fAPosPlaceFourAxle;
	m_pProCore->GetProTransfer()->GetMotorFourAngleA()->MoveTo(des);

	des = m_pProCore->GetParamData()->GetParamTransfer()->fBPosPlaceFourAxle;
	m_pProCore->GetProTransfer()->GetMotorFourAngleB()->MoveTo(des);

#endif

	UpDateTips(PLACE);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep12()
{
#ifndef FE_DEBUG_OFFLINE

	//��е�������˶�����װλ��
	double des = m_pProCore->GetParamData()->GetParamTransfer()->fZPosPlacePicker;
	m_pProCore->GetProTransfer()->GetMotorTransferZ()->MoveTo(des);
#endif

	UpDateTips(BLOW);

	return TRUE;
}


BOOL CDlgTransferManual::PositiveStep13()
{
#ifndef FE_DEBUG_OFFLINE

	//�ر������������������
	m_pProCore->GetProTransfer()->GetIoVacAttach()->Off();
	Sleep(100);

	m_pProCore->GetProTransfer()->GetIoVacBlow()->On();

	//��ʱ��ѯѹ��
	SetTimer(1, 10, NULL);
#endif

	UpDateTips(END);

	return TRUE;
}

BOOL CDlgTransferManual::PositiveStep14()
{
#ifndef FE_DEBUG_OFFLINE

	//�ر�ƽ̨���
	m_pProCore->GetProTransfer()->GetIoPickPlatform()->Off();
	GoHome();

#endif
    
    UpDateTips(INIT);

	return TRUE;
}

/*
** @name: GoHome
** @Function: תӡģ��������
** @Input: NULL
** @Output: NULL
*/
BOOL CDlgTransferManual::GoHome()
{
	return TRUE;
}


/***************************************************************** 
** ��������: UpDateTips
** �������: �����
** ���:	     BOOL
** ��������: ��������ʱ������ʾ������ʾ��Ӧ����ʾ��Ϣ
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CDlgTransferManual::UpDateTips(int num)
{
	m_strTips = _T("");
	switch (num)
	{
	case GO_HOME:
		m_strTips = _T("���������...");
		break;
		
	case TO_TRANSCAM_VIEW:
		m_strTips = _T("��ʾ���ȴ���������󣬵�����һ����ʹתӡ����˶�����ͼλ��");
		break;

	case ANGLE_LOCA:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ���������ֶ�ƽ̨�����Ƕ����С��0.1");
		break;

	case POSY_LOCA:
		m_strTips = _T("��ʾ���Ƕȵ�����ɺ󣬵�����һ��������Y�����ֶ���̨ʹ���С��0.1������һ��");
		break;

	case TO_PICK_POS:
		m_strTips = _T("��ʾ��Y������������󣬵�����һ������е���˶���PI�Ϸ�׼��ʰȡ");
		break;

	case PICK:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ����Z���е���˶���ʰȡλ��");
		break;

	case SUCTION:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ���������������");
		break;
		
	case ROD_RUN:
		m_strTips = _T("��ʾ��Z����������ȫ�߶Ⱥ󣬵�����һ�������Ὺʼ����");
		break;

	case TO_UPCAM_VIEW:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ�����˶������������ͼλ�ã���е�ֱ��γ�����״̬");
		break;

	case PLACE_LOCA:
		m_strTips = _T("��ʾ���˶�ֹͣ�󣬵�����һ����ʼ��װ��λ");
		break;

	case TO_PLACE_POSE:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ���������˶�����װλ��");
		break;

	case SURFACE_ROTATE:
		m_strTips = _T("��ʾ�����ֹͣ�󣬵�����һ����ʼ������ת");
		break;

	case PLACE:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ����Z�����˶�����װ��");
		break;

	case BLOW:
		m_strTips = _T("��ʾ������˶�ֹͣ�󣬵�����һ�����ر������������������");
		break;

	case END:
		m_strTips = _T("��ʾ���������Խ���������ص���λ");
		break;

	case INIT:
		m_strTips = _T("�������ò���Ȼ������ʼ��������");
		break;

	default:
		break;
	}

	//����Ϊ͸������Ҫ�ֲ�ˢ������������
	RefreshStatic();

	CWnd* pTmpWnd = GetDlgItem(IDC_TRANSFER_M_TIPS_STATIC);
	ASSERT(pTmpWnd);
	
	pTmpWnd->SetWindowText(m_strTips);
	return TRUE;

	return FALSE;
}


/***************************************************************** 
** ��������: RefreshStatic
** �������: ��
** ���:	     ��
** ��������: ���ھֲ�ˢ��
** ������:	 ����
** Version:1.0
*****************************************************************/
void CDlgTransferManual::RefreshStatic()
{
	if ((CStatic*)GetDlgItem(IDC_TRANSFER_M_TIPS_STATIC)->GetSafeHwnd())  //�жϴ����Ƿ�����
	{
		CStatic * pWnd = ((CStatic*)GetDlgItem(IDC_TRANSFER_M_TIPS_STATIC));
		ASSERT(pWnd); //�ж�ָ���Ƿ�Ϊ��
		CRect Rect;
		pWnd ->GetWindowRect(&Rect);
		ScreenToClient(&Rect);
		InvalidateRect(&Rect);
	}
}


/***************************************************************** 
** ��������: OnTimer
** �������: nIDEvent����ʱ����
** ���:	     ��
** ��������: ��ʱ��ѯ����Ƿ�ﵽָ��ֵ
** ������:	 ����
** Version:1.0
*****************************************************************/
void CDlgTransferManual::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(nIDEvent)
	{
	case 0:
		//����ﵽָ��ֵ����ʹZ�������ƣ��رն�ʱ��
		
		break;

	case 1:
		//����ﵽָ��ֵ����ʹZ�������ƣ��رն�ʱ��

		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


void CDlgTransferManual::OnBnClickedTransferMCameraTransDownRadio()
{
	m_pProCore->SwitchCamera(TRANS_DOWN);
	m_pProCore->SetShowInfo(TRANS_DOWN, m_windowHandle_Pic, m_winSize_Pic);
}


void CDlgTransferManual::OnBnClickedTransferMCameraTransUpRadio()
{
	m_pProCore->SwitchCamera(TRANS_UP);
	m_pProCore->SetShowInfo(TRANS_UP, m_windowHandle_Pic, m_winSize_Pic);
}
