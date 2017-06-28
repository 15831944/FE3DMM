#pragma once
class CFE3DMMDlg;
class CParamData;

class CProcessLaserStrip
{
public:
	CProcessLaserStrip(void);
	~CProcessLaserStrip(void);

	void SetMainDlgPointer(CFE3DMMDlg* pDlg);		    //����������ָ��
	void Init();
	void Release();
	void Home();										//����
	void SetParamData(CParamData* pData);				//�������ò�����ָ��

	//CCtrlMotor* GetMotorLaserStripX();
	//CCtrlMotor* GetMotorLaserStripY();

//2017.03.23 Edited By Zhoulaoboyang
	void TransferPara(double ScanLen,double ScanSpace,double ScanSpeed,double TransRowSpeed,int ScanNum);		//����P��������λ��
	bool GetProgStatus();																						//��������״̬���޳�������=0���г�������=1��
	void RunProgram();																						    //������λ������

private:
	CFE3DMMDlg*					m_pMainDlg;					//���Ի���ָ��
	CParamData*					m_pParamData;				//���ò�����ָ��


	//�˶����
// 	CCtrlMotor				m_MotorLaserStripX;
// 	CCtrlMotor				m_MotorLaserStripY;

// 2017.03.23 Edited By Zhoulaoboyang
	//��λ������
	CCtrlProg				m_Prog200;					//��ɨ���Զ�����

	//P����
	CCtrlParam				m_P200;						// ��λ��>>��λ�� ����ʼ=1���������=0
	CCtrlParam				m_P201;						// ��λ��>>��λ�� ɨ�賤�� L
	CCtrlParam				m_P202;						// ��λ��>>��λ�� ɨ���� D
	CCtrlParam				m_P203;						// ��λ��>>��λ�� ɨ���ٶ� Vl
	CCtrlParam				m_P204;						// ��λ��>>��λ�� �����ٶ� Vd
	CCtrlParam				m_P205;						// ��λ��>>��λ�� ɨ������ N
//
};

