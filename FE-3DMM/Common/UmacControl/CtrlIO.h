#pragma once
#include "PmacDevice.h"

class CCtrlIO : private CPmacDevice
{
public:
	CCtrlIO(void);
	~CCtrlIO(void);

	void ConfigIO(long card, CString name, CString descri);
	void SendCommand();
	void On();				//IO��			
	void Off();				//IO�ر�
	int GetIoState();		//��ȡIO״̬

private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;         //����
	CString		 m_strName;		  //IO��
	CString		 m_strDescri;     //IO����
	CString		 m_strCommand;	  //����
	CString		 m_strAnswer;	  //��λ����Ӧ����ֵ
};

