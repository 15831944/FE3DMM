#include "StdAfx.h"
#include "AdoDatabase.h"


CAdoDatabase::CAdoDatabase(void)
{
}


CAdoDatabase::~CAdoDatabase(void)
{
	Close();
}

bool CAdoDatabase::OpenMDB(CString strPath)
{
	//����Connection����
	HRESULT nRet = m_pConn.CreateInstance(/*__uuidof(Connection)*/"ADODB.Connection");
	if (FAILED(nRet))
	{
		return false;
	}

	//���ýӿں���Open��������ݿ�����
	CString strConnec;
	strConnec.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s", strPath);
	nRet = m_pConn->Open(_bstr_t(strConnec), "", "", -1);
	if (FAILED(nRet))
	{
		return false;
	}

	return true;
}

void CAdoDatabase::Close()
{
	if (NULL != m_pConn)
	{
		m_pConn->Close();
		m_pConn = NULL;
	}
}

void CAdoDatabase::ExecuteSql(CString strSql)
{
	m_pConn->Execute(_bstr_t(strSql), NULL, adCmdText);
}

bool CAdoDatabase::IsDatabaseOpen()
{
	return (NULL != m_pConn && (m_pConn->State & adStateOpen));
}