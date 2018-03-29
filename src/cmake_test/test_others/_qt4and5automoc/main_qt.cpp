
#include <QObject>

class SomeObject : public QObject
{
  Q_OBJECT
public:
  explicit SomeObject(QObject *parent = 0)
    : QObject(parent)
  {

  }
};
#include "main_qt.moc"
