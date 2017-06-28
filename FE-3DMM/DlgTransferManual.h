#pragma once
#include "afxcmn.h"
#include "DlgTransferManualNew.h"
#include "DlgTransferManualAdvanced.h"

// CDlgTransferManual �Ի���

class CDlgTransferManual : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransferManual)



/************************************************ public functions ***********************************************/
public:
	// �Ի���ID
	enum { IDD = IDD_DLG_TRANSFER_MANUAL };

	/*
	** @Name: CDlgTransferManual
	** @Function: ���캯��
	** @Input: ��������ָ�룬Ĭ�ϲ���Ϊ�գ�������ָ�룬Ĭ�ϲ���ΪNULL
	** @Output: NULL
	*/
	CDlgTransferManual(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��

	/*
	** @Function: ����������
	*/
	virtual ~CDlgTransferManual();


	/*
	** @name: Cancel
	** @function: ����Cancel�������ٴ��ں��Ӵ���
	** @ Input: NULL
	** @Output: NULL
	*/
	void Cancel();   //���ٴ��ڼ��Ӵ���


	/*
	** @name: InitDlgCtrl
	** @Function: ��ʼ���ؼ�
	** @Input: NULL
	** @Output: NULL
	*/
	void InitDlgCtrl();

	/*
	** @name: UpdateList
	** @Function: ������ݺ�ˢ��list�ؼ���ʾ
	** @Input: NULL
	** @Output: NULL
	*/
	void UpdateList();


	int GetSelProduct();


	/*
	** @name: ReadCtrlValue
	** @Function: ��ȡEDIT�ؼ��е�X��Y��Angle
	** @Input: NULL
	** @Output: NULL
	*/
	void ReadCtrlValue();



/********************************************************* protected functions *****************************************************/
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();





/********************************************************* private functions *******************************************************/
private:

		void InitWindowHandle();		//��ʼ��Pic�ؼ���ʾ����

	/*
	** @name: Release
	** @Function: �ֶ��ͷŸ������ڶ��Ϸ�����ڴ�
	** @Input: NULL
	** @Output: NULL
	*/
	void Release();        //�ͷű��������������ڴ�
	


	/*
	** @name: StepRun
	** @Function: ������������µ������к���
	** @Input: NULL
	** @Output: NULL
	*/
	void StepRun();



	/*
	** @name: PositiveStepRun
	** @Function: ������������µ������к���
	** @Input: NULL
	** @Output: NULL
	*/
	void PositiveStepRun();



	/*
	** @name: PositiveStepRun
	** @Function: ������������µ������к���
	** @Input: NULL
	** @Output: NULL
	*/
	void NegtiveStepRun();




	/*
	** @name: StepRunEnableCtrl
	** @Function: ������������£�ʹ�ܿؼ�������ֹ���й����У�תӡ��ʽ�����л������Զ�������
	** @Input: bool������true��ʾʹ��ʹ�ã�false��ʾʹ����ʹ��
	** @Output: NULL
	*/
	void StepRunEnableCtrl(bool);



	/*����תӡ������������غ���*/
	BOOL PositiveStep1();
	BOOL PositiveStep2();
	BOOL PositiveStep3();
	BOOL PositiveStep4();
	BOOL PositiveStep5();
	BOOL PositiveStep6();
	BOOL PositiveStep7();
	BOOL PositiveStep8();
	BOOL PositiveStep9();
	BOOL PositiveStep10();
	BOOL PositiveStep11();
	BOOL PositiveStep12();
	BOOL PositiveStep13();
	BOOL PositiveStep14();

	/*
	** @name: GoHome
	** @Function: תӡģ��������
	** @Input: NULL
	** @Output: NULL
	*/
	BOOL GoHome();


	/*
	** @name: UpDateTips
	** @Function: ������ʾ��Ϣ
	** @Input: NULL
	** @Output: NULL
	*/
	BOOL UpDateTips(int num);


	/*
	** @name: UpDateTips
	** @Function: ˢ����Ϊ͸��ģʽ�ľ�̬�ı��ؼ������ڸ�����ʾ��Ϣ��ʹ��
	** @Input: NULL
	** @Output: NULL
	*/
	void RefreshStatic();






/**************************************************************** private members **********************************************************/
private:

	/* ������ʾ��ö�ٳ��� */
	enum Tips { GO_HOME, TO_TRANSCAM_VIEW, ANGLE_LOCA, POSY_LOCA, TO_PICK_POS, PICK, SUCTION, 
		ROD_RUN,  TO_UPCAM_VIEW, PLACE_LOCA, TO_PLACE_POSE, SURFACE_ROTATE, PLACE, BLOW, END, INIT };


	/* ö�ٴ���궨�壬�Ե������Բ����Ĵ��� */
	enum Step { STEP1 = 1, STEP2, STEP3, STEP4, STEP5, STEP6, STEP7, STEP8, STEP9, STEP10, STEP11, STEP12, STEP13, STEP14};


	CProcessCore     *m_pProCore;      //��������ָ��
	CXPGroupBox			m_GB1;
	CXPGroupBox			m_GB2;
	CXPGroupBox			m_GB3;
	CXPGroupBox			m_GB4;

	CBmpBtn               m_bmpBtn[9];
	CListCtrlCl             m_cListObject;

	//CDlgTransferManualNew*           m_DlgNewObject;                 //�½����󴰿�
	//CDlgTransferManualAdvanced* m_DlgAdvancedSetting;      //�߼����ô���

	//�ؼ���������
	int m_cTransTypeRadio;   //תӡ��ʽ��ѡ��ť�󶨲���

	int m_cCamNum;                //�����ѡ��ť�󶨲���

	CString m_strTips;              //תӡ��ʾ�ı���Ϣ
	
	static int m_NextBtnCount;     //��һ����ť����

	/**����������ر���**/
	static int m_iClickNum;         //��ť�������



	//ͼ����ر���
	HalconCpp::HObject m_hoImage;

	HTuple	m_windowHandle_Pic;	//Pic�ؼ�������Halcon���ھ��
	Size			m_winSize_Pic;					//Pic���ڴ�С




/************************************************************** respond functions *******************************************************/
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg LRESULT OnChangeTips(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedTransferMNewBtn();
	afx_msg void OnBnClickedTransferMAdvancedBtn();
	afx_msg void OnBnClickedTransferMDeleteBtn();
    afx_msg void OnBnClickedTransferMStartBtn();
	afx_msg void OnBnClickedTransferMNextBtn();	
	afx_msg void OnBnClickedTransferMStepdebugBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedTransferMCameraTransDownRadio();
	afx_msg void OnBnClickedTransferMCameraTransUpRadio();
};


