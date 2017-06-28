#include "StdAfx.h"
#include "ProcessLaserStrip.h"
#include "FE-3DMMDlg.h"
#include "ParamData.h"


CProcessLaserStrip::CProcessLaserStrip(void)
{
	m_pMainDlg = NULL;
}


CProcessLaserStrip::~CProcessLaserStrip(void)
{
	Release();
}


void CProcessLaserStrip::SetMainDlgPointer(CFE3DMMDlg* pDlg)
{
	m_pMainDlg = pDlg;
}


void CProcessLaserStrip::Init()
{

	//��ʼ������۲����
// 	m_CameraView.SetCameraInfo("GigEVision", "dianjiao");
// 	m_CameraView.SetCameraType(DISP);
// 	m_CameraView.Init();
// 	m_CameraView.StartCapture(); 

	//�����ʼ��
// 	m_MotorLaserStripX.ConfigMotor(0, 9, "�������X");
// 	m_MotorLaserStripY.ConfigMotor(0, 10, "�������Y");
// 	m_MotorLaserStripX.Enable();
// 	m_MotorLaserStripY.Enable();

// 2017.03.23 Edited By Zhoulaoboyang
	//��λ���Զ�����
	m_Prog200.ConfigProg(0,0,200,"��ɨ���Զ�����");

	//P����
	m_P200.ConfigParam(0,"P200","��������־");
	m_P201.ConfigParam(0,"P201","ɨ�賤��L");
	m_P202.ConfigParam(0,"P202","ɨ����D");
	m_P203.ConfigParam(0,"P203","ɨ���ٶ�Vl");
	m_P204.ConfigParam(0,"P204","�����ٶ�Vd");
	m_P205.ConfigParam(0,"P205","ɨ������");
//
}


void CProcessLaserStrip::Release()
{

}


void CProcessLaserStrip::Home()
{
// 	m_MotorLaserStripX.Home();
// 	m_MotorLaserStripY.Home();
}


//2017.03.23 Edited By Zhoulaoboyang
void CProcessLaserStrip::TransferPara(double ScanLen,double ScanSpace,double ScanSpeed,double TransRowSpeed,int ScanNum)
{
	m_P201.SetParamValue(ScanLen);
	m_P202.SetParamValue(ScanSpace);
	m_P203.SetParamValue(ScanSpeed);
	m_P204.SetParamValue(TransRowSpeed);
	m_P205.SetParamValue(ScanNum);
}

bool CProcessLaserStrip::GetProgStatus()
{
	if(m_P200.GetParamValue() == 0)
		return FALSE;
	else 
		return TRUE;
}

void CProcessLaserStrip::RunProgram()
{
	m_Prog200.Run();
}

void CProcessLaserStrip::SetParamData(CParamData* pData)
{
	m_pParamData = pData;
}


// CCtrlMotor* CProcessLaserStrip::GetMotorLaserStripX()
// {
// 	return &m_MotorLaserStripX;
// }


// CCtrlMotor* CProcessLaserStrip::GetMotorLaserStripY()
// {
// 	return &m_MotorLaserStripY;
// }

