#pragma once
#include "PmacDevice.h"
#include "CtrlCommand.h"
#include "CtrlMotor.h"
#include "CtrlParam.h"
#include "CtrlIO.h"
#include "CtrlDPR.h"
#include "CtrlPLC.h"
#include "CtrlProg.h"

class CCtrlCard : private CPmacDevice
{
public:
	CCtrlCard(void);
	~CCtrlCard(void);

	void ConfigCard(long card);
	void ConnectPmacCard();					//����Pmac���ƿ�
	BOOL IsConnectPmac();					//�Ƿ�����Pmac
	void Save();							//�򿨷���saveָ��

private:
	CPmacDevice  m_pmacDevice;
	BOOL		 m_bConnectPmacFlag;	//����Pmac��־
	long		 m_lCard;				//�����	
};

