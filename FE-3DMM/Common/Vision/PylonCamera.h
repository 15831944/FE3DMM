// PylonCamera.h: interface for the PylonCamera class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#include <pylonc/PylonC.h>
#include <pylon/PylonIncludes.h>
#pragma comment(lib, "PylonC_MD_VC120.lib")
#include "HalconCpp.h"
using namespace HalconCpp;

#define CHECK( errc ) if ( S_OK != errc ) pressEnterToExit()							//������ʾ��
#define NUM_BUFFERS 5																						//����ץͼ�����ŵ�buffer��Ŀ

class PylonCamera  
{
public:
	PylonCamera();
	virtual ~PylonCamera();
	void Init(const CString &strCamName);															//��ʼ��
	void Exit();																												//�˳�
	void StartGrab();																									//��ʼ�ɼ�
	void StopGrab();																									//ֹͣ�ɼ�	
	HObject* GetSingleLocal();																				//��ȡһ֡ͼ�����ڶ�λ
	HObject* GetSingleShow();																				//��ȡһ֡ͼ��������ʾ
	HObject* GetSingleSave();																					//��ȡһ֡ͼ�����ڴ洢

private:
	void pressEnterToExit();																						//��֪�û������˳�
	void loadCamera() ;																								//�������
	void unloadCamera() ;																							//ж�����
	void loadStreamGrabber() ;																				//����������ץȡ����																							
	void unloadStreamGrabber() ;																			//ж��������ץȡ����																											
	static UINT GrabThreadProc(LPVOID pVoid);													//�ɼ��߳�
	void GrabFunc();																									//�ɼ�����		
	void BalserToHalcon(const PylonGrabResult_t &pylonGrabRes, HObject *pHobjectImage);   //Balser->Halcon

private:
	GENAPIC_RESULT										res;														//����ִ�н�������ڴ�����֤
	CString														m_strCameraName;							//�������
	size_t															m_numDevices;								//�����Ŀ           
	BOOL															m_isOpenDev;									//����Ƿ��Ѿ���
	BOOL															m_isOpenStream;							//�Ƿ��Ѿ���������ץȡ����
    int32_t														m_payloadSize;								//ץȡ���ݵĴ�С
    unsigned char											*m_buffers[NUM_BUFFERS];			//�������ڴ�ָ��
	PYLON_DEVICE_HANDLE						m_hDev;												//���������
	PYLON_STREAMGRABBER_HANDLE	m_hGrabber;										//������ץȡ������
	PYLON_WAITOBJECT_HANDLE				m_hWait;											//����������ץȡ�����ͬ������
    PYLON_STREAMBUFFER_HANDLE		m_bufHandles[NUM_BUFFERS];	//ע������ڴ��ָ�����
    PylonGrabResult_t									m_grabResult;									//ץȡ���

	CWinThread												*m_pThread ;									//��ͼ�߳�
	HANDLE														m_hEvent[2];										//��ͼ�¼�
	CRITICAL_SECTION									m_criticalsection;								//�ٽ���,ʵ��ͼ���ͬ������
	HObject														m_hoImage;										//Halcon�洢��ͼ��
	HObject														m_hoSingleLocal;								//��֡ͼ�����ڶ�λ
	HObject														m_hoSingleShow;							//��֡ͼ��������ʾ
	HObject														m_hoSingleSave;								//��֡ͼ�����ڴ洢
};