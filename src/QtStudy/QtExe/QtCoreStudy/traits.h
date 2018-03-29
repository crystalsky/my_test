#include "glog.h"

template<typename T>
class TypeInfo
{
public:
	enum{Is_Ptr = 0, Is_Ref = 0, Is_Array = 0};

	typedef T baseT;
	typedef T bottomT;
};

template<typename T>
class TypeInfo<T*>
{
public:
	enum{Is_Ptr = 1, Is_Ref = 0, Is_Array = 0};

	typedef T baseT;
	typedef typename TypeInfo<T>::bottomT bottomT;
};

template<typename T>
class TypeInfo<T&>
{
public:
	enum{Is_Ptr = 0, Is_Ref = 1, Is_Array = 0};
	typedef T baseT;
	typedef typename TypeInfo<T>::bottomT bottomT;
};

template<typename T, size_t N>
class TypeInfo<T[N]>
{
public:
	enum{Is_Ptr = 0, Is_Ref = 0, Is_Array = 1};
	typedef T baseT;
	typedef typename TypeInfo<T>::bottomT bottomT;
};