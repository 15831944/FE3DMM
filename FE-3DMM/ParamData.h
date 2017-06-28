#pragma once
#include "ParamDefine.h"

class CParamData
{
public:
	CParamData(void);
	~CParamData(void);

	Param3DMeasure* GetParam3DMeasure();		
	ParamLaserStrip* GetParamLaserStrip();			
	ParamTransfer* GetParamTransfer();				
	ParamPrint* GetParamPrint();							
	ParamCamera* GetParamCamera();

	CString ReadParam(LPCSTR lpAppName, LPCSTR lpKeyName, LPCSTR lpFileName,int paramtype,void *param);		//��ȡ����
	void WriteParam(LPCSTR lpAppName, LPCSTR lpKeyName , LPCSTR lpFileName,int paramtype,void *param);			//д����

	CString LoadMeasurePa();
	CString SaveMeasurePa();

	CString LoadLaserStripPa();
	CString SaveLaserStripPa();

	CString LoadTransferPa();
	CString SaveTransferPa();
	CString LoadTransferPa(int TransferType, int PISize);  //���غ���������תӡ��ʽ�ͣ�PI�ߴ��������
	CString SaveTransferPa(int TransferType, int PISize);  

	CString LoadPrintPa();
	CString SavePrintPa();

	CString LoadCameraPa();
	CString SaveCameraPa();

private:
	CString							m_strConfigPath;		
	Param3DMeasure		m_param3DMeasure;				//3D�������ò���
	ParamLaserStrip			m_paramLaserStrip;				//����������ò���
	ParamTransfer				m_paramTransfer;					//תӡ���ò���
	ParamPrint						m_paramPrint;							//��ӡ���ò���
	ParamCamera				m_paramCamera;						//������ò���
};

