#ifndef LiskovSubstitutionPrinciple_h__
#define LiskovSubstitutionPrinciple_h__

#include <string>
#include <vector>
#include <map>
#include <list>
#include <glog.h>
#include "boost\smart_ptr\shared_ptr.hpp"

namespace LiskovSubstitutionPrinciple
{
	class MyObjectBase
	{
	public:
		virtual std::string run()const
		{
			return "This is MyObjectBase...";
		}
	};

	class MyObject1 : public MyObjectBase
	{
	public:
		virtual std::string run()const
		{
			return "This is MyObject1...";
		}
	};

	class father
	{
	public:
		father(){}

		virtual void Say(const MyObjectBase& obj)
		{
			LOG(INFO) << "fater Say:" << obj.run();
		}

		void dosomthing(const MyObjectBase& obj)
		{
			LOG(INFO) << "father dosomthing:" << obj.run();
		}

		void dosomthing1(MyObjectBase& obj)
		{
			LOG(INFO) << "father111:" << obj.run();
		}
	};

	class child : public father
	{
	public:
		child(){}

		virtual void Say(const MyObjectBase& obj)
		{
			LOG(INFO) << "child Say:" << obj.run();
		}

		void dosomthing(const MyObjectBase& obj)
		{
			LOG(INFO) << "child dosomthing:" << obj.run();
		}

		void dosomthing1(MyObject1& obj)
		{
			LOG(INFO) << "child111:" << obj.run();
		}
	};

	static void run()
	{
		{
			boost::shared_ptr<father> fatherobj(new father);
			MyObjectBase obj;
			fatherobj->Say(obj);

			fatherobj.reset(new child);
			fatherobj->Say(obj);
		}

		{
			boost::shared_ptr<father> fatherobj(new father);
			MyObjectBase obj;
			fatherobj->dosomthing(obj);

			fatherobj.reset(new child);
			fatherobj->dosomthing(obj);
		}

		{
			father fatherobj;
			child childobj;

			MyObjectBase obj;
			fatherobj.dosomthing1(obj);

			MyObject1 obj1;
			childobj.dosomthing1(*(MyObject1*)&obj);
		}
		
	}
}


#endif // LiskovSubstitutionPrinciple_h__
