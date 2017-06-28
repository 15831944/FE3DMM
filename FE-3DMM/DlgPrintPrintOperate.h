#pragma once


// CDlgPrintPrintOperate �Ի���

class CDlgPrintPrintOperate : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrintPrintOperate)

public:
	CDlgPrintPrintOperate(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrintPrintOperate();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT_PRINTING };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedPrintPrLoadUGfileBtn();
	afx_msg void OnBnClickedPrintPrStartprintBtn();
	afx_msg void OnBnClickedPrintPrStopprintBtn();
	afx_msg void OnBnClickedPrintPrLinkprintBtn();
	afx_msg void OnBnClickedPrintPrPauseprintBtn();
	afx_msg void OnBnClickedPrintPrContinueprintBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedPrintPrCameraslopewatchRadio();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();																	//�ͷű�����������new���ڴ�
	void InitGridList();															//��ʼ���豸״̬�б�
	void UpdateGridList();													//ˢ���豸״̬�б�
	void InitProgress();
	void InitWindowHandle();												//��ʼ��Pic�ؼ���ʾ����

private:
	CXPGroupBox					m_GB1;
	CXPGroupBox					m_GB2;
	CXPGroupBox					m_GB3;
	CBmpBtn							m_bmpBtn[6];
	CGridCtrl							m_gridListState;
	CGradientProgressCtrl	m_progressPrint;
	CProcessCore					*m_pProCore;						//��������ָ��
	CString								m_strUgFileName;
	CString								m_strUgFilePath;
	double								m_dPrintSpeed;	
	HTuple								m_windowHandle_Pic;		//Pic�ؼ�������Halcon���ھ��
	Size										m_winSize_Pic;						//Pic���ڴ�С
};
