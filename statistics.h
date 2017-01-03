/*
�ļ���statics.h
���ݣ����ͳ�ƹ��������к��������� words ��� keywords �����ͳ��
*/

#ifndef STATICS_H_INCLUDED
#define STATICS_H_INCLUDED

#include "io.h"
#include <iostream>
#include <fstream>
#include"exceptions.h"
using namespace std;

void save_essay(words& w);
void save_cpp(key_words &k);

/*
������File_txt
������������ ifstream& in ����� ofstream& out
���ܣ�ʵ�ֵ��� txt �ļ���ͳ�ƣ����������ж�ȡ��������������
*/
void File_txt(ifstream &in, ofstream &out, int way)
{
	words w(in);
	if (way == 9) w.print_all(out);
	else w.print(way, out);
	return;
}

/*
������File_cpp
������������ ifstream& in ����� ofstream& out
���ܣ�ʵ�ֵ��� cpp �ļ���ͳ�ƣ����������ж�ȡ��������������
*/
void File_cpp(ifstream &in, ofstream &out, int way)
{
	key_words k(in);
	if (way == 5)
		k.print_all(out);
	else k.print(way, out);
	return;
}

/*
������essay
���ܣ���Ӧ main �����е� order = 2
	ͳ�Ƶ����ı��ļ��У�Ӣ�ĵ��ʵĴ�Ƶ
*/
void essay()
{
	ifstream in;
	char path[100];
	int order;
	cout << "�������ļ�·��:";
	cin >> path;
	in.open(path);
	if (!in)
	{
		throw(pathError());
	}	
	words w(in);
	cout << "ͳ�����\n";
	while (1)
	{
		try {
			cout << "-------------------------------\n";
			cout << "������ͳ�ƽ���鿴��ʽ\n";
			cout << "1.���ִ�Сд�������ֵ���˳��\n";
			cout << "2.���ִ�Сд�������ֵ�������\n";
			cout << "3.���ִ�Сд�����մ�Ƶ������\n";
			cout << "4.���ִ�Сд�����մ�Ƶ����\n";
			cout << "5.�����ִ�Сд�������ֵ���˳��\n";
			cout << "6.�����ִ�Сд�������ֵ�������\n";
			cout << "7.�����ִ�Сд�����մ�Ƶ������\n";
			cout << "8.�����ִ�Сд�����մ�Ƶ����\n";
			cout << "9.����\n";
			cout << "10.������\n";
			cin >> order;
			if (order <= 8 && order >= 1)
			{
				w.print(order, cout);
			}
			else if (order == 9)
				break;
			else if (order == 10)
			{
				save_essay(w);
			}
			else
				throw(orderError());
		}
		catch (orderError)
		{
			cout << "��������ȷ��ָ��\n";
		}
		catch (pathError)
		{
			cout << "·������ʧ��\n";
		}
	}
	return;
}

/*
������prog
���ܣ���Ӧ main �����е� order = 3
	ͳ�Ƶ����ı��ļ��У�c++�ؼ��ʴ�Ƶ
*/
void prog()
{
	ifstream in;
	char path[100];
	int order;
	cout << "�������ļ�·��:";
	cin >> path;
	in.open(path);
	
	if (!in)
	{
		throw pathError();
	}
	
	key_words w(in);
	cout << "ͳ�����\n";
	while (1)
	{
		try {
			cout << "-------------------------------\n";
			cout << "������ͳ�ƽ���鿴��ʽ\n";
			cout << "1.�����ֵ���˳��\n";
			cout << "2.�����ֵ�������\n";
			cout << "3.���մ�Ƶ������\n";
			cout << "4.���մ�Ƶ����\n";
			cout << "5.����\n";
			cout << "6.������\n";
			cin >> order;
			if (order <= 4 && order >= 1)
			{
				w.print(order, cout);
			}
			else if (order == 5)
				break;
			else if (order == 6)
				save_cpp(w);
			else
				throw(orderError());
		}
		catch (orderError)
		{
			cout << "��������ȷָ��\n";
		}
		catch (pathError)
		{
			cout << "·������ʧ��\n";
		}
	}
	return;
}

/*
������Folder
���ܣ�ʵ��ͳ�������ļ��������е� txt �� cpp �ļ������ҽ���������� txt �ļ���
	�������ļ����д��� statics_res �ļ���
	�������н�������ļ�����
	ÿ���ļ���Ӧ��ͳ�ƽ���ļ�����ԭ���ļ�����ͬ
*/
#define inPath string(inFolder).append("\\").append(FileInfo.name)
#define outPath string(inFolder).append("\\statics_res").append("\\").append(FileInfo.name)
void Folder()
{
	int order;
	char inFolder[200];		//�ļ�����
	ifstream in;			//ÿ���ļ�ʹ�õ�������
	ofstream out;			//ÿ���ļ�ʹ�õ������
	cout << "-------------------------------\n";
	cout << "�����ļ���·��:\n";
	cin >> inFolder;
	long Handle;
	struct _finddata_t FileInfo;		//�����ļ���Ϣ
	string outFolder(string(inFolder).append("\\statics_res"));	//����ļ�����·��
	cout << "ͳ�ƽ�����������ļ���" << outFolder << endl;
	//system(string("rd/s/q ").append(outFolder).c_str());
	system(string("md ").append(outFolder).c_str());

	//��txt�ļ�����ͳ��
	if ((Handle = _findfirst(string(inFolder).append("\\*.txt").c_str(), &FileInfo)) == -1L)
	{
		cout <<"û���ҵ� txt �ļ�\n";
	}
	else
	{
		cout << "-------------------------------\n";
		cout << "���ļ����ڵ�txt�ļ�������������ʽ��\n";
		cout << "1.���ִ�Сд�������ֵ���˳��\n";
		cout << "2.���ִ�Сд�������ֵ�������\n";
		cout << "3.���ִ�Сд�����մ�Ƶ������\n";
		cout << "4.���ִ�Сд�����մ�Ƶ����\n";
		cout << "5.�����ִ�Сд�������ֵ���˳��\n";
		cout << "6.�����ִ�Сд�������ֵ�������\n";
		cout << "7.�����ִ�Сд�����մ�Ƶ������\n";
		cout << "8.�����ִ�Сд�����մ�Ƶ����\n";
		cout << "9.�������� (����ָ�Ĭ�������������)\n";
		cin >> order;
		if (order > 9 || order < 1) order = 9;
		in.open(inPath);
		out.open(outPath);
		File_txt(in, out, order);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			in.close(); out.close();
			in.open(inPath);
			out.open(outPath);
			File_txt(in, out, order);
		}
		in.close(); out.close();
		_findclose(Handle);
	}

	//��cpp�ļ�����ͳ��
	if ((Handle = _findfirst(string(inFolder).append("\\*.cpp").c_str(), &FileInfo)) == -1L)
	{
		cout << "û���ҵ� cpp �ļ�\n";
		return;
	}
	else
	{
		cout << "-------------------------------\n";
		cout << "���ļ����ڵ�cpp�ļ�������������ʽ��\n";
		cout << "1.�����ֵ���˳��\n";
		cout << "2.�����ֵ�������\n";
		cout << "3.���մ�Ƶ������\n";
		cout << "4.���մ�Ƶ����\n";
		cout << "5.�������� (����ָ�Ĭ�������������)\n";
		cin >> order;
		if (order > 5 || order < 1) order = 5;
		in.open(inPath);
		out.open(outPath);
		File_cpp(in, out,order);
		while (_findnext(Handle, &FileInfo) == 0)
		{
			in.close(); out.close();
			in.open(inPath);
			out.open(outPath);
			File_cpp(in, out,order);
		}
		in.close(); out.close();
		_findclose(Handle);
	}
	return;
}

/*
������save_essay
������words&
���ܣ��Ե���ͳ�ƽ���ı���
*/
void save_essay(words& w)
{
	ofstream out;
	char path[200];
	int order;
	cout << "-------------------------------\n";
	cout << "����·����";
	cin >> path;	
	out.open(path);
	if (!out)
	{
		throw pathError();
	}
	
	cout << "�������ݣ�\n";
	cout << "1.���ִ�Сд�������ֵ���˳��\n";
	cout << "2.���ִ�Сд�������ֵ�������\n";
	cout << "3.���ִ�Сд�����մ�Ƶ������\n";
	cout << "4.���ִ�Сд�����մ�Ƶ����\n";
	cout << "5.�����ִ�Сд�������ֵ���˳��\n";
	cout << "6.�����ִ�Сд�������ֵ�������\n";
	cout << "7.�����ִ�Сд�����մ�Ƶ������\n";
	cout << "8.�����ִ�Сд�����մ�Ƶ����\n";
	cout << "9.��������\n";
	cin >> order;
	if (order < 9 && order >0)
	{
		w.print(order, out);
	}
	else if (order == 9)
	{
		w.print_all(out);
	}
	else
		cout << "��������ȷ��ָ��\n";
	return;
}

/*
������save_cpp
������key_words&
���ܣ��Թؼ���ͳ�ƽ���ı���
*/
void save_cpp(key_words &k)
{
	ofstream out;
	char path[200];
	int order;
	cout << "-------------------------------\n";
	cout << "����·����";
	cin >> path;
	
	out.open(path);
	if (!out)
	{
		throw pathError();
	}
	cout << "�������ݣ�\n";
	cout << "1.�����ֵ���˳��\n";
	cout << "2.�����ֵ�������\n";
	cout << "3.���մ�Ƶ������\n";
	cout << "4.���մ�Ƶ����\n";
	cout << "5.��������\n";
	cin >> order;
	if (order < 5 && order >0)
	{
		k.print(order, out);
	}
	else if (order == 5)
	{
		k.print_all(out);
	}
	else
		cout << "��������ȷ��ָ��\n";
	return;
}

#endif
