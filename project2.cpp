/*
����ۺ�ʵ�� project2
������������
ѧ�ţ�515030910469
ʹ�� map �洢���ʼ���Ƶ�����vector��ɴ�Ƶ���򣬰���4��ͷ�ļ���1��cpp�ļ�
ʹ�õ���Ҫc++11����: auto�ؼ��֣� foreach������emplace����
*/

/*
�ļ���project2.cpp
���ݣ�main �������൱�ڳ������ϲ���û��ӿ�
*/

#include"words.h"
#include"key_words.h"
#include"statistics.h"
#include"exceptions.h"

using namespace std;

int main()
{
	int order;
	cout << "�˳���ͳ�������еĵ��ʺʹ�Ƶ�� C++ �����еĹؼ���\n";
	while (1)
	{
		try {
			cout << "-------------------------------\n";
			cout << "1.ͳ�������ļ����е������ļ����������н�����ļ���ʽ���\n";
			cout << "2.ͳ�Ƶ����ļ���Ӣ�ĵ��ʴ�Ƶ\n";
			cout << "3.ͳ�Ƶ����ļ���c++�ؼ��ʴ�Ƶ\n";
			cout << "4.�˳�\n";
			cin >> order;
			switch (order)
			{
				//Folder��essay��prog �ֱ��Ӧ����ͳ��ָ����� statics.h ��ʵ��
			case(1) : Folder(); break;
			case(2) : essay(); break;
			case(3) : prog(); break;
			case(4) : return 0;
			default: throw(orderError());
			}
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
	return 0;
}
