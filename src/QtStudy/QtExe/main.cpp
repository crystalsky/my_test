#include <QApplication>
#include "mainwindow.h"
#include "glogInit.h"
#include <iostream>
#include <iosfwd>
#include "def.h"
#include <QRegExp>

namespace dtUtil
{
   /**
    * Templated function to provide a generic object construction
    * utility.
    */
   template<typename BaseType, typename DerivedType>
   BaseType *construct()
   {
      return new DerivedType();
   }

   /**
    * This class is a template object factory.  It allows one to
    * create any type of object as long as there is a common base
    * class.  The common base class is defined on a per-factory
    * basis using the templated parameter <code>BaseType</code>.
    * @note
    *   The ObjectFactory implementation only supports objects with
    *   a default constructor.  It will not work with objects that
    *   only have named constructors.
    */
   template<typename UniqueIdTypeClass,typename BaseTypeClass,typename ltCmpClass=std::less<UniqueIdTypeClass> >
   class ObjectFactory
   {
   public:

      typedef UniqueIdTypeClass UniqueIdType;
      typedef BaseTypeClass BaseType;
      typedef ltCmpClass ltCmp;

      typedef BaseType *(*createObjectFunc)(); /// Function pointer type for functions creating objects.
      typedef std::map<UniqueIdType,createObjectFunc,ltCmp> ObjectMap;
	  typedef std::map<std::string, createObjectFunc> ObjectNameMap;
      typedef typename ObjectMap::iterator ObjTypeItor;
      typedef typename ObjectMap::const_iterator ObjTypeItorConst;
      ObjectFactory() {}  // constructor


      virtual ~ObjectFactory() {}

   public:
      /**
       * Registers a new type of object with the factory.
       * @return false if the type is a duplicate.
       */
      template<typename DerivedType>
      bool RegisterType(UniqueIdType id)
      {
         if (this->objectTypeMap.find(id) != this->objectTypeMap.end())
         {
            return false;
         }

		 {
			 const std::string& cs = "class";
			 std::string strName = typeid(DerivedType).name();
			 int nClassIndex = strName.find(cs);
			 if (nClassIndex != std::string::npos)
			 {
				 strName = strName.substr(nClassIndex + cs.length() + 1, strName.length() - (cs.length() + 1));
			 }


			 this->objectNameMap[strName] = &construct<BaseType,DerivedType>;
		 }
		 

         this->objectTypeMap[id] = &construct<BaseType,DerivedType>;
         return true;
      }

      /**
       * Removes an existing object type from the factory's known list
       * of object types.
       */
      void RemoveType(UniqueIdType id) {
         this->objectTypeMap.erase(id);
      }

      /**
       * Checks to see if the factory can create objects of the given type.
       * @param id The type of object to check for.
       * @return True if the type is supported, false otherwise.
       */
      bool IsTypeSupported(UniqueIdType id) const
      {
         ObjTypeItorConst itor(this->objectTypeMap.find(id));
         if (itor != this->objectTypeMap.end())
         {
            return true;
         }
         else
         {
            return false;
         }
      }

      /**
       * Gets a list of types that this factory knows how to create.
       */
      void GetSupportedTypes(std::vector<UniqueIdType> &types) const
      {
         types.clear();
         for (ObjTypeItorConst itor=this->objectTypeMap.begin();
            itor != this->objectTypeMap.end(); ++itor)
         {
            types.push_back(itor->first);
         }
      }

      /**
       * Creates a new object.
       * @param id - Type of object to create.
       * @return Returns a pointer to the newly created object or NULL if the given id has not been registered.
       * @throw Exception is thrown if the factory does not know how to create
       *  the requested type.
       */
      BaseType* CreateObject(const UniqueIdType id) const
      {
         ObjTypeItorConst itor(this->objectTypeMap.find(id));

         // We cannot create a new object if we do not know what type it is
         // so throw an exception.
         if (itor == this->objectTypeMap.end())
         {
            return NULL;
         }

         return (itor->second)();
      }

      const ObjectMap& GetMap() const { return objectTypeMap; }

   private:
      ///Maps a unique id to a function pointer that when called creates an
      ///object of the appropriate type.
      ObjectMap objectTypeMap;
	  ObjectNameMap objectNameMap;
   };
}

class Base
{
public:
	Base(){}
};

class myType1 : public Base
{
public:
	myType1(){}
};
class myType2 : public Base
{
public:
	myType2(){}
};

class myType3 : public Base
{
public:
	myType3(){}
};



class TypeT
{
public:
	TypeT(int n){this->m_n = n;}

	bool operator < (const TypeT& t)const
	{
		
		return this->m_n < t.m_n;
	}

private:
	int m_n;
};


dtUtil::ObjectFactory<TypeT, Base>  mActorFactory;




int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

	glogInit::GetInstance()->init(argv[0]);


	mActorFactory.RegisterType<myType1>(TypeT(1));
	mActorFactory.RegisterType<myType2>(TypeT(2));
	mActorFactory.RegisterType<myType3>(TypeT(3));



	LOG(INFO) << "11111:" << g_nVal;
	LOG(INFO) << "22222:" << AAA;
	const QString& str = 
		"file:///H:/XWorkX/CodeStudy/_my_study/data/QML/property_binding.qml:87:40: Unable to assign QString to double";
	const bool b = str.contains(QRegExp("\\bfile:///"));
	const bool b2 = str.contains(QRegExp("\\bfile:///"));
	const bool b3 = str.contains(QRegExp(":\\d+:\\d+:"));
	if (b)
	{
		LOG(ERROR) << "..." << str.toLocal8Bit().data();
	}


	MainWindow mainWin;
    mainWin.show();
    int n = app.exec();

	glogInit::ExitInstance();

	return n;
}
