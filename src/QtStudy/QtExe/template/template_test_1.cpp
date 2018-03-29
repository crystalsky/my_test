#include "template_test_1.h"
#include <boost/shared_ptr.hpp>
#include <list>
#include <vector>
#include <QVector>
#include <QList>
#include <deque>
#include <QSharedPointer>
#include <tp_typetraits.h>
#include "data_gen_functions.h"

namespace XmlSerialize
{
	class TinyXmlSerializer;
}

struct data
{
	int a;
	std::string b;
	data()
	{
		this->a = data_gen_functions::genInt();
		this->b = data_gen_functions::genString(data_gen_functions::genBool());
	}

	virtual bool check()const
	{
		return false;
	}

	friend std::ostream& operator << (std::ostream& o, const data& d);
};

struct data2 : public data
{

};

std::ostream& operator <<(std::ostream& o, const data& d)
{
	o << "IntVal:[" << d.a << "]" << " string:[" << d.b << "]";
	return o;
}

template<typename T, typename Container>
struct MyTypeInfo
{
	enum{
		isPointer = false,
		isSharedPointer = false,
		isStatic = true
	};

	MyTypeInfo()
	{
		
	}

	typedef typename Container::const_iterator IterContainer;

	typedef typename T value_type;
	typedef typename T return_type;
	typedef typename const T& const_reference_type;

	static return_type createValueType()
	{
		return value_type();
	}
	static const_reference_type referenceType(const IterContainer& iter)
	{
		return *iter;
	}
};

template<typename T, typename Container>
struct MyTypeInfo<T*, Container>
{
	enum{
		isPointer = true,
		isSharedPointer = false,
		isStatic = false
	};

	MyTypeInfo()
	{
		

	}
	typedef typename Container::const_iterator IterContainer;

	typedef typename T value_type;
	typedef typename T* return_type;
	typedef typename const T& const_reference_type;
	static return_type createValueType()
	{
		return new value_type();
	}

	static const_reference_type referenceType(const IterContainer& iter)
	{
		return *(*iter);
	}
};

template<typename T, typename Container>
struct MyTypeInfo<boost::shared_ptr<T>, Container>
{
	enum{
		isPointer = false,
		isSharedPointer = true,
		isStatic = false
	};
	typedef typename Container::const_iterator IterContainer;

	typedef typename boost::shared_ptr<T> value_type;
	typedef typename boost::shared_ptr<T> return_type;
	typedef typename const T& const_reference_type;
	static return_type createValueType()
	{
		return value_type(new T());
	}

	static const_reference_type referenceType(const IterContainer& iter)
	{
		return *((*iter).get());
	}
};

template<typename T, typename Container>
struct MyTypeInfo<QSharedPointer<T>, Container>
{
	enum{
		isPointer = false,
		isSharedPointer = true,
		isStatic = false
	};
	typedef typename Container::const_iterator IterContainer;

	typedef typename QSharedPointer<T> value_type;
	typedef typename QSharedPointer<T> return_type;
	typedef typename const T& const_reference_type;
	static return_type createValueType()
	{
		return value_type(new T());
	}

	static const_reference_type referenceType(const IterContainer& iter)
	{
		return *((*iter).data());
	}
};


template<typename Container>
class RealContainer
{
public:
	typedef typename  Container::value_type Real_Container_Value_Type;
	typedef typename Container::const_iterator CItor;

	template<typename T>
	struct _TypeInfo : public UtilityKit::TypeTraits<T>
	{
		typedef typename UtilityKit::TypeTraits<T>::return_type this_return_type;
		static this_return_type createValueType()
		{
			static UtilityKit::TypeTraits<T>::value_type sVal;
			sVal = UtilityKit::TypeTraits<T>::value_type();
			return sVal;
		}

		typedef typename UtilityKit::TypeTraits<T>::const_reference this_const_ref;
		static this_const_ref iterRef(CItor iter)
		{
			return *iter;
		}

		static void release(CItor iter)
		{

		}
	};

	template<typename T>
	struct _TypeInfo<T*> : public UtilityKit::TypeTraits<T*>
	{
		typedef typename UtilityKit::TypeTraits<T*>::return_type this_return_type;
		static this_return_type createValueType()
		{
			return new UtilityKit::TypeTraits<T*>::value_type();
		}

		typedef typename UtilityKit::TypeTraits<T*>::const_reference this_const_ref;
		static this_const_ref iterRef(CItor iter)
		{
			return **iter;
		}
	};

	template<typename T>
	struct _TypeInfo<boost::shared_ptr<T>> : public UtilityKit::TypeTraits<boost::shared_ptr<T>>
	{
		typedef typename UtilityKit::TypeTraits<boost::shared_ptr<T>>::value_type this_return_type;
		static this_return_type createValueType()
		{
			return UtilityKit::TypeTraits<boost::shared_ptr<T>>::value_type(new T());
		}

		typedef typename const T& this_const_ref;
		static this_const_ref iterRef(CItor iter)
		{
			return *((*iter).get());
		}
	};

	template<typename T>
	struct _TypeInfo<QSharedPointer<T>> : public UtilityKit::TypeTraits<QSharedPointer<T>>
	{
		typedef typename UtilityKit::TypeTraits<QSharedPointer<T>>::value_type this_return_type;
		static this_return_type createValueType()
		{
			return UtilityKit::TypeTraits<QSharedPointer<T>>::value_type(new T());
		}

		typedef typename const T& this_const_ref;
		static this_const_ref iterRef(CItor iter)
		{
			return *((*iter).data());
		}
	};
	
	Real_Container_Value_Type createValue()
	{
		return _TypeInfo<Real_Container_Value_Type>::createValueType();
	}

public:
	RealContainer(Container& myCon) : m_con(myCon)
	{
		std::cout 
			<<"value_type: " << typeid(Real_Container_Value_Type).name() <<" \n"
			<< "IsPointer: "<< UtilityKit::IsPointer<Real_Container_Value_Type>::IS_POINTER << " " 
			<< std::endl << std::endl;

		for (int i = 0; i < 5; i++)
		{
			Real_Container_Value_Type val = 
				_TypeInfo<Real_Container_Value_Type>::createValueType();
			m_con.push_back(val);
		}
	}

	~RealContainer()
	{
		//_TypeInfo<Real_Container_Value_Type>::clear
		//for (CItor iter = m_con.begin(); iter != m_con.end(); ++iter)
		//{
			//_TypeInfo<Real_Container_Value_Type>::release(iter);
		//}
	}

	bool isEmpty()const
	{
		return m_begin == m_end;
	}

	void print()
	{
		typedef typename _TypeInfo<Real_Container_Value_Type>::this_const_ref rt;
		for (CItor ibegin = m_con.cbegin(); ibegin != m_con.cend(); ++ibegin)
		{
			rt t= _TypeInfo<Real_Container_Value_Type>::iterRef(ibegin);
			std::cout << t << std::endl << std::endl;
		}
	}

	//IterBegin begin()const{return m_begin;}
	//IterEnd end()const{return m_end;}
private:
	//IterBegin m_begin;
	//IterEnd m_end;
	Container& m_con;
};

template<typename T, typename Container>
class MyContainer
{
public:
	typename typedef Container::const_iterator MyContainerIter;
	typename typedef Container::value_type Container_Value_Type;;
	typedef MyContainerIter IterBegin;
	typedef MyContainerIter IterEnd;
public:
	MyContainer(){
		std::cout << typeid(Container::value_type).name() << std::endl;
		for (int i = 0; i < 10; i++)
		{
			if(MyTypeInfo<T, Container>::isStatic)
			{
				m_con.push_back(MyTypeInfo<T, Container>::createValueType());
				std::cout << "isStatic" << std::endl;
			}
			else if (MyTypeInfo<T, Container>::isPointer)
			{
				m_con.push_back(MyTypeInfo<T, Container>::createValueType());
				std::cout << "isPointer" << std::endl;
			}
			else if (MyTypeInfo<T, Container>::isSharedPointer)
			{
				m_con.push_back(MyTypeInfo<T, Container>::createValueType());
				std::cout << "isSharedPointer" << std::endl;
			}
		}
		m_begin = m_con.cbegin();
		m_end = m_con.cend();
	}

	bool isEmpty()const
	{
		return m_begin == m_end;
	}

	void print()
	{
		typedef typename MyTypeInfo<T, Container>::const_reference_type ctype;
		for (MyContainerIter ibegin = begin(); ibegin != end(); ++ibegin)
		{
			ctype t= MyTypeInfo<T, Container>::referenceType(ibegin);
			std::cout << t << std::endl;
		}
	}

	IterBegin begin()const{return m_begin;}
	IterEnd end()const{return m_end;}
private:
	IterBegin m_begin;
	IterEnd m_end;
	Container m_con;
};

using namespace UtilityKit;
template<typename Container>
class serialize_container
{
public:
	typedef typename Container::value_type container_value_type;
	typedef typename Container::const_iterator container_const_iterator;
	typedef typename Container::iterator container_iterator;

protected:
#pragma region _serialize_types
	template<typename U>
	struct _serialize_types : public TypeTraits<U>
	{
		typedef typename TypeTraits<U>::return_type			t_return_type;
		typedef typename TypeTraits<U>::const_reference		t_const_ref;
		typedef typename TypeTraits<U>::pointer_type		t_pointer;

		static t_return_type create_value()
		{
			static TypeTraits<U>::value_type sVal;
			sVal = TypeTraits<U>::value_type();
			return sVal;
		}

		static void clearContainer(Container& con)
		{
			con.clear();
		}

		static t_const_ref const_ref_val(container_const_iterator iter)
		{
			return *iter;
		}

		static t_pointer getValuePointer(Container& con, int nIndex)
		{
			t_pointer p = &con[nIndex];
			return p;
		}
	};

	template<typename U>
	struct _serialize_types<U*> : public TypeTraits<U*>
	{
		typedef typename TypeTraits<U*>::return_type		t_return_type;
		typedef typename TypeTraits<U*>::const_reference	t_const_ref;
		typedef typename TypeTraits<U*>::pointer_type		t_pointer;

		static t_return_type create_value()
		{
			return new TypeTraits<U*>::value_type();
		}

		static t_const_ref const_ref_val(container_const_iterator iter)
		{
			return **iter;
		}

		static void clearContainer(Container& con)
		{
			for (container_const_iterator ci = con.cbegin();
				ci != con.cend();
				++ci)
			{
				delete *ci;
			}

			con.clear();
		}

		static t_pointer getValuePointer(Container& con, int nIndex)
		{
			t_pointer p = con[nIndex];
			return p;
		}
	};

	template<typename U>
	struct _serialize_types<boost::shared_ptr<U>> : public TypeTraits<boost::shared_ptr<U>>
	{
		typedef typename TypeTraits<boost::shared_ptr<U>>::value_type	t_return_type;
		typedef typename const U&										t_const_ref;
		typedef typename U*												t_pointer;

		static t_return_type create_value()
		{
			return TypeTraits<boost::shared_ptr<U>>::value_type(new U());
		}

		static t_const_ref const_ref_val(container_const_iterator iter)
		{
			return *((*iter).get());
		}

		static void clearContainer(Container& con)
		{
			con.clear();
		}

		static t_pointer getValuePointer(Container& con, int nIndex)
		{
			t_pointer p = con[nIndex].get();
			return p;
		}
	};

	template<typename U>
	struct _serialize_types<QSharedPointer<U>> : public TypeTraits<QSharedPointer<U>>
	{
		typedef typename TypeTraits<QSharedPointer<U>>::value_type	t_return_type;
		typedef typename const U&									t_const_ref;
		typedef typename U*											t_pointer;

		static t_return_type create_value()
		{
			return TypeTraits<QSharedPointer<U>>::value_type(new U());
		}

		static t_const_ref const_ref_val(container_const_iterator iter)
		{
			return *((*iter).data());
		}

		static void clearContainer(Container& con)
		{
			con.clear();
		}

		static t_pointer getValuePointer(Container& con, int nIndex)
		{
			t_pointer p = con[nIndex].data();
			return p;
		}
	};
	#pragma endregion
public:
	typedef typename _serialize_types<container_value_type>::t_return_type	return_type;
	typedef typename _serialize_types<container_value_type>::t_const_ref	const_reference;
	typedef typename _serialize_types<container_value_type>::t_pointer		pointer_type;
public:
	serialize_container(Container& con)
		: m_con(con)
	{

	}

	void resize(int nSize)
	{
		if (nSize < 1)
		{
			return;
		}

		for (int i = 0; i < nSize; ++i)
		{
			return_type val = _serialize_types<container_value_type>::create_value();
			m_con.push_back(val);
		}
	}

	void print()
	{		
		for (container_const_iterator ibegin = m_con.cbegin(); ibegin != m_con.cend(); ++ibegin)
		{
			const_reference t= _serialize_types<container_value_type>::const_ref_val(ibegin);
			std::cout << t << std::endl;
		}
	}

	pointer_type operator[](unsigned int nidex)const
	{
		pointer_type p = NULL;
		if (nidex >= 0 && nidex < m_con.size())
		{
			p = _serialize_types<container_value_type>::getValuePointer(m_con, nidex);
		}
		return p;
	}

	bool serailize(XmlSerialize::TinyXmlSerializer& xmlSerializerObj)const
	{

	}

	void clear()
	{
		_serialize_types<container_value_type>::clearContainer(m_con);
	}

	const_reference const_reference_val(container_const_iterator iter)
	{
		return _serialize_types<container_value_type>::const_ref(iter);
	}
private:
	Container& m_con;
};

IMPLEMENT_REFLECTED_CLASS(template_test_1)
template_test_1::template_test_1()
{
	
}

template_test_1::~template_test_1()
{
	
}



void template_test_1::run()
{
	test_serialize_container();

	test_MyContainer();

	test_RealContainer();
}

void template_test_1::test_serialize_container()
{
	{
		std::vector<data> c;
		serialize_container<std::vector<data>> tc(c);
		tc.resize(3);
		tc.print();

		data* d1 = tc[0];
		if (d1 != NULL)
		{
			d1->a = 111444;
		}

// 		for (std::vector<data>::const_iterator iter = c.cbegin();
// 			iter != c.cend();
// 			++iter)
// 		{
// 			data& d = *iter;
// 		}

		tc.print();
	}

	{
		std::vector<data*> c;
		serialize_container<std::vector<data*>> tc(c);
		tc.resize(3);
		tc.print();

		data* d1 = tc[0];
		if (d1 != NULL)
		{
			d1->a = 111444;
		}

// 		for (std::vector<data*>::const_iterator iter = c.cbegin();
// 			iter != c.cend();
// 			++iter)
// 		{
// 			const data* d = *iter;
// 			d->a = 12;
// 		}

		tc.print();
	}

	{
		std::vector<boost::shared_ptr<data>> c;
		serialize_container<std::vector<boost::shared_ptr<data>>> tc(c);
		tc.resize(3);
		tc.print();

		data* d1 = tc[0];
		if (d1 != NULL)
		{
			d1->a = 1;
		}

		/*for (std::vector<boost::shared_ptr<data>>::const_iterator iter = c.cbegin();
			iter != c.cend();
			++iter)
		{
			const boost::shared_ptr<data>& d = *iter;
			d->a = 12;
		}*/

		tc.print();
	}

	{
		std::vector<QSharedPointer<data>> c;
		serialize_container<std::vector<QSharedPointer<data>>> tc(c);
		tc.resize(3);
		tc.print();

		data* d1 = tc[0];
		if (d1 != NULL)
		{
			d1->a = 2;
		}

		tc.print();
	}
}

void template_test_1::test_MyContainer()
{
	MyContainer<int, std::vector<int>> vecInt;
	vecInt.print();

	MyContainer<data, std::vector<data>> vecData;
	vecData.print();

	MyContainer<boost::shared_ptr<data>, std::list<boost::shared_ptr<data>>> listSharedData;
	listSharedData.print();

	MyContainer<QSharedPointer<data>, std::list<QSharedPointer<data>>> listSharedData2;
	listSharedData2.print();

	MyContainer<int*, std::vector<int*>> vecintptr;
	vecintptr.print();
}

void template_test_1::test_RealContainer()
{
	std::vector<data> c1;
	std::vector<data*> c2;
	std::vector<boost::shared_ptr<data>> c3;
	std::vector<QSharedPointer<data>> c4;

	//boost::shared_ptr<data>::value_type;
	RealContainer<std::vector<data>> rc1(c1);
	rc1.print();

	RealContainer<std::vector<data*>> rc2(c2);
	rc2.print();

	RealContainer<std::vector<boost::shared_ptr<data>>> rc3(c3);
	rc3.print();

	RealContainer<std::vector<QSharedPointer<data>>> rc4(c4);
	rc4.print();

	std::deque<data> dc1;
	RealContainer<std::deque<data>> ddc1(dc1);
	ddc1.print();
}


