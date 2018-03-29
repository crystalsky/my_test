#include "_XML_Testor.h"
#include "_XML_Attribute_Object.h"
#include "_XML_Element_Object.h"
#include "_XML_Container_Element_Object.h"
#include "_XML_Herited_Object.h"
#include "_XML_Container_Object.h"
#include "_XML_Relected_Object.h"
#include <ctime>
#include <math.h>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace xml_data_gen_functions;


std::string getFilePath(const std::string& strFileName)
{
	int nSize = sizeof(std::string);

	char path[250];
	getApplicationFileDir(path, sizeof(path));

	cleanupFileString(path);
	std::string strPath = std::string(path) + "/" + strFileName;

	return strPath;
}

void XML_Testor::base_test()
{
	XML_Testor test;

	test.test_serialize_attribute();

	test.test_serialize_element();

	test.test_serialize_container_element();

	test.test_serialize_container_object();

	test.test_xml_reflect_container_object();
}

void XML_Testor::speed_test()
{
	XML_Testor test;
	test.speed_test_serialize_container_object_mem();
	test.speed_test_serialize_container_object_file();
	test.speed_serialize_container_element();
}

void XML_Testor::speed_serialize_container_element()
{
	output_msg("test_serialize_container_element", S_Begin);

	//write file 
	for (int i = 0; i < 15; ++i)
	{
		static std::stringstream ss;
		ss.str("");
		ss << "speed_serialize_container_element";
		ss << i;
		ss << ".xml";
		const std::string strFile = getFilePath(ss.str());
		
		int nSize = (int)pow(double(2.0), double(i));

		XmlSerialize::XmlSerializeStreamFile streamWrite(strFile.c_str()),
			streamRead(strFile.c_str());
		XML_Container_Element_Object objSerialize(nSize), objDeserialize;

		int nStart = GetTickCount();

		if(!(streamWrite << objSerialize))
		{
			output_msg("speed_serialize_container_element", S_Failed);
			return;
		}

		if(!(streamRead >> objDeserialize))
		{
			output_msg("speed_serialize_container_element Deserialize", S_Failed);
			return;
		}

		if (objSerialize == objDeserialize)
		{
			int nelpse = GetTickCount() - nStart;
			std::cout << "Serialize Element Container [Size]=" << nSize << " [Time]=" << nelpse << std::endl; 
		}
		else
		{
			output_msg("speed_serialize_container_element obj equal", S_Failed);
		}
	}
	
}

void XML_Testor::speed_test_serialize_container_object_mem()
{
	output_msg("speed_test_serialize_container_object", S_Begin);

	//write file 
	for (int i = 0; i < 15; ++i)
	{
		int nSize = (int)pow(double(2.0), double(i));

		XmlSerialize::XmlSerializeStreamString streamWrite, streamRead;
		XML_Container_Object objSerialize(nSize), objDeserialize;

		int nStart = GetTickCount();

		if(!(streamWrite << objSerialize))
		{
			output_msg("speed_serialize_container_element", S_Failed);
			return;
		}
		
		streamRead.setXmlString(streamWrite.getXmlString().c_str());
		if(!(streamRead >> objDeserialize))
		{
			output_msg("speed_serialize_container_element Deserialize", S_Failed);
			return;
		}
		
		if (objSerialize == objDeserialize)
		{
			int nelpse = GetTickCount() - nStart;
			std::cout << "Serialize Element Container [Size]=" << nSize << " [Time]=" << nelpse << std::endl; 
		}
		else
		{
			output_msg("speed_serialize_container_element obj equal", S_Failed);
		}
	}
}

void XML_Testor::speed_test_serialize_container_object_file()
{
	output_msg("speed_test_serialize_container_object", S_Begin);

	//write file 
	for (int i = 0; i < 15; ++i)
	{
		static std::stringstream ss;
		ss.str("");
		ss << "speed_test_serialize_container_object";
		ss << i;
		ss << ".xml";
		const std::string strFile = getFilePath(ss.str());

		int nSize = (int)pow(double(2.0), double(i));

		XmlSerialize::XmlSerializeStreamFile streamWrite(strFile.c_str()),
			streamRead(strFile.c_str());
		XML_Container_Object objSerialize(nSize), objDeserialize;

		int nStart = GetTickCount();

		if(!(streamWrite << objSerialize))
		{
			output_msg("speed_serialize_container_element", S_Failed);
			return;
		}

		if(!(streamRead >> objDeserialize))
		{
			output_msg("speed_serialize_container_element Deserialize", S_Failed);
			return;
		}

		if (objSerialize == objDeserialize)
		{
			int nelpse = GetTickCount() - nStart;
			std::cout << "Serialize Element Container [Size]=" << nSize << " [Time]=" << nelpse << std::endl; 
		}
		else
		{
			output_msg("speed_serialize_container_element obj equal", S_Failed);
		}
	}
}

void XML_Testor::runTest()
{
	base_test();

	speed_test();
}

void XML_Testor::test_serialize_attribute()
{
	output_msg("test_serialize_attribute", S_Begin);

	XmlSerialize::XmlSerializeStreamFile streamWrite(getFilePath("test_serialize_attribute.xml").c_str()),
		streamRead(getFilePath("test_serialize_attribute.xml").c_str());

	XML_Attribute_Object objSerialize, objDeserialize;

	if(!(streamWrite << objSerialize))
	{
		output_msg("test_serialize_attribute", S_Failed);
		return;
	}

	if(!(streamRead >> objDeserialize))
	{
		output_msg("test_serialize_attribute Deserialize", S_Failed);
		return;
	}
	
	if (objSerialize == objDeserialize)
	{
		output_msg("test_serialize_attribute obj equal", S_SUCCESS);
	}
	else
	{
		output_msg("test_serialize_attribute obj equal", S_Failed);
	}
}

void XML_Testor::test_serialize_element()
{
	output_msg("test_serialize_element", S_Begin);

	XmlSerialize::XmlSerializeStreamFile streamWrite(getFilePath("test_serialize_element.xml").c_str()),
		streamRead(getFilePath("test_serialize_element.xml").c_str());
	XML_Element_Object objSerialize, objDeserialize;

	if(!(streamWrite << objSerialize))
	{
		output_msg("test_serialize_element", S_Failed);
		return;
	}

	if(!(streamRead >> objDeserialize))
	{
		output_msg("test_serialize_element Deserialize", S_Failed);
		return;
	}

	if (objSerialize == objDeserialize)
	{
		output_msg("test_serialize_element obj equal", S_SUCCESS);
	}
	else
	{
		output_msg("test_serialize_element obj equal", S_Failed);
	}
}

void XML_Testor::test_serialize_container_element()
{
	output_msg("test_serialize_container_element", S_Begin);

	XmlSerialize::XmlSerializeStreamFile streamWrite(getFilePath("test_serialize_container_element.xml").c_str()),
		streamRead(getFilePath("test_serialize_container_element.xml").c_str());
	
	XML_Container_Element_Object objSerialize(5), objDeserialize;

	if(!(streamWrite << objSerialize))
	{
		output_msg("test_serialize_container_element", S_Failed);
		return;
	}

	if(!(streamRead >> objDeserialize))
	{
		output_msg("test_serialize_container_element Deserialize", S_Failed);
		return;
	}

	if (objSerialize == objDeserialize)
	{
		output_msg("test_serialize_container_element obj equal", S_SUCCESS);
	}
	else
	{
		output_msg("test_serialize_container_element obj equal", S_Failed);
	}

	{
		XmlSerialize::XmlSerializeStreamFile streamWriteNoUTF8(getFilePath("test_serialize_container_element_no_utf8.xml").c_str());
		streamWriteNoUTF8.setXMLCoding(XmlSerialize::XmlSerializeStream::XML_ANSI);
		if (streamWriteNoUTF8 << objSerialize)
		{

		}
	}
}

void XML_Testor::test_serialize_container_object()
{
	output_msg("test_serialize_container_object", S_Begin);

	XmlSerialize::XmlSerializeStreamFile streamWrite(getFilePath("test_serialize_container_object.xml").c_str()),
		streamRead(getFilePath("test_serialize_container_object.xml").c_str());
	XML_Container_Object objSerialize(2), objDeserialize;

	if(!(streamWrite << objSerialize))
	{
		output_msg("test_serialize_container_object", S_Failed);
		return;
	}

	if(!(streamRead >> objDeserialize))
	{
		output_msg("test_serialize_container_object Deserialize", S_Failed);
		return;
	}

	if (objSerialize == objDeserialize)
	{
		output_msg("test_serialize_container_object obj equal", S_SUCCESS);
	}
	else
	{
		output_msg("test_serialize_container_object obj equal", S_Failed);
	}
}

void XML_Testor::test_xml_reflect_container_object()
{
	output_msg("test_xml_reflect_container_object", S_Begin);

	XmlSerialize::XmlSerializeStreamFile streamWrite(getFilePath("test_xml_reflect_container_object.xml").c_str()),
		streamRead(getFilePath("test_xml_reflect_container_object.xml").c_str());
	CGroupReflectedContainerObject objSerialize(2), objDeserialize;

	if(!(streamWrite << objSerialize))
	{
		output_msg("test_xml_reflect_container_object", S_Failed);
		return;
	}

	if(!(streamRead >> objDeserialize))
	{
		output_msg("test_xml_reflect_container_object Deserialize", S_Failed);
		return;
	}

	if (objSerialize == objDeserialize)
	{
		output_msg("test_xml_reflect_container_object obj equal", S_SUCCESS);
	}
	else
	{
		output_msg("test_xml_reflect_container_object obj equal", S_Failed);
	}
}