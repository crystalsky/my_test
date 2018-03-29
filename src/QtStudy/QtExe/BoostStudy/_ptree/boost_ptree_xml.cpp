#include "boost_ptree_xml.h"
#include <boost/program_options/detail/convert.hpp>
#include <boost/program_options/detail/utf8_codecvt_facet.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/xml_parser.hpp>  
#include <boost/foreach.hpp>  
#include <boost/typeof/std/utility.hpp>  
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <set>
#include <QtProjectPath.h>

#define _UNICODE
#ifndef _UNICODE
#define tptree boost::property_tree::ptree
#else
#define tptree boost::property_tree::wptree
#endif 
using namespace boost;
//using namespace ws;

using namespace boost::property_tree;

struct TestConfig  
{  
	std::string title;  
	int number;  
	std::map<int, std::string> groups;  
	std::set<std::string> classes;  
	void load(const std::string& filename);  
	void save(const std::string& filename);  
};  

void TestConfig::load(const std::string& filename)  
{  
	/*using boost::property_tree::ptree;  
	tptree pt;  
	// 其中new的facet会被locale自动delete
	locale current_locale(locale(""), new program_options::detail::utf8_codecvt_facet());
	read_xml(filename, pt, boost::property_tree::xml_parser::trim_whitespace,current_locale);  


	std::vector<boost::any> vec;
	boost::any any1(double(1.1));
	vec.push_back(any1);
	vec.push_back(boost::any("123"));

	BOOST_FOREACH(const auto& a, vec)
	{
		try
		{
			double d = boost::any_cast<double>(a);
			std::cout << d<< std::endl;
		}
		catch (boost::exception& e)
		{
			std::cout << "sdf" << std::endl;
		}
	}
	
	//title = pt.get_child(L"content.title").get<std::wstring>("<xmlattr>.value");  
	//std::cout << title << std::endl;  

	//number = pt.get<int>("content.number");  
	//std::cout << number << std::endl;  

	tptree &groups_node = pt.get_child(L"content.groups");  
	BOOST_FOREACH(const tptree::value_type& vt, groups_node)  
	{  
		std::wstring num = vt.second.get<std::wstring>(L"<xmlattr>.num");  
		std::wstring type = vt.second.get<std::wstring>(L"<xmlattr>.type");  
		//groups.insert(std::pair<int, std::string>(atoi(num.c_str()), type));  
		std::wcout << num << L"," << type << std::endl;  

		std::string s = UtilityKit::convertUTF16toUTF8(type.c_str(), type.length());

		std::string s1 = UtilityKit::convertStringFromUTF8toCurrentCodePage(s.c_str());

		std::cout << s1 << std::endl;

		std::wcout <<type.c_str() <<std::endl;
	}  

	//ptree &classes_node = pt.get_child("content.classes");  
	//BOOST_FOREACH(const ptree::value_type& vt, classes_node)  
	//{  
		//classes.insert(vt.second.data());  
		//std::cout << vt.second.data() << std::endl;  
	//}  */

	using boost::property_tree::ptree;  
	ptree pt;  
	read_xml(filename, pt, boost::property_tree::xml_parser::trim_whitespace);

	title = pt.get_child("content.title").get<std::string>("<xmlattr>.value");  
	std::cout << title << std::endl;  

	number = pt.get<int>("content.number");  
	std::cout << number << std::endl;  

	ptree &groups_node = pt.get_child("content.groups");  
	BOOST_FOREACH(const ptree::value_type& vt, groups_node)  
	{  
		std::string num = vt.second.get<std::string>("<xmlattr>.num");  
		std::string type = vt.second.get<std::string>("<xmlattr>.type");  
		groups.insert(std::pair<int, std::string>(atoi(num.c_str()), type));  
		std::cout << num << "," << type << std::endl;  
	}  

	ptree &classes_node = pt.get_child("content.classes");  
	BOOST_FOREACH(const ptree::value_type& vt, classes_node)  
	{  
		classes.insert(vt.second.data());  
		std::cout << vt.second.data() << std::endl;  
	}  
}  

void TestConfig::save(const std::string& filename)  
{  
	using boost::property_tree::ptree;  
	ptree pt, pattr1;  

	pattr1.add<std::string>("<xmlattr>.value", title);  
	pt.add_child("content.title", pattr1);  
	pt.put("content.number", number);  

	typedef std::map<int, std::string> map_type;  
	BOOST_FOREACH(const map_type::value_type &grp, groups)  
	{  
		ptree pattr2;  
		pattr2.add<int>("<xmlattr>.num", grp.first);  
		pattr2.add<std::string>("<xmlattr>.type", grp.second);  
		pt.add_child("content.groups.class", pattr2);  
	}  

	BOOST_FOREACH(const std::string& cls, classes)  
	{  
		pt.add("content.classes.name", cls);  
	}  

	// 格式化输出，指定编码（默认utf-8）  
	auto settings = 
		boost::property_tree::xml_writer_make_settings<std::string>('\t', 1, "GB2312");   

	std::ostringstream s;
	//std::basic_ostream<std::string> s;
	boost::property_tree::write_xml(s, pt, settings);  
	std::cout << s.str() << std::endl;

	boost::property_tree::write_xml(filename, pt, std::locale(), settings);  
}  



IMPLEMENT_REFLECTED_CLASS(boost_ptree_xml)
boost_ptree_xml::boost_ptree_xml()
{
	
}

boost_ptree_xml::~boost_ptree_xml()
{
	
}

void boost_ptree_xml::run()
{
	try  
	{  
		const QString& strFilePath = QtProjectPath::DirPaths::GetAppRootDataPath();

		const QString strPath = 
			strFilePath + QString("/test1.xml");
		const QString strPath1 = 
			strFilePath + QString("/test2.xml");
		TestConfig tc;  
		tc.load(strPath.toLocal8Bit().data());  
		tc.save(strPath1.toLocal8Bit().data());  
		std::cout << "Success\n";  
	}  
	catch (std::exception &e)  
	{  
		std::cout << "Error: " << e.what() << "\n";  
	}  
}
