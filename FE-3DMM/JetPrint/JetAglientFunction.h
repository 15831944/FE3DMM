#pragma once

#include <stdio.h>
#include <string.h>
#include "visa.h"

class CJetAglientFunction
{
public:
	CJetAglientFunction();
	virtual ~CJetAglientFunction();
	bool Connect();
	bool Disconnect();
	void SetDCMode(double offset = 0.0);
	void SetACMode();
	void SetOffset(double offset = 0.0);
	void SetFrequency(double freq);
	void SetAmplitude (double amp);
	void SetRatio(double dCycle);
	void SetOutput(bool isOutput);
	bool IsDeviceConnect() const;

private:
	bool				m_bIsConn;									//��ǰ�Ƿ�����
	ViSession		m_drms;											//�Ự������
	ViSession		Function_Generator_33500B;	//����������
};

