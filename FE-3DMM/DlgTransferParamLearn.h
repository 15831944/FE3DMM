#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "DlgTransferParamCoordCalib.h"

using HalconCpp::HObject;


// CDlgTransferParamLearn �Ի���
class CDlgTransferParamLearn : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransferParamLearn)

	//public class members
public:
	CDlgTransferParamLearn(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTransferParamLearn();

    // �Ի�������
	enum { IDD = IDD_DLG_TRANSFER_PARAM };

	// ��յ�ѡ��ť
	enum {FILMNEGETIVE = 0, FILEPOSITIVE, RODVACUUM, PLATVACUUM};

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();

	//protect class members
protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);     // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
	virtual void PostNcDestroy();
	virtual void OnCancel();
	

	//private class members
private:
	void Release();							//�ͷű�����������new���ڴ�
	void InitWindowHandle();		//��ʼ��Pic�ؼ���ʾ����
	void RefreshLocalRegion(const int & ID);//�ػ�ؼ��ֲ�

	//public class variable
public:
	CXPGroupBox			m_GB1;   //�ؼ�����
	CXPGroupBox			m_GB2;	//�ؼ�����
	CXPGroupBox			m_GB3;
	CBmpBtn				    m_bmpBtn[27];
	CComboBox             m_cPISizeComBox;

	CmySliderControl    m_cSliderPace;
	CEdit m_cEditPace;
	CSpinButtonCtrl m_cSpinPace;

	CEdit                          m_cEditVacuum;
	CSpinButtonCtrl      m_cSpinVacuum;

	CmySliderControl  m_cSldV;
	CEdit                         m_cEditV;
	CSpinButtonCtrl     m_cSpinV;

	CmySliderControl m_cSldF;
	CEdit                        m_cEditF;
	CSpinButtonCtrl    m_cSpinF;

	//private class variable
private:
	bool                           m_bFilmNegOpen;     //��տ�����־
	bool                           m_bFilmPosiOpen;
	bool                           m_bRodVacuumOpen;
	bool                           m_bPlatVacuumOpen;

	bool			                m_bElecStaticOpen;   //��տ�����־lecStaticOpen
	CProcessCore*		    m_pProCore;  //��������ָ��
	
	int m_iTransferType;             //תӡ��ʽ��ѡ��ť�󶨵�intֵ
	int m_iPushRodNum;            //ֱ���Ƹ˵�ѡ��ť�󶨵�intֵ           
	int m_iRadioVacuum;            //��ѹ��ѹѡ��ѡ��ť
	int m_iRadioCamera;             //�����ѡ��ť�󶨵�intֵ

	bool   m_bIsContinueSnap;
	int m_iPace;           //����˶�����

	//ͼ������ر���
	HObject m_hoImage;

	HTuple		m_windowHandle_Pic;	//Pic�ؼ�������Halcon���ھ��
	Size				m_winSize_Pic;					//Pic���ڴ�С

	//child window
	CDlgTransferParamCoordCalib* m_pDlgCoordCalib;

public:
	//��Ϣ��Ӧ����
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);	
	afx_msg void OnBnClickedTransferPVacuumOpenBtn();
	afx_msg void OnBnClickedTransferPElecstaticOpenBtn();
	afx_msg void OnBnClickedTransferPXlBtn();
	afx_msg void OnBnClickedTransferPPickupviewBtn();
	afx_msg void OnBnClickedTransferPXrBtn();
	afx_msg void OnBnClickedTransferPZupBtn();
	afx_msg void OnBnClickedTransferPZdownBtn();
	afx_msg void OnBnClickedTransferPPushrodleftBtn();
	afx_msg void OnBnClickedTransferPPushrodrightBtn();
	afx_msg void OnBnClickedTransferPMecharmpickBtn();
	afx_msg void OnBnClickedTransferPCameraTransDownRadio();
	afx_msg void OnBnClickedTransferPCameraTransUpRadio();
	afx_msg void OnEnChangeTransferPVacuumEdit();
	afx_msg void OnDeltaposTransferPVacuumSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureTransferPVoltageSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTransferPVoltageEdit();
	afx_msg void OnDeltaposTransferPVoltageSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureTransferPFrequencySlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTransferPFrequencyEdit();
	afx_msg void OnDeltaposTransferPFrequencySpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedTransferPVacuumSaveBtn();
	afx_msg void OnBnClickedTransferPActivemodeRadio();
	afx_msg void OnBnClickedTransferPPassivemodeRadio();
	afx_msg void OnBnClickedTransferPUpviewBtn();
	afx_msg void OnBnClickedTransferPFouraxleupviewBtn();
	afx_msg void OnBnClickedTransferPCoordcalibBtn();
	afx_msg void OnBnClickedTransferPNewLearnposBtn();
	afx_msg void OnNMReleasedcaptureTransferPPaceSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposTransferPPaceSpin(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeTransferPPaceEdit();
	afx_msg void OnBnClickedTransferPVacuumCloseBtn();
	afx_msg void OnBnClickedTransferPVacuumnegRadio();
	afx_msg void OnBnClickedTransferPVacuumposiRadio();
	afx_msg void OnBnClickedTransferPVacuumrodRadio();
	afx_msg void OnBnClickedTransferPVacuumplatRadio();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};
