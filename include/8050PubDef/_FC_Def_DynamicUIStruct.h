//************************************************************************/
//********************---------------------------------*******************/
//*******************|    Copyright (c) 2003 - 2014    |******************/
//*******************|      by ViRe Technologies.      |******************/
//*******************|       All Rights Reserved       |******************/
//********************---------------------------------*******************/
//************************************************************************/
//
// If any question, please write to VIRE Technologies for 
// more information: 
//			Room 1222,High Tech Mansion of BUPT, 
//			Beijing, China
//			Post Code: 100876.
// 
// For more, please visit company website: www.vi-re.com
//************************************************************************/
/************************************************************************* 
 * @file     : _FC_Def_DynamicUIStruct.h
 * @brief    : 轻量级动态UI相关信息结构定义
 * @note     : 
 * @author   : dell
 * @date     : 2014/09/18
 * @version  : 1.0.0.0
 * @CopyRight: 
 *************************************************************************/
#ifndef _FC_Def_DynamicUIStruct_h__
#define _FC_Def_DynamicUIStruct_h__

#include <QString>
#include <QVector>
#include <QStringList>
#include <QSharedPointer>

namespace FacilitiesCommunication
{
	namespace Def_DynamicUIStruct
	{
		class CWidgetItem
		{
		public:
			/////////////////////////
			//结构体变量
			QString strName;		//字名称
			QString strWidgetType;	//控件类型
			int		nOffset;		//偏移量
			/////////////////////////
		public:
			CWidgetItem()
			{
				init();
			}

			~CWidgetItem()
			{
				release();
			}

			CWidgetItem(const CWidgetItem& src)
			{
				*this = src;
			}

			CWidgetItem& operator=(const CWidgetItem& src)
			{
				if(this != &src)
				{
					release();

					//赋值、
					strName = src.strName;
					strWidgetType = src.strWidgetType;
					nOffset = src.nOffset;
				}
				return *this;
			}

			//初始化
			void init()
			{
				//赋值
				nOffset = 0;
			}

			//析构
			void release()
			{

			}
		};
		typedef QList<QSharedPointer<CWidgetItem*>>	ListWidgetItem;

		class CCheckBoxItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//结构体变量
			
			/////////////////////////
		public:
			CCheckBoxItem()
			{
				init();
			}
			
			~CCheckBoxItem()
			{
				release();
			}
			
			CCheckBoxItem(const CCheckBoxItem& src)
			{
				*this = src;
			}
		
			CCheckBoxItem& operator=(const CCheckBoxItem& src)
			{
				if(this != &src)
				{
					release();
					
					//赋值
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//初始化
			void init()
			{
				//赋值
				
			}
		
			//析构
			void release()
			{
		
			}
		};

		class CRadioButtonItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//结构体变量
			
			/////////////////////////
		public:
			CRadioButtonItem()
			{
				init();
			}
			
			~CRadioButtonItem()
			{
				release();
			}
			
			CRadioButtonItem(const CRadioButtonItem& src)
			{
				*this = src;
			}
		
			CRadioButtonItem& operator=(const CRadioButtonItem& src)
			{
				if(this != &src)
				{
					release();
					
					//赋值
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//初始化
			void init()
			{
				//赋值
				
			}
		
			//析构
			void release()
			{
		
			}
		};

		class CLabelItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//结构体变量
			
			/////////////////////////
		public:
			CLabelItem()
			{
				init();
			}
			
			~CLabelItem()
			{
				release();
			}
			
			CLabelItem(const CLabelItem& src)
			{
				*this = src;
			}
		
			CLabelItem& operator=(const CLabelItem& src)
			{
				if(this != &src)
				{
					release();
					
					//赋值
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//初始化
			void init()
			{
				//赋值
				
			}
		
			//析构
			void release()
			{
		
			}
		};

		class CEditItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//结构体变量
			QString strValueType;	//值类型
			/////////////////////////
		public:
			CEditItem()
			{
				init();
			}
			
			~CEditItem()
			{
				release();
			}
			
			CEditItem(const CEditItem& src)
			{
				*this = src;
			}
		
			CEditItem& operator=(const CEditItem& src)
			{
				if(this != &src)
				{
					release();
					
					//赋值
					CWidgetItem::operator = (src);
					strValueType = src.strValueType;
				}
				return *this;
			}
		
			//初始化
			void init()
			{
				//赋值
				
			}
		
			//析构
			void release()
			{
		
			}
		};

		class CComboItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//结构体变量
			struct Item
			{
				QString strItemText;
				int nValue;
			};
			QList<Item> listItem;
			/////////////////////////
		public:
			CComboItem()
			{
				init();
			}
			
			~CComboItem()
			{
				release();
			}
			
			CComboItem(const CComboItem& src)
			{
				*this = src;
			}
		
			CComboItem& operator=(const CComboItem& src)
			{
				if(this != &src)
				{
					release();
					
					//赋值
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//初始化
			void init()
			{
				//赋值
				
			}
		
			//析构
			void release()
			{
				
			}
		};

		class CLayOutItem
		{
		public:
			/////////////////////////
			//结构体变量
			QString strDirection;				//水平还是垂直layout
			ListWidgetItem	listWidgetItem;		//LayOut下的Item
			/////////////////////////
		public:
			CLayOutItem()
			{
				init();
			}

			~CLayOutItem()
			{
				release();
			}

			CLayOutItem(const CLayOutItem& src)
			{
				*this = src;
			}

			CLayOutItem& operator=(const CLayOutItem& src)
			{
				if(this != &src)
				{
					release();

					//赋值
					CWidgetItem::operator = (src);
				}
				return *this;
			}

			//初始化
			void init()
			{
				//赋值

			}

			//析构
			void release()
			{

			}
		};
		typedef QList<QSharedPointer<CLayOutItem*>> ListLayOutItem;

		class CPage
		{
		public:
			/////////////////////////
			//结构体变量
			ListLayOutItem	listLayOutItem;
			/////////////////////////
		public:
			CPage()
			{
				init();
			}
			
			~CPage()
			{
				release();
			}
			
			CPage(const CPage& src)
			{
				*this = src;
			}
		
			CPage& operator=(const CPage& src)
			{
				if(this != &src)
				{
					release();
					
					//赋值
					listLayOutItem = src.listLayOutItem;
				}
				return *this;
			}
		
			//初始化
			void init()
			{
				//赋值
				
			}
		
			//析构
			void release()
			{
		
			}
		};
	}
}

#endif // _FC_Def_DynamicUIStruct_h__