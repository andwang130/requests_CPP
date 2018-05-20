#include<iostream>
#include<requests.h>
#include<WinSock2.h>
#include <ws2tcpip.h>
#include<DNSLooK.h>
using namespace std;
int main()
{

	string url = "www.carzy.wang";
	Crequests requests;
	map < string, string> headers=
	{
		{"Accept","text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8"},
		{"Accept - Encoding","gzip, deflate"},
		{"Accept-Language","zh-CN,zh;q=0.9"},
		{"User-Agent","Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.139 Safari/537.36"},
		{"Host","blog.sina.com.cn"},
		{"Connection","keep-alive"},
		{"Upgrade-Insecure-Requests","1"}
	};
	map<string, string>data;
	data["sds"] = "ffff";
	string get = "GET";
	requests.test(url,get,headers,data);
	cin.get();
	return 0;
}