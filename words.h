/*
�ļ���words.h
���ݣ����� words �࣬������ɵ��ʴ�Ƶ��ͳ��
*/
#ifndef MAP_H_INCLUDED
#define MAP_H_INClUDED

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef pair<string, int> PAIR;

//�ȽϺ��������ڶ�vector��������ɰ�Ƶ������
struct myCom_value {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.second < rhs.second;
	}
};

struct myCom_key {
	bool operator()(const PAIR& lhs, const PAIR& rhs) {
		return lhs.first < rhs.first;
	}
};

inline bool isLetter(char c)
{
	return ((c <= 'z'&&c >= 'a') || (c <= 'Z' && c >= 'A'));
}

inline bool isLetter2(char c)
{
	return ((c <= 'z'&&c >= 'a') || (c <= 'Z' && c >= 'A') || c == '\'' || c == '-');
}
class words
{
private:
	//���ݴ洢��map�У�ʵ�ֿ��ٵ��������
	map<string, int> m_dif;	//���ִ�Сд
	map<string, int> m_sam;	//�����ִ�Сд
	vector<PAIR>* v_dif;	//m1��Ƶ������
	vector<PAIR>* v_sam;	//m2��Ƶ������
	
	void add(string &str);	//�� map ����ӵ���
	void sort_freq();		//����Ƶ���򣬲������������ vector ��
public:
	words(ifstream& in);
	~words() { delete v_dif; delete v_sam; }
	void print(int way, ostream &out);	//way = 1~8,���� 8 �������ʽ
	void print_all(ostream &out);		//���ΰ��հ��������ʽ���
};

words::words(ifstream& in)
{
	string str;
	char tmp_ch;
	char tmp_st[200];
	int size = 0;
	while (1)
	{
		size = 0;
		if(isLetter(tmp_ch = in.get()))
		{
			do {
				tmp_st[size++] = tmp_ch;
			} while (isLetter2(tmp_ch = in.get()));
		}
		if (size)
		{
			tmp_st[size] = '\0';
			str = tmp_st;
			add(str);
		}
		if (tmp_ch == EOF)	break;
	}
	//���д�Ƶ����
	sort_freq();
}

void words::add(string &str)
{
	//Ϊ m_dif ���
	if (str.length())
	{
		auto ite = m_dif.find(str);	//
		if (ite != m_dif.end())	//�ҵ���
		{
			ite->second++;
		}
		else
		{
			m_dif.emplace(PAIR(str, 1));
		}
	}
	//Ϊ m_sam ���
	{
		transform(str.begin(), str.end(), str.begin(), tolower);
		auto ite = m_sam.find(str);	//
		if (ite != m_sam.end())	//�ҵ���
		{
			ite->second++;
		}
		else
		{
			m_sam.emplace(PAIR(str, 1));
		}
	}
}

void words::sort_freq()
{
	v_dif = new vector<PAIR>(m_dif.begin(), m_dif.end());
	v_sam = new vector<PAIR>(m_sam.begin(), m_sam.end());
	sort(v_dif->begin(), v_dif->end(), myCom_value());
	sort(v_sam->begin(), v_sam->end(), myCom_value());
	return;
}

void words::print(int way, ostream& out)
{
	if (m_dif.empty())
	{
		cout << "�޵���\n";
		return;
	}
	switch (way)
	{
	case(1) :
		out << "���ִ�Сд�������ֵ���˳��\n";
		out << "��Ƶ\t����\n";
		for (auto ite : m_dif)		//
		{
			out <<  ite.second <<'\t'<< ite.first << endl;
		}
		break;
	case(2):
		out << "���ִ�Сд�������ֵ�������\n";
		out << "��Ƶ\t����\n";
		for (auto ite = --m_dif.end(); ite != m_dif.begin();ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << m_dif.begin()->second << '\t' << m_dif.begin()->first << endl;
		break;
	case(3):
		out << "���ִ�Сд�����մ�Ƶ������\n";
		out << "��Ƶ\t����\n";
		for (auto ite : *v_dif)
		{
			out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(4):
		out << "���ִ�Сд�����մ�Ƶ����\n";
		out << "��Ƶ\t����\n";
		for (auto ite = --(v_dif->end()); ite != v_dif->begin();ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << v_dif->begin()->second << '\t' << v_dif->begin()->first << endl;
		break;
	case(5) :
		out << "�����ִ�Сд�������ֵ���˳��\n";
		out << "��Ƶ\t����\n";
		for (auto ite : m_sam)		//
		{
			out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(6) :
		out << "�����ִ�Сд�������ֵ�������\n";
		out << "��Ƶ\t����\n";
		for (auto ite = --m_sam.end(); ite != m_sam.begin(); ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << m_sam.begin()->second << '\t' << m_sam.begin()->first << endl;
		break;
	case(7) :
		out << "�����ִ�Сд�����մ�Ƶ������\n";
		out << "��Ƶ\t����\n";
		for (auto ite : *v_sam)
		{
			out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(8) :
		out << "�����ִ�Сд�����մ�Ƶ����\n";
		out << "��Ƶ\t����\n";
		for (auto ite = --(v_sam->end()); ite != v_sam->begin(); ite--)
		{
			out << ite->second << '\t' << ite->first << endl;
		}
		out << v_sam->begin()->second <<'\t' << v_sam->begin()->first << endl;
		break;
	}
	return;
}


void words::print_all(ostream &out)
{
	for (int way = 1; way <= 8; way++)
	{
		print(way, out);
		out << "***************************\n";
	}
	return;
}
#endif