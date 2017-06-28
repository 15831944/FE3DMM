#pragma once
class CDlgPrintParamAdjust;


// CDlgPrintParamDataRecord �Ի���
enum VoltageMode{DcMode = 0, AcMode};							//��ѹģʽ
enum FlowAdjustPattern{PumpPattern = 0, FeedAirPressPattern};	//�������ڷ�ʽ


typedef struct st_DataCollect
{
	VoltageMode			enumVolMode;			//��ѹģʽ
	FlowAdjustPattern	enumFlowAdjPattern;		//�������ڷ�ʽ
	double				dDcOffset;				//ֱ��ƫ��
	double				dAcOffset;				//����ƫ��
	double				dAcFreq;				//����Ƶ��
	double				dAcAmplitude;			//������ֵ
	double				dAcRatio;				//����ռ�ձ�
	double				dAuxiAirPress;			//������ѹֵ
	double				dPumpFlowRate;			//������������
	double				dFeedAirFlowRate;		//������ѹ������
}DataCollect;


class CDlgPrintParamDataRecord: public CDialog
{
	DECLARE_DYNAMIC(CDlgPrintParamDataRecord)

public:
	CDlgPrintParamDataRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrintParamDataRecord();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT_PARAM_DATARECORD };

	void Cancel();				//���ٴ��ڼ��Ӵ���

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnBnClickedPrintPaDataApplyBtn();
	afx_msg void OnBnClickedPrintPaDataAddBtn();
	afx_msg void OnBnClickedPrintPaDataModifyBtn();
	afx_msg void OnBnClickedPrintPaDataDeleteBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

private:
	void Release();				//�ͷű�����������new���ڴ�
	void InitDlgCtrl();
	void InitGridListData();
	void ShowGridListData(CAdoRecordset* pRecordSet);

private:
	CDlgPrintParamAdjust*	m_pDlgParamMain;		//�������ڴ���
	CBmpBtn					m_bmpBtn[4];
	CGridCtrl				m_gridlistData;	
	CString					m_strDatabasePath;
	CAdoDatabase			m_adoDatabase;

public:
	DataCollect				m_PrintParamTable;		//��ӡ������

	
};