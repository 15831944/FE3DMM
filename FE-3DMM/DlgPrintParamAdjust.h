#pragma once
#include "DlgPrintParamDataRecord.h"
#include "DlgPrintParamCameraWatch.h"

// CDlgPrintParamAdjust �Ի���


class CDlgPrintParamAdjust : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrintParamAdjust)

public:
	CDlgPrintParamAdjust(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrintParamAdjust();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT_PARAM };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrintPaVoltageAirOpenBtn();
	afx_msg void OnBnClickedPrintPaPumpmodeRadio();
	afx_msg void OnBnClickedPrintPaFeedAirPressmodeRadio();
	afx_msg void OnBnClickedPrintPaDataRecordBtn();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnUMCameraWatchShow();
	afx_msg void OnBnClickedPrintPaDcModeRadio();
	afx_msg void OnBnClickedPrintPaAcModeRadio();
	afx_msg void OnBnClickedPrintPaFlowstartBtn();
	afx_msg void OnBnClickedPrintPaFlowstopBtn();
	afx_msg void OnDeltaposPrintPaAmplitudeSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposPrintPaFreqSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposPrintPaOffsetSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposPrintPaDutyratioSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposPrintPaAuxiairpressSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposPrintPaFlowsetSpin(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedPrintPaCamerawatchRadio();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();																		//�ͷű�����������new���ڴ�
	void InitFlowAdjustCtrlState(bool bEnabled);				//��ʼ���������ڿؼ�״̬
	void InitVoltageAirAdjustCtrlState(bool bEnabled);	//��ʼ����ѹ��ѹ���ڿؼ�״̬	
	void SetFlowComponentState(bool bEdit,bool bForward,bool bBackward,bool bStart,bool bStop); //���������������״̬
	void SetVoltageComponentState(bool bOffset,bool bAmplitude,bool bFreq,bool bDutyRatio);			//���õ�ѹ�������״̬			
	void InitWindowHandle();													//��ʼ��Pic�ؼ���ʾ����

public:
	void AddPrintParamTable();												//��Ӵ�ӡ������
	void ApplyPrintParamTable();											//Ӧ�ô�ӡ������


private:
	CXPGroupBox				m_GB1;
	CXPGroupBox				m_GB2;
	CBmpBtn						m_bmpBtn[6];
	CProcessCore				*m_pProCore;								//��������ָ��
	bool								m_bVoltageAirOpen;		
	bool								m_bParamDataShow;					//���������Ƿ���ʾ
	bool								m_bCameraWatchShow;			//ī�ι۲�����Ƿ񵥶���ʾ
	bool								m_bForwardOrBackwardFlag;	//������˱����±�־
	VoltageMode				m_enumVolMode;						//��ѹģʽ
	FlowAdjustPattern		m_enumFlowAdjPattern;			//�������ڷ�ʽ
	double							m_dDcOffset;								//ֱ��ƫ��
	double							m_dAcOffset;								//����ƫ��
	double							m_dAcFreq;									//����Ƶ��
	double							m_dAcAmplitude;						//������ֵ
	double							m_dAcRatio;									//����ռ�ձ�
	double							m_dAuxiAirPress;							//������ѹֵ
	double							m_dPumpFlowRate;					//������������
	double							m_dFeedAirFlowRate;					//������ѹ������
	
	HTuple							m_windowHandle_Pic;				//Pic�ؼ�������Halcon���ھ��
	Size									m_winSize_Pic;								//Pic���ڴ�С
	CDlgPrintParamDataRecord*	m_pDlgPrintParamDataRecord;			//��¼��������
	CDlgPrintParamCameraWatch*	m_pDlgPrintParamCameraWatch;	//ī��۲����
};
