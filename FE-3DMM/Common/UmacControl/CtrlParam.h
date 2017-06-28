#pragma once
#include "PmacDevice.h"

class CCtrlParam : private CPmacDevice
{
public:
	CCtrlParam(void);
	~CCtrlParam(void);

	void ConfigParam(long card, CString name, CString descri);
	void SendCommand();
	void SetParamValue(float fValue);    //����P������ֵ
	long GetParamValue();				 //��ȡP������ֵ

private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;         //����
	CString		 m_strName;       //P������
	CString		 m_strDescri;     //P��������
	CString		 m_strCommand;	  //����
	CString		 m_strAnswer;	  //��λ����Ӧ����ֵ
};

