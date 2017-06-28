#include "StdAfx.h"
#include "JetHarvardPump.h"

CJetHarvardPump::CJetHarvardPump(void)
{
	m_nInfuseRate = 0;
}

CJetHarvardPump::~CJetHarvardPump(void)
{
}

/**
 *����:	��ʼ��������
 *����:	nPort		--������ռ�õĴ��ں�
 *����:	�ɹ�ΪTRUE��ʧ��ΪFALSE
**/
BOOL CJetHarvardPump::Init(const int nPort)
{
	//�򿪺ͳ�ʼ������
	if (FALSE == m_comm.Open(nPort, 115200, 8, CJetFlowPort::TwoStopBits))
	{
		return FALSE;
	}

	//����PC�����������ӣ���������ʱ����\r->����:
	m_strSend = TEXT("\r");
	m_comm.GetResponse(m_strSend, m_strReceive);
	if (m_strReceive.GetAt(1) == TEXT(':'))//ʵ�ʷ�������Ϊ"\n:"
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/**
 *����:	�����ÿ�ʼ�Զ�ע��
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::Run()
{
	m_strSend = TEXT("irun\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	�����ÿ�ʼ�����Զ�ע��
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::RunBack()
{
	m_strSend = TEXT("wrun\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	������ֹͣ�Զ�ע��
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::Stop()
{
	m_strSend = TEXT("stop\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	�������л��Զ�ע��״̬�����ֶ���������ÿ�������ϵĿ�ʼ/ֹͣ��ťЧ��һ��
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::SwitchRunAndStop()
{
	m_strSend = TEXT("run\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	���õ�ǰע������
 *����:	nRate		--������nl/min
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::SetInfuseRate( const int nRate )
{
	m_strSend.Format(TEXT("irate %d nl/min\r"), nRate);
	m_comm.GetResponse(m_strSend, m_strReceive);

	m_nInfuseRate = nRate;
	return TRUE;
}

/**
 *����:	���õ�ǰ����ע������
 *����:	nRate		--������nl/min
 *����:	ʼ��ΪTRUE������ʵ��
 **/
BOOL CJetHarvardPump::SetWithdrawRate( const int nRate )
{
	m_strSend.Format(TEXT("wrate %d nl/min\r"), nRate);
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	���õ�ǰע������Ϊ���
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::SetMaxInfuseRate()
{
	m_strSend = TEXT("irate max\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	���õ�ǰ����ע������Ϊ���
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::SetMaxWithdrawRate()
{
	m_strSend = TEXT("wrate max\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	���õ�ǰע������Ϊ��С
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::SetMinInfuseRate()
{
	m_strSend = TEXT("irate min\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	���õ�ǰ����ע������Ϊ��С
 *����:	��
 *����:	ʼ��ΪTRUE������ʵ��
**/
BOOL CJetHarvardPump::SetMinWithdrawRate()
{
	m_strSend = TEXT("wrate min\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

/**
 *����:	���ע��������ע������
 *����:	��
 *����:	����ע��������nl/min
**/
int CJetHarvardPump::GetInfuseRate()
{
	int iRate=0;

	m_strSend = TEXT("irate\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	iRate = _ttoi(m_strReceive);
	return iRate;
}

double CJetHarvardPump::GetSyringeVolume()
{
	double dbVolume = 0;
	m_strSend = TEXT("svolume\r");
	m_comm.GetResponse(m_strSend,m_strReceive);

	dbVolume = _ttof(m_strReceive);

	return dbVolume;

}

/**
 *����:	���ע��������ע������
 *����:	��
 *����:	����ע��������nl/min
**/
int CJetHarvardPump::GetWithdrawRate()
{
	int wRate=0;

	m_strSend = TEXT("wrate\r");
	m_comm.GetResponse(m_strSend, m_strReceive);

	sscanf_s(m_strReceive, TEXT("\n%d "), &wRate);//safe function
	//_stscanf(m_strReceive, TEXT("\n%d "), &wRate);
	return wRate;
}

/**
 *����:	����ע����ֱ��
 *����:	dbDiameter		--ֱ����mm,Ĭ��Ϊ4.608mm
 *����:	ʼ��ΪTRUE������ʵ��
 *˵���� ע����������ע����ֱ���������������0����Ҫ��������
**/
BOOL CJetHarvardPump::SetSyringeDiameter( const double dbDiameter/*=4.608*/ )
{
	m_strSend.Format(TEXT("diameter %f mm\r"), dbDiameter);
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

BOOL CJetHarvardPump::SetSyringeVolume(double dbVolume)
{
	m_strSend.Format(TEXT("svolume %f ul\r"), dbVolume);
	m_comm.GetResponse(m_strSend, m_strReceive);

	return TRUE;
}

void CJetHarvardPump::CloseHarvardPump()
{
	m_comm.Close();
}