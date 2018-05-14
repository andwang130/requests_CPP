#include<requests.h>
#include<iostream>
#include<regex>
using namespace std;
void Crequests::socket_send(string url, string body)
{
	cout << body << endl;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //绑定socket版本，在windos操作系统上，使用socket都要先绑定版本
	struct sockaddr_in server_in; //地址结构体
	SOCKET socket_= socket(AF_INET,SOCK_STREAM,0);//建立一个cocket。3个参数，第一个	协议族，AF_INET表示网络连接，第二类型SOCK_STREAM TCP，0表示使用第二参数的协议类型
	server_in = socket_url_ip(url); //获取到IP
	//bind(SOCKET, (struct sockaddr*) &server_in.sin_addr, sizeof(server_in));//绑定socket,传入socket和地址结构体转换成sockaddr指针类型，第三个参数是结构体的大小
	char ipbuf[16];
	cout << inet_ntop(AF_INET,&server_in.sin_addr,ipbuf,16) << endl;
	server_in.sin_port =htons(80);
	cout << connect(socket_, (struct sockaddr*) &server_in, sizeof(server_in)) << endl;;//客户端建立连接
	cout << WSAGetLastError() << endl;  //打印一下错误码
	send(socket_,body.c_str(),strlen(body.c_str()),0);
	char req[4090];
	int recv_max = 0;

	//u_long mode = 1;
	//ioctlsocket(socket_, FIONBIO, &mode);//将socket设置为非塞模式

	int buf = recv(socket_, req, 4090, 0); //获取到Content-Lengt长度,MSG_PEEKW标志不会将缓存区的数据拿出来
	get_response_head(req);
	//get_Content_Lengt（req,recv_max,buf);
	//cout << req << endl;
	int i= 0;
	string str;
	while(true) //recv返回字节数，recv传递4个参数。第一个是socket,第二个是结束返回的数据的，char *，第三个是单次接收的大小，第四个一般为0
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
sockaddr_in  Crequests::socket_url_ip(string url)//传入域名，返回ip信息
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //绑定socket版本，在windos操作系统上，使用socket都要先绑定版本
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
		throw "The IP of the domain name is not found"; //抛出异常，改域名的IP未找到
	}
}
string Crequests::body_structure(string &method,string &url,map<string, string>&head,map<string, string>&data) //bdoy构造函数
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
	map<string, string>::iterator iter; //迭代器
	for (iter=head.begin(); iter != head.end();iter++) //拼接headers
	{
		code += iter->first + ":" + iter->second+"\r\n";  //first是键，second是值
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
	//这个函数用来查找到\r\n\r\n的位置，取到head；
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