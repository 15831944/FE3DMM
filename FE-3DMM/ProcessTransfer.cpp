#include "StdAfx.h"
#include "ProcessTransfer.h"
#include "FE-3DMMDlg.h"
#include "ParamData.h"


CProcessTransfer::CProcessTransfer()
	:m_BeModelLoad(false)
	,m_bStepAdjustRun(false)
{
	m_pProcessCore = NULL;
	m_pMainDlg = NULL;
}


CProcessTransfer::~CProcessTransfer(void)
{
	Release();
}


void CProcessTransfer::SetMainDlgPointer(CFE3DMMDlg* pDlg)
{
	ASSERT(pDlg);
	m_pMainDlg = pDlg;
}

void CProcessTransfer::SetParamData(CParamData* pData)
{
	ASSERT(pData);
	m_pParamData = pData;
}

void CProcessTransfer::SetProcessCore(CProcessCore* pProcesscore)
{
	ASSERT(pProcesscore);
	m_pProcessCore = pProcesscore;
}

void CProcessTransfer::SetRunMode(int Mode)
{
	if (Mode == CONTINUE)
	{
		m_RunMode = CONTINUE;
	}
	else if(Mode == STEP)
	{
		m_RunMode = STEP;
	}
	else
	{
		ASSERT(FALSE);
	}
}

void CProcessTransfer::Init()
{
	//���
	m_MotorTransferX.ConfigMotor(0,11,"תӡX");				    //���X
	m_MotorTransferZ.ConfigMotor(0,12,"תӡZ");					//���Z
	m_MotorRod11.ConfigMotor(0, 16, "�Ƹ�11"); 
	m_MotorRod12.ConfigMotor(0, 17, "�Ƹ�12");     
	m_MotorRod13.ConfigMotor(0, 18, "�Ƹ�13");     
	m_MotorRod21.ConfigMotor(0, 19, "�Ƹ�21");     
	m_MotorRod22.ConfigMotor(0, 20, "�Ƹ�22");     
	m_MotorRod23.ConfigMotor(0, 21, "�Ƹ�23");     
	m_MotorRod31.ConfigMotor(0, 22, "�Ƹ�31");     
	m_MotorRod32.ConfigMotor(0, 23, "�Ƹ�32");
	m_MotorRod33.ConfigMotor(0, 24, "�Ƹ�33"); 

#ifndef FE_DEBUG_OFFLINE
	m_MotorTransferX.Enable();
	m_MotorTransferZ.Enable();
	m_MotorRod11.Enable();
	m_MotorRod12.Enable();
	m_MotorRod13.Enable();
	m_MotorRod21.Enable();
	m_MotorRod22.Enable();
	m_MotorRod23.Enable();
	m_MotorRod31.Enable();
	m_MotorRod32.Enable();
	m_MotorRod33.Enable();
#endif

	//��λ���Զ�����
	m_prog1.ConfigProg(0, 3, 1, "תӡ�Զ�����");

	//IO
	m_IO_VacAttach.ConfigIO(0,"M7912","��װ�������");		//��װ���������on/off���أ�
	m_IO_VacBlow.ConfigIO(0,"M7913","��װ��տ���");		    //��װ��տ���
	m_IO_RodAttach.ConfigIO(0, "Mxxxx", "�Ƹ�����");
	m_IO_PickPlatform.ConfigIO(0, "Mxxx", "ʰȡƽ̨����");

	//P����
	m_P301.ConfigParam(0, "P301", "");
	m_P302.ConfigParam(0, "P302", "");		
	m_P303.ConfigParam(0, "P303", "");
	m_P304.ConfigParam(0, "P304", "");
	m_P305.ConfigParam(0, "P305", "");
	m_P306.ConfigParam(0, "P306", "");
	m_P307.ConfigParam(0, "P307", "");
	m_P308.ConfigParam(0, "P308", "");
	m_P309.ConfigParam(0, "P309", "");
	m_P310.ConfigParam(0, "P310", "");
    m_P311.ConfigParam(0, "P311", "");
	m_P312.ConfigParam(0, "P312", "");
	m_P313.ConfigParam(0, "P313", "");
	m_P314.ConfigParam(0, "P314", "");
	m_P315.ConfigParam(0, "P315", "");
	m_P316.ConfigParam(0, "P316", "");
	m_P317.ConfigParam(0, "P317", "");
	m_P318.ConfigParam(0, "P318", "");
	m_P319.ConfigParam(0, "P319", "");
	m_P320.ConfigParam(0, "P320", "");

	m_P350.ConfigParam(0, "P350", "");
	m_P351.ConfigParam(0, "P351", "");

	m_P360.ConfigParam(0, "P360", "");
	m_P361.ConfigParam(0, "P361", "");

	//��ʼ���߳�
	ThreadInit();
}

void CProcessTransfer::Release()
{

}



/***************************************************************** 
** ��������: ����תӡʵ�飬�����ⲿ���õĺ���
** ������:	 ����
** ����:        ��
** Version:1.0
****************************************************************/
void CProcessTransfer::Run()
{
	TRACE("Experiment starting...\n");

	//��ͬ�Ķ�����Ҫ���ز�ͬ��ģ�壬ֻ���ڿ�ʼ���֪��������һ��ģ��
	if (!LoadModel())
	{
		MessageBox(NULL, "ģ�����ʧ��", "��ʾ", MB_ICONWARNING);
		return;
	}
	TRACE("ģ����سɹ�");
	
	TransferPara();   //����λ�����Ͳ��ֲ���

	//����
	SetEvent(m_hTransfer[1]);
	//������ת
	SetEvent(m_hTransfer[1]);
}

/***************************************************************** 
** ��������: ֹͣתӡʵ�飬�����ⲿ���õĺ���
** ������:	 ����
** ����:        ��
** Version:1.0
****************************************************************/
BOOL CProcessTransfer::Stop()
{
	//ǿ����KILL���

	return TRUE;
}

/***************************************************************** 
** ��������: ThreadInit
** �������: ��
** ���:	     �Ƿ�ɹ�
** ��������: ��ʼ���̣߳������̣߳���ʼ���¼�
** ������:	 ����
** Version:1.0
****************************************************************/
BOOL CProcessTransfer::ThreadInit()
{
	//��ʼ����ʾ��
	m_BeModelLoad = false;

	m_hTransfer[0] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hTransfer[1] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hTransfer[2] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hTransfer[3] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hTransfer[4] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hTransfer[5] = CreateEventA(NULL, TRUE, FALSE, NULL);

	m_hVariableInquire[0] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hVariableInquire[1] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hVariableInquire[2] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hVariableInquire[3] = CreateEventA(NULL, TRUE, FALSE, NULL);

 	m_hAssist[0] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hAssist[1] = CreateEventA(NULL, TRUE, FALSE, NULL);
	m_hAssist[2] = CreateEventA(NULL, TRUE, FALSE, NULL);

	//����תӡ��ʽ�Ͷ�����ض�Ӧ���ļ�
	int iType = m_pParamData->GetParamTransfer()->TransferType;
	int iSize = m_pParamData->GetParamTransfer()->TransferSize;
	if ("" == m_pParamData->LoadTransferPa(iType, iSize))
	{
		MessageBox(NULL, _T("��������ʧ�ܣ�\n"), _T("��ʾ"), MB_OK |MB_ICONERROR);
		return FALSE;
	}

	//תӡ���߳�
	m_pInitiativeTransferThread = AfxBeginThread(InitiativeTransferThread, this);
	if (NULL == m_pInitiativeTransferThread)
	{
		return FALSE;
	}
	//������ѯ�߳�
	m_pVariableInquireThread = AfxBeginThread(VariableInquireThread, this);
	if (NULL == m_pVariableInquireThread)
	{
		return FALSE;
	}
	//�����߳�
	m_pAssistThread = AfxBeginThread(AssistThread, this);
	if (NULL == m_pAssistThread)
	{
		return FALSE;
	}

	//����תӡ�߳�
	//m_pPassitivityTransferThread = AfxBeginThread(PassitivityTransferThread, this);
	//if (NULL == m_pPassitivityTransferThread)
	//{
	//	return FALSE;
	//}

	//���������߳�
	m_pStepAdjustThread = AfxBeginThread(StepAdjustThread, this);
	if(NULL == m_pStepAdjustThread)
	{
		return FALSE;
	}

	return TRUE;
}

/***************************************************************** 
** ��������: ThreadExit
** �������: ��
** ���:	     �Ƿ�ɹ�
** ��������: �߳�ǿ���˳�
** ������:	 ����
** Version:1.0
****************************************************************/
BOOL CProcessTransfer::ThreadExit()
{	
	SetEvent(m_hTransfer[0]);
	SetEvent(m_hVariableInquire[0]);
	SetEvent(m_hAssist[0]);
	SetEvent(m_hStepAdjust[0]);
	return TRUE;
}

/***************************************************************** 
** ��������: InitiativeTransferThread
** �������: this
** ���:	     0
** ��������: ����תӡ��ʽ��ʵ�����߳�
** ������:	 ����
** Version:1.0
****************************************************************/
UINT CProcessTransfer::InitiativeTransferThread(LPVOID lParam)
{
	bool bIsRunning = true;
	CProcessTransfer* pProcessTransfer = (CProcessTransfer*)lParam;
	while (bIsRunning)
	{
		switch(WaitForMultipleObjects(4, pProcessTransfer->m_hTransfer, FALSE, INFINITE))
		{
			//�˳��߳��¼�
		case  WAIT_OBJECT_0 :
			bIsRunning = false;		
			break;
			//������λ������
		case  WAIT_OBJECT_0 + 1:
			ResetEvent(pProcessTransfer->m_hTransfer[1]);
			pProcessTransfer->Start();
			break;
		case WAIT_OBJECT_0 + 2:
			//��λ�Ƕ�
			pProcessTransfer->PickAngleLocation();
			break;
		case WAIT_OBJECT_0 + 3:
			//��λY
			pProcessTransfer->PickPosYLocation();
			break;
		case WAIT_OBJECT_0 + 4:
			//��λX
			pProcessTransfer->PickPosXLocation();
			break;
		case WAIT_OBJECT_0 + 5:
			//���������λ
			pProcessTransfer->PlaceLocation();
			break;
			//ʰȡ��λ
		default:
			break;
		}
	}
	ResetEvent(pProcessTransfer->m_hTransfer[0]);
	ASSERT(_T("the main thread exit"));
	return 0;
}


/***************************************************************** 
** ��������: PassitivityTransferThread
** �������: this
** ���:	     0
** ��������: ������ʽתӡ��תӡ�߳�
** ������:	 ����
** Version:1.0
*****************************************************************/
UINT CProcessTransfer::PassitivityTransferThread(LPVOID lParam)
{
	return 0;
}



/***************************************************************** 
** ��������: VariableInquireThread
** �������: this
** ���:	     0
** ��������: �̺߳�����������ѯ�̣߳���ѯ��λ���ı�־��
** ������:	 ����
** Version:1.0
*****************************************************************/
UINT CProcessTransfer::VariableInquireThread(LPVOID lParam)
{
	bool bRunning = true;
	CProcessTransfer* pProcessTransfer = (CProcessTransfer*)lParam;
	while (bRunning)
	{
		switch(WaitForMultipleObjects(2, pProcessTransfer->m_hVariableInquire, FALSE, INFINITE))
		{
		case WAIT_OBJECT_0:
			bRunning = false;
			break;
		case WAIT_OBJECT_0 + 1:
			if(pProcessTransfer->m_P350.GetParamValue())
			{
				ResetEvent(pProcessTransfer->m_hVariableInquire[1]);
				SetEvent(pProcessTransfer->m_hTransfer[2]);
			}
			break;
		case WAIT_OBJECT_0 +2:
			if (pProcessTransfer->m_P351.GetParamValue() && pProcessTransfer->m_P350.GetParamValue())
			{
				ResetEvent(pProcessTransfer->m_hVariableInquire[2]);
				SetEvent(pProcessTransfer->m_hAssist[2]);
			}
			break;
		case WAIT_OBJECT_0 + 3:
			if (pProcessTransfer->m_P350.GetParamValue())
			{
				ResetEvent(pProcessTransfer->m_hAssist[3]);
				SetEvent(pProcessTransfer->m_hTransfer[5]);
			}
		default:
			break;
		}
	}
	ResetEvent(pProcessTransfer->m_hVariableInquire[0]);
	ASSERT(_T("variable inquire thread exit!"));
	return 0;
}

/***************************************************************** 
** ��������: AssistThread
** �������: this
** ���:	     0
** ��������: ����תӡ�����̺߳��������������߳̿����ڼ����������ת��Ϣ
** ������:	 ����
** Version:1.0
*****************************************************************/
UINT CProcessTransfer::AssistThread(LPVOID lParam)
{
	bool bRunning = true;
	CProcessTransfer* pProcessTransfer = (CProcessTransfer*)lParam;
	while (bRunning)
	{
		switch(WaitForMultipleObjects(3, pProcessTransfer->m_hAssist, FALSE, INFINITE))
		{
		case WAIT_OBJECT_0:
			bRunning = false;
			break;
		case WAIT_OBJECT_0 + 1:
			ResetEvent(pProcessTransfer->m_hAssist[1]);
			pProcessTransfer->CalRotateInfo();
			break;
		case WAIT_OBJECT_0 + 2:
			ResetEvent(pProcessTransfer->m_hAssist[2]);
			pProcessTransfer->HandTransform();
			break;
		default:
			break;
		}
	}
	ResetEvent(pProcessTransfer->m_hAssist[0]);
	ASSERT(_T("assist thread exit!"));
	return 0;
}


void CProcessTransfer::TransferPara()
{
	//λ��
	float fParam;
	fParam = (float)m_pParamData->GetParamTransfer()->fDisPickerCamX;
	m_P301.SetParamValue(fParam);
	m_P302.SetParamValue(0.0);
	m_P303.SetParamValue(0.0);
	m_P306.SetParamValue(0.0);
	m_P307.SetParamValue(0.0);
	m_P308.SetParamValue(0.0);
	m_P309.SetParamValue(0.0);
	m_P310.SetParamValue(0.0);
}

/***************************************************************** 
** ��������: Start
** �������: ��
** ���:	     �Ƿ�ɹ�
** ��������: ʵ���ʼ����ɺ󣬿�ʼ���к����������ڲ�����
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::Start()
{
	//������λ��תӡ�Զ�����
	m_prog1.Run();
	return TRUE;
}

/***************************************************************** 
** ��������: LoadModel
** �������: ��
** ���:	     �Ƿ�ɹ�
** ��������: ����תӡ��ʽ��ת�ƶ���ͬ����ģ��ͼ��
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::LoadModel()
{
	//����תӡ�����ҵ���Ҫ���õĶ�Ӧģ��
	CString strModelName;
	//תӡ��ʽ
	if (INITIATIVE == m_pParamData->GetParamTransfer()->TransferType)
	{
		strModelName = _T("Initiative_TransCam_");
	} 
	else if(PASSITIVITY == m_pParamData->GetParamTransfer()->TransferType)
	{
		strModelName = _T("Passitivity_TransCam_");
	}
	//תӡ����
	switch(m_pParamData->GetParamTransfer()->TransferSize)
	{
	case SIZE11:
		strModelName += _T("1mm X 1mm");
		break;
	case SIZE22:
		strModelName += _T("2mm X 2mm");
		break;
	case SIZE33:
		strModelName += _T("3mm X 3mm");
		break;
	case SIZE44:
		strModelName += _T("4mm X 4mm");
		break;
	case SIZE55:
		strModelName += _T("5mm X 5mm");
		break;
	case SIZE66:
		strModelName += _T("6mm X 6mm");
		break;
	}
	CString strDebugPath = m_gAppExePath.Left(m_gAppExePath.ReverseFind('\\')+1);
	CString strFileName = strDebugPath + "Model\\Ncc";
	CString strFullName = strFileName + "\\" + strModelName;
	//Ĭ�ϲ���nccƥ�䣬����nccģ�壬�������Ը��������޸�
	//m_pProcessCore->GetCameraTransDown()->ReloadModel(strFullName);
	return TRUE;
}

/***************************************************************** 
** ��������: PickAngleLocation
** �������: ��
** ���:	     �Ƿ�ɹ�
** ��������: ʰȡǰ���нǶȶ�λ��ʵʱ�����������߽����ֶ�����
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::PickAngleLocation()
{
	//�ж�ģ���Ƿ�������
	if (m_BeModelLoad != true)
	{
		TRACE(_T("δ�ɹ�����ģ�壡"));
		//���ܴ���ģ�廹�ڼ��صĿ��ܣ��ȴ�����
		Sleep(500);
		if (m_BeModelLoad != true)
		{
			return FALSE;
		}
	}
	//�ж��Ƿ�������һ��������˽Ƕȵ���
	if (!m_BeAdjustAngle)
	{
		//����ģ��ƥ�䣬�ҵ���Ӧֵ
		//GetCameraTrans()->SingleGrab();
		//���ƥ�䶨λ
		//GetCameraTrans()->Match();
		//�����Զ�����Ϣ���ô��ڸ�����ʾ
		HWND hwnd = ((CFE3DMMDlg*)AfxGetApp()->m_pMainWnd)->m_pDlgTransfer->m_pDlgTransferManual->m_hWnd;
		SendMessageA(hwnd, WM_CHANGETIPS,1, NULL);
	}
	else
	{
		ResetEvent(m_hTransfer[2]);
		SetEvent(m_hTransfer[3]);
	}

	return TRUE;
}

BOOL CProcessTransfer::PickPosYLocation()
{
	//�ж��Ƿ�������һ���������Y�����
	if (!m_BeAdjustPosY)
	{
		//����ģ��ƥ�䣬�ҵ���Ӧֵ
		//GetCameraTrans()->SingleGrab();
		//���ƥ�䶨λ
		//GetCameraTrans()->Match();
		//�����Զ�����Ϣ���ô��ڸ�����ʾ
		HWND hwnd = ((CFE3DMMDlg*)AfxGetApp()->m_pMainWnd)->m_pDlgTransfer->m_pDlgTransferManual->m_hWnd;
		SendMessageA(hwnd, WM_CHANGETIPS,2, NULL);
	}
	else
	{
		ResetEvent(m_hTransfer[3]);
		SetEvent(m_hTransfer[4]);
	}	
	return TRUE;
}

BOOL CProcessTransfer::PickPosXLocation()
{
	ResetEvent(m_hTransfer[4]);

	//����ģ��ƥ�䣬�ҵ���Ӧֵ
	//GetCameraTrans()->SingleGrab();
	//���ƥ�䶨λ
	//GetCameraTrans()->Match();

	//����P��������λ������λ���
	float fPos = (float)(m_pParamData->GetParamTransfer()->fXPosPickPicker);
	m_P303.SetParamValue(fPos);

	Sleep(50);
	//���źű�־����0
	m_P350.SetParamValue(0);

	//�����Զ�����Ϣ���ô��ڸ�����ʾ
	HWND hwnd = ((CFE3DMMDlg*)AfxGetApp()->m_pMainWnd)->m_pDlgTransfer->m_pDlgTransferManual->m_hWnd;
	SendMessageA(hwnd, WM_CHANGETIPS,3, NULL);
	//ʰȡ�¼���λ

	return TRUE;
}

BOOL CProcessTransfer::PlaceLocation()
{
	//m_CameraUp.SingleGrab();
	//m_CameraUp.Match();
	//����λ�����ݲ���

	Sleep(50);
	//����λ��־����0
	m_P350.SetParamValue(0);
	return TRUE;
}


BOOL CProcessTransfer::CalRotateInfo()
{
	//��ʼ��
	double x = m_pParamData->GetParamTransfer()->iPlacePos.fPosX;
	double y = m_pParamData->GetParamTransfer()->iPlacePos.fPosY;
	double z = m_pParamData->GetParamTransfer()->iPlacePos.fPosA;
	m_RotateCal.SetOriginPos(x, y, z);

	//������ת����
	m_RotateCal.Rotate();

	//��������������������
	std::vector<double> tmpVec(9);
	tmpVec = m_RotateCal.GetRodDisplacement();
	m_pParamData->GetParamTransfer()->RodStransform.fRod11 = tmpVec[0];
	m_pParamData->GetParamTransfer()->RodStransform.fRod12 = tmpVec[1];
	m_pParamData->GetParamTransfer()->RodStransform.fRod13 = tmpVec[2];
	m_pParamData->GetParamTransfer()->RodStransform.fRod21 = tmpVec[3];
	m_pParamData->GetParamTransfer()->RodStransform.fRod22 = tmpVec[4];
	m_pParamData->GetParamTransfer()->RodStransform.fRod23 = tmpVec[5];
	m_pParamData->GetParamTransfer()->RodStransform.fRod31 = tmpVec[6];
	m_pParamData->GetParamTransfer()->RodStransform.fRod32 = tmpVec[7];
	m_pParamData->GetParamTransfer()->RodStransform.fRod33 = tmpVec[8];

	m_pParamData->GetParamTransfer()->fAPosPlaceFourAxle = m_RotateCal.GetRotateAngleA();
	m_pParamData->GetParamTransfer()->fBPosPlaceFourAxle = m_RotateCal.GetRotateAngleB();

	return TRUE;
}

BOOL CProcessTransfer::HandTransform()
{
	//�Ƹ˱���
	m_MotorRod11.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod11);
	m_MotorRod12.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod12);
	m_MotorRod13.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod13);
	m_MotorRod21.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod21);
	m_MotorRod22.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod22);
	m_MotorRod23.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod23);
	m_MotorRod31.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod31);
	m_MotorRod32.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod32);
	m_MotorRod33.MoveTo(m_pParamData->GetParamTransfer()->RodStransform.fRod33);
	return TRUE;
}


/***************************************************************** 
** ��������: EnableTransMotor
** �������: bool������true��ʾʹ�ܣ�FLASE��ʾ��ʹ��
** ���:	     void
** ��������: ����תӡ���ʹ��
** ������:	 ����
** Version:1.0
*****************************************************************/
void CProcessTransfer::EnableTransMotor(const bool bEnable)
{
	if (bEnable)
	{
		m_MotorTransferX.Enable();
		m_MotorTransferZ.Enable();
	}
	else
	{
		m_MotorTransferX.Disable();
		m_MotorTransferZ.Disable();
	}
}

/***************************************************************** 
** ��������: StepAdjustThread
** �������: LPVOID תӡ�������thisָ��
** ���:	     UINT
** ��������: ��������ʱ�������ǶȺ�Y���̺߳���
** ������:	 ����
** Version:1.0
*****************************************************************/
UINT CProcessTransfer::StepAdjustThread(LPVOID lParam)
{
	bool bRunning  = true;

	CProcessTransfer* pProcessTransfer = (CProcessTransfer*) lParam;

	TRACE("�������У��Ƕ���Yƫ������߳����� ");

	while(bRunning)
	{
		DWORD ret = WaitForMultipleObjects(2, pProcessTransfer->m_hStepAdjust, FALSE, INFINITE);
		switch(ret)
		{
		case 0:
			DWORD dwExitCode;
			GetExitCodeThread(pProcessTransfer->m_pStepAdjustThread->m_hThread, &dwExitCode);
			AfxEndThread(dwExitCode, TRUE);
			break;
		case 1:
			{
				//�ж�ģ���Ƿ�������
				if (pProcessTransfer->m_BeModelLoad != true)
				{
					TRACE(_T("δ�ɹ�����ģ�壡"));
					//���ܴ���ģ�廹�ڼ��صĿ��ܣ��ȴ�����
					Sleep(100);
					break;
				}

				//����ģ��ƥ�䣬�ҵ���Ӧֵ
				//pProcessTransfer->GetCameraTrans()->SingleGrab();
				//���ƥ�䶨λ
				//pProcessTransfer->GetCameraTrans()->Match();
				//�����Զ�����Ϣ���ô��ڸ�����ʾ
				HWND hwnd = ((CFE3DMMDlg*)AfxGetApp()->m_pMainWnd)->m_pDlgTransfer->m_pDlgTransferManual->m_hWnd;
				SendMessageA(hwnd, WM_CHANGETIPS,1, NULL);
				break;
			}
			
		case 2:
			{
				/*
				** ����߳��ڽǶȵ����̵߳ĺ��濪����ǰ����Ա�֤ģ���Ѿ�������ϣ��ʲ�����Ҫ
				*/
				//����ģ��ƥ�䣬�ҵ���Ӧֵ
				//pProcessTransfer->GetCameraTrans()->SingleGrab();
				//���ƥ�䶨λ
				//pProcessTransfer->GetCameraTrans()->Match();
				//�����Զ�����Ϣ���ô��ڸ�����ʾ
				HWND hwnd = ((CFE3DMMDlg*)AfxGetApp()->m_pMainWnd)->m_pDlgTransfer->m_pDlgTransferManual->m_hWnd;
				SendMessageA(hwnd, WM_CHANGETIPS,2, NULL);
				break;
			}
			
		default:
			break;
		}
	}

	return 0;
}

/***************************************************************** 
** ��������: StepRunInit
** �������: NULL
** ���:	     NULL
** ��������: ��������ʱ�����г�ʼ�������������̣߳������¼�
** ������:	 ����
** Version:1.0
*****************************************************************/
void CProcessTransfer::StepRunInit()
{
	//�����ֶ���λ�¼�
	m_hStepAdjust[0] = CreateEventA(NULL, TRUE, FALSE, NULL);   //�˳��¼�
	m_hStepAdjust[1] = CreateEventA(NULL, TRUE, FALSE, NULL);    //�Ƕȵ���
	m_hStepAdjust[2] = CreateEventA(NULL, TRUE, FALSE, NULL);    //Y�����
}



/***************************************************************** 
** ��������: StartAngleAdjust
** �������: NULL
** ���:	     BOOL
** ��������: ��������ʱ����ʼ�Ƕȵ������¼���λ
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::StartAngleAdjust()
{
	BOOL ret;

	ret = SetEvent(m_hStepAdjust[1]);

	return ret;
}



/***************************************************************** 
** ��������: EndAngleAdjust
** �������: NULL
** ���:	     BOOL
** ��������: ��������ʱ����ʼ�Ƕȵ������¼���λ
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::EndAngleAdjust()
{
	BOOL ret;

	ret = ResetEvent(m_hStepAdjust[1]);

	return ret;
}



/***************************************************************** 
** ��������: StartYAdjust
** �������: NULL
** ���:	     BOOL
** ��������: ��������ʱ����ʼ�Ƕȵ������¼���λ
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::StartYAdjust()
{
	BOOL ret;

	ret = SetEvent(m_hStepAdjust[2]);

	return ret;
}


/***************************************************************** 
** ��������: EndYAdjust
** �������: NULL
** ���:	     BOOL
** ��������: ��������ʱ����ʼ�Ƕȵ������¼���λ
** ������:	 ����
** Version:1.0
*****************************************************************/
BOOL CProcessTransfer::EndYAdjust()
{
	BOOL ret;

	ret = ResetEvent(m_hStepAdjust[2]);

	return ret;
}

