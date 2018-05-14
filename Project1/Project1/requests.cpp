#include<requests.h>
#include<iostream>
#include<regex>
using namespace std;
void Crequests::socket_send(string url, string body)
{
	cout << body << endl;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //��socket�汾����windos����ϵͳ�ϣ�ʹ��socket��Ҫ�Ȱ󶨰汾
	struct sockaddr_in server_in; //��ַ�ṹ��
	SOCKET socket_= socket(AF_INET,SOCK_STREAM,0);//����һ��cocket��3����������һ��	Э���壬AF_INET��ʾ�������ӣ��ڶ�����SOCK_STREAM TCP��0��ʾʹ�õڶ�������Э������
	server_in = socket_url_ip(url); //��ȡ��IP
	//bind(SOCKET, (struct sockaddr*) &server_in.sin_addr, sizeof(server_in));//��socket,����socket�͵�ַ�ṹ��ת����sockaddrָ�����ͣ������������ǽṹ��Ĵ�С
	char ipbuf[16];
	cout << inet_ntop(AF_INET,&server_in.sin_addr,ipbuf,16) << endl;
	server_in.sin_port =htons(80);
	cout << connect(socket_, (struct sockaddr*) &server_in, sizeof(server_in)) << endl;;//�ͻ��˽�������
	cout << WSAGetLastError() << endl;  //��ӡһ�´�����
	send(socket_,body.c_str(),strlen(body.c_str()),0);
	char req[4090];
	int recv_max = 0;

	//u_long mode = 1;
	//ioctlsocket(socket_, FIONBIO, &mode);//��socket����Ϊ����ģʽ

	int buf = recv(socket_, req, 4090, 0); //��ȡ��Content-Lengt����,MSG_PEEKW��־���Ὣ�������������ó���
	get_response_head(req);
	//get_Content_Lengt��req,recv_max,buf);
	//cout << req << endl;
	int i= 0;
	string str;
	while(true) //recv�����ֽ�����recv����4����������һ����socket,�ڶ����ǽ������ص����ݵģ�char *���������ǵ��ν��յĴ�С�����ĸ�һ��Ϊ0
	{
		int buf = recv(socket_, req, 4090, 0);
		i = i + buf;
		cout << buf<< endl;
		str += req;
		cout << "***************"<<i << endl;
		memset(req, 0, 4090);
		if (buf <= 0)
		{
			break;
		}
		
	}
	cout << str << endl;;
}
sockaddr_in  Crequests::socket_url_ip(string url)//��������������ip��Ϣ
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //��socket�汾����windos����ϵͳ�ϣ�ʹ��socket��Ҫ�Ȱ󶨰汾
	struct addrinfo *answer, *curr;
	struct addrinfo hint;
	struct sockaddr_in *addr;
	memset(&hint, 0, sizeof(struct addrinfo));
	hint.ai_family = AF_INET;
	hint.ai_socktype = SOCK_STREAM;
	hint.ai_protocol = 0;
	hint.ai_flags = AI_PASSIVE;
	const char *name = url.c_str();
	int ret = getaddrinfo(name, NULL, &hint, &answer);
	
	if (ret == 0)
	{
		
		curr = answer;
			addr = (struct sockaddr_in *) curr->ai_addr;
			return *addr;

		
		
	}
	else
	{
		throw "The IP of the domain name is not found"; //�׳��쳣����������IPδ�ҵ�
	}
}
string Crequests::body_structure(string &method,string &url,map<string, string>&head,map<string, string>&data) //bdoy���캯��
{
	string code;
	string url_pr="/";
	string::iterator striter;
	for (striter = url.begin(); striter != url.end(); striter++)
	{
		if (*striter == '/')
		{
			string url_(striter, url.end());
			url_pr = url_;
			break;
		}
	}
	code = method + ' '+ url_pr +' '+"HTTP/1.1\r\n";
	map<string, string>::iterator iter; //������
	for (iter=head.begin(); iter != head.end();iter++) //ƴ��headers
	{
		code += iter->first + ":" + iter->second+"\r\n";  //first�Ǽ���second��ֵ
	}
	code += "\r\n";
	/*for (iter=data.begin(); iter != data.end(); iter++)
	{
		code += iter->first + '=' + iter->second;
	}*/
	return code;
}
char * Crequests::get_response_head(char *req)
{
	//��������������ҵ�\r\n\r\n��λ�ã�ȡ��head��
	//
	char flag[5] = "\r\n\r\n";
	int req_lent = strlen(req);
	int flag_lent = strlen(flag);
	cout << "req_lent" << flag_lent << endl;
	for (int i = 0; i < req_lent; i++)
	{
		int j=0;
		for (; j< flag_lent; j++)
		{
			if (req[i+j] != flag[j])
			{
				break;
			}
			
		}
		if (j == flag_lent)
		{
			cout <<"jssss"<< j << endl;
			cout << i << endl;
			string  head;
			req_to_head(head, req, i);
			cout << head << endl;
			return flag;
		}
	}
}
void Crequests::req_to_head(string &head, char *req,int max)
{
	for (int i = 0; i < max; i++)
	{
		head.push_back(req[i]);
	}
	
}
void Crequests::get_Content_Lengt(char *req,int max,int buf)
{
	cmatch st;
	regex length("Content-Length: (\\d+)");

	if (regex_search(req, st, length))
	{
		cout << st[1] << endl;
	}
	else
	{

	}
	

}
 void Crequests::test(string url,string &method, map<string, string>&head, map<string, string>&data)
{
	string body = "sdsdsdsds";
	string body_m=body_structure(method, url, head, data);
	string now_url;
	string::iterator striter;
	for (striter = url.begin(); striter != url.end(); striter++)
	{
		if (*striter == '/')
		{
			string url_(url.begin(), striter);
			now_url = url_;
			break;
		}
	}
	cout<<body_m<< endl;
	cout << now_url << endl;
	socket_send(now_url, body_m);
}