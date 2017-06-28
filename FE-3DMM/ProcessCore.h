#pragma once
#include "./Common/Vision/PylonCamera.h"
#include "./Common/Vision/ImageOperate.h"
#include "./Common/UmacControl/CtrlCard.h"    //by jsb
#include "Process3DMeasure.h"
#include "ProcessLaserStrip.h"
#include "ProcessTransfer.h"
#include "ProcessPrint.h"
#include "ParamData.h"
class CFE3DMMDlg;


typedef struct st_SHOWINFO
{
	CameraType  cameratype;				//��ʾ���������
	HTuple			 windowHandle;		//��ʾ��Halcon���ھ��
	Size					 windowSize;				//��ʾ���ڵĴ�С
}SHOWINFO;


class CProcessCore
{
public:
	CProcessCore(void);
	~CProcessCore(void);
	void Init();
	void Release();
	void SetMainDlgPointer(CFE3DMMDlg* pDlg);			//����������ָ��
	CProcess3DMeasure* GetPro3DMeasure();				//��ò���������ָ��
	CProcessLaserStrip* GetProLaserStrip();					//��ð��������ָ��
	CProcessTransfer* GetProTransfer();							//���תӡ������ָ��
	CProcessPrint* GetProPrint();										//��ô�ӡ������ָ��
	CParamData* GetParamData();										//��ȡ���ò�����ָ��

	PylonCamera* GetCameraLaserView();						//��ȡ����۲����ָ��
	PylonCamera* GetCameraTransUp();							//��ȡתӡ�������ָ��
	PylonCamera* GetCameraTransDown();						//��ȡתӡ�������ָ��
	PylonCamera* GetCameraPrintLoc();							//��ȡ��ӡ��λ���ָ��
	PylonCamera* GetCameraPrintHoriz();						//��ȡ��ӡˮƽ�۲����ָ��
	PylonCamera* GetCameraPrintAskant();						//��ȡ��ӡб�ӹ۲����ָ��
	void SetShowInfo(const CameraType &camtype, const HTuple &winHandle, const Size &winSize);
	SHOWINFO GetShowInfo();
	void SwitchCamera(const CameraType camtype);	//�л����

// 	CCtrlMotor* GetMotorX();											//��õ��X
// 	CCtrlMotor* GetMotorY();											//��õ��Y
// 	CCtrlMotor* GetMotorZ();											//��õ��Z
// 	CCtrlMotor* GetMotorA();										//��õ��A
// 	CCtrlMotor* GetMotorC();											//��õ��C

private:
	CFE3DMMDlg*					m_pMainDlg;						//���Ի���ָ��
	CProcess3DMeasure		m_Pro3DMeasure;				//�������������
	CProcessLaserStrip			m_ProLaserStrip;					//������������
	CProcessTransfer				m_ProTransfer;						//תӡ���������
	CProcessPrint					m_ProPrint;							//��ӡ���������
	CParamData						m_ParamData;						//���ò�������
	SHOWINFO						m_showinfo;							//Pic�ؼ���ʾ��Ϣ
	PylonCamera						m_CameraLaserView;			//����۲����
	PylonCamera						m_CameraTransUp;				//תӡ�������
	PylonCamera						m_CameraTransDown;		//תӡ�������
	PylonCamera						m_CameraPrintLoc;				//��ӡ��λ���
	PylonCamera						m_CameraPrintHoriz;			//��ӡˮƽ�۲����
	PylonCamera						m_CameraPrintAskant;		//��ӡб�ӹ۲����

//     CCtrlCard							m_umacCard;					//umac���ƿ�     //by jsb
// 	CCtrlMotor						m_MotorX;						//���X
// 	CCtrlMotor						m_MotorY;						//���Y
// 	CCtrlMotor						m_MotorZ;						//���Z
// 	CCtrlMotor						m_MotorA;						//���A
// 	CCtrlMotor						m_MotorC;						//���C

public:
	//������ص�P����
// 	CCtrlParam						m_P3006;							//���
// 	CCtrlParam						m_P3007;							//�Ƶ�
// 	CCtrlParam						m_P3008;							//�̵�
// 	CCtrlParam						m_P200;								//��ͣ������
// 	CCtrlParam						m_P2001;							//�豸����
// 	CCtrlParam						m_M130;							//X��������λ
// 	CCtrlParam						m_M131;							//X��������λ
// 	CCtrlParam						m_M132;							//Y��������λ
// 	CCtrlParam						m_M133;							//Y��������λ
// 	CCtrlParam						m_M134;							//Z��������λ
// 	CCtrlParam						m_M135;							//Z��������λ
// 	CCtrlParam						m_M136;							//A��������λ
// 	CCtrlParam						m_M137;							//A��������λ
// 	CCtrlParam						m_M138;							//C��������λ
// 	CCtrlParam						m_M139;							//C��������λ
	
};

