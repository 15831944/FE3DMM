#pragma once
#include "PmacDevice.h"

class CCtrlDPR : private CPmacDevice
{
public:
	CCtrlDPR(void);
	~CCtrlDPR(void);

	void ConfigDPR(long card, UINT offset, UINT bit, CString descri);
	long GetDprValue(UINT offset);           //��ȡdpr������ֵ
	void ResetDpr();						 //����dpr������ֵ
	void ResetDpr(UINT offset, UINT bit);	 //����dpr������ֵ

private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;         //����
	UINT 		 m_nOffset;	
	UINT		 m_nBit;
	CString		 m_strDescri;     //DPR����
};

