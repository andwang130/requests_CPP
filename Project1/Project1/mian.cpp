#include<iostream>
#include<requests.h>
#include<WinSock2.h>
#include <ws2tcpip.h>
using namespace std;
int main()
{
	
	string url = "www.baidu.com";
	Crequests requests;
	requests.test(url);
	cin.get();
	return 0;
}