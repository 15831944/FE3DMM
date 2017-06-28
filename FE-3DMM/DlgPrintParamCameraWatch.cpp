// DlgPrintParamCameraWatch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgPrintParamCameraWatch.h"
#include "DlgPrintParamAdjust.h"
#include "afxdialogex.h"


// CDlgPrintParamCameraWatch �Ի���

IMPLEMENT_DYNAMIC(CDlgPrintParamCameraWatch, CDialog)

CDlgPrintParamCameraWatch::CDlgPrintParamCameraWatch(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrintParamCameraWatch::IDD, pParent)
{
	m_pProCore						= pProCore;
	m_pDlgParamMain			= (CDlgPrintParamAdjust*)pParent;

	m_bDrawTickMark			= false;
	m_bWriteVideo				= false;
	m_strFileName					= _T("");
	m_strStorePath				= _T("");
	m_strPhotoAllPath			= _T("");
	m_strVideoAllPath			= _T("");
}

CDlgPrintParamCameraWatch::~CDlgPrintParamCameraWatch()
{
	Release();
}

void CDlgPrintParamCameraWatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRINT_PA_CAMERA_PicShow_STATIC, m_staticPicShow);
	DDX_Text(pDX, IDC_PRINT_PA_CAMERA_FileName_EDIT, m_strFileName);
}


BEGIN_MESSAGE_MAP(CDlgPrintParamCameraWatch, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PRINT_PA_CAMERA_FileName_BTN, &CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraFilenameBtn)
	ON_BN_CLICKED(IDC_PRINT_PA_CAMERA_Photo_BTN, &CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraPhotoBtn)
	ON_BN_CLICKED(IDC_PRINT_PA_CAMERA_Video_BTN, &CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraVideoBtn)
	ON_BN_CLICKED(IDC_PRINT_PA_CAMERA_TickMark_BTN, &CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraTickmarkBtn)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgPrintParamCameraWatch ��Ϣ�������


void CDlgPrintParamCameraWatch::OnCancel()
{
	DestroyWindow();
}


void CDlgPrintParamCameraWatch::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgPrintParamCameraWatch::Cancel()
{
	KillTimer(1);  //�رն�ʱ��
	OnCancel();
}


void CDlgPrintParamCameraWatch::Release()
{

}


HBRUSH CDlgPrintParamCameraWatch::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDlgPrintParamCameraWatch::OnEraseBkgnd(CDC* pDC)
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


void CDlgPrintParamCameraWatch::OnClose()
{
	if (NULL != m_pDlgParamMain)
	{
		m_pDlgParamMain->OnUMCameraWatchShow();
	}
}


BOOL CDlgPrintParamCameraWatch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();

	m_strStorePath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1) + "Storage\\PrintSave\\";

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_PRINT_PA_CAMERA_PicShow_STATIC);
	CRect rcPicShow;
	pWnd->GetClientRect(&rcPicShow);
	m_imageoperate.Init(PRINT_HORIZONTAL, rcPicShow.Width(), rcPicShow.Height());     //��ʼ��,����ռ�
 
 	///SetTimer(1, 50, NULL);					 //��ʾ

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPrintParamCameraWatch::InitDlgCtrl()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_PRINT_PA_CAMERA_FileName_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("ȡ��");

	m_bmpBtn[1].SubclassDlgItem(IDC_PRINT_PA_CAMERA_Photo_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(15);
	m_bmpBtn[1].SetTitle("����");

	m_bmpBtn[2].SubclassDlgItem(IDC_PRINT_PA_CAMERA_Video_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(15);
	m_bmpBtn[2].SetTitle("��ʼ¼��");

	m_bmpBtn[3].SubclassDlgItem(IDC_PRINT_PA_CAMERA_TickMark_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[3].SetFont(15);
	m_bmpBtn[3].SetTitle("�̶���");

}

void CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraFilenameBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
}


void CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraPhotoBtn()
{
	//���ͼƬ�洢ȫ·��
	CTime time;
	CString strTime = _T("");
	time = CTime::GetCurrentTime();
	strTime = time.Format(_T("%Y%m%d_%H%M%S"));

	if (_T("") != m_strFileName)
	{
		m_strPhotoAllPath = m_strStorePath + _T("Photos\\") + m_strFileName + _T("_") + strTime + _T(".jpg");
	}
	else
	{
		m_strPhotoAllPath = m_strStorePath + _T("Photos\\") + strTime + _T(".jpg");
	}

	//����ͼƬ  
	if (NULL == m_pProCore)  return;	
	m_pProCore->GetCameraPrintHoriz()->StartGrab();
	HObject	*pHobj= NULL;
	pHobj = m_pProCore->GetCameraPrintHoriz()->GetSingleSave();
	IplImage* pIplImg = NULL;
	pIplImg = m_imageoperate.HObject2IplImage(*pHobj);
	if (NULL ==pIplImg)  return;
	cvSaveImage(m_strPhotoAllPath, pIplImg);
}


void CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraVideoBtn()
{
	//�����Ƶ�洢ȫ·��
	CTime time;
	CString strTime = _T("");
	time = CTime::GetCurrentTime();
	strTime = time.Format(_T("%Y%m%d_%H%M%S"));

	if (_T("") != m_strFileName)
	{
		m_strVideoAllPath = m_strStorePath + _T("Videos\\") + m_strFileName + _T("_") + strTime + _T(".avi");
	}
	else
	{
		m_strVideoAllPath = m_strStorePath + _T("Videos\\") + strTime + _T(".avi");
	}

	//������Ƶ
	if (!m_bWriteVideo)
	{
		m_bWriteVideo = true;
		m_bmpBtn[2].SetTitle("ֹͣ¼��");
	}
	else
	{
		m_bWriteVideo = false;
		m_videoWriter.release();
		m_bmpBtn[2].SetTitle("��ʼ¼��");
	}

	CRect rect;
	GetDlgItem(IDC_PRINT_PA_CAMERA_Video_BTN)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	RedrawWindow(&rect);
}


void CDlgPrintParamCameraWatch::OnBnClickedPrintPaCameraTickmarkBtn()
{
	if (!m_bDrawTickMark)
	{
		m_bDrawTickMark = true;
		m_staticPicShow.SetDrawTickMark(true);
	}
	else
	{
		m_bDrawTickMark = false;
		m_staticPicShow.SetDrawTickMark(false);
	}
}


void CDlgPrintParamCameraWatch::OnTimer(UINT_PTR nIDEvent)
{
 	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (1 == nIDEvent)
	{
		if (NULL == m_pProCore)  return;	
		m_pProCore->GetCameraPrintHoriz()->StartGrab();
		HObject	*pHobj= NULL;
		pHobj = m_pProCore->GetCameraPrintHoriz()->GetSingleShow();
		if (NULL == pHobj) return;
		IplImage* pIplImg = NULL;
		pIplImg = m_imageoperate.HObject2IplImage(*pHobj);
		if (NULL == pIplImg)  return;
		m_staticPicShow.SetShowImage(pIplImg);

		if (m_bWriteVideo)
		{
			//д��Ƶ
			if (!m_videoWriter.isOpened())
			{
				int iFrameRate = 25;
				Size frameSize;
				frameSize.width = pIplImg->width;
				frameSize.height = pIplImg->height;
				if (!m_videoWriter.open((LPCSTR)m_strVideoAllPath, CV_FOURCC('D','I','V','X'),iFrameRate,frameSize,false))
				{
					MessageBox("����Ƶʧ�ܣ�");
					return;
				}
			}
			Mat mat(pIplImg);   //ǳ����
			m_videoWriter.write(mat);
		}
	}

	CDialog::OnTimer(nIDEvent);
}


BOOL CDlgPrintParamCameraWatch::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
