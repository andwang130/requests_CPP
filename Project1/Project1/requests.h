#pragma once
#ifdef _WIN32  //�ж��Ƿ�����winows�ϣ�linux��winodsʹ�õ��ǲ�ͬ��socket
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
	
	void socket_send(string url, string body);  //������������body����
	sockaddr_in  socket_url_ip(string url);  //��������������ip��Ϣ
	string body_structure(string method, string url, map<string, string>head, map<string, string>data); //bdoy���캯��
public:
	string post(string url, map<string, string> headers, map<string, string> data);
	string get(string url, map<string, string> headers, map<string, string> data);
    void test(string url);
};