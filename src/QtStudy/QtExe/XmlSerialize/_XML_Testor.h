#ifndef _H__XML_TESTOR_H_
#define _H__XML_TESTOR_H_

class XML_Testor
{
public:
	XML_Testor(){}

	static void runTest();
protected:
	static void base_test();
	void test_serialize_attribute();
	void test_serialize_element();
	void test_serialize_container_element();
	void test_serialize_container_object();
	void test_xml_reflect_container_object();

	static void speed_test();
	void speed_serialize_container_element();
	void speed_test_serialize_container_object_mem();
	void speed_test_serialize_container_object_file();
};

#endif //_H__XML_TESTOR_H_