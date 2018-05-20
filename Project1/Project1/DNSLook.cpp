#include"DNSLooK.h"
#include<boost\asio.hpp>
#include <boost\lexical_cast.hpp>//ʹ���ַ���ת������  
using namespace boost::asio;
vector<string> Cdnslook::look(const char *url,int port) //dns����ƴ�Ӻ���
{
	io_service ios;
	//����resolver����  
	ip::tcp::resolver slv(ios);
	//����query����  
	ip::tcp::resolver::query qry(url, boost::lexical_cast<string>(port));//��int�Ͷ˿�ת��Ϊ�ַ���  
																			//ʹ��resolve�����˵�  
	ip::tcp::resolver::iterator it = slv.resolve(qry);
	ip::tcp::resolver::iterator end;
	vector<string> ip;
	for (; it != end; it++)
	{
		ip.push_back((*it).endpoint().address().to_string());
	}
	return ip;

}