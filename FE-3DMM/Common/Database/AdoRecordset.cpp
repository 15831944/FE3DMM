#include "StdAfx.h"
#include "AdoRecordset.h"


CAdoRecordset::CAdoRecordset(void)
{
}


CAdoRecordset::~CAdoRecordset(void)
{
	CloseTable();
}

BOOL CAdoRecordset::OpenTable(CString strTable, CAdoDatabase* pDatabase)
{
	//����Recordset����
	HRESULT nRet = m_pSet.CreateInstance(__uuidof(Recordset));
	if (FAILED(nRet))
	{
		return FALSE;
	}

	//���ýӿں���Open�򿪱�
	nRet = m_pSet->Open(_variant_t(strTable),	//����
		(IDispatch*)pDatabase->m_pConn,			//�����
		adOpenKeyset, adLockOptimistic, adCmdTable);
	if (FAILED(nRet))
	{
		return FALSE;
	}

	return TRUE;
}

void CAdoRecordset::CloseTable()
{
	if (NULL != m_pSet)
	{
		m_pSet->Close();
		m_pSet = NULL;
	}
}

long CAdoRecordset::GetFieldCount()
{
	return m_pSet->Fields->GetCount();
}

void CAdoRecordset::GetFieldName(long nColIndex, CString& strName)
{
	strName = (LPSTR)m_pSet->Fields->GetItem(nColIndex)->GetName();
}

CString CAdoRecordset::GetFieldValue(long nColIndex)
{
	CString strValue;
	_variant_t varValue = m_pSet->Fields->GetItem(nColIndex)->Value;
	if (VT_NULL == varValue.vt)
	{
		strValue = "";    
	}
	else
	{
		strValue = (LPSTR)(_bstr_t)varValue;
	}

	return strValue;
}

CString CAdoRecordset::GetFieldValue(CString strFieldName)
{
	CString strValue;
	_variant_t varValue = m_pSet->Fields->GetItem((_variant_t)strFieldName)->Value;
	if (VT_NULL == varValue.vt)
	{
		strValue = "";    
	}
	else
	{
		strValue = (LPSTR)(_bstr_t)varValue;
	}

	return strValue;
}

void CAdoRecordset::SetFieldValue(long nColIndex, CString strValue)
{
	m_pSet->Fields->GetItem(nColIndex)->Value = (_variant_t)strValue;
}

void CAdoRecordset::SetFieldValue(CString strFieldName, CString strValue)
{
	m_pSet->Fields->GetItem((_variant_t)strFieldName)->Value = (_variant_t)strValue;
}

long CAdoRecordset::GetRecordCount()
{
	long nRows = 0;
	if (IsBOF() && IsEOF())
	{
		return nRows;
	}

	m_pSet->MoveLast();
	nRows = m_pSet->GetRecordCount();
	return nRows;
}

void CAdoRecordset::MoveFirst()
{
	m_pSet->MoveFirst();
}

void CAdoRecordset::MoveLast()
{
	m_pSet->MoveLast();
}

void CAdoRecordset::MoveNext()
{
	m_pSet->MoveNext();
}

void CAdoRecordset::Move(long nRowIndex)
{
	m_pSet->Move(nRowIndex, (long)adBookmarkFirst);
}

void CAdoRecordset::MovePrevious()
{
	m_pSet->MovePrevious();
}

BOOL CAdoRecordset::IsBOF()
{
	return m_pSet->BOF;
}

BOOL CAdoRecordset::IsEOF()
{
	return m_pSet->adoEOF;
}

void CAdoRecordset::AddNew()
{
	m_pSet->AddNew();
}

void CAdoRecordset::Update()
{
	m_pSet->Update();
}

void CAdoRecordset::Delete()
{
	//ɾ���α굱ǰ������
	m_pSet->Delete(adAffectCurrent);  
}

