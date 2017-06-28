// PylonCamera.cpp: implementation of the PylonCamera class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PylonCamera.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PylonCamera::PylonCamera()
{
	m_isOpenDev			= FALSE ;
	m_isOpenStream		= FALSE ;
	m_strCameraName	= "";
	m_numDevices			= 0;
	m_hDev						= NULL;

	m_pThread				= NULL;
	InitializeCriticalSection(&m_criticalsection);
}


PylonCamera::~PylonCamera()
{
	DeleteCriticalSection(&m_criticalsection);
}


/************************************************************************/
/*����:��֪�û����������󣬼����رճ���,��ǿ�����Ѻ���
**ʱ��:2012.5.5
**����:����@1.0*/
/************************************************************************/
void PylonCamera::pressEnterToExit()
{
	::MessageBox(NULL, TEXT("Pylon�������,�����رճ���\n��<ȷ��>�رճ���"), TEXT("�������"), MB_OK) ;
	
	//���Ǵ�ץȡͼ��������ȹر�
	if (TRUE == m_isOpenStream)
	{
		unloadStreamGrabber() ;
	}

	//�����豸��ر�
	if (TRUE == m_isOpenDev)
	{
		PylonDeviceClose(m_hDev) ;
		PylonTerminate();
	}

	exit(EXIT_FAILURE);
}


/************************************************************************/
/*����:�������, ʹ�����ǰ������øú���
**����:��
**ʱ��:2012.5.5
**����:����@1.0
**�޸�:����@1.1��2016.10  **** �޸�:by jiang 2017/3 */
/************************************************************************/
void PylonCamera::loadCamera()
{
	/************************************************************************/
	/*���������*/
	/************************************************************************/
    //����Pylon�ķ���ǰ��Ҫ����Pylon�Ķ�̬���п�
    PylonInitialize(); 

    //������е�����������ڴ����������ǰ���øú���
	res = PylonEnumerateDevices( &m_numDevices );
	CHECK(res);
	if ( 0 == m_numDevices )
	{
		::MessageBox(NULL, TEXT("û�з����κ�����豸"), TEXT("����"), MB_OK) ;
		//�˳�����
		//pressEnterToExit();
	}

	if (FALSE == m_isOpenDev)
	{
		//����������󣬸�����������жϴ��ĸ����
		for (size_t i = 0; i < m_numDevices; i++)
		{
			PylonDeviceInfo_t Pdi;		//�����Ϣ�ṹ��
			PylonGetDeviceInfo(i, &Pdi);
			if (Pdi.FriendlyName == m_strCameraName)
			{
				res = PylonCreateDeviceByIndex( i, &m_hDev );
				CHECK(res);
				break;
			}
		}
		
		if (NULL != m_hDev)
		{
			//���������
			res = PylonDeviceOpen( m_hDev, PYLONC_ACCESS_MODE_CONTROL | PYLONC_ACCESS_MODE_STREAM );
			CHECK(res);
			m_isOpenDev = TRUE ;
		}
		else
		{
			::MessageBox(NULL, TEXT("�����û�б���⵽, �����������"), TEXT("����"), MB_OK) ;
			//�˳�����
			//pressEnterToExit();
		}
	}
}


/************************************************************************/
/*����:ж�������ʹ�������������øú���
**ʱ��:2012.5.5
**����:����@1.0*/
/************************************************************************/
void PylonCamera::unloadCamera()
{	
	//���Ǵ�ץȡͼ��������ȹر�
	if (TRUE == m_isOpenStream)
	{
		unloadStreamGrabber() ;
	}
	
	/************************************************************************/
	/*�ر����*/
	/************************************************************************/
	if (TRUE == m_isOpenDev)
	{
		//�ر��������
		res = PylonDeviceClose( m_hDev );
		//CHECK(res);
		m_isOpenDev = FALSE ;
		
		//�����������
		res = PylonDestroyDevice ( m_hDev );
		//CHECK(res);
		
		//�ͷŶ�̬ϵͳ��Դ
		PylonTerminate(); 
	}
}


/************************************************************************/
/*����:����ͼ��ץȡ����ץͼǰ������øú���
**ʱ��:2012.5.5
**����:����@1.0*/
/************************************************************************/
void PylonCamera::loadStreamGrabber()
{
	/************************************************************************/
	/*��������ץȡ����(Stream Grabber)*/
	/************************************************************************/
	//��ȡ������֧�ֵ�stream��Ŀ, һ����������ж����ͬ��ץȡͨ��
	UINT nStreams ;
	res = PylonDeviceGetNumStreamGrabberChannels( m_hDev, &nStreams );
	CHECK(res);
	if ( nStreams < 1 )
	{
		::MessageBox(NULL, TEXT("��������֧������������ɼ�"), TEXT("����"), MB_OK) ;

		return ;
	}

	if (FALSE == m_isOpenStream)
	{
		//��úʹ�stream grab����Ĭ�ϵĵ�һ��ͨ����
		res = PylonDeviceGetStreamGrabber( m_hDev, 0, &m_hGrabber );
		CHECK(res);
		res = PylonStreamGrabberOpen( m_hGrabber );
		CHECK(res);
		m_isOpenStream = TRUE ;
		
		//��ȡ����ͬ����wait object�������ڵȴ�buffers������
		res = PylonStreamGrabberGetWaitObject( m_hGrabber, &m_hWait );
		CHECK(res);
	}
	else
	{
		::MessageBox(NULL, TEXT("������ץȡ�����Ѿ���"), TEXT("����"), MB_OK) ;
		return ;
	}

	/************************************************************************/
	/*������ץȡ����(Stream Grabber)ץͼ��Դ׼��*/
	/************************************************************************/
	//���ò�ͼ����
	res = PylonDeviceGetIntegerFeatureInt32( m_hDev,"PayloadSize",&m_payloadSize ); //��òɼ�оƬ���ش�С
	CHECK(res) ;
	PylonStreamGrabberSetMaxBufferSize(m_hGrabber, m_payloadSize );							 //����ͼ������Ŀ
	PylonStreamGrabberSetMaxNumBuffer( m_hGrabber, NUM_BUFFERS );						 //����ͼbuffer��Ŀ
	
	//�����ͼ�ڴ�
	UINT i ;
	for ( i = 0; i < NUM_BUFFERS; ++i )
	{
		m_buffers[i] = new unsigned char[m_payloadSize];
		if ( NULL == m_buffers[i] )
		{
			::MessageBox(NULL, TEXT("�����ͼ�ڴ�ʱ���ڴ治��"), TEXT("����"), MB_OK);
		}
	}
	
	//�����ͼҪ����Դ���˺�������������ٸ���,ֱ��FinishGrab()
	PylonStreamGrabberPrepareGrab( m_hGrabber );							
	
	//buffer����ע��������ڲ�ͼ��ÿ��buffer�����ض�Ӧ�ľ��
	for ( i = 0; i < NUM_BUFFERS; ++i )
	{
		res = PylonStreamGrabberRegisterBuffer( m_hGrabber, m_buffers[i], 
			m_payloadSize, &m_bufHandles[i] );
	}
	
	//��buffer���η����ͼ����, ��ʱ��û�п�ʼ�ɼ�
	//buffer�������������ֶ��У�׼�����ڲɼ���buffer����������У��ɼ���ɵ�buffer����������С�
	for ( i = 0; i < NUM_BUFFERS; ++i )
	{
		res = PylonStreamGrabberQueueBuffer( m_hGrabber, m_bufHandles[i], (void *) i );
	}
}


/************************************************************************/
/*����:ж��ͼ��ץȡ����ץͼ�������øú���
**ʱ��:2012.5.5
**����:����@1.0*/
/************************************************************************/
void PylonCamera::unloadStreamGrabber()
{
	if (TRUE == m_isOpenStream)
	{
		/************************************************************************/
		/*������ץȡ����(Stream Grabber)ץͼ��Դ�ͷ�*/
		/************************************************************************/
		//��֤����buffer��λ�����������
		res = PylonStreamGrabberCancelGrab( m_hGrabber );
		//CHECK(res);
		
		//����������ϵ�����ȫ��ȡ��
		bool isReady ;
		do 
		{
			res = PylonStreamGrabberRetrieveResult( m_hGrabber, &m_grabResult, &isReady );
			//CHECK(res);
		} while ( isReady && (res == S_OK));
		
		//ȡ��buffer��ע��
		UINT i ;
		for ( i = 0; i < NUM_BUFFERS; ++i )   
		{
			res = PylonStreamGrabberDeregisterBuffer( m_hGrabber, m_bufHandles[i] );
			//CHECK(res);
			free( m_buffers[i] );
		}
		
		//�ͷ���ص���Դ,�˺�����Ӱ��payloadsize�Ĳ���(��AOI�Ŀ�Ⱥ͸߶�)�����������Ը���
		res = PylonStreamGrabberFinishGrab( m_hGrabber );
		//CHECK(res);
		
		/************************************************************************/
		/*�ر�������ץȡ����(Stream Grabber)*/
		/************************************************************************/
		PylonStreamGrabberClose(m_hGrabber) ;
		//CHECK(res);
		m_isOpenStream = FALSE ;
	}
}


/************************************************************************/
/*����:��basler�ɼ���ͼ��ת��Ϊhalcon��ͼ������ָ��
**ʱ��:2016.10
**����:����@1.0   �޸�:by jiang 2017/3*/
/************************************************************************/
void PylonCamera::BalserToHalcon(const PylonGrabResult_t &pylonGrabRes, HObject *pHobjectImage)
{
	ASSERT(pylonGrabRes.pBuffer);
	HTuple hv_Error, hv_ErrorText;
	try
	{
		hv_Error = 2;
		GenImage1(pHobjectImage, "byte", (HTuple)pylonGrabRes.SizeX, 
			(HTuple)pylonGrabRes.SizeY, (Hlong)((unsigned char *)pylonGrabRes.pBuffer));	
	}
	catch(HalconCpp::HException e)
	{
		hv_Error = (int)e.ErrorCode();
		int errnotmp = hv_Error;
		hv_ErrorText  = e.ErrorMessage();
		CString strtmp = hv_ErrorText.ToString();
		strtmp = "תΪhalconͼ��ʧ��: "+strtmp;
		::MessageBox(NULL, strtmp, TEXT("�쳣"), MB_OK) ;
	}
}


void PylonCamera::Init(const CString &strCamName)
{
	m_strCameraName = strCamName; 
	loadCamera();

	m_pThread = AfxBeginThread(GrabThreadProc, this);
	ASSERT(m_pThread);
	
	m_hEvent[0] = CreateEventA(NULL, TRUE, FALSE, NULL);    //�ɼ��¼�
	m_hEvent[1] = CreateEventA(NULL, TRUE, FALSE, NULL);    //�߳��˳��¼�
}


void PylonCamera::Exit()
{
	ResetEvent(m_hEvent[0]);
	SetEvent(m_hEvent[1]);
	Sleep(200);     //�ȴ���ͼ�߳��˳�

	unloadCamera();
}


UINT PylonCamera::GrabThreadProc(LPVOID pVoid)
{
	PylonCamera* pThis = (PylonCamera*)pVoid;
	pThis->GrabFunc();
	return 0;	
}


void PylonCamera::GrabFunc()
{
	//���вɼ�ǰ��׼������
	if (TRUE == m_isOpenStream)
	{
		res = PylonDeviceExecuteCommandFeature( m_hDev, "AcquisitionStop") ;	//ֹͣ��ͼ
		CHECK(res) ;
	}
	else
	{
		loadStreamGrabber() ;
	}

	res = PylonDeviceFeatureFromString( m_hDev, "AcquisitionMode", "Continuous" );	 //�ɼ�ģʽΪ"����"
	CHECK(res) ;

	res = PylonDeviceExecuteCommandFeature( m_hDev, "AcquisitionStart") ;	 //����������ͼģʽ
	CHECK(res) ;

	bool isReady;	 //��ʱ��ʶ����

	while (1)
	{
		switch(WaitForMultipleObjects(2, m_hEvent, FALSE, INFINITE))
		{
		case WAIT_OBJECT_0:
			//ResetEvent(m_hEvent[0]);
			if (TRUE == m_isOpenStream)
			{
				int bufferIndex;														//buffer��־

				//�ȴ���һ��buffer�����
				res = PylonWaitObjectWait( m_hWait, 2000, &isReady );
				if (GENAPI_E_OK == res && !isReady )
				{	//��ʱ
					::MessageBox(NULL, TEXT("�ɼ���ʱ���˳��ɼ�"), TEXT("��ʱ"), MB_OK) ;
					break; //ֹͣ�ɼ�
				}
				//CHECK(res) ;

				//�����Ϻ��ȡ�ɼ����
				res = PylonStreamGrabberRetrieveResult( m_hGrabber, &m_grabResult, &isReady );
				if (GENAPI_E_OK == res && !isReady )
				{
					::MessageBox(NULL, TEXT("��ȡ�ɼ������ʱ���˳��ɼ�"), TEXT("��ʱ"), MB_OK) ;
					break;
				}
				//CHECK(res) ;

				//��ǰץȡ�ɹ����������ʾ
				if ( (m_grabResult.Status == Grabbed))
				{	
					EnterCriticalSection(&m_criticalsection);
					BalserToHalcon(m_grabResult, &m_hoImage);	
					LeaveCriticalSection(&m_criticalsection);
				}

				//��ʾ�꣬��buffer���·Żض������ڽ��ղ�ͼ���
				//��ȡ��ǰbuffer
				bufferIndex = (int) m_grabResult.Context;
				res = PylonStreamGrabberQueueBuffer( m_hGrabber, m_grabResult.hBuffer, (void*) bufferIndex );
			}	
			continue;

		case WAIT_OBJECT_0+1:
			ResetEvent(m_hEvent[1]);
			// ֹͣ�ɼ� 
			res = PylonDeviceExecuteCommandFeature(m_hDev, "AcquisitionStop");
			//CHECK(res);
			DWORD dwExitCode;
			GetExitCodeThread(m_pThread->m_hThread, &dwExitCode);
			AfxEndThread(dwExitCode, TRUE);
			break;
		}
	}
}


void PylonCamera::StartGrab()
{
	SetEvent(m_hEvent[0]);
}


void PylonCamera::StopGrab()
{
	ResetEvent(m_hEvent[0]);
}


HObject* PylonCamera::GetSingleLocal()
{
	EnterCriticalSection(&m_criticalsection);
	if (m_hoImage.IsInitialized())
	{
			CopyImage(m_hoImage, &m_hoSingleLocal);
	}
	LeaveCriticalSection(&m_criticalsection);
	return &m_hoSingleLocal;
}


HObject* PylonCamera::GetSingleShow()
{
	EnterCriticalSection(&m_criticalsection);
	if (m_hoImage.IsInitialized())
	{
		CopyImage(m_hoImage, &m_hoSingleShow);
	}
	LeaveCriticalSection(&m_criticalsection);
	return &m_hoSingleShow;
}


HObject* PylonCamera::GetSingleSave()
{
	EnterCriticalSection(&m_criticalsection);
	if (m_hoImage.IsInitialized())
	{
		CopyImage(m_hoImage, &m_hoSingleSave);
	}
	LeaveCriticalSection(&m_criticalsection);
	return &m_hoSingleSave;
}
