#pragma once
#include "PmacDevice.h"

class CCtrlPLC : private CPmacDevice
{
public:
	CCtrlPLC(void);
	~CCtrlPLC(void);


	void ConfigPLC(long card, int plcNo, CString descri);
	void SendCommand();
	void Enable();				  //ʹ��PLC
	void Disable();				  //����PLC


private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;         //����
	int 		 m_nPlcNO;		  //PLC���
	CString		 m_strDescri;     //PLC����
	CString		 m_strCommand;	  //����
};

