#pragma once
#include<iostream>
using namespace std;
class Response
{
public:
	string text();//�����ַ����ͣ��Զ�ת��
	string json();//����һ��json
	string content();//����һ����ת���ԭʼ����
	Response(string html);
};
