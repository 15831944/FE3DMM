#pragma once
#include "PmacDevice.h"

class CCtrlMotor : private CPmacDevice
{
public:
	CCtrlMotor(void);
	~CCtrlMotor(void);

	void ConfigMotor(long card, int motorID, CString descri);
	void SendCommand();
	void Jog(UINT nDir);		  //���Jog
	void MoveTo(double dPos);	  //���Jog��ĳλ��
	void Move(double dDis);		  //���Jogһ�ξ���
	void JogStop();				  //���ֹͣJog
	void Enable();				  //���ʹ��,ͬʱ���õ��ֹͣJog
	void Disable();				  //�������
	void Home();				  //�������
	float GetMotorPostion();	  //��õ��λ��
	void SetSpeed(double dSpeed); //���õ���ٶ�

private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;         //����
	int			 m_nMotorID;      //���ID
	CString		 m_strDescri;     //�������
	CString		 m_strCommand;	  //����
	CString		 m_strAnswer;	  //��λ����Ӧ����ֵ
};

