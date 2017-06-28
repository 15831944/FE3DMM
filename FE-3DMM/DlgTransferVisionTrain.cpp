// DlgTransferVisionTrain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgTransferVisionTrain.h"
#include "afxdialogex.h"


// CDlgTransferVisionTrain �Ի���

IMPLEMENT_DYNAMIC(CDlgTransferVisionTrain, CDialog)

CDlgTransferVisionTrain::CDlgTransferVisionTrain(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTransferVisionTrain::IDD, pParent)
	, m_iTransferType(0)
	, m_iMatchType(0)
{
	m_pProCore = pProCore;
}

CDlgTransferVisionTrain::~CDlgTransferVisionTrain()
{
	Release();
}

void CDlgTransferVisionTrain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TRANSFER_V_GB1_GROUP, m_GB1);
	DDX_Control(pDX, IDC_TRANSFER_V_GB2_GROUP, m_GB2);
	DDX_Control(pDX, IDC_TRANSFER_V_GB3_GROUP, m_GB3);
	DDX_Control(pDX, IDC_TRANSFER_V_PicShow_STATIC, m_staticPicShow);
	DDX_Control(pDX, IDC_TRANSFER_V_Model_LIST, m_cModelList);
	DDX_Control(pDX, IDC_TRANSFER_V_Object_COMBO, m_cComBoxObject);
	DDX_Radio(pDX, IDC_TRANSFER_V_INITIATIVE_RADIO, m_iTransferType);
	DDX_Radio(pDX, IDC_TRANSFER_V_NCC_RADIO, m_iMatchType);
}


BEGIN_MESSAGE_MAP(CDlgTransferVisionTrain, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TRANSFER_V_CameraTransUp_RADIO, &CDlgTransferVisionTrain::OnBnClickedTransferVCameraTransUpRadio)
	ON_BN_CLICKED(IDC_TRANSFER_V_CameraTransDown_RADIO, &CDlgTransferVisionTrain::OnBnClickedTransferVCameraTransDownRadio)
	ON_BN_CLICKED(IDC_TRANSFER_V_CameraLIVE_CHECK, &CDlgTransferVisionTrain::OnBnClickedTransferVCameraliveCheck)
	ON_BN_CLICKED(IDC_TRANSFER_V_INITIATIVE_RADIO, &CDlgTransferVisionTrain::OnBnClickedTransferVInitiativeRadio)
	ON_BN_CLICKED(IDC_TRANSFER_V_PASSIVITY_RADIO, &CDlgTransferVisionTrain::OnBnClickedTransferVPassivityRadio)
	ON_BN_CLICKED(IDC_TRANSFER_V_Calibrate_BTN, &CDlgTransferVisionTrain::OnBnClickedTransferVCalibrateBtn)
	ON_BN_CLICKED(IDC_TRANSFER_V_MakeModel_BTN, &CDlgTransferVisionTrain::OnBnClickedTransferVMakemodelBtn)
	ON_BN_CLICKED(IDC_TRANSFER_V_ModelDel_BTN, &CDlgTransferVisionTrain::OnBnClickedTransferVModeldelBtn)
	ON_NOTIFY(NM_CLICK, IDC_TRANSFER_V_Model_LIST, &CDlgTransferVisionTrain::OnNMClickTransferVModelList)
END_MESSAGE_MAP()


// CDlgTransferVisionTrain ��Ϣ�������
void CDlgTransferVisionTrain::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgTransferVisionTrain::OnCancel()
{
	DestroyWindow();
}


void CDlgTransferVisionTrain::Cancel()
{
	KillTimer(1);    //�ر������ʾ��ʱ��
	OnCancel();
}


void CDlgTransferVisionTrain::Release()
{

}


HBRUSH CDlgTransferVisionTrain::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_STATIC:
		case  IDC_TRANSFER_V_CameraTransUp_RADIO:
		case IDC_TRANSFER_V_CameraTransDown_RADIO:
		case IDC_TRANSFER_V_INITIATIVE_RADIO:
		case IDC_TRANSFER_V_PASSIVITY_RADIO:
		case IDC_TRANSFER_V_CameraLIVE_CHECK:
		case IDC_TRANSFER_V_NCC_RADIO:
		case IDC_TRANSFER_V_SHAPE_RADIO:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}


BOOL CDlgTransferVisionTrain::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgTransferVisionTrain::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();
	InitHalconWindow();

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_TRANSFER_V_PicShow_STATIC);
	CRect rcPicShow;
	pWnd->GetClientRect(&rcPicShow);
	m_imgoperTransUp.Init(TRANS_UP, rcPicShow.Width(), rcPicShow.Height());
	m_imgoperTransDown.Init(TRANS_UP, rcPicShow.Width(), rcPicShow.Height());
	m_staticPicShow.SetDrawRect(true);		//Pic�������û�����

	return TRUE;  
}

void CDlgTransferVisionTrain::InitDlgCtrl()
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


	m_bmpBtn[0].SubclassDlgItem(IDC_TRANSFER_V_Calibrate_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("�궨");

	m_bmpBtn[1].SubclassDlgItem(IDC_TRANSFER_V_MakeModel_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(15);
	m_bmpBtn[1].SetTitle("����ģ��");

	m_bmpBtn[2].SubclassDlgItem(IDC_TRANSFER_V_ModelDel_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(15);
	m_bmpBtn[2].SetTitle("ɾ��ģ��");
	
	//��ʼ��PI�ߴ���Ͽ�ؼ�
	m_cComBoxObject.InsertString(0, "1mm X 1mm");
	m_cComBoxObject.InsertString(1, "2mm X 2mm");
	m_cComBoxObject.InsertString(2, "3mm X 3mm");
	m_cComBoxObject.InsertString(3, "4mm X 4mm");
	m_cComBoxObject.InsertString(4, "5mm X 5mm");
	m_cComBoxObject.InsertString(5, "6mm X 6mm");

	m_cComBoxObject.SetCurSel(5);  

	//��ʼ���б�ؼ�
	m_cModelList.ModifyStyle(NULL,LVS_REPORT);
	m_cModelList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_MULTIWORKAREAS);

	m_cModelList.SetHeaderBKColor(0x00,0xB2,0xEE, 3);
	LV_COLUMN lvColumn;
	lvColumn.mask = LVCF_FMT|LVCF_WIDTH|LVCF_TEXT|WS_CHILD|WS_BORDER|WS_GROUP|LVS_REPORT/*|LVS_EDITLABELS*/;
	lvColumn.fmt = LVCFMT_CENTER;

	CRect rect;
	m_cModelList.GetWindowRect(&rect);
	int nWidth = rect.Width()/2;

	m_cModelList.InsertColumn(0, "�������", LVCFMT_CENTER);
	m_cModelList.InsertColumn(1, "ģ������", LVCFMT_CENTER);

	m_cModelList.SetColumnWidth(0, (int)(nWidth*0.6));
	m_cModelList.SetColumnWidth(1, (int)(nWidth*1.37));

	SetDlgItemText(IDC_TRANSFER_V_DotsDis_EDIT, _T("0.25"));
	SetDlgItemText(IDC_TRANSFER_V_DotsDimeter_EDIT, _T("0.25"));
	SetDlgItemText(IDC_TRANSFER_V_DotsRowNum_EDIT, _T("5"));
	SetDlgItemText(IDC_TRANSFER_V_DotsColNum_EDIT, _T("5"));

	UpdateModelList();
}

void CDlgTransferVisionTrain::InitHalconWindow()
{
	SetCheck("~father");
	Hlong hlWnd;
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_TRANSFER_V_ModelPicShow_STATIC);
	hlWnd = (Hlong)(pWnd ->GetSafeHwnd());

	CRect rc; 
	pWnd->GetClientRect(&rc);
	OpenWindow(0, 0, rc.Width(), rc.Height(), hlWnd, "", "", &m_hvModelWindow);
	SetPart(m_hvModelWindow, 0, 0, rc.Height()-1, rc.Width()-1);
	SetWindowAttr("background_color", "black");
	SetCheck("father");
}

BOOL CDlgTransferVisionTrain::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgTransferVisionTrain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (1 == nIDEvent)
	{
		if (NULL == m_pProCore)  return;	

		HObject	*pHobj= NULL;
		IplImage *pIplImg = NULL;
		switch(m_cameratypeTrans)
		{
		case TRANS_UP:
			pHobj = m_pProCore->GetCameraTransUp()->GetSingleShow();
			pIplImg = m_imgoperTransUp.HObject2IplImage(*pHobj);
			break;

		case TRANS_DOWN:
			pHobj = m_pProCore->GetCameraTransDown()->GetSingleShow();
			pIplImg = m_imgoperTransDown.HObject2IplImage(*pHobj);
			break;

		default:
			break;
		}
	
		if (NULL == pIplImg)  return;
		m_staticPicShow.SetShowImage(pIplImg);
	}

	CDialog::OnTimer(nIDEvent);
}


void CDlgTransferVisionTrain::SetTransCameraType(const CameraType camtype)
{
	m_cameratypeTrans = camtype;
}


void CDlgTransferVisionTrain::OnBnClickedTransferVCameraTransUpRadio()
{
	SetTransCameraType(TRANS_UP);
	if (NULL != m_pProCore)
		m_pProCore->SwitchCamera(TRANS_UP);
}


void CDlgTransferVisionTrain::OnBnClickedTransferVCameraTransDownRadio()
{
	SetTransCameraType(TRANS_DOWN);
	if (NULL != m_pProCore)
		m_pProCore->SwitchCamera(TRANS_DOWN);
}


void CDlgTransferVisionTrain::OnBnClickedTransferVCameraliveCheck()
{
	CButton* pBtn = (CButton*)GetDlgItem(IDC_TRANSFER_V_CameraLIVE_CHECK);
	int nState = pBtn->GetCheck();
	if (BST_CHECKED == nState)
	{
		SetTimer(1, 50, NULL);	 //���������ʾ��ʱ��
	}
	else
	{
		KillTimer(1);      //�ر������ʾ��ʱ��
	}
}

/***************************************************************** 
** ��������: ����ģ���б�
** �������: ��
** ���:	     ��
** ��������: ��ģ���б�ؼ�������ˢ��һ��
** ������:	 ����
** Version:1.0
****************************************************************/
void CDlgTransferVisionTrain::UpdateModelList()
{
	UpdateData(TRUE);
	//���list
	m_cModelList.DeleteAllItems();
	ASSERT(m_cModelList.GetItemCount() == 0);
	//����һ���ļ��У����ļ����ؽ�ȥ
	int iItem = 0;
	CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);
	//Ѱ������ģ��
	CString strFilePath = strDebugPath + "Storage\\Model";	
	CString strTemp = strFilePath + "\\*.*";
	CString strFileName("");
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
		//�ж��Ƿ�ΪͼƬ
		if (-1 != strFileName.Find(".bmp"))
			continue;

		CString strTempName = strFileName.Mid(strFileName.Find('_') + 1);
		CString strCamName = strTempName.Left(strTempName.Find('_'));
		m_cModelList.InsertItem(iItem,_T(""));

		if (strCamName == "TransCam")
		{
			m_cModelList.SetItemText(iItem, 0, "תӡ���"); 
		} 
		else if (strCamName == "UpCam")
		{
			m_cModelList.SetItemText(iItem, 0, "�������");
		}
		m_cModelList.SetItemText(iItem, 1, strFileName);
		++iItem;
	}
}

void CDlgTransferVisionTrain::OnBnClickedTransferVInitiativeRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateModelList();
}


void CDlgTransferVisionTrain::OnBnClickedTransferVPassivityRadio()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateModelList();
}


void CDlgTransferVisionTrain::OnBnClickedTransferVCalibrateBtn()
{
	UpdateData(TRUE);

	//��ȡ�궨����
	float fDotsDis(0.0), fDotsDimeter(0.0);
	int nRowDotsNum(0), nColumnDotsNum(0);
	char chTemp[100];
	memset(chTemp, '\0', sizeof(chTemp));
	if (0 == GetDlgItemText(IDC_TRANSFER_V_DotsDis_EDIT, chTemp, 100))
	{
		MessageBox("���������������������������", "��ʾ", MB_OK);
		return;
	}
	else
	{
		fDotsDis = atof(chTemp);
	}
	
	if (0 == GetDlgItemText(IDC_TRANSFER_V_DotsDimeter_EDIT, chTemp, 100))
	{
		MessageBox("���������������������������", "��ʾ", MB_OK);
		return;
	}
	else
	{
		fDotsDimeter = atof(chTemp);
	}

	if (0 == GetDlgItemText(IDC_TRANSFER_V_DotsRowNum_EDIT, chTemp, 100))
	{
		MessageBox("���������������������������", "��ʾ", MB_OK);
		return;
	}
	else
	{
		nRowDotsNum = atoi(chTemp);
	}
	
	if (0 == GetDlgItemText(IDC_TRANSFER_V_DotsColNum_EDIT, chTemp, 100))
	{
		MessageBox("���������������������������", "��ʾ", MB_OK);
		return;
	}
	else
	{
		nColumnDotsNum = atoi(chTemp);
	}

	//��ȡ��Ƥ���rect
	CRect rc = m_staticPicShow.GetTrackerRect();
	float fPixelHeight, fPixelWidth;
	CImageOperate* pImgOp;
	if (m_cameratypeTrans == TRANS_DOWN)
	{
		pImgOp = &m_imgoperTransDown;
	}
	else if (m_cameratypeTrans == TRANS_UP)
	{
		pImgOp = &m_imgoperTransUp;
	}
	else
	{
		MessageBox("��ѡ��궨�����������", "��ʾ", MB_OK);
		return;
	}

	if (nRowDotsNum == 3 && nColumnDotsNum == 3)
	{
		pImgOp->Calibrate(rc, fDotsDis, fDotsDimeter, Three, fPixelWidth, fPixelHeight);
	}		
	else if (nRowDotsNum == 4 && nColumnDotsNum == 4)
	{
		pImgOp->Calibrate(rc, fDotsDis, fDotsDimeter, Four, fPixelWidth, fPixelHeight);
	}
	else if (nRowDotsNum == 5 && nColumnDotsNum == 5)
	{
		pImgOp->Calibrate(rc, fDotsDis, fDotsDimeter, Five, fPixelWidth, fPixelHeight);
	}
	else if (nRowDotsNum == 6 && nColumnDotsNum == 6)
	{
		pImgOp->Calibrate(rc, fDotsDis, fDotsDimeter, Six, fPixelWidth, fPixelHeight);
	}
	else
	{
		MessageBox("����ĵ�������ȷ�����������������", "��ʾ", MB_OK);
	}

	//����궨����
	if (m_cameratypeTrans == TRANS_DOWN)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->fDownPixelWidth = fPixelWidth;
		m_pProCore->GetParamData()->GetParamTransfer()->fDownPixelHeight = fPixelHeight;
	}
	else if (m_cameratypeTrans == TRANS_UP)
	{
		m_pProCore->GetParamData()->GetParamTransfer()->fUpPixelWidth = fPixelWidth;
		m_pProCore->GetParamData()->GetParamTransfer()->fUpPixelHeight = fPixelHeight;
	}
	//д���ļ���
	m_pProCore->GetParamData()->SaveTransferPa();
}


void CDlgTransferVisionTrain::OnBnClickedTransferVMakemodelBtn()
{
	UpdateData(TRUE);

	CString strTransferType;
	switch(m_iTransferType)
	{
	case 0:
		strTransferType = _T("Initiative");
		break;
	case 1:
		strTransferType = _T("Passivity");
		break;
	default:
		::MessageBox(NULL, _T("��ѡ��һ��תӡ��ʽ������"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
		return;
	}

	int iSel;
	CString strCamName;
	CString strObject("Null");
	CString strModelName;

	switch(m_cameratypeTrans)
	{
	case TRANS_DOWN:
		strCamName = strTransferType + "_TransCam";
		break;
	case TRANS_UP:
		strCamName = strTransferType + "_UpCam";
		break;
	default:
		AfxMessageBox(_T("����ʧ�ܣ�"));
		return;
	}

	iSel = m_cComBoxObject.GetCurSel();
	if (CB_ERR  != iSel)
	{
		m_cComBoxObject.GetLBText(iSel, strObject);
	}

	strModelName = strCamName + "_" + strObject;

	switch(m_iMatchType)
	{
	case NCC:
		strModelName += "_NCC";
		break;
	case SHAPE:
		strModelName += "_SHAPE";
		break;
	default:
		AfxMessageBox(_T("����ʧ�ܣ�"));
		return;
	}

	CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);
	CString strImageName = strDebugPath + "Storage\\Model\\" + strModelName;
	//�����Ƿ��Ѿ�����
	CFileFind FileFind;
	if (FileFind.FindFile(strImageName))
	{
		int ret = ::MessageBox(NULL, _T("��ģ���Ѿ�����\n�滻��ԭģ�岻�ɻָ����Ƿ��滻��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONQUESTION);
		if (IDCANCEL== ret)
		{
			return;
		} 
	}


	CRect rc = m_staticPicShow.GetTrackerRect();
	HObject* ho_Image = NULL;
	switch(m_cameratypeTrans)
	{
	case TRANS_DOWN:
		{
			m_pProCore->GetCameraTransDown()->GetSingleSave();
			ho_Image = m_pProCore->GetCameraTransDown()->GetSingleSave();
			m_imgoperTransDown.CreateModel(ho_Image, rc, strModelName);
			break;
		}
	case TRANS_UP:
		{
			m_pProCore->GetCameraTransUp()->GetSingleSave();
			ho_Image = m_pProCore->GetCameraTransDown()->GetSingleSave();
			m_imgoperTransDown.CreateModel(ho_Image, rc, strModelName);
			break;
		}
	default:
		break;
	}
	//����ģ���б�
	UpdateModelList();

	////���½���ģ����Ϊѡ��״̬��ѭ�����ҵ�ָ����λ��
	//for(int nIndex = 0; nIndex < m_cModelList.GetItemCount(); ++nIndex)
	//{
	//	CString name = m_cModelList.GetItemText(nIndex, 1);
	//	if (name == strModelName)
	//	{
	//		m_cModelList.SetItemState(nIndex, LVIS_SELECTED |LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	//		HTuple hv_Width, hv_Height;
	//		ReadImage(&m_hoImageModel, HTuple(strImageName));
	//		GetImageSize(m_hoImageModel, &hv_Width, &hv_Height);
	//		SetPart(m_hvModelWindowHandle, 0, 0, hv_Height - 1, hv_Width - 1);
	//		DispObj(m_hoImageModel, m_hvModelWindowHandle);
	//	}
	//}
}


void CDlgTransferVisionTrain::OnBnClickedTransferVModeldelBtn()
{
	//�ɴ���ͬʱɾ��һ�л���е����
	while(m_cModelList.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED) != -1)
	{
		int nItem = m_cModelList.GetNextItem(-1,LVNI_ALL | LVNI_SELECTED);
		CString strModelName = m_cModelList.GetItemText(nItem, 1);

		CFileFind FileFind;
		CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);

		CString strFilePath = strDebugPath + "Storage\\Model\\";	
		CString strFullPath = strFilePath + strModelName;

		HTuple  hv_Error,hv_ErrorText;
		try
		{
			//ɾ��ģ���ļ�
			HalconCpp::DeleteFile((HTuple)strFullPath);
			//ɾ��ģ��ͼ��
			strFullPath += _T(".bmp");
			HalconCpp::DeleteFile((HTuple)strFullPath);
		}
		catch(HException e)
		{
			hv_Error = (int)e.ErrorCode();
			int errnotmp = hv_Error;
			CString strCode;
			strCode.Format("%d", errnotmp);
			hv_ErrorText  = e.ErrorMessage();
			CString strtmp = hv_ErrorText.ToString();
			strtmp = strCode + ":  ɾ��ʧ��\n"+strtmp;
			AfxMessageBox(strtmp);
			return;
		}
		m_cModelList.DeleteItem(nItem);
	}
}


void CDlgTransferVisionTrain::OnNMClickTransferVModelList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CString strModelName;
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if(-1 != pNMListView->iItem)
	{
		strModelName = m_cModelList.GetItemText(pNMListView->iItem, 1);
	}
	else
	{
		//��մ���
		ClearWindow(m_hvModelWindow);
		return;
	}

	CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);
	CString strImageName = strDebugPath + "Storage\\Model\\" + strModelName + ".bmp";
	HTuple hv_Width, hv_Height;

	try
	{
		ReadImage(&m_hoImageModel, HTuple(strImageName));
		GetImageSize(m_hoImageModel, &hv_Width, &hv_Height);
		SetPart(m_hvModelWindow, 0, 0, hv_Height - 1, hv_Width - 1);
		DispObj(m_hoImageModel, m_hvModelWindow);
	}
	catch(HalconCpp::HException e)
	{
		ClearWindow(m_hvModelWindow);
		return;
	}
}
