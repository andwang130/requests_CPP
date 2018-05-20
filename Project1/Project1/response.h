#pragma once
#include<iostream>
using namespace std;
class Response
{
public:
	string text();//返回字符类型，自动转码
	string json();//返回一个json
	string content();//返回一个不转码的原始数据
	Response(string html);
};
