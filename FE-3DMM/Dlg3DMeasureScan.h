#pragma once


// CDlg3DMeasureScan �Ի���
class CDlg3DMeasureScan : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DMeasureScan)

public:
	CDlg3DMeasureScan(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg3DMeasureScan();

// �Ի�������
	enum { IDD = IDD_DLG_3DMEASURE_SCAN };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();


public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClicked3dmeasureSConnectBtn();
	afx_msg void OnBnClicked3dmeasureSStartBtn();
	afx_msg void OnBnClicked3dmeasureSStopBtn();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnTimer(UINT nIDEvent);
	void OnChangeLens();
	void OnChangeProbes();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();				//�ͷű�����������new���ڴ�

private:
	CXPGroupBox			m_GB1;
	CBmpBtn				m_bmpBtn[3];
	CProcessCore		*m_pProCore;	//��������ָ��

public:
	CComboBox	m_cbLens;
	CSliderCtrl	m_sliderPower;
	CComboBox	m_CBProbes;
	CComboBox	m_CBProbeType;
	CString	m_sDisMin;
	CString	m_sDisMax;
	CString	m_sDistance;
	CString	m_sSNR;
	CString m_Freq;
	CString	m_sQuality;
	CString	m_sSliderPower;
	unsigned int timer1,timer2;
	afx_msg void OnCbnSelchange3dmeasureSLensmaxdisCombox();
	afx_msg void OnEnChange3dmeasureSPointfreqEdit();
};
