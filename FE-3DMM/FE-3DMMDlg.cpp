
// FE-3DMMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "FE-3DMMDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
	
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFE3DMMDlg �Ի���


CFE3DMMDlg::CFE3DMMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFE3DMMDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pDlgLaserStrip	= NULL;
	m_pDlg3DMeasure	= NULL;
	m_pDlgTransfer		= NULL;
	m_pDlgPrint				= NULL;

	m_pProCore				= NULL;
	m_pProCore				= new CProcessCore();
	ASSERT(m_pProCore);

	m_strErrorStatus		= _T("�豸����!");
}

void CFE3DMMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIN_ERROR_STATUS_EDIT, m_editErrorStatus);
	DDX_Text(pDX, IDC_MAIN_ERROR_STATUS_EDIT, m_strErrorStatus);
}

BEGIN_MESSAGE_MAP(CFE3DMMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_MAIN_3DMEASURE_BTN, &CFE3DMMDlg::OnBnClickedMain3dmeasureBtn)
	ON_BN_CLICKED(IDC_MAIN_UG_BTN, &CFE3DMMDlg::OnBnClickedMainUgBtn)
	ON_BN_CLICKED(IDC_MAIN_LASERSTRIP_BTN, &CFE3DMMDlg::OnBnClickedMainLaserstripBtn)
	ON_BN_CLICKED(IDC_MAIN_TRANSFER_BTN, &CFE3DMMDlg::OnBnClickedMainTransferBtn)
	ON_BN_CLICKED(IDC_MAIN_PRINT_BTN, &CFE3DMMDlg::OnBnClickedMainPrintBtn)
	ON_BN_CLICKED(IDC_MAIN_EXIT_BTN, &CFE3DMMDlg::OnBnClickedMainExitBtn)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFE3DMMDlg ��Ϣ�������

BOOL CFE3DMMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitButton();
	InitErrorStatusEdit();
	CreateSubDialog();
	ShowSubDialog(SW_SHOW);

	//���������ʼ��
	m_pProCore->SetMainDlgPointer(this);  // �����Ի���ָ�봫�ݸ�CProessCore��
	m_pProCore->Init();
	
	SetTimer(TIMER_ERROR_STATUS, 200, NULL);     	//�������ϱ�����ʱ��
	SetTimer(TIMER_IMAGE_SHOW, 50, NULL);			//����ͼ����ʾ��ʱ��

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFE3DMMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFE3DMMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFE3DMMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CFE3DMMDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC) 
	{ 
		switch(pWnd->GetDlgCtrlID()) 
		{
		case IDC_MAIN_SUBWIN_STATIC:
			pDC->SetBkMode(TRANSPARENT); 
			pDC->SetTextColor(RGB(0,0,0)); 
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
		default: 
			break; 
		} 
	}
	return hbr;
}

BOOL CFE3DMMDlg::OnEraseBkgnd(CDC* pDC)
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

void CFE3DMMDlg::InitButton()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_MAIN_EMPTY_BTN, this);
	m_bmpBtn[0].SetFont(18);
	m_bmpBtn[0].SetBmp(IDB_BITMAP_BTNEMPTY,IDB_BITMAP_BTNEMPTY);
	m_bmpBtn[0].SetTitle("");

	m_bmpBtn[1].SubclassDlgItem(IDC_MAIN_3DMEASURE_BTN, this);
	m_bmpBtn[1].SetFont(18);
	m_bmpBtn[1].SetBmp(IDB_BITMAP_MAINBTN,IDB_BITMAP_MAINBTNCLK);
	m_bmpBtn[1].SetTitle("3D����");

	m_bmpBtn[2].SubclassDlgItem(IDC_MAIN_UG_BTN, this);
	m_bmpBtn[2].SetFont(18);
	m_bmpBtn[2].SetBmp(IDB_BITMAP_MAINBTN,IDB_BITMAP_MAINBTNCLK);
	m_bmpBtn[2].SetTitle("UG");

	m_bmpBtn[3].SubclassDlgItem(IDC_MAIN_LASERSTRIP_BTN, this);
	m_bmpBtn[3].SetFont(18);
	m_bmpBtn[3].SetBmp(IDB_BITMAP_MAINBTN,IDB_BITMAP_MAINBTNCLK);
	m_bmpBtn[3].SetTitle("�������");

	m_bmpBtn[4].SubclassDlgItem(IDC_MAIN_TRANSFER_BTN, this);
	m_bmpBtn[4].SetFont(18);
	m_bmpBtn[4].SetBmp(IDB_BITMAP_MAINBTN,IDB_BITMAP_MAINBTNCLK);
	m_bmpBtn[4].SetTitle("����תӡ");

	m_bmpBtn[5].SubclassDlgItem(IDC_MAIN_PRINT_BTN, this);
	m_bmpBtn[5].SetFont(18);
	m_bmpBtn[5].SetBmp(IDB_BITMAP_MAINBTN,IDB_BITMAP_MAINBTNCLK);
	m_bmpBtn[5].SetTitle("���δ�ӡ");

	m_bmpBtn[6].SubclassDlgItem(IDC_MAIN_EXIT_BTN, this);
	m_bmpBtn[6].SetFont(18);
	m_bmpBtn[6].SetBmp(IDB_BITMAP_MAINBTN,IDB_BITMAP_MAINBTNCLK);
	m_bmpBtn[6].SetTitle("�˳�");

	m_bmpBtn[1].EnableWindow(0);
}

void CFE3DMMDlg::CreateSubDialog()
{
	m_pDlg3DMeasure = new CDlg3DMeasure(m_pProCore);
	ASSERT(m_pDlg3DMeasure);
	m_pDlg3DMeasure->Create(IDD_DLG_3DMEASURE, GetDlgItem(IDC_MAIN_SUBWIN_STATIC));

	m_pDlgLaserStrip = new CDlgLaserStrip(m_pProCore);
	ASSERT(m_pDlgLaserStrip);
	m_pDlgLaserStrip->Create(IDD_DLG_LASERSTRIP, GetDlgItem(IDC_MAIN_SUBWIN_STATIC));

	m_pDlgTransfer = new CDlgTransfer(m_pProCore);
	ASSERT(m_pDlgTransfer);
	m_pDlgTransfer->Create(IDD_DLG_TRANSFER, GetDlgItem(IDC_MAIN_SUBWIN_STATIC));

	m_pDlgPrint = new CDlgPrint(m_pProCore);
	ASSERT(m_pDlgPrint);
	m_pDlgPrint->Create(IDD_DLG_PRINT, GetDlgItem(IDC_MAIN_SUBWIN_STATIC));
}

void CFE3DMMDlg::ShowSubDialog(INT measure, INT laserstrip, INT tranfer, INT print)
{
	m_pDlg3DMeasure->ShowWindow(measure);
	m_pDlgLaserStrip->ShowWindow(laserstrip);
	m_pDlgTransfer->ShowWindow(tranfer);
	m_pDlgPrint->ShowWindow(print);
}


void CFE3DMMDlg::OnBnClickedMain3dmeasureBtn()
{
	GetDlgItem(IDC_MAIN_3DMEASURE_BTN)->EnableWindow(0);
	GetDlgItem(IDC_MAIN_UG_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_LASERSTRIP_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_TRANSFER_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_PRINT_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_EXIT_BTN)->EnableWindow(1);
	ShowSubDialog(SW_SHOW);
}


void CFE3DMMDlg::OnBnClickedMainUgBtn()
{
	GetDlgItem(IDC_MAIN_3DMEASURE_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_UG_BTN)->EnableWindow(0);
	GetDlgItem(IDC_MAIN_LASERSTRIP_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_TRANSFER_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_PRINT_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_EXIT_BTN)->EnableWindow(1);
	ShowUgWnd();
}


void CFE3DMMDlg::OnBnClickedMainLaserstripBtn()
{
	GetDlgItem(IDC_MAIN_3DMEASURE_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_UG_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_LASERSTRIP_BTN)->EnableWindow(0);
	GetDlgItem(IDC_MAIN_TRANSFER_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_PRINT_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_EXIT_BTN)->EnableWindow(1);
	ShowSubDialog(SW_HIDE, SW_SHOW);
}


void CFE3DMMDlg::OnBnClickedMainTransferBtn()
{
	GetDlgItem(IDC_MAIN_3DMEASURE_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_UG_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_LASERSTRIP_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_TRANSFER_BTN)->EnableWindow(0);
	GetDlgItem(IDC_MAIN_PRINT_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_EXIT_BTN)->EnableWindow(1);
	ShowSubDialog(SW_HIDE, SW_HIDE, SW_SHOW);
}


void CFE3DMMDlg::OnBnClickedMainPrintBtn()
{
	GetDlgItem(IDC_MAIN_3DMEASURE_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_UG_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_LASERSTRIP_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_TRANSFER_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_PRINT_BTN)->EnableWindow(0);
	GetDlgItem(IDC_MAIN_EXIT_BTN)->EnableWindow(1);
	ShowSubDialog(SW_HIDE, SW_HIDE, SW_HIDE, SW_SHOW);
}


void CFE3DMMDlg::OnBnClickedMainExitBtn()
{
	GetDlgItem(IDC_MAIN_3DMEASURE_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_UG_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_LASERSTRIP_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_TRANSFER_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_PRINT_BTN)->EnableWindow(1);
	GetDlgItem(IDC_MAIN_EXIT_BTN)->EnableWindow(0);
	OnCancel();
}


void CFE3DMMDlg::OnCancel()
{
	//�ȹرն�ʱ��
	KillTimer(TIMER_ERROR_STATUS); 
	KillTimer(TIMER_IMAGE_SHOW);

	CloseUgWnd();
	m_pDlg3DMeasure->Cancel();
	m_pDlgLaserStrip->Cancel();
	m_pDlgTransfer->Cancel();
	m_pDlgPrint->Cancel();
	Release();   //�ͷŲ�����

	CDialogEx::OnCancel();
}


void CFE3DMMDlg::Release()
{
	if (NULL != m_pProCore)
	{
		delete m_pProCore;
		m_pProCore = NULL;
	}
}


BOOL CFE3DMMDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFE3DMMDlg::ShowUgWnd()
{
// 	CWnd* pWnd = NULL;
// 	pWnd = CWnd::FindWindow(NULL, _T("QQ"));
// 	if (NULL != pWnd)
// 	{
// 		pWnd->ShowWindow(SW_SHOWNORMAL);
// 	}
// 	else
// 	{
// 		AfxGetMainWnd()->BeginWaitCursor();
// 		CString strExePath = "D:\\Program Files (x86)\\Tencent\\QQ\\Bin\\";
// 		CString strExeName = "D:\\Program Files (x86)\\Tencent\\QQ\\Bin\\QQScLauncher.exe";
// 		
// 		::ShellExecute(NULL, _T("OPEN"), strExeName, NULL, strExePath, SW_SHOW);
// 
// 		Sleep(1000);
// 		AfxGetMainWnd()->EndWaitCursor();
// 	}
}


void CFE3DMMDlg::CloseUgWnd()
{
// 	HWND hWnd = ::FindWindow(NULL, _T("QQ"));
// 	if (NULL != hWnd)
// 	{
// 		::SendMessage(hWnd, WM_CLOSE, 0, 0);
// 	}
}


void CFE3DMMDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case TIMER_ERROR_STATUS:
		RefreshErrorStatus();
		break;

	case TIMER_IMAGE_SHOW:
		RefreshImageShow();
		break;

	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CFE3DMMDlg::InitErrorStatusEdit()
{
	//��ʼ��������ʾEdit
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 18;
	font.CreateFontIndirect(&lf);
	m_editErrorStatus.SetFont(&font);
	m_editErrorStatus.SetBackColor(RGB(255,255,255));
	m_editErrorStatus.SetTextColor(RGB(0,0,0));
}


void CFE3DMMDlg::RefreshErrorStatus()
{
	UpdateData(TRUE);

// 	if (1 == m_pProCore->m_P200.GetParamValue())
// 	{
// 		m_editErrorStatus.SetBackColor(RGB(255,0,0));
// 		m_editErrorStatus.SetTextColor(RGB(255,255,255));
// 		m_strErrorStatus = "��ͣ������!";
// 
// 		m_pProCore->m_P3006.SetParamValue(1);
// 	}
// 	else
// 	{
// 		if (1 == m_pProCore->m_P2001.GetParamValue())
// 		{
// 			m_editErrorStatus.SetBackColor(RGB(255,0,0));
// 			m_editErrorStatus.SetTextColor(RGB(255,255,255));
// 			m_strErrorStatus = "�豸���ϣ�";
// 
// 			if (1 == m_pProCore->m_M130)
// 			{
// 				m_strErrorStatus += "X��������λ";
// 			}
// 			if (1 == m_pProCore->m_M131)
// 			{
// 				m_strErrorStatus += "X��������λ";
// 			}
// 			if (1 == m_pProCore->m_M132)
// 			{
// 				m_strErrorStatus += "Y��������λ";
// 			}
// 			if (1 == m_pProCore->m_M133)
// 			{
// 				m_strErrorStatus += "Y��������λ";
// 			}
// 			if (1 == m_pProCore->m_M134)
// 			{
// 				m_strErrorStatus += "Z��������λ";
// 			}
// 			if (1 == m_pProCore->m_M135)
// 			{
// 				m_strErrorStatus += "Z��������λ";
// 			}
// 			if (1 == m_pProCore->m_M136)
// 			{
// 				m_strErrorStatus += "A��������λ";
// 			}
// 			if (1 == m_pProCore->m_M137)
// 			{
// 				m_strErrorStatus += "A��������λ";
// 			}
// 			if (1 == m_pProCore->m_M138)
// 			{
// 				m_strErrorStatus += "C��������λ";
// 			}
// 			if (1 == m_pProCore->m_M139)
// 			{
// 				m_strErrorStatus += "C��������λ";
// 			}
// 
// 			m_pProCore->m_P3006.SetParamValue(1);
// 		}
// 		else
// 		{
// 			m_editErrorStatus.SetBackColor(RGB(255,255,255));
// 			m_editErrorStatus.SetTextColor(RGB(0,0,0));
// 			m_strErrorStatus = "�豸����!";
// 
// 			m_pProCore->m_P3006.SetParamValue(0);
// 			m_pProCore->m_P3007.SetParamValue(0);
// 			m_pProCore->m_P3008.SetParamValue(1);
// 		}
// 	}

	UpdateData(FALSE);
}


void CFE3DMMDlg::RefreshImageShow()
{
	HObject	*pImg = NULL;
	SHOWINFO showinfo = m_pProCore->GetShowInfo();
	
	switch(showinfo.cameratype)
	{
	case LASER_VIEW:
		pImg = m_pProCore->GetCameraLaserView()->GetSingleShow();
		break;

	case TRANS_UP:
		pImg = m_pProCore->GetCameraTransUp()->GetSingleShow();
		break;

	case TRANS_DOWN:
		pImg = m_pProCore->GetCameraTransDown()->GetSingleShow();
		break;
		
	case PRINT_LOCAL:
		pImg = m_pProCore->GetCameraPrintLoc()->GetSingleShow();
		break;

	case PRINT_HORIZONTAL:
		pImg = m_pProCore->GetCameraPrintHoriz()->GetSingleShow();
		break;

	case PRINT_ASKANT:
		pImg = m_pProCore->GetCameraPrintAskant()->GetSingleShow();
		break;

	default:
		break;
	}

	if (NULL != pImg && pImg->IsInitialized())
	{
		DispImage(*pImg, showinfo.windowHandle);

		int nWinWid = showinfo.windowSize.width;
		int nWinHei = showinfo.windowSize.height;
		int nMax = max(nWinWid, nWinHei);
		DispCross(showinfo.windowHandle, nWinHei/2, nWinWid/2, nMax, 0);
		DispArrow(showinfo.windowHandle, nWinHei-10, 10, nWinHei-35, 10, 1);
		DispArrow(showinfo.windowHandle, nWinHei-10, 10, nWinHei-10, 35, 1);
	}
}

