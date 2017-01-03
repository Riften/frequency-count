/*
文件：statics.h
内容：完成统计工作的所有函数，调用 words 类和 keywords 类完成统计
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
函数：File_txt
参数：输入流 ifstream& in 输出流 ofstream& out
功能：实现单个 txt 文件的统计，从输入流中读取并且输出到输出流
*/
void File_txt(ifstream &in, ofstream &out, int way)
{
	words w(in);
	if (way == 9) w.print_all(out);
	else w.print(way, out);
	return;
}

/*
函数：File_cpp
参数：输入流 ifstream& in 输出流 ofstream& out
功能：实现单个 cpp 文件的统计，从输入流中读取并且输出到输出流
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
函数：essay
功能：对应 main 函数中的 order = 2
	统计单个文本文件中，英文单词的词频
*/
void essay()
{
	ifstream in;
	char path[100];
	int order;
	cout << "请输入文件路径:";
	cin >> path;
	in.open(path);
	if (!in)
	{
		throw(pathError());
	}	
	words w(in);
	cout << "统计完成\n";
	while (1)
	{
		try {
			cout << "-------------------------------\n";
			cout << "请输入统计结果查看方式\n";
			cout << "1.区分大小写，按照字典序顺序\n";
			cout << "2.区分大小写，按照字典序逆序\n";
			cout << "3.区分大小写，按照词频序升序\n";
			cout << "4.区分大小写，按照词频降序\n";
			cout << "5.不区分大小写，按照字典序顺序\n";
			cout << "6.不区分大小写，按照字典序逆序\n";
			cout << "7.不区分大小写，按照词频序升序\n";
			cout << "8.不区分大小写，按照词频序降序\n";
			cout << "9.返回\n";
			cout << "10.保存结果\n";
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
			cout << "请输入正确的指令\n";
		}
		catch (pathError)
		{
			cout << "路径访问失败\n";
		}
	}
	return;
}

/*
函数：prog
功能：对应 main 函数中的 order = 3
	统计单个文本文件中，c++关键词词频
*/
void prog()
{
	ifstream in;
	char path[100];
	int order;
	cout << "请输入文件路径:";
	cin >> path;
	in.open(path);
	
	if (!in)
	{
		throw pathError();
	}
	
	key_words w(in);
	cout << "统计完成\n";
	while (1)
	{
		try {
			cout << "-------------------------------\n";
			cout << "请输入统计结果查看方式\n";
			cout << "1.按照字典序顺序\n";
			cout << "2.按照字典序逆序\n";
			cout << "3.按照词频序升序\n";
			cout << "4.按照词频序降序\n";
			cout << "5.返回\n";
			cout << "6.保存结果\n";
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
			cout << "请输入正确指令\n";
		}
		catch (pathError)
		{
			cout << "路径访问失败\n";
		}
	}
	return;
}

/*
函数：Folder
功能：实现统计整个文件夹中所有的 txt 和 cpp 文件，并且将结果保存在 txt 文件中
	在输入文件夹中创建 statics_res 文件夹
	并将所有结果存入文件夹中
	每个文件对应的统计结果文件名与原来文件名相同
*/
#define inPath string(inFolder).append("\\").append(FileInfo.name)
#define outPath string(inFolder).append("\\statics_res").append("\\").append(FileInfo.name)
void Folder()
{
	int order;
	char inFolder[200];		//文件夹名
	ifstream in;			//每个文件使用的输入流
	ofstream out;			//每个文件使用的输出流
	cout << "-------------------------------\n";
	cout << "输入文件夹路径:\n";
	cin >> inFolder;
	long Handle;
	struct _finddata_t FileInfo;		//输入文件信息
	string outFolder(string(inFolder).append("\\statics_res"));	//输出文件保存路径
	cout << "统计结果将保存在文件夹" << outFolder << endl;
	//system(string("rd/s/q ").append(outFolder).c_str());
	system(string("md ").append(outFolder).c_str());

	//对txt文件进行统计
	if ((Handle = _findfirst(string(inFolder).append("\\*.txt").c_str(), &FileInfo)) == -1L)
	{
		cout <<"没有找到 txt 文件\n";
	}
	else
	{
		cout << "-------------------------------\n";
		cout << "对文件夹内的txt文件结果保存的排序方式：\n";
		cout << "1.区分大小写，按照字典序顺序\n";
		cout << "2.区分大小写，按照字典序逆序\n";
		cout << "3.区分大小写，按照词频序升序\n";
		cout << "4.区分大小写，按照词频降序\n";
		cout << "5.不区分大小写，按照字典序顺序\n";
		cout << "6.不区分大小写，按照字典序逆序\n";
		cout << "7.不区分大小写，按照词频序升序\n";
		cout << "8.不区分大小写，按照词频序降序\n";
		cout << "9.上述所有 (错误指令将默认输出所有排序)\n";
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

	//对cpp文件进行统计
	if ((Handle = _findfirst(string(inFolder).append("\\*.cpp").c_str(), &FileInfo)) == -1L)
	{
		cout << "没有找到 cpp 文件\n";
		return;
	}
	else
	{
		cout << "-------------------------------\n";
		cout << "对文件夹内的cpp文件结果保存的排序方式：\n";
		cout << "1.按照字典序顺序\n";
		cout << "2.按照字典序逆序\n";
		cout << "3.按照词频序升序\n";
		cout << "4.按照词频序降序\n";
		cout << "5.上述所有 (错误指令将默认输出所有排序)\n";
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
函数：save_essay
参数：words&
功能：对单词统计结果的保存
*/
void save_essay(words& w)
{
	ofstream out;
	char path[200];
	int order;
	cout << "-------------------------------\n";
	cout << "保存路径：";
	cin >> path;	
	out.open(path);
	if (!out)
	{
		throw pathError();
	}
	
	cout << "保存内容：\n";
	cout << "1.区分大小写，按照字典序顺序\n";
	cout << "2.区分大小写，按照字典序逆序\n";
	cout << "3.区分大小写，按照词频序升序\n";
	cout << "4.区分大小写，按照词频降序\n";
	cout << "5.不区分大小写，按照字典序顺序\n";
	cout << "6.不区分大小写，按照字典序逆序\n";
	cout << "7.不区分大小写，按照词频序升序\n";
	cout << "8.不区分大小写，按照词频序降序\n";
	cout << "9.上述所有\n";
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
		cout << "请输入正确的指令\n";
	return;
}

/*
函数：save_cpp
参数：key_words&
功能：对关键词统计结果的保存
*/
void save_cpp(key_words &k)
{
	ofstream out;
	char path[200];
	int order;
	cout << "-------------------------------\n";
	cout << "保存路径：";
	cin >> path;
	
	out.open(path);
	if (!out)
	{
		throw pathError();
	}
	cout << "保存内容：\n";
	cout << "1.按照字典序顺序\n";
	cout << "2.按照字典序逆序\n";
	cout << "3.按照词频序升序\n";
	cout << "4.按照词频序降序\n";
	cout << "5.上述所有\n";
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
		cout << "请输入正确的指令\n";
	return;
}

#endif
