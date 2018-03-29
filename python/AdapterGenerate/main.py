import os
import xml.dom.minidom
from xml.dom.minidom import parse

#属性定义
class MemberVariable:
    def __init__(self):
        self.strLableName = ''	#属性中文名称(LableName)
        self.strCode = ''		#属性变量名
        self.strComment = ''	#属性注释
        self.strType = ''		#属性类型
        self.strParamOutOrIn = ''  #属性是输入还是输出

#模型信息
class ModuleInfo:
    def __init__(self):
        self.strModuleID = ''			#模型ID
        self.strParentModuleName = ''	    #父模型名
        self.strParentClassName = ''		    #父模型类名
        self.strCurrentModuleName = ''	    #当前模型名
        self.strCurrentClassName = ''	    #当前模型类名
        self.strCurrentClassComment = ''    #当前模型类注释
        self.strModuleCategory = ''         #模型类别
        self.strModuleName = ''			    #模型名称
        self.strPluginName = ''             #插件名
        self.strParentProxyClassName = ''  #父模型Proxy类名
        self.listMemberVariable = []    #所有成员变量定义

#读取模型信息
class ReadXML:
    def _readModuleProperties(self, elementModule, moduleInfo):
        eleProperties = elementModule.getElementsByTagName('Properties')[0]
        lstProperties = eleProperties.getElementsByTagName('Property')
        for property in lstProperties:



    def readxml(self, xmlfile):
        domTree = xml.dom.minidom.parse(xmlfile)
        modules = domTree.getElementsByTagName("Module")

        lstModules = []
        for mo in modules:
            temModuleInfo = ModuleInfo()
            self._readModuleProperties(mo, temModuleInfo)
            #if movie.hasAttribute("title"):
            #    print ("Title: %s" % movie.getAttribute("title"))
#
            #type = movie.getElementsByTagName('type')[0]
            #print ("Type: %s" % type.childNodes[0].data)
            #format = movie.getElementsByTagName('format')[0]
            #print ("Format: %s" % format.childNodes[0].data)
            #rating = movie.getElementsByTagName('rating')[0]
            #print ("Rating: %s" % rating.childNodes[0].data)
            #description = movie.getElementsByTagName('description')[0]
            #print ("Description: %s" % description.childNodes[0].data)

            lstModules.append(temModuleInfo)
        return lstModules
        

if ( __name__ == "__main__"):
    filePath = os.path.dirname(__file__) + "\\module_1.xml"
    
    readXML = ReadXML()
    lst = readXML.readxml(filePath)
    print("length", len(lst))