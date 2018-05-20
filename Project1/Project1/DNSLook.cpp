#include"DNSLooK.h"
#include<boost\asio.hpp>
#include <boost\lexical_cast.hpp>//使用字符串转换功能  
using namespace boost::asio;
vector<string> Cdnslook::look(const char *url,int port) //dns报文拼接函数
{
	io_service ios;
	//创建resolver对象  
	ip::tcp::resolver slv(ios);
	//创建query对象  
	ip::tcp::resolver::query qry(url, boost::lexical_cast<string>(port));//将int型端口转换为字符串  
																			//使用resolve迭代端点  
	ip::tcp::resolver::iterator it = slv.resolve(qry);
	ip::tcp::resolver::iterator end;
	vector<string> ip;
	for (; it != end; it++)
	{
		ip.push_back((*it).endpoint().address().to_string());
	}
	return ip;

}