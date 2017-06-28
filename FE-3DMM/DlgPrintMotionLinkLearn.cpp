// DlgPrintMotionLinkLearn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgPrintMotionLinkLearn.h"
#include "DlgPrintMotionControl.h"
#include "afxdialogex.h"


// CDlgPrintMotionLinkLearn �Ի���

IMPLEMENT_DYNAMIC(CDlgPrintMotionLinkLearn, CDialog)

CDlgPrintMotionLinkLearn::CDlgPrintMotionLinkLearn(CProcessCore* pProCore, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrintMotionLinkLearn::IDD, pParent)
{
	m_pProCore			= pProCore;
	m_pDlgMotionMain	= (CDlgPrintMotionControl*)pParent;
	m_fPrintLinesSpeed	= 0.0;

}

CDlgPrintMotionLinkLearn::~CDlgPrintMotionLinkLearn()
{
	Release();
}

void CDlgPrintMotionLinkLearn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRINT_M_L_Lines_LIST, m_listLines);
}


BEGIN_MESSAGE_MAP(CDlgPrintMotionLinkLearn, CDialog)
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_PRINT_M_L_BeginPoint_BTN, &CDlgPrintMotionLinkLearn::OnBnClickedPrintMLBeginpointBtn)
	ON_BN_CLICKED(IDC_PRINT_M_L_EndPoint_BTN, &CDlgPrintMotionLinkLearn::OnBnClickedPrintMLEndpointBtn)
	ON_BN_CLICKED(IDC_PRINT_M_L_LinkLine_BTN, &CDlgPrintMotionLinkLearn::OnBnClickedPrintMLLinklineBtn)
	ON_COMMAND(UM_IDM_MOTION_LINE_DELETE, OnUMLineDelete)
	ON_COMMAND(UM_IDM_MOTION_LINE_CLEAR, OnUMLineClear)
	ON_NOTIFY(NM_RCLICK, IDC_PRINT_M_L_Lines_LIST, &CDlgPrintMotionLinkLearn::OnRclickPrintMLLinesList)
END_MESSAGE_MAP()


// CDlgPrintMotionLinkLearn ��Ϣ�������


void CDlgPrintMotionLinkLearn::OnCancel()
{
	DestroyWindow();
}


void CDlgPrintMotionLinkLearn::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgPrintMotionLinkLearn::Cancel()
{
	OnCancel();
}


void CDlgPrintMotionLinkLearn::Release()
{

}


BOOL CDlgPrintMotionLinkLearn::OnEraseBkgnd(CDC* pDC)
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


HBRUSH CDlgPrintMotionLinkLearn::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDlgPrintMotionLinkLearn::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();

	GetDlgItem(IDC_PRINT_M_L_BeginPoint_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRINT_M_L_EndPoint_EDIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRINT_M_L_LinesNum_EDIT)->EnableWindow(FALSE);

	//��ʼ������list
	CRect rect;
	m_listLines.GetClientRect(&rect);
	m_listLines.SetExtendedStyle(m_listLines.GetExtendedStyle()|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_listLines.InsertColumn(1, _T("���"), LVCFMT_CENTER, rect.Width()/2, 0);
	m_listLines.InsertColumn(2, _T("�յ�"), LVCFMT_CENTER, rect.Width()/2, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPrintMotionLinkLearn::InitDlgCtrl()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_PRINT_M_L_BeginPoint_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("���");

	m_bmpBtn[1].SubclassDlgItem(IDC_PRINT_M_L_EndPoint_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(15);
	m_bmpBtn[1].SetTitle("�յ�");

	m_bmpBtn[2].SubclassDlgItem(IDC_PRINT_M_L_LinkLine_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(15);
	m_bmpBtn[2].SetTitle("����");
}


void CDlgPrintMotionLinkLearn::OnClose()
{
	if (NULL != m_pDlgMotionMain)
	{
		m_pDlgMotionMain->OnBnClickedPrintMLinklearnBtn();
	}
}


BOOL CDlgPrintMotionLinkLearn::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
 	{
		CString strTemp = _T("");
		float fEditValue = 0.0;

		if (GetFocus() == GetDlgItem(IDC_PRINT_M_L_PrintLineSpeed_EDIT))
		{
			GetDlgItem(IDC_PRINT_M_L_PrintLineSpeed_EDIT)->GetWindowText(strTemp);
			fEditValue = _ttof(strTemp);
			if(fEditValue < 0.0)
				fEditValue = 0.0;
			else if (fEditValue > 1000.0)
				fEditValue = 1000.0;
			strTemp.Format(_T("%.2f"), fEditValue);
			GetDlgItem(IDC_PRINT_M_L_PrintLineSpeed_EDIT)->SetWindowText(strTemp);
		
			m_fPrintLinesSpeed = fEditValue;		
		}

		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CDlgPrintMotionLinkLearn::OnBnClickedPrintMLBeginpointBtn()
{
// 	m_straightline.beginpoint.fPosX = m_pProCore->GetMotorX()->GetMotorPostion();
// 	m_straightline.beginpoint.fPosY = m_pProCore->GetMotorY()->GetMotorPostion();
// 	m_straightline.angle.fAngleA = m_pProCore->GetMotorA()->GetMotorPostion();
// 	m_straightline.angle.fAngleC = m_pProCore->GetMotorC()->GetMotorPostion();

	CString strTemp;
	strTemp.Format(_T("(%.2f,%.2f)"), m_straightline.beginpoint.fPosX, m_straightline.beginpoint.fPosY);
	GetDlgItem(IDC_PRINT_M_L_BeginPoint_EDIT)->SetWindowText(strTemp);
}


void CDlgPrintMotionLinkLearn::OnBnClickedPrintMLEndpointBtn()
{
// 	m_straightline.endpoint.fPosX = m_pProCore->GetMotorX()->GetMotorPostion();
// 	m_straightline.endpoint.fPosY = m_pProCore->GetMotorY()->GetMotorPostion();

	CString strTemp;
	strTemp.Format(_T("(%.2f,%.2f)"), m_straightline.endpoint.fPosX, m_straightline.endpoint.fPosY);
	GetDlgItem(IDC_PRINT_M_L_EndPoint_EDIT)->SetWindowText(strTemp);
}


void CDlgPrintMotionLinkLearn::OnBnClickedPrintMLLinklineBtn()
{
 	m_vecLine.push_back(m_straightline);

	CString strBeginPt, strEndPt;
	strBeginPt.Format(_T("(%.2f,%.2f)"), m_straightline.beginpoint.fPosX, m_straightline.beginpoint.fPosY);
	strEndPt.Format(_T("(%.2f,%.2f)"), m_straightline.endpoint.fPosX, m_straightline.endpoint.fPosY);
		
	int nRowCnt = m_listLines.GetItemCount();    
	m_listLines.InsertItem(nRowCnt, strBeginPt); 
	m_listLines.SetItemText(nRowCnt, 1, strEndPt);
	
	//����Edit
	GetDlgItem(IDC_PRINT_M_L_BeginPoint_EDIT)->SetWindowText(strBeginPt);
	GetDlgItem(IDC_PRINT_M_L_EndPoint_EDIT)->SetWindowText(strEndPt);
	UpdateLineNum();
}


void CDlgPrintMotionLinkLearn::OnUMLineDelete()
{
	int nSelectRow = m_listLines.GetSelectionMark();
	if (nSelectRow >= 0)
	{
		if (nSelectRow < m_vecLine.size())
		{
			m_vecLine.erase(m_vecLine.begin()+nSelectRow);
		}	
		m_listLines.DeleteItem(nSelectRow);		
	}

	UpdateLineNum();
}


void CDlgPrintMotionLinkLearn::OnUMLineClear()
{
	m_vecLine.clear(); 
	m_listLines.DeleteAllItems();
	UpdateLineNum();
}


void CDlgPrintMotionLinkLearn::UpdateLineNum()
{
	int nItemCount = m_listLines.GetItemCount();  //��ȡ����
	CString strTemp;
	strTemp.Format("%d", nItemCount);
	SetDlgItemText(IDC_PRINT_M_L_LinesNum_EDIT, strTemp);
}


void CDlgPrintMotionLinkLearn::OnRclickPrintMLLinesList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (pNMItemActivate->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));

		//��̬���������˵�
		CMenu menu;
		menu.CreatePopupMenu();
		menu.AppendMenuA(MF_BYCOMMAND|MF_STRING, UM_IDM_MOTION_LINE_DELETE, _T("ɾ��"));
		menu.AppendMenuA(MF_BYCOMMAND|MF_STRING, UM_IDM_MOTION_LINE_CLEAR, _T("���"));

		menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	}

	*pResult = 0;
}
