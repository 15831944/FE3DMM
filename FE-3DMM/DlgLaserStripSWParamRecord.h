#pragma once
class CDlgLaserStripSubWin;


// CDlgLaserStripSWParamRecord �Ի���

class CDlgLaserStripSWParamRecord : public CDialog
{
	DECLARE_DYNAMIC(CDlgLaserStripSWParamRecord)

public:
	CDlgLaserStripSWParamRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLaserStripSWParamRecord();

// �Ի�������
	enum { IDD = IDD_DLG_LASERSTRIP_SUB_PARAMRECODE };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSelchangeLaserstripSubPRScanModeCombo();
	afx_msg void OnClickedLaserstripSubPrAddBtn();
	afx_msg void OnBnClickedLaserstripSubPrDeleteBtn();
	afx_msg void OnBnClickedLaserstripSubPrApplyBtn();

private:
	void Release();						//�ͷű�����������new���ڴ�
	void InitDlgCtrl();
	void InitGridListData();
	void InitGridListSingleParam();
	void InitGridListMultiParam();
	void ShowGridListSingleParam(CAdoRecordset* pRecordSet);
	void ShowGridListMultiParam(CAdoRecordset* pRecordSet);
	void AddGridListSingleParam();      //������ɨ����������GridList��
	void AddGridListMultiParam();		//������ɨ����������GridList��
	void ApplyGridListSingleParam();    //Ӧ��GridList������������ɨ������ṹ�壬����ʾ���������Static�ؼ�
	void ApplyGridListMultiParam();		//Ӧ��GridList������������ɨ������ṹ�壬����ʾ���������Static�ؼ�
	
private:
	CDlgLaserStripSubWin*	m_pDlgLaserStripSubWinMain;		//������SubWin
	CBmpBtn					m_bmpBtn[3];
	CGridCtrl				m_gridlistSingleParam;	
	CGridCtrl				m_gridlistMultiParam;	
	CString					m_strDatabasePath;
	CAdoDatabase			m_adoDatabase;
	CComboBox				m_comboboxScanMode;

};
