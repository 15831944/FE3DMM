#pragma once
#include "GCodeAnalysis.h"
#include "./JetPrint/JetAglientFunction.h"
#include "./JetPrint/JetHarvardPump.h"
#include "./JetPrint/JetAirPressureSet.h"
class CFE3DMMDlg;
class CParamData;

#define ROT_PROG_ROWS  600		//ÿ��������ת��������������

class CProcessPrint
{
public:
	CProcessPrint(void);
	~CProcessPrint(void);

	void SetMainDlgPointer(CFE3DMMDlg* pDlg);		//����������ָ��
	void Init();
	void Release();
	void Home();																	//����
	void SetParamData(CParamData* pData);				//�������ò�����ָ��

	static UINT	PrintThreadProc(LPVOID pVoid);			//��ӡ�̺߳���
	void ExitPrintThread();												//�˳���ӡ�߳�
	void PausePrint();															//��ͣ
	void ContinuePrint();													//����
	void StartPrint();															//��ʼ
	void StopPrint();															//ֹͣ
	void MonitorProg();													//������λ������
	void OpenGCodeFile(CString strPath);					//��ȡ������G�����ļ�

private:
	void StraightLinePrint();												//ֱ�ߴ�ӡ
	void DownLoadProg(vector<CString> &vecCode, 
		int &nDownLoadCnt);												//�����˶�����
						

public:
	bool								m_bIsLinesPrint;					//�ж�: trueֱ�ߴ�ӡ,false�����ӡ
// 	CJetAglientFunction   m_JetAglientFunc;				//����������
// 	CJetHarvardPump		m_JetHarvardPump;			//������
// 	CJetAirPressureSet		m_JetAirPress;						//��ѹ����

private:
	CFE3DMMDlg*			m_pMainDlg;							//���Ի���ָ��
	CParamData*				m_pParamData;						//���ò�����ָ��
	CWinThread*			m_pThreadPrint;						//��ӡ�߳�
	HANDLE						m_hEventPrint[3];						//��ӡ�¼�
	bool							m_bPrintLinesFlag;					//ֱ�ߴ�ӡ��־
	bool							m_bDownProgFlag;					//Prog���ر�־
	bool							m_bThreadExit;						//�߳��˳���־
	CGCodeAnalysis		m_gcodeAnalysis;					//G�������
    bool							m_bRemainDownLoadFlag;	//ʣ�����ر�־
	int								m_nDownLoadCount;				//���ش�������
// 
// 	//P����
// 	CCtrlParam				m_P400;										//ֱ������
// 	CCtrlParam				m_P401;										//ֱ�߿�ʼ��X
// 	CCtrlParam				m_P402;										//ֱ�߿�ʼ��Y
// 	CCtrlParam				m_P403;										//ֱ�߽�����X
// 	CCtrlParam				m_P404;										//ֱ�߽�����Y
// 	CCtrlParam				m_P405;										//ֱ�߽Ƕ�A
// 	CCtrlParam				m_P406;										//ֱ�߽Ƕ�C
// 	CCtrlParam				m_P407;										//ֱ�ߴ�ӡ״̬  1:��ʼ 0:����	
// 	CCtrlParam				m_P408;										//ֱ�ߴ�ӡ�ٶ�
// 	CCtrlParam				m_P409;										//�����λ��Prog����
// 
// 	//��λ���Զ�����
// 	CCtrlProg					m_Prog4;									//ֱ�ߴ�ӡ�Զ�����
// 
//  	//IO
// 	CCtrlIO						m_IO_m7912;							//�������
// 	CCtrlIO						m_IO_m7913;							//��տ���
 
	
};

