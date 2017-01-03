/*
�ļ���key_words.h
���ݣ����� key_words �࣬���� c++ �ؼ��ʵ�ͳ��
*/
#ifndef KEY_WORDS_H_INCLUDED
#define KEY_WORDS_H_INCLUDED

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

inline bool isBlock(char ch){
	return (ch == ' ' || ch == '\t' || ch == '\n');
}
inline bool isLegal(char ch) {
	return ((ch <= 'z' && ch >= 'a') || ch=='_' || (ch>='0' && ch<='9') || (ch >='A' && ch <='Z'));
}

/*
������solve_note1 solve_note2 solve_str1 solve_str2
���ܣ�����c++�����г���ע�ͺ��ַ��������������ע�ͺ��ַ����еĹؼ���
*/
char solve_note1(ifstream& in)
{
	char ch;
	while ((ch = in.get()) != '\n');
	return ch;
}

char solve_note2(ifstream& in)
{
	char tmp_ch;
	char pre_ch;
	tmp_ch = ' ';
	while (1)
	{
		pre_ch = tmp_ch;
		tmp_ch = in.get();
		if (tmp_ch == '/' && pre_ch == '*')
			return tmp_ch;
	}
}

char solve_str(ifstream& in)
{
	char ch;
	while ((ch = in.get()) != '\"')
	{
		if (ch == '\\') ch = in.get();
	}
	return ch;
}

class key_words
{
private:
	map<string,int> m;
	vector<PAIR>* v;
	void add(string &str);
	void sort_freq();
public:
	key_words(ifstream &in);
	void print(int way, ostream &out);	//way = 1~4�� 4�Ӳ�ͬ�����ʽ
	void print_all(ostream &out);		//���ΰ���4�ӷ�ʽ���
};

key_words::key_words(ifstream& in)
{
	string strs[63] = {
	"asm","auto","bool","break","case","catch","char","class",
	"const","const_cast","continue","default","delete",
	"do","double","dynamic_cast","else","enum","explicit",
	"export","extern","false","float","for","friend","goto",
	"if","inline","int","long","mutable","namespace","new",
	"operator","private","protected","public","register",
	"reinterpret_cast","return","short","signed","sizeof",
	"static","static_cast","struct","switch","template",
	"this","throw","true","try","typedef","typeid","typename",
	"union","unsigned","using","virtual","void","volatile",
	"wchar_t","while"
	};
	for (int i = 0; i < 63; i++)
	{
		m.emplace(PAIR(strs[i], 0));
	}
	string str;
	char tmp_ch;
	char pre_ch = ' ';
	char tmp_st[200];
	int size = 0;
	tmp_ch = in.get();
	while (1)
	{
		//��������е�ע��
		if (tmp_ch == '/' && pre_ch == '/')
		{
			pre_ch = solve_note1(in);
			tmp_ch = in.get();
		}
		else if (tmp_ch == '*' && pre_ch == '/')
		{
			pre_ch = solve_note2(in);
			tmp_ch = in.get();
		}
		//��������е��ַ���
		else if (tmp_ch == '\"')
		{
			pre_ch = solve_str(in);
			tmp_ch = in.get();
		}
		//�����ʶ��������ǲ��ǹؼ���
		else if (isLegal(tmp_ch))
		{
			size = 0;
			do {
				tmp_st[size++] = tmp_ch;
				pre_ch = tmp_ch;
			} while (isLegal(tmp_ch = in.get()));
			tmp_st[size] = '\0';
			str = tmp_st;
			add(str);
		}
		else if (tmp_ch == EOF)	break;
		else
		{
			pre_ch = tmp_ch;
			tmp_ch = in.get();
		}
	}
	//���д�Ƶ����
	sort_freq();
}

void key_words::sort_freq()
{
	v = new vector<PAIR>(m.begin(), m.end());
	sort(v->begin(), v->end(), myCom_value());
	return;
}

void key_words::add(string &str)
{
	if (str.length())
	{
		auto ite = m.find(str);	//
		if (ite != m.end())	//�ҵ���
		{
			ite->second++;
		}
	}
	return;
}

void key_words::print(int way, ostream &out)
{
	if (m.empty())
	{
		cout << "�޹ؼ���\n";
		return;
	}
	switch (way)
	{
	case(1) :
		out << "�����ֵ���˳��\n";
		out << "��Ƶ\t�ؼ���\n";
		for (auto ite : m)		//
		{
			if(ite.second)
				out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(2) :
		out << "�����ֵ�������\n";
		out << "��Ƶ\t�ؼ���\n";
		for (auto ite = --m.end(); ite != m.begin(); ite--)
		{
			if(ite->second)
				out << ite->second << '\t' << ite->first << endl;
		}
		if(m.begin()->second)
			out << m.begin()->second << '\t' << m.begin()->first << endl;
		break;
	case(3) :
		out << "���մ�Ƶ������\n";
		out << "��Ƶ\t�ؼ���\n";
		for (auto ite : *v)
		{
			if(ite.second)
				out << ite.second << '\t' << ite.first << endl;
		}
		break;
	case(4) :
		out << "���մ�Ƶ����\n";
		out << "��Ƶ\t�ؼ���\n";
		for (auto ite = --(v->end()); ite != v->begin(); ite--)
		{
			if(ite->second)
				out << ite->second << '\t' << ite->first << endl;
		}
		if(v->begin()->second)
			out << v->begin()->second << '\t' << v->begin()->first << endl;
		break;
	}
	return;
}

void key_words::print_all(ostream &out)
{
	for (int way = 1; way <= 4; way++)
	{
		print(way, out);
		out << "***************************\n";
	}
	return;
}

#endif