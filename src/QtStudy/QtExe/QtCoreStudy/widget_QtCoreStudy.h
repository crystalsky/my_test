#ifndef widget_QtCoreStudy_h__
#define widget_QtCoreStudy_h__

#include <QList>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>

namespace Study_QtCore
{
	class CStudyWidget : public QWidget
	{
	public:
		CStudyWidget(QWidget* pParent = NULL);
		~CStudyWidget();
	protected:
		void init();

	private:
		QTabWidget*		m_pTabWidget;
	};
}

#endif // widget_QtCoreStudy_h__
