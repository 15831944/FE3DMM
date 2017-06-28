
#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using std::vector;
using std::string;


// �������;�����
template <typename Object>
class CMATRIX
{
public:
	explicit CMATRIX() : array( 0 ) {}

	CMATRIX( int rows, int cols):array( rows )
	{
		for( int i = 0; i < rows; ++i )
		{
			array[i].resize( cols );
		}
	}

	CMATRIX( const CMATRIX<Object>& m ){ *this = m;}

	void resize( int rows, int cols );                         // �ı䵱ǰ�����С
	bool push_back( const vector<Object>& v );   // �ھ���ĩβ���һ������
	void swap_row( int row1, int row2 );                // �������е�����

	int  rows() const{ return array.size(); }
	int  cols() const { return rows() ? (array[0].size()) : 0; }
	bool empty() const { return rows() == 0; }        // �Ƿ�Ϊ��
	bool square() const { return (!(empty()) && rows() == cols()); }  // �Ƿ�Ϊ����


	const vector<Object>& operator[](int row) const { return array[row]; } //[]���������� 
	vector<Object>& operator[](int row){ return array[row]; }

protected:
	vector< vector<Object> > array;
};

// �ı䵱ǰ�����С
template <typename Object>
void CMATRIX<Object>::resize( int rows, int cols )
{
	int rs = this->rows();
	int cs = this->cols();

	if ( rows == rs && cols == cs )
	{
		return;
	}
	else if ( rows == rs && cols != cs )
	{
		for ( int i = 0; i < rows; ++i )
		{
			array[i].resize( cols );
		}
	}
	else if ( rows != rs && cols == cs )
	{
		array.resize( rows );
		for ( int i = rs; i < rows; ++i )
		{
			array[i].resize( cols );
		}
	}
	else
	{
		array.resize( rows );
		for ( int i = 0; i < rows; ++i )
		{
			array[i].resize( cols );
		}
	}
}

// �ھ���ĩβ���һ��
template <typename Object>
bool CMATRIX<Object>::push_back( const vector<Object>& v )
{
	if ( rows() == 0 || cols() == (int)v.size() )
	{
		array.push_back( v );
	}
	else
	{
		return false;
	}

	return true;
}

// ��������
template <typename Object>
void CMATRIX<Object>::swap_row( int row1, int row2 )
{
	if ( row1 != row2 && row1 >=0 &&
		row1 < rows() && row2 >= 0 && row2 < rows() )
	{
		vector<Object>& v1 = array[row1];
		vector<Object>& v2 = array[row2];
		vector<Object> tmp = v1;
		v1 = v2;
		v2 = tmp;
	}
}

// ����ת��
template <typename Object>
const CMATRIX<Object> trans( const CMATRIX<Object>& m )
{
	CMATRIX<Object> ret;
	if ( m.empty() ) return ret;

	int row = m.cols();
	int col = m.rows();
	ret.resize( row, col );

	for ( int i = 0; i < row; ++i )
	{
		for ( int j = 0; j < col; ++j )
		{
			ret[i][j] = m[j][i];
		}
	}

	return ret;
}

//////////////////////////////////////////////////////////
// double���;����࣬���ڿ�ѧ����
// �̳���CMATRIX��
// ʵ�ֳ��ò��������أ���ʵ�ּ�����������ʽ�����Լ�LU�ֽ�
class CMatrix:public CMATRIX<double>
{
public:
	CMatrix():CMATRIX<double>(){}
	CMatrix( int c, int r ):CMATRIX<double>(c,r){}
	CMatrix( const CMatrix& m){ *this  = m; }

	const CMatrix& operator+=( const CMatrix& m );
	const CMatrix& operator-=( const CMatrix& m );
	const CMatrix& operator*=( const CMatrix& m );
};

bool  operator==( const CMatrix& lhs, const CMatrix& rhs );        // ���ز�����==
bool  operator!=( const CMatrix& lhs, const CMatrix& rhs );        // ���ز�����!=
const CMatrix operator+( const CMatrix& lhs, const CMatrix& rhs );  // ���ز�����+
const CMatrix operator-( const CMatrix& lhs, const CMatrix& rhs );  // ���ز�����-
const CMatrix operator*( const CMatrix& lhs, const CMatrix& rhs );  // ���ز�����*

const CMatrix abs( const CMatrix& m );                             // ��������Ԫ�صľ���ֵ
const CMatrix trans( const CMatrix& m );                           // ����ת�þ���
const CMatrix submatrix(const CMatrix& m,int rb,int re,int cb,int ce);  // �����Ӿ���
#endif

