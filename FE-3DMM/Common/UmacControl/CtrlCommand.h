#pragma once
#include "PmacDevice.h"

class CCtrlCommand : private CPmacDevice
{
public:
	CCtrlCommand(long card = 0);
	~CCtrlCommand(void);

	void ConfigCommand(long card);
	void GiveCommand(LPCTSTR strCommand);   //����λ������ָ������

private:
	CPmacDevice  m_pmacDevice;
	long		 m_lCard;					//�����	
};

