/*
* Licensed to the Apache Software Foundation (ASF) under one or more
* contributor license agreements.  See the NOTICE file distributed with
* this work for additional information regarding copyright ownership.
* The ASF licenses this file to You under the Apache License, Version 2.0
* (the "License"); you may not use this file except in compliance with
* the License.  You may obtain a copy of the License at
* 
*      http://www.apache.org/licenses/LICENSE-2.0
* 
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*
* $Id: DTest.h 806472 2009-08-21 09:19:38Z amassari $
*/


/**
* This class tests methods for XML DOM implementation
*
* DOMException errors are tested by calls to DOMExceptionsTest from: Main, docBuilder...
*
*/

#include <xercesc/dom/DOM.hpp>

//  define null for compatibility with original Java source code.
#define null 0

XERCES_CPP_NAMESPACE_USE

	XERCES_CPP_NAMESPACE_BEGIN
class XercesDOMParser;
class XERCES_CPP_NAMESPACE::DOMDocument;
XERCES_CPP_NAMESPACE_END


class DOMTest {
public:
	static int test();
public:
	static DOMElement           *testElementNode;
	static DOMAttr              *testAttributeNode;
	static DOMText              *testTextNode;
	static DOMCDATASection      *testCDATASectionNode;
	static DOMEntityReference   *testEntityReferenceNode;
	static DOMEntity            *testEntityNode;
	static DOMProcessingInstruction *testProcessingInstructionNode;
	static DOMComment           *testCommentNode;
	static XERCES_CPP_NAMESPACE::DOMDocument          *testDocumentNode;
	static XERCES_CPP_NAMESPACE::DOMDocumentType      *testDocumentTypeNode;
	static XERCES_CPP_NAMESPACE::DOMDocumentFragment  *testDocumentFragmentNode;
	static DOMNotation          *testNotationNode;


	DOMTest();

	XERCES_CPP_NAMESPACE::DOMDocument* createDocument();
	XERCES_CPP_NAMESPACE::DOMDocumentType* createDocumentType(XERCES_CPP_NAMESPACE::DOMDocument* doc, XMLCh* name);
	DOMEntity* createEntity(XERCES_CPP_NAMESPACE::DOMDocument* doc, XMLCh* name);
	DOMNotation* createNotation(XERCES_CPP_NAMESPACE::DOMDocument* doc, XMLCh* name);
	bool docBuilder(XERCES_CPP_NAMESPACE::DOMDocument* document, XMLCh* name);

	void findTestNodes(XERCES_CPP_NAMESPACE::DOMDocument* document);
	void findTestNodes(DOMNode* node);


	bool testAttr(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testCDATASection(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testCharacterData(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testChildNodeList(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testComment(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testDeepNodeList(XERCES_CPP_NAMESPACE::DOMDocument* document);

	/**
	**** ALL XERCES_CPP_NAMESPACE::DOMDocument create methods are run in docBuilder except createAttribute which is in testAttribute**
	*/
	bool testDocument(XERCES_CPP_NAMESPACE::DOMDocument* document);


	/**
	********This really isn't needed, only exists to throw NO_MODIFICATION_ALLOWED_ERR ********
	*/
	bool testDocumentFragment(XERCES_CPP_NAMESPACE::DOMDocument* document);

	bool testDocumentType(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testDOMerrors(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testXPath(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testDOMImplementation(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testElement(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testEntity(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testEntityReference(XERCES_CPP_NAMESPACE::DOMDocument* document);


	/**
	********* This is only for a test of cloneNode "deep"*******
	********* And for error tests*********
	*/
	bool testNode(XERCES_CPP_NAMESPACE::DOMDocument* document);

	bool testNotation(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testPI(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool testText(XERCES_CPP_NAMESPACE::DOMDocument* document);
	bool treeCompare(DOMNode* node, DOMNode* node2);

	bool testBaseURI(XercesDOMParser* parser);
	bool testWholeText(XercesDOMParser* parser);
	bool testLSExceptions();
	bool testElementTraversal();

	bool testRegex();
	bool testScanner(XercesDOMParser* parser);
	bool testUtilFunctions();

};

class myUserDataHandler : public DOMUserDataHandler {
private:
	DOMOperationType currentType;
	XMLCh* currentKey;
	void* currentData;
	DOMNode* currentSrc;
	DOMNode* currentDst;

public:
	myUserDataHandler() :
		currentKey(0),
		currentData(0),
		currentSrc(0),
		currentDst(0) {};

	virtual void handle(DOMOperationType operation,
		const XMLCh* const key,
		void* data,
		const DOMNode* src,
		DOMNode* dst)
	{
		currentType = operation;
		currentKey = (XMLCh*) key;
		currentData = data;
		currentSrc = (DOMNode*) src;
		currentDst = dst;
	};

	DOMOperationType getCurrentType() {
		return currentType;
	};
	XMLCh* getCurrentKey() const {
		return currentKey;
	};
	void* getCurrentData() const {
		return currentData;
	};
	DOMNode* getCurrentSrc() const {
		return currentSrc;
	};
	DOMNode* getCurrentDst() const {
		return currentDst;
	};

};


