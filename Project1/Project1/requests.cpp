#include<requests.h>
#include<iostream>
using namespace std;
void Crequests::socket_send(string url, string body)
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //��socket�汾����windos����ϵͳ�ϣ�ʹ��socket��Ҫ�Ȱ󶨰汾
	struct sockaddr_in server_in; //��ַ�ṹ��
	SOCKET socket_= socket(AF_INET,SOCK_STREAM,0);//����һ��cocket��3����������һ��	Э���壬AF_INET��ʾ�������ӣ��ڶ�����SOCK_STREAM TCP��0��ʾʹ�õڶ�������Э������
	server_in = socket_url_ip(url); //��ȡ��IP
	//bind(SOCKET, (struct sockaddr*) &server_in.sin_addr, sizeof(server_in));//��socket,����socket�͵�ַ�ṹ��ת����sockaddrָ�����ͣ������������ǽṹ��Ĵ�С
	char ipbuf[16];
	cout << inet_ntop(AF_INET,
		&server_in.sin_addr,ipbuf,16) << endl;
	server_in.sin_port = 80;
	cout << connect(socket_, (struct sockaddr*) &server_in, sizeof(server_in)) << endl;;//�ͻ��˽�������
	cout << WSAGetLastError() << endl;
	
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
string Crequests::body_structure(string method, string url, map<string, string>head, map<string, string>data) //bdoy���캯��
{
	return "ss";
}
 void Crequests::test(string url)
{
	string body = "sdsdsdsds";
	socket_send(url, body);
}