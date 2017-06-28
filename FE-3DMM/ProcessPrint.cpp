#include "StdAfx.h"
#include "ProcessPrint.h"
#include "FE-3DMMDlg.h"
#include "ParamData.h"


CProcessPrint::CProcessPrint(void)
{
	m_pMainDlg				= NULL;
	m_pThreadPrint			= NULL;
	m_bPrintLinesFlag		= false;
	m_bDownProgFlag			= false;
	m_bThreadExit			= false;
	m_bRemainDownLoadFlag	= false;
	m_nDownLoadCount		= 0;
	m_bIsLinesPrint			= false;
}


CProcessPrint::~CProcessPrint(void)
{
	Release();
}


void CProcessPrint::SetMainDlgPointer(CFE3DMMDlg* pDlg)
{
	m_pMainDlg = pDlg;
}


void CProcessPrint::Init()
{
// 	//��ʼ������������
// 	if (false == m_JetAglientFunc.Connect())
// 	{
// 		AfxMessageBox("��������������ʧ��!");
// 	}
// 	//��ʼ��������
// 	if (FALSE == m_JetHarvardPump.Init(11))
// 	{
// 		AfxMessageBox("�����ó�ʼ��ʧ��!");
// 	}
// 	//��ʼ����ѹ����
// 	if (TRUE == m_JetAirPress.Init(1))
// 	{
// 		m_JetAirPress.SetAnalogInputType(3);
// 	}
// 	else
// 	{
// 		AfxMessageBox("��ѹ���ڳ�ʼ��ʧ��!");
// 	}


	//��ʼ��ī�ι۲����
// 	m_CameraWatch.SetCameraInfo("GigEVision", "dianjiao");
// 	m_CameraWatch.SetCameraType(DISP);
// 	m_CameraWatch.Init();
// 	m_CameraWatch.StartCapture(); 

	//��ʼ����ӡ��λ���
// 	m_CameraLocate.SetCameraInfo("GigEVision", "dianjiao");
// 	m_CameraLocate.SetCameraType(DISP);
// 	m_CameraLocate.Init();
// 	m_CameraLocate.StartCapture(); 

	//P����
// 	m_P400.ConfigParam(0,"P400","ֱ������");	
// 	m_P401.ConfigParam(0,"P401","ֱ�߿�ʼ��X");	
// 	m_P402.ConfigParam(0,"P402","ֱ�߿�ʼ��Y");	
// 	m_P403.ConfigParam(0,"P403","ֱ�߽�����X");	
// 	m_P404.ConfigParam(0,"P404","ֱ�߽�����Y");	
// 	m_P405.ConfigParam(0,"P405","ֱ�߽Ƕ�A");
// 	m_P406.ConfigParam(0,"P406","ֱ�߽Ƕ�C");
// 	m_P407.ConfigParam(0,"P407","ֱ�ߴ�ӡ״̬");
// 	m_P408.ConfigParam(0,"P408","ֱ�ߴ�ӡ�ٶ�");
//	m_P409.ConfigParam(0,"P409","�����λ��Prog����");

//  	//��λ���Զ�����
//  	m_Prog4.ConfigProg(0, 1, 4, "ֱ�ߴ�ӡ�Զ�����");


 	//IO
// 	m_IO_m7912.ConfigIO(0,"M7912","��װ�������");		//��װ���������on/off���أ�
// 	m_IO_m7913.ConfigIO(0,"M7913","��װ��տ���");		//��װ��տ���

	//������ת������
// 	CCtrlCommand cmd(0);
// 	cmd.GiveCommand("CLOSE");
// 	cmd.GiveCommand("&1A");
// 	cmd.GiveCommand("END GATHER");						//�������ݲɼ��������������ͻ
// 	cmd.GiveCommand("DELETE GATHER");					//ɾ�����ݲɼ�������
// 	cmd.GiveCommand("&1 DELETE ROT");					//ɾ��&1�������ת������
// 	cmd.GiveCommand("&1 DEFINE ROT 40000");				//������ת��������СΪ40000
// 	cmd.GiveCommand("&1 BO");							//׼��������ת����������
// 	cmd.GiveCommand("&1 CLEAR");						//������������	
// 	cmd.GiveCommand("&1 R");							//����

	m_pThreadPrint = AfxBeginThread(PrintThreadProc, this);
	ASSERT(m_pThreadPrint);

	m_hEventPrint[0] = CreateEventA(NULL, TRUE, FALSE, NULL);  //ֱ�ߴ�ӡ���¼�
	m_hEventPrint[1] = CreateEventA(NULL, TRUE, FALSE, NULL);  //�����ӡ����������¼�
	m_hEventPrint[2] = CreateEventA(NULL, TRUE, FALSE, NULL);  //�߳��˳����¼�

}


void CProcessPrint::Release()
{
// 	if (m_JetAglientFunc.IsDeviceConnect())
// 	{
// 		m_JetAglientFunc.SetAmplitude(1);
// 		m_JetAglientFunc.SetOffset(1);
// 		m_JetAglientFunc.SetOutput(FALSE);
// 		m_JetAglientFunc.Disconnect();
// 	}  
// 
// 	if (m_JetHarvardPump.IsHarvardOpen())
// 	{
// 		m_JetHarvardPump.Stop();
// 		m_JetHarvardPump.CloseHarvardPump();
// 	}
// 
// 	m_JetAirPress.UnInit();
}


void CProcessPrint::Home()
{

}


void CProcessPrint::SetParamData(CParamData* pData)
{
	m_pParamData = pData;
}


UINT CProcessPrint::PrintThreadProc(LPVOID pVoid)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);
	CProcessPrint* pThis = (CProcessPrint*)pVoid;

	while(1)
	{
		switch (WaitForMultipleObjects(3, pThis->m_hEventPrint, FALSE, INFINITE))
		{
		case WAIT_OBJECT_0:
			ResetEvent(pThis->m_hEventPrint[0]);
			/////��ѹ����
			pThis->StraightLinePrint();
			/////��ѹ�ر�
			break;

		case WAIT_OBJECT_0+1:
			ResetEvent(pThis->m_hEventPrint[1]);
			pThis->DownLoadProg(pThis->m_gcodeAnalysis.m_vecStrGCode, pThis->m_nDownLoadCount);		
			break;

		case WAIT_OBJECT_0+2:
			ResetEvent(pThis->m_hEventPrint[2]);
 			DWORD dwExitCode;
			GetExitCodeThread(pThis->m_pThreadPrint->m_hThread, &dwExitCode);
			AfxEndThread(dwExitCode, TRUE);
			break;

		default:
			break;
		}		
	}

	CoUninitialize();
	return 0;
}


void CProcessPrint::StraightLinePrint()
{
	m_bPrintLinesFlag = true;

// 	int nLineNum = m_pMainDlg->m_pDlgPrint->m_pDlgPrintMotionControl->m_pDlgPrintMotionLinkLearn->m_vecLine.size();
// 	float fPrintLineSpeed = m_pMainDlg->m_pDlgPrint->m_pDlgPrintMotionControl->m_pDlgPrintMotionLinkLearn->m_fPrintLinesSpeed;
// 	m_P400.SetParamValue(nLineNum);
// 	m_P408.SetParamValue(fPrintLineSpeed);    //��ӡ�ٶ�
// 	m_Prog4.Run();   //��������
// 
// 	StraightLine lineTemp;
// 	for (int i = 0; i < nLineNum; i++)
// 	{
// 		lineTemp =  m_pMainDlg->m_pDlgPrint->m_pDlgPrintMotionControl->m_pDlgPrintMotionLinkLearn->m_vecLine[i];
// 		m_P401.SetParamValue(lineTemp.beginpoint.fPosX);
// 		m_P402.SetParamValue(lineTemp.beginpoint.fPosY);
// 		m_P403.SetParamValue(lineTemp.endpoint.fPosX);
// 		m_P404.SetParamValue(lineTemp.endpoint.fPosY);
// 		m_P405.SetParamValue(lineTemp.angle.fAngleA);
// 		m_P406.SetParamValue(lineTemp.angle.fAngleC);
// 		m_P407.SetParamValue(1);
// 		while (m_P407.GetParamValue() == 1)  //�ȴ�P407Ϊ0ʱcontinue
// 		{
// 			if (m_bThreadExit) break;		 //�߳��˳�
// 		}
// 	}
// 
// 	m_Prog4.Stop(); 

	m_bPrintLinesFlag = false;
}


void CProcessPrint::ExitPrintThread()
{
	//�˳���ӡ�߳�
	m_bThreadExit = true;
	ResetEvent(m_hEventPrint[0]);
	ResetEvent(m_hEventPrint[1]);
	SetEvent(m_hEventPrint[2]);
}


void CProcessPrint::PausePrint()	
{
	////�˴���������"-h"////

	if (m_bIsLinesPrint)
	{
		//ֱ�ߴ�ӡ
		//m_Prog4.Stop();   
	}
	else
	{
		//�����ӡ,����Prog
		m_bRemainDownLoadFlag = false;
	}	
}


void CProcessPrint::ContinuePrint()
{
	if (m_bIsLinesPrint)
	{
		//ֱ�ߴ�ӡ
		//m_Prog4.Run();   
	}
	else
	{
		//�����ӡ,����Prog
		m_bRemainDownLoadFlag = true;
	}	
}


void CProcessPrint::StartPrint()
{
	if (m_bIsLinesPrint)
	{
		//ֱ�ߴ�ӡ
		if (m_bPrintLinesFlag) return;
		m_bThreadExit = false;
		SetEvent(m_hEventPrint[0]); 
	}
	else
	{
		//�����ӡ,����Prog
		if (m_bDownProgFlag) return;
		////��������λ������P1P2P3����P������ֵ
		SetEvent(m_hEventPrint[1]);
	}
}


void CProcessPrint::StopPrint()
{
	if (m_bIsLinesPrint)
	{
		//ֱ�ߴ�ӡ
		m_bThreadExit = true;
	}
	else
	{
		//�����ӡ,����Prog
		m_bRemainDownLoadFlag = false;
		m_nDownLoadCount = 0;
	}
}


void CProcessPrint::DownLoadProg(vector<CString> &vecCode, int &nDownLoadCnt)
{
	m_bDownProgFlag = true;

// 	int nSize = vecCode.size();
// 	int nDownedRows = nDownLoadCnt * ROT_PROG_ROWS;		//����������
// 	int nRemainRows = nSize - nDownedRows;				//ʣ������
// 	if (nRemainRows <= 0) return;
// 
// 	CCtrlCommand cmd(0);
// 	cmd.GiveCommand("&1 OPEN ROT");						//����ת������
// 	int nDowningRows = 0;								//�������ص�����
// 
// 	if (nRemainRows > ROT_PROG_ROWS)
// 	{
// 		m_bRemainDownLoadFlag = true;
// 		nDowningRows = ROT_PROG_ROWS;
// 	}
// 	else
// 	{
// 		m_bRemainDownLoadFlag = false;
// 		nDowningRows = nRemainRows;
// 	}
// 
// 	for (int i = 0; i < nDowningRows; i++)
// 	{
// 		CString strCmd = vecCode[nDownedRows + i];
// 		cmd.GiveCommand(strCmd);
// 		if (i == ROT_PROG_ROWS/2)
// 		{
// 			cmd.GiveCommand("P101=1");
// 		}
// 	}
// 
// 	cmd.GiveCommand("CLOSE");							//�ر���ת������
// 	nDownLoadCnt++;										//���ش���,������DownLoadProg����

	m_bDownProgFlag = false;
}


void CProcessPrint::MonitorProg()
{
	if (m_bRemainDownLoadFlag)
	{
// 		if (1 == m_P409.GetParamValue())
// 		{
// 			m_P409.SetParamValue(0);
// 
// 			SetEvent(m_hEventPrint[1]);
// 		}
	}
}


void CProcessPrint::OpenGCodeFile(CString strPath)
{
	m_gcodeAnalysis.ReadGCodeFile(strPath);
}