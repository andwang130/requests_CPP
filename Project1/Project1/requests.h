#pragma once
#ifdef _WIN32  //判断是否是在winows上，linux和winods使用的是不同的socket
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <sys/socket.h>
#endif
#include<string>
#include <ws2tcpip.h>
#include<map>
using namespace std;
class Crequests
{

private:
	
	void socket_send(string url, string body);  //传入域名，和body发送
	sockaddr_in  socket_url_ip(string url);  //传入域名，返回ip信息
	string body_structure(string method, string url, map<string, string>head, map<string, string>data); //bdoy构造函数
public:
	string post(string url, map<string, string> headers, map<string, string> data);
	string get(string url, map<string, string> headers, map<string, string> data);
    void test(string url);
};