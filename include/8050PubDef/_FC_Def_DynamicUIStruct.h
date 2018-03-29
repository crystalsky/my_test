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
 * @brief    : ��������̬UI�����Ϣ�ṹ����
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
			//�ṹ�����
			QString strName;		//������
			QString strWidgetType;	//�ؼ�����
			int		nOffset;		//ƫ����
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

					//��ֵ��
					strName = src.strName;
					strWidgetType = src.strWidgetType;
					nOffset = src.nOffset;
				}
				return *this;
			}

			//��ʼ��
			void init()
			{
				//��ֵ
				nOffset = 0;
			}

			//����
			void release()
			{

			}
		};
		typedef QList<QSharedPointer<CWidgetItem*>>	ListWidgetItem;

		class CCheckBoxItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//�ṹ�����
			
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
					
					//��ֵ
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				
			}
		
			//����
			void release()
			{
		
			}
		};

		class CRadioButtonItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//�ṹ�����
			
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
					
					//��ֵ
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				
			}
		
			//����
			void release()
			{
		
			}
		};

		class CLabelItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//�ṹ�����
			
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
					
					//��ֵ
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				
			}
		
			//����
			void release()
			{
		
			}
		};

		class CEditItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//�ṹ�����
			QString strValueType;	//ֵ����
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
					
					//��ֵ
					CWidgetItem::operator = (src);
					strValueType = src.strValueType;
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				
			}
		
			//����
			void release()
			{
		
			}
		};

		class CComboItem : public CWidgetItem
		{
		public:
			/////////////////////////
			//�ṹ�����
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
					
					//��ֵ
					CWidgetItem::operator = (src);
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				
			}
		
			//����
			void release()
			{
				
			}
		};

		class CLayOutItem
		{
		public:
			/////////////////////////
			//�ṹ�����
			QString strDirection;				//ˮƽ���Ǵ�ֱlayout
			ListWidgetItem	listWidgetItem;		//LayOut�µ�Item
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

					//��ֵ
					CWidgetItem::operator = (src);
				}
				return *this;
			}

			//��ʼ��
			void init()
			{
				//��ֵ

			}

			//����
			void release()
			{

			}
		};
		typedef QList<QSharedPointer<CLayOutItem*>> ListLayOutItem;

		class CPage
		{
		public:
			/////////////////////////
			//�ṹ�����
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
					
					//��ֵ
					listLayOutItem = src.listLayOutItem;
				}
				return *this;
			}
		
			//��ʼ��
			void init()
			{
				//��ֵ
				
			}
		
			//����
			void release()
			{
		
			}
		};
	}
}

#endif // _FC_Def_DynamicUIStruct_h__