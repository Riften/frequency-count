/*
编程综合实践 project2
姓名：黄永锡
学号：515030910469
使用 map 存储单词及词频，配合vector完成词频排序，包括4个头文件和1个cpp文件
使用的主要c++11特性: auto关键字， foreach遍历，emplace插入
*/

/*
文件：project2.cpp
内容：main 函数，相当于程序最上层的用户接口
*/

#include"words.h"
#include"key_words.h"
#include"statistics.h"
#include"exceptions.h"

using namespace std;

int main()
{
	int order;
	cout << "此程序统计文章中的单词和词频或 C++ 程序中的关键字\n";
	while (1)
	{
		try {
			cout << "-------------------------------\n";
			cout << "1.统计整个文件夹中的所有文件，并将所有结果以文件形式输出\n";
			cout << "2.统计单个文件中英文单词词频\n";
			cout << "3.统计单个文件中c++关键词词频\n";
			cout << "4.退出\n";
			cin >> order;
			switch (order)
			{
				//Folder，essay，prog 分别对应三个统计指令，均在 statics.h 中实现
			case(1) : Folder(); break;
			case(2) : essay(); break;
			case(3) : prog(); break;
			case(4) : return 0;
			default: throw(orderError());
			}
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
	return 0;
}
