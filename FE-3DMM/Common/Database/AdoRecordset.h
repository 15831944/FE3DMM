#pragma once
#include "AdoDatabase.h"

class CAdoRecordset
{
public:
	CAdoRecordset(void);
	virtual ~CAdoRecordset(void);
	
	//�򿪱�
	BOOL OpenTable(CString strTable, CAdoDatabase* pDatabase);
	//�رձ�
	void CloseTable();
	//��ȡ�ֶ�����
	long GetFieldCount();
	//��ȡ�ֶα���
	void GetFieldName(long nColIndex, CString& strName);
	//��ȡ�ֶε�ֵ
	CString GetFieldValue(long nColIndex);			//����������
	CString GetFieldValue(CString strFieldName);	//�����ֶ���
	//�����ֶε�ֵ
	void SetFieldValue(long nColIndex, CString strValue);
	void SetFieldValue(CString strFieldName, CString strValue);
	//��ü�¼��(����)
	long GetRecordCount();							

	//�α����
	void MoveFirst();
	void MoveLast();
	void MoveNext();
	void Move(long nRowIndex);	//�ƶ���ָ���ļ�¼λ��
	void MovePrevious();		//�ƶ���ǰһ����¼
	BOOL IsBOF();				//�α��Ƿ��ڼ�¼������ʼλ��
	BOOL IsEOF();				//�α��Ƿ��ڼ�¼���Ľ���λ��

	//�����¼�¼
	void AddNew();
	//���������ݿ�
	void Update();
	//ɾ����¼
	void Delete();

public:
	_RecordsetPtr m_pSet;    //����ָ��

};

