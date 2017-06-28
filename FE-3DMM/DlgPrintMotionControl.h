#pragma once
#include "DlgPrintMotionLinkLearn.h"

// CDlgPrintMotionControl �Ի���

class CDlgPrintMotionControl : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrintMotionControl)

public:
	CDlgPrintMotionControl(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrintMotionControl();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT_MOTION };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedPrintMContinuMoveRadio();
	afx_msg void OnBnClickedPrintMInterMoveRadio();
	afx_msg void OnBnClickedPrintMXpositiveBtn();
	afx_msg void OnBnClickedPrintMXnegativeBtn();
	afx_msg void OnBnClickedPrintMYpositiveBtn();
	afx_msg void OnBnClickedPrintMYnegativeBtn();
	afx_msg void OnDeltaposPrintMContinuMoveSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposPrintMInterMoveStepSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedPrintMLinklearnBtn();
	afx_msg void OnBnClickedPrintMCameralocateRadio();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();
	
private:
	void Release();														//�ͷű�����������new���ڴ�
	void InitSimulatePanel();										//��ʼ���˶�ģ�����
	void SetMoveComponentState();					//�����˶��������״̬
	void InitWindowHandle();									//��ʼ��Pic�ؼ���ʾ����

public:
	CDlgPrintMotionLinkLearn* m_pDlgPrintMotionLinkLearn;  	//����ѧϰDlg

private:
	CXPGroupBox				m_GB1;
	CXPGroupBox				m_GB2;
	CXPGroupBox				m_GB3;
	CBmpBtn						m_bmpBtn[7];
	CPanelWnd					m_panelwnd;
	CProcessCore				*m_pProCore;											//��������ָ��
	bool								m_bContinuousMove;							//true����  false�㶯
	double							m_dContinMoveSpeed;
	double							m_dInterMoveStep;
	bool								m_bLinkLearn;											//�Ƿ��������ѧϰ
	HTuple							m_windowHandle_Pic;							//Pic�ؼ�������Halcon���ھ��
	Size									m_winSize_Pic;											//Pic���ڴ�С
};
