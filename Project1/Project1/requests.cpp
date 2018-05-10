#include<requests.h>
#include<iostream>
using namespace std;
void Crequests::socket_send(string url, string body)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //绑定socket版本，在windos操作系统上，使用socket都要先绑定版本
	struct sockaddr_in server_in; //地址结构体
	SOCKET socket_= socket(AF_INET,SOCK_STREAM,0);//建立一个cocket。3个参数，第一个	协议族，AF_INET表示网络连接，第二类型SOCK_STREAM TCP，0表示使用第二参数的协议类型
	server_in = socket_url_ip(url); //获取到IP
	//bind(SOCKET, (struct sockaddr*) &server_in.sin_addr, sizeof(server_in));//绑定socket,传入socket和地址结构体转换成sockaddr指针类型，第三个参数是结构体的大小
	char ipbuf[16];
	cout << inet_ntop(AF_INET,
		&server_in.sin_addr,ipbuf,16) << endl;
	server_in.sin_port = 80;
	cout << connect(socket_, (struct sockaddr*) &server_in, sizeof(server_in)) << endl;;//客户端建立连接
	cout << WSAGetLastError() << endl;
	
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
string Crequests::body_structure(string method, string url, map<string, string>head, map<string, string>data) //bdoy构造函数
{
	return "ss";
}
 void Crequests::test(string url)
{
	string body = "sdsdsdsds";
	socket_send(url, body);
}