#include "xerces_dom_test.h"
#include "DTest.h"
#include "xercesc\parsers\XercesDOMParser.hpp"
#include <xercesc\sax\HandlerBase.hpp>
#include <xercesc\sax\SAXException.hpp>

using namespace std;

IMPLEMENT_REFLECTED_CLASS(xerces_dom_test)
xerces_dom_test::xerces_dom_test()
{
	
}

xerces_dom_test::~xerces_dom_test()
{
	
}

void xerces_dom_test::run()
{
	read_with_chinese();
	write_with_chinese();

	DOMTest::test();
}

std::string xerces_dom_test::getString( const XMLCh *pch )
{
	char* str = XMLString::transcode(pch);
	std::string strDst(str);
	XMLString::release(&str);
	
	return strDst;
}


std::string get(int i)
{
	string sss;
	for (int s = 0; s < i; ++s)
	{
		sss += "--";
	}

	sss += ">";
	return sss;
}

void print(DOMNode* pNode);
void print(DOMNodeList* lstNode);

void print(DOMNode* pNode)
{
	if (!pNode)
	{
		return;
	}

	//////////////////////////////////////////////////////////////////////////
	{
		DOMNode::NodeType at = pNode->getNodeType();

		std::string sa = XERCES_STRING(pNode->getNodeName());
		std::cout << sa << std::endl;

		DOMNamedNodeMap* trributs = pNode->getAttributes();
		if (trributs)
		{
			for (int j = 0; j < trributs->getLength(); ++j)
			{
				DOMNode* att = trributs->item(j);

				if (att != NULL)
				{
					at = att->getNodeType();

					std::string s1 = XERCES_STRING(att->getNodeName());
					//std::cout << s1 << std::endl;

					std::string s2 = XERCES_STRING(att->getNodeValue());
					//std::cout << s2 << std::endl;
				}
			}
		}
	}
	
	
	//////////////////////////////////////////////////////////////////////////
	if (pNode->hasChildNodes())
	{
		print(pNode->getChildNodes());
	}

	while (pNode = pNode->getNextSibling())
	{
		print(pNode);
	} 
}

void print(DOMNodeList* lstNode)
{
	for (int i = 0; i < lstNode->getLength(); ++i)
	{
		DOMNode* pNode = lstNode->item(i);
		
		print(pNode);
	}
}

bool xerces_dom_test::read_with_chinese()
{
	try {
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch) {
		char *pMessage = XMLString::transcode(toCatch.getMessage());
		fprintf(stderr, "Error during initialization! \n  %s \n", pMessage);
		XMLString::release(&pMessage);
		return false;
	}

	const QString& strFilePath = QtProjectPath::DirPaths::GetAppRootDataPath();
	const QString& strFileDom1 = strFilePath + "/xerces_data" + "/dom_chinese.xml";
	try
	{
		XercesDOMParser* parser = new XercesDOMParser();
		parser->setValidationScheme(XercesDOMParser::Val_Always);
		parser->setDoNamespaces(true);
		ErrorHandler* err = (ErrorHandler*)new HandlerBase();
		parser->setErrorHandler(err);

		parser->parse(strFileDom1.toLocal8Bit().data());
		XERCES_CPP_NAMESPACE::DOMDocument *doc = parser->getDocument();
		
		std::string strInputEncoding = XERCES_STRING(doc->getInputEncoding());
		string strXmlEncoding = XERCES_STRING(doc->getXmlEncoding());

		DOMNode* node = doc->getFirstChild();
		print(node);
	}
	catch(const XMLException& e)
	{
		char *pMessage = XMLString::transcode(e.getMessage());
		fprintf(stderr, "Error during initialization! \n  %s \n", pMessage);
		XMLString::release(&pMessage);
		return false;
	}
	catch(const DOMException& e)
	{
		char *pMessage = XMLString::transcode(e.getMessage());
		fprintf(stderr, "Error during initialization! \n  %s \n", pMessage);
		XMLString::release(&pMessage);
		return false;
	}
	catch(const SAXException& e)
	{
		char *pMessage = XMLString::transcode(e.getMessage());
		fprintf(stderr, "Error during initialization! \n  %s \n", pMessage);
		XMLString::release(&pMessage);
		return false;
	}
	catch(...)
	{
		return false;
	}

	

}

bool xerces_dom_test::write_with_chinese()
{
	return true;
}
