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
	
	string headers;
	string text;
	int head_buf=0;//head���ֽ�
	int readbuf=0;//�Ѿ���ȡ��
	int sum_buf=0;//�ܹ���
	void socket_send(string url, string body);  //������������body����
	sockaddr_in  socket_url_ip(string url);  //��������������ip��Ϣ
	string body_structure( string &method,string &url,map<string, string>&head, map<string, string>&data); //bdoy���캯��
	int get_Content_Lengt(); //��ȡ���������ݳ��ȵĲ���
	bool  get_response_head( char *req);
	void req_to_head(string &head, char *req, int max);
	int str_to_int(string str);
public:
	string post(string url, map<string, string> headers, map<string, string> data);
	string get(string url, map<string, string> headers, map<string, string> data);
    void test(string url,string &method, map<string, string>&head, map<string, string>&data);
};