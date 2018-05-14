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
	string body_structure( string &method,string &url,map<string, string>&head, map<string, string>&data); //bdoy构造函数
	void get_Content_Lengt(char *req, int max, int buf); //获取到返回数据长度的参数
	char * get_response_head( char *req);
	void req_to_head(string &head, char *req, int max);
public:
	string post(string url, map<string, string> headers, map<string, string> data);
	string get(string url, map<string, string> headers, map<string, string> data);
    void test(string url,string &method, map<string, string>&head, map<string, string>&data);
};