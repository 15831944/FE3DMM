#pragma once
#include "DlgLaserStripSWScanPath.h"
#include "DlgLaserStripSWParamRecord.h"


// CDlgLaserStripSubWin �Ի���
enum ScanMode{EMPTY = 0, SingleROW, MultiROW};
typedef struct st_ParamScan
{
	ScanMode		 scanmode;
	ParamSingleScan  paramSingleScan;
	ParamMultiScan	 paramMultiScan;

	st_ParamScan()
	{
		scanmode = EMPTY;
	}
}ParamScan;


class CDlgLaserStripSubWin : public CDialog
{
	DECLARE_DYNAMIC(CDlgLaserStripSubWin)

public:
	CDlgLaserStripSubWin(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLaserStripSubWin();

// �Ի�������
	enum { IDD = IDD_DLG_LASERSTRIP_SUBWIN };

	void Cancel();									//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();
	ParamScan* GetParamScan();		//��ȡɨ�����ָ��
	void SetParamInStatic();					//����ɨ�������Static�ؼ�
	CDlgLaserStripSWScanPath* GetDlgLaserStripSWScanPath();  //��ȡDlgLaserStripSWScanPath�Ի���ָ��

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedLaserstripSContiMoveRadio();
	afx_msg void OnBnClickedLaserstripSInterMoveRadio();
	afx_msg void OnDeltaposLaserstripSContiMoveSpeedSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposLaserstripSInterMoveStepSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedLaserstripSubwinXLBtn();
	afx_msg void OnClickedLaserstripSubwinXRBtn();
	afx_msg void OnClickedLaserstripSubwinYBBtn();
	afx_msg void OnClickedLaserstripSubwinYFBtn();
	afx_msg void OnClickedLaserstripSFastMoveBtn();
	afx_msg void OnClickedLaserstripSStartStripBtn();
	afx_msg void OnClickedLaserstripSToHomeBtn();
	afx_msg void OnBnClickedLaserstripSScanPathSetBtn();
	afx_msg void OnBnClickedLaserstripSPathParamSaveBtn();
	afx_msg void OnBnClickedLaserstripSLaserConfigBtn();
	afx_msg void OnBnClickedLaserstripSCameraRadio();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();																//�ͷű�����������new���ڴ�
	void SetMoveComponentState();							//�����˶��������״̬
	void ShowBmpInStatic();											//��Bmp��ʾ��Static�ؼ���
	void InitWindowHandle();											//��ʼ��Pic�ؼ���ʾ����

private:
	CXPGroupBox					 m_GB1;
	CXPGroupBox					 m_GB2;
	CXPGroupBox					 m_GB3;
	CBmpBtn							m_bmpBtn[10];
	CProcessCore					*m_pProCore;					//��������ָ��
	bool									m_bScanPathSet;				//�Ƿ�����ɨ��·��
	bool									m_bPathParamSave;		//�Ƿ񱣴�·������
	bool									m_bContinuousMove;	//true����  false�㶯
	double								m_dContinMoveSpeed;
	double								m_dInterMoveStep;
	double								m_dFastMoveXPos;
	double								m_dFastMoveYPos;
	ParamScan				 			m_paramscan;					//ɨ�����
	HTuple								m_windowHandle_Pic;	//Pic�ؼ�������Halcon���ھ��
	Size										m_winSize_Pic;					//Pic���ڴ�С
	CDlgLaserStripSWScanPath*	 m_pDlgLaserStripSWScanPath;	//ɨ��·�����ô���
	CDlgLaserStripSWParamRecord* m_pDlgLaserStripSWParamRecord;	//ɨ�������¼����
	
	
};
