#pragma once
#include "TransferRotateCal.h"

class CFE3DMMDlg;
class CParamData;
class CProcessCore;

enum Mode {CONTINUE = 0, STEP}; 

class CProcessTransfer
{
public:
	CProcessTransfer(void);
	~CProcessTransfer(void);

	void SetProcessCore(CProcessCore* pProcesscore);
	void SetMainDlgPointer(CFE3DMMDlg* pDlg);		//����������ָ��
	void SetParamData(CParamData* pData);              //�������ò�����ָ��

	void Init();
	void Release();
	void Run();										//�Զ�����
	void TransferPara();						//����λ�����ݲ���	
	void RestoreModel();					//����ƥ��ģ��


	//���תӡ���X
	inline CCtrlMotor* GetMotorTransferX(){ return &m_MotorTransferX;}		
	//���תӡ���Z
	inline CCtrlMotor* GetMotorTransferZ(){ return &m_MotorTransferZ;};		
	//���������X
	inline CCtrlMotor* GetMotorFourX()      { return &m_MotorFourX;}
	//���������Z
	inline CCtrlMotor* GetMotorFourY()      { return &m_MotorFourY;}
	//�������Ƕ�A
	inline CCtrlMotor* GetMotorFourAngleA(){ return &m_MotorFourAngleA;}
	//�������Ƕ�B
	inline CCtrlMotor* GetMotorFourAngleB(){ return &m_MotorFourAngleB;}
	//�������Ƕ�C
	inline CCtrlMotor* GetMotorFourAngleC(){ return &m_MotorFourAngleC;}

	//���ֱ���Ƹ˵��1-9
	inline CCtrlMotor* GetMotorRod11()    { return &m_MotorRod11;}	                        
	inline CCtrlMotor* GetMotorRod12()    { return &m_MotorRod12;}	
	inline CCtrlMotor* GetMotorRod13()    { return &m_MotorRod13;}	
	inline CCtrlMotor* GetMotorRod21()    { return &m_MotorRod21;}	
	inline CCtrlMotor* GetMotorRod22()    { return &m_MotorRod22;}	
	inline CCtrlMotor* GetMotorRod23()    { return &m_MotorRod23;}	
	inline CCtrlMotor* GetMotorRod31()    { return &m_MotorRod31;}	
	inline CCtrlMotor* GetMotorRod32()    { return &m_MotorRod32;}	
	inline CCtrlMotor* GetMotorRod33()    { return &m_MotorRod33;}	

	//��е��Ĥ������
	inline CCtrlIO* GetIoVacAttach()    { return &m_IO_VacAttach;}
	//��е��Ĥ�Ĵ���
	inline CCtrlIO* GetIoVacBlow()       { return &m_IO_VacBlow;}
	//��е�־Ÿ��Ƹ�������
	inline CCtrlIO* GetIoRodAttach()   {return &m_IO_RodAttach;}
	//ʰȡƽ̨�������
	inline CCtrlIO* GetIoPickPlatform() {return &m_IO_PickPlatform;}
	
	void SetRunMode(int Mode);


/************************************************************************/
/*  ����תӡ��ʽ���ýӿ�
/************************************************************************/
public:
	/*
	** ����תӡ����Ƿ�ʹ�ܣ���������
	*/
	void EnableTransMotor(const bool);

	/* ������ת��Ϣ */
	BOOL CalRotateInfo();

	//����ģ��
	BOOL LoadModel();

/************************************************************************/
/*  �Զ�����תӡ���ֲ�����ӿں���
/************************************************************************/
	//public functions
public:
	//thread function
	static UINT InitiativeTransferThread(LPVOID lParam);        //�������η�ʽתӡ���߳�
	static UINT VariableInquireThread(LPVOID lParam);            //��ѯ��λ�������߳�
	static UINT AssistThread(LPVOID lParam);                             //����תӡ�߳�

	//��������
	BOOL ThreadInit();      //�̳߳�ʼ��
	BOOL ThreadExit();     //�����˳�ʧ����ǿ�ƽ����߳�

	BOOL Start();	
	BOOL PickAngleLocation();
	BOOL PickPosYLocation();
	BOOL PickPosXLocation();
	BOOL Pick();
	
	BOOL HandTransform();
	BOOL PlaceLocation();
	BOOL Place();
    BOOL Stop();
	

private:
	//Thread Pointer
	CWinThread* m_pInitiativeTransferThread;         //��������תӡ�߳�ָ��	
	CWinThread* m_pVariableInquireThread;
	CWinThread* m_pAssistThread;

	/***************���߳��¼�***************/
	
	//�˳��¼�
	//���߳̿�ʼ�¼�
	//�Ƕȶ�λ�¼�
	//Y��λ
	//X��λ
	//��װ��λ
	
	HANDLE m_hTransfer[6];

	/************������ѯ�¼�**************/
	//�˳��¼�
	//�������������ͼλ��
	//���Խ��о������
	//�������������ͼλ�ã��Ҿ�����ɱ���	
	HANDLE m_hVariableInquire[4];

	/************�����߳��¼�*************/
	//�˳��¼�
	//������ת��Ϣ����
	//�������	
	HANDLE m_hAssist[3];

	//��ת����
	CTransferRotateCal m_RotateCal;

public:
	//Mark Varible
	bool m_BeModelLoad;         //ģ������Ƿ����
	bool m_BeAdjustAngle;
	bool m_BeAdjustPosY;


/************************************************************************/
/*  ����תӡ���ֲ�����ӿں���
/************************************************************************/
public:

	static UINT PassitivityTransferThread(LPVOID lParam);      //�������η�ʽתӡ���߳�

private:
	CWinThread* m_pPassitivityTransferThread;       //���������߳�ָ��


/************************************************************************/
/* ���������е��õĽӿں���
/************************************************************************/
public:

	/*
	** �������г�ʼ������
	*/
	void StepRunInit();


	/*
	** �������п�ʼ�Ƕȵ������ӿں���
	*/
	BOOL StartAngleAdjust();   


	/*
	** �������н����Ƕȵ������ӿں���
	*/
	BOOL EndAngleAdjust();


	/*
	** �������п�ʼY����λ�õ������ӿں���
	*/
	BOOL StartYAdjust();


	/*
	** �������н���Y����λ�õ������ӿں���
	*/
	BOOL EndYAdjust();


	/*
	** �����������и����̺߳���
	*/
	static UINT StepAdjustThread(LPVOID lParam);      //�������й����У��ֶ�����ƫ���߳�


/************************************************************************/
/*  �����������˽�г�Ա����
/************************************************************************/
private:
	/*
	** ���Ƶ������е����߳��Ƿ��˳��Ŀ��Ʊ���
	*/
	bool m_bStepAdjustRun;


	/*
	*�������Եĸ����߳�
	*/
	CWinThread* m_pStepAdjustThread;   /*�Ƕȵ����߳�*/


	/*
	** ���������¼��������
	*/
	HANDLE m_hStepAdjust[3];



private:
	CProcessCore       *m_pProcessCore;
	CFE3DMMDlg		*m_pMainDlg;				    //���Ի���ָ��
	CParamData			*m_pParamData;				//���ò�����ָ��
	Mode                      m_RunMode;                   //����ģʽ��������������


	//���
	CCtrlMotor			m_MotorTransferX;					//תӡ���X
	CCtrlMotor			m_MotorTransferZ;					//תӡ���Z
	CCtrlMotor           m_MotorFourX;
	CCtrlMotor           m_MotorFourY;
	CCtrlMotor           m_MotorFourAngleA;           //��X����ת
	CCtrlMotor           m_MotorFourAngleB;           //��Y����ת
	CCtrlMotor           m_MotorFourAngleC;           //��Z����ת
	/*********ֱ���Ƹ˵���ֲ�**********/
	/*11 12 13*/
	/*21 22 23*/
	/*31 32 33*/
	CCtrlMotor           m_MotorRod11;                      //ֱ���Ƹ�11
	CCtrlMotor           m_MotorRod12;  
	CCtrlMotor           m_MotorRod13;  
	CCtrlMotor           m_MotorRod21;  
	CCtrlMotor           m_MotorRod22;  
	CCtrlMotor           m_MotorRod23;  
	CCtrlMotor           m_MotorRod31;  
	CCtrlMotor           m_MotorRod32;  
	CCtrlMotor           m_MotorRod33;  

	// ��λ��תӡ�Զ�����
	CCtrlProg          m_prog1;                       //������򣬱�־λP100����ʼΪ1������Ϊ0

	//IO
	CCtrlIO				m_IO_VacAttach;				//�������
	CCtrlIO				m_IO_VacBlow;					//��տ���
	CCtrlIO               m_IO_RodAttach;
	CCtrlIO               m_IO_PickPlatform;

	/*λ����*/
	CCtrlParam            m_P301;		//P301תӡ��е��X11ƽ���ͼλ�ã�ѧϰ��
	CCtrlParam			m_P302;		//P302תӡ��е��Z12ƽ���ͼλ�ã�ѧϰ��
	CCtrlParam			m_P303;		//P303תӡ��е��X11ʰȡλ��
	CCtrlParam			m_P304;	    //P304תӡ��е��Z12ʰȡλ��
	CCtrlParam			m_P305;		//P305תӡ��е��Z12ʰȡ��������λ�ã�ѧϰ��
	CCtrlParam			m_P306;		//P306תӡ��е��Z11����״̬��ͼλ�ã�ѧϰ��
	CCtrlParam			m_P307;		//P307תӡ��е��Z12����״̬��ͼλ�ã�ѧϰ��
	CCtrlParam			m_P308;		//P308�����е��X1����״̬��ͼλ�ã�ѧϰ��
	CCtrlParam			m_P309;		//P309�����е��Y2����״̬��ͼλ�ã�ѧϰ��
	CCtrlParam			m_P310;		//P310תӡ��е��Z12��ͼ��ɺ�����λ�ã�ѧϰ��

	/*�����ת���ü���ֵ*/
	CCtrlParam			m_P311;		//P311�����е��X1��װλ��
	CCtrlParam			m_P312;		//P312�����е��Y2��װλ��
	CCtrlParam			m_P313;		//P313�����е��A��ת�Ƕ�
	CCtrlParam			m_P314;		//P314�����е��B��ת�Ƕ�
	CCtrlParam			m_P315;		//P315�����е��C��ת�Ƕ�

	/*�����ת����UGģ��ֵ*/
	CCtrlParam			m_P316;		//P316����X1λ��
	CCtrlParam			m_P317;		//P317����Y2λ��
	CCtrlParam			m_P318;		//P318����Aλ��
	CCtrlParam			m_P319;		//P319����Bλ��
	CCtrlParam			m_P320;		//P320��װ�ǻ�е��Z12λ��

	/*��λ��Ϣ��־��*/
	CCtrlParam			m_P350;		//P350���й����е�λ��־��
	CCtrlParam			m_P351;		//P351�Ÿ���е�ֵ�λ��־��

	/*�ٶ���*/
	CCtrlParam			m_P360;		//P360תӡ��е��X11�ٶ�
	CCtrlParam			m_P361;		//P361תӡ��е��Z12�ٶ�
};
