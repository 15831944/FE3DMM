#pragma once
class CAdoDatabase
{
public:
	CAdoDatabase(void);
	virtual ~CAdoDatabase(void);

	//�����ݿ�
	bool OpenMDB(CString strPath);	
	//�ر����ݿ�
	void Close();

	//ִ��Sql��䣬ͨ���ú����������ݿ�
	void ExecuteSql(CString strSql);

	//�ж����ݿ��Ƿ��(����)
	bool IsDatabaseOpen();

public:
	_ConnectionPtr m_pConn;  //����ָ��

};

