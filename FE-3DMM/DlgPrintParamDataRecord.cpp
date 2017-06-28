// DlgPrintParamData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FE-3DMM.h"
#include "DlgPrintParamDataRecord.h"
#include "afxdialogex.h"
#include "DlgPrintParamAdjust.h"


// CDlgPrintParamDataRecord �Ի���

IMPLEMENT_DYNAMIC(CDlgPrintParamDataRecord, CDialog)

CDlgPrintParamDataRecord::CDlgPrintParamDataRecord(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPrintParamDataRecord::IDD, pParent)
{
	m_pDlgParamMain = (CDlgPrintParamAdjust*)pParent;
	m_strDatabasePath = _T("");
}

CDlgPrintParamDataRecord::~CDlgPrintParamDataRecord()
{
	Release();
}

void CDlgPrintParamDataRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPrintParamDataRecord, CDialog)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(IDC_PRINT_PA_DATA_Apply_BTN, &CDlgPrintParamDataRecord::OnBnClickedPrintPaDataApplyBtn)
	ON_BN_CLICKED(IDC_PRINT_PA_DATA_Add_BTN, &CDlgPrintParamDataRecord::OnBnClickedPrintPaDataAddBtn)
	ON_BN_CLICKED(IDC_PRINT_PA_DATA_Modify_BTN, &CDlgPrintParamDataRecord::OnBnClickedPrintPaDataModifyBtn)
	ON_BN_CLICKED(IDC_PRINT_PA_DATA_Delete_BTN, &CDlgPrintParamDataRecord::OnBnClickedPrintPaDataDeleteBtn)
END_MESSAGE_MAP()


// CDlgPrintParamDataRecord ��Ϣ�������


void CDlgPrintParamDataRecord::OnCancel()
{
	DestroyWindow();
}


void CDlgPrintParamDataRecord::PostNcDestroy()
{
	CDialog::PostNcDestroy();
	delete this;
}


void CDlgPrintParamDataRecord::Cancel()
{
	OnCancel();
}


void CDlgPrintParamDataRecord::Release()
{

}


HBRUSH CDlgPrintParamDataRecord::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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


BOOL CDlgPrintParamDataRecord::OnEraseBkgnd(CDC* pDC)
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


BOOL CDlgPrintParamDataRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	InitDlgCtrl();
	InitGridListData();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgPrintParamDataRecord::InitDlgCtrl()
{
	m_bmpBtn[0].SubclassDlgItem(IDC_PRINT_PA_DATA_Apply_BTN, this);
	m_bmpBtn[0].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[0].SetFont(15);
	m_bmpBtn[0].SetTitle("Ӧ��");

	m_bmpBtn[1].SubclassDlgItem(IDC_PRINT_PA_DATA_Add_BTN, this);
	m_bmpBtn[1].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[1].SetFont(15);
	m_bmpBtn[1].SetTitle("����");

	m_bmpBtn[2].SubclassDlgItem(IDC_PRINT_PA_DATA_Modify_BTN, this);
	m_bmpBtn[2].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[2].SetFont(15);
	m_bmpBtn[2].SetTitle("�޸�");

	m_bmpBtn[3].SubclassDlgItem(IDC_PRINT_PA_DATA_Delete_BTN, this);
	m_bmpBtn[3].LoadBitmaps(IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK,IDB_BITMAP_BTN,IDB_BITMAP_BTNCLK);
	m_bmpBtn[3].SetFont(15);
	m_bmpBtn[3].SetTitle("ɾ��");
}


void CDlgPrintParamDataRecord::OnClose()
{
	if (NULL != m_pDlgParamMain)
	{
		m_pDlgParamMain->OnBnClickedPrintPaDataRecordBtn();
	}	
}


void CDlgPrintParamDataRecord::InitGridListData()
{
	m_strDatabasePath =  m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1) + _T("Storage\\Database.mdb");
	if (!m_adoDatabase.OpenMDB(m_strDatabasePath))
	{
		MessageBox("�������ݿ�ʧ�ܣ�");
		return;
	}

	CAdoRecordset recordset;
	if (!recordset.OpenTable("PrintParamTable", &m_adoDatabase))
	{
		MessageBox("�򿪲������ݱ�ʧ�ܣ�");
		return;
	}

	CRect rcGrid;
	GetDlgItem(IDC_PRINT_PA_DATA_LIST)->GetClientRect(&rcGrid);
	m_gridlistData.Create(rcGrid, GetDlgItem(IDC_PRINT_PA_DATA_LIST), IDC_PRINT_PA_DATA_LIST);

	//��ʼ���б����
	int nFixedColum = 1;
	int nFixedRow = 1;
	int nRowCount = 1;
	int nColumCount = recordset.GetFieldCount();

	m_gridlistData.SetAutoSizeStyle();
	m_gridlistData.SetEditable(TRUE);
	m_gridlistData.SetFixedColumnSelection(FALSE);
	m_gridlistData.ExpandColumnsToFit(TRUE);

	m_gridlistData.SetRowCount(nRowCount);
	m_gridlistData.SetColumnCount(nColumCount);
	m_gridlistData.SetFixedColumnCount(nFixedColum);
	m_gridlistData.SetFixedRowCount(nFixedRow);

	CString strItemText = _T("");
	GV_ITEM item;
	item.crBkClr = RGB(200, 255, 255);
	item.nFormat = DT_CENTER|DT_WORDBREAK;
	item.mask = GVIF_TEXT|GVIF_BKCLR|GVIF_FORMAT;
	item.row = 0;

	for (int iColIndex=0; iColIndex<nColumCount; iColIndex++)
	{
		recordset.GetFieldName(iColIndex, strItemText);
		item.col = iColIndex;
		item.strText = strItemText;
		m_gridlistData.SetItem(&item);

		if (0 == iColIndex)
			m_gridlistData.SetColumnWidth(iColIndex, 132);
		else
			m_gridlistData.SetColumnWidth(iColIndex, 80);	
	}

	ShowGridListData(&recordset);

	recordset.CloseTable();
}


void CDlgPrintParamDataRecord::ShowGridListData(CAdoRecordset* pRecordSet)
{
	if (NULL == pRecordSet || (pRecordSet->IsBOF() && pRecordSet->IsEOF()))
	{
		return;
	}
	else
	{
		pRecordSet->MoveFirst();
	}

	//����б�������
	m_gridlistData.DeleteNonFixedRows();

	int row = 1;
	GV_ITEM item;
	item.crBkClr = RGB(255, 255, 255);
	item.nFormat = DT_CENTER|DT_VCENTER;
	item.mask = GVIF_TEXT|GVIF_BKCLR|GVIF_FORMAT|GVIF_STATE;

	CString strValue = "";
	int iColCount = pRecordSet->GetFieldCount();
	while (!pRecordSet->IsEOF())
	{
		m_gridlistData.InsertRow(NULL); //��ĩβ����һ��

		for (int iColIndex=0; iColIndex<iColCount; iColIndex++)
		{
			if (row%2 == 0)
			{
				item.crBkClr = RGB(255, 255, 255);
			}
			else
			{
				item.crBkClr = RGB(210, 210, 210);
			}

			if (iColIndex==1 || iColIndex==2)
			{
				item.nState = GVIS_MODIFIED;
			}
			else
			{
				item.nState = GVIS_READONLY;
			}

			item.row = row;
			item.col = iColIndex;
			strValue = pRecordSet->GetFieldValue(iColIndex);
			item.strText = strValue;
			m_gridlistData.SetItem(&item);
		}	

		++row;
		pRecordSet->MoveNext();
	}

	m_gridlistData.UpdateData(FALSE);
	m_gridlistData.Refresh();
}


void CDlgPrintParamDataRecord::OnBnClickedPrintPaDataApplyBtn()
{
	int nRowIndex = m_gridlistData.GetFocusCell().row;
	int nColCount = m_gridlistData.GetColumnCount();

	if (nRowIndex <= 0) return;

	CString strItemText = _T("");
	for (int nColIndex=3; nColIndex<nColCount; nColIndex++)
	{
		strItemText = m_gridlistData.GetItemText(nRowIndex, nColIndex);
		switch(nColIndex)
		{
		case 3: //��ѹģʽ
			if (strItemText == _T("����"))
			{
				m_PrintParamTable.enumVolMode = AcMode;
			}
			else if (strItemText == _T("ֱ��"))
			{
				m_PrintParamTable.enumVolMode = DcMode;
			}
			break;

		case 4: //ֱ��ƫ��
			m_PrintParamTable.dDcOffset = _ttof(strItemText);
			break;

		case 5: //����ƫ��
			m_PrintParamTable.dAcOffset = _ttof(strItemText);
			break;
			
		case 6: //����Ƶ��
			m_PrintParamTable.dAcFreq = _ttof(strItemText);
			break;
			
		case 7: //������ֵ
			m_PrintParamTable.dAcAmplitude = _ttof(strItemText);
			break;
	
		case 8: //����ռ�ձ�
			m_PrintParamTable.dAcRatio = _ttof(strItemText);
			break;
	
		case 9: //������ѹֵ
			m_PrintParamTable.dAuxiAirPress = _ttof(strItemText);
			break;
	
		case 10: //�������ڷ�ʽ
			if (strItemText == _T("������"))
			{
				m_PrintParamTable.enumFlowAdjPattern = PumpPattern;
			}
			else if (strItemText == _T("������ѹ"))
			{
				m_PrintParamTable.enumFlowAdjPattern = FeedAirPressPattern;
			}
			break;

		case 11: //����������
			m_PrintParamTable.dPumpFlowRate = _ttof(strItemText);
			break;

		case 12: //������ѹ����
			m_PrintParamTable.dFeedAirFlowRate = _ttof(strItemText);
			break;

		default:
			break;
		}
	}

	if (NULL != m_pDlgParamMain)
	{
		m_pDlgParamMain->ApplyPrintParamTable();
		m_pDlgParamMain->UpdateData(FALSE);
	}	
}


void CDlgPrintParamDataRecord::OnBnClickedPrintPaDataAddBtn()
{
	if (NULL == m_pDlgParamMain) return;

	m_pDlgParamMain->AddPrintParamTable();   //��Ӵ�ӡ����

	CAdoRecordset recordset;
	if (!recordset.OpenTable("PrintParamTable", &m_adoDatabase))
	{
		MessageBox("�򿪲������ݱ�ʧ�ܣ�");
		return;
	}

	recordset.AddNew();    //����һ��

	CTime time;
	CString strTime = _T("");
	time = CTime::GetCurrentTime();
	strTime = time.Format(_T("%Y/%m/%d-%H/%M/%S"));

	recordset.SetFieldValue(0, strTime);
	recordset.SetFieldValue(1, "");
	recordset.SetFieldValue(2, "");
	CString strTemp = _T("");
	if (m_PrintParamTable.enumVolMode == AcMode)
	{
		strTemp = _T("����");
		recordset.SetFieldValue(3, strTemp);
		recordset.SetFieldValue(4, "");
		strTemp.Format(_T("%.2f"), m_PrintParamTable.dAcOffset);
		recordset.SetFieldValue(5, strTemp);
		strTemp.Format(_T("%.2f"), m_PrintParamTable.dAcFreq);
		recordset.SetFieldValue(6, strTemp);
		strTemp.Format(_T("%.2f"), m_PrintParamTable.dAcAmplitude);
		recordset.SetFieldValue(7, strTemp);
		strTemp.Format(_T("%.2f"), m_PrintParamTable.dAcRatio);
		recordset.SetFieldValue(8, strTemp);	
	}
	if (m_PrintParamTable.enumVolMode == DcMode)
	{
		strTemp = _T("ֱ��");
		recordset.SetFieldValue(3, strTemp);
		strTemp.Format(_T("%.2f"), m_PrintParamTable.dDcOffset);
		recordset.SetFieldValue(4, strTemp);
		recordset.SetFieldValue(5, "");
		recordset.SetFieldValue(6, "");
		recordset.SetFieldValue(7, "");
		recordset.SetFieldValue(8, "");	
	}
	
	strTemp.Format(_T("%.2f"), m_PrintParamTable.dAuxiAirPress);
	recordset.SetFieldValue(9, strTemp);

	if (m_PrintParamTable.enumFlowAdjPattern == PumpPattern)
	{
		strTemp = _T("������");
		recordset.SetFieldValue(10, strTemp);
		strTemp.Format(_T("%.4f"), m_PrintParamTable.dPumpFlowRate);
		recordset.SetFieldValue(11, strTemp);
		recordset.SetFieldValue(12, "");
	}
	else if (m_PrintParamTable.enumFlowAdjPattern == FeedAirPressPattern)
	{
		strTemp = _T("������ѹ");
		recordset.SetFieldValue(10, strTemp);	
		recordset.SetFieldValue(11, "");
		strTemp.Format(_T("%.4f"), m_PrintParamTable.dFeedAirFlowRate);
		recordset.SetFieldValue(12, strTemp);
	}
	
	recordset.Update();

	ShowGridListData(&recordset);
	recordset.CloseTable();
}


void CDlgPrintParamDataRecord::OnBnClickedPrintPaDataModifyBtn()
{
	CAdoRecordset recordset;
	if (!recordset.OpenTable("PrintParamTable", &m_adoDatabase))
	{
		MessageBox("�򿪲������ݱ�ʧ�ܣ�");
		return;
	}

	int nRowIndex = m_gridlistData.GetFocusCell().row;
	int nColCount = m_gridlistData.GetColumnCount();

	if (nRowIndex>0)
	{
		recordset.Move(nRowIndex-1);     //�б��е�1�ж�Ӧ���ݿ��е�0��
		CString strItemText = _T("");
		for (int j=0; j<nColCount; j++)
		{
			strItemText = m_gridlistData.GetItemText(nRowIndex, j);
			recordset.SetFieldValue(j, strItemText);
			recordset.Update();
		}
		ShowGridListData(&recordset);
	}
	recordset.CloseTable();
}


void CDlgPrintParamDataRecord::OnBnClickedPrintPaDataDeleteBtn()
{
	CAdoRecordset recordset;
	if (!recordset.OpenTable("PrintParamTable", &m_adoDatabase))
	{
		MessageBox("�򿪲������ݱ�ʧ�ܣ�");
		return;
	}

	int nRowIndex = m_gridlistData.GetFocusCell().row;
	if (nRowIndex > 0)
	{
		recordset.Move(nRowIndex-1);   //�б��е�1�ж�Ӧ���ݿ��е�0��
		recordset.Delete();
		recordset.Update();
		ShowGridListData(&recordset);
	}	
	recordset.CloseTable();
}


BOOL CDlgPrintParamDataRecord::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYDOWN == pMsg->message && VK_RETURN == pMsg->wParam)
	{
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
