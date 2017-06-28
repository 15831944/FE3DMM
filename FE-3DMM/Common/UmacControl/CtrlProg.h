#pragma once
#include "PmacDevice.h"

class CCtrlProg : private CPmacDevice
{
public:
	CCtrlProg(void);
	~CCtrlProg(void);

	void ConfigProg(long card, int coordNo, int progNo, CString descri);
	void SendCommand();
	void Run();					  //����
	void Stop();				  //ֹͣ

private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;         //����
	int			 m_nCoordNO;	  
	int 		 m_nProgNO;		  //�Զ��������
	CString		 m_strDescri;     //�Զ���������
	CString		 m_strCommand;	  //����
};

