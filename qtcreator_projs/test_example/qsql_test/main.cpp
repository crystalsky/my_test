#include "mainwindow.h"
#include <QApplication>
#include "DBManager.h"
#include <QSqlError>
#include <QtConcurrent/QtConcurrent>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /*
         * 注：关于附加参数
         * 这是可以不写的，如果要写的话，可以参考这个：
         *
         * 单次打开数据库最大时间：也就是最大open的时间，对于某些数据库，长时间open但不使用，不仅会造成资源浪费还会意外断开。在设置了60 * 1000后，且60秒内未进行查询，就自动断开。
         * 多线程支持：简单的说就是高级点的数据库，比如 MySql 写 JasonQt_Database::QueryMultiMode ；低级的，比如 Sqlite ，写 JasonQt_Database::QuerySingleMode ,就可以了。
         * 最小等待时间：对于某些数据库，比如Sqlite，密集查询时可能出错，此时可以适当的提升两次查询之间的最小等待时间，比如10ms
         */
        // Sqlite的连接方式                    类型        连接名        Sqlite文件路径      单次打开数据库最大时间                多线程支持           最小等待时间
        //JasonQt_Database::Control control({ "QSQLITE", "TestDB", "/Users/Jason/test.db" }, { 60 * 1000,        JasonQt_Database::QuerySingleMode, 10});

        // MySql的连接方式                      类型      连接名        IP        数据库    用户名        密码
        JasonQt_Database::DatabaseSettings
            setting("QMYSQL", "conn_netxdb", "192.168.0.1", "netxdb", "netx", "netx");
        JasonQt_Database::Control control(setting);


        // SqlServer的连接方式                  类型      连接名                                    数据库              数据库名   用户名         密码
    //  JasonQt_Database::Control control({ "QODBC", "TestDB", "Driver={SQL SERVER};server=iZ23kn6vmZ\\TEST;database=test;uid=sa;pwd=YourPassword;" });

        auto insert = [&]()
        {
            auto query(control.query()); // 这里的query在解引用（ -> 或者 * ）后返回的是 QSqlQuery ，直接用就可以了，不需要单独打开数据库或者其他的初始化

            query->prepare("insert into Test1 values(?)"); // 模拟插入操作

            query->addBindValue(rand() % 1280);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }

            query->clear();

            query->prepare("insert into Test2 values(NULL, ?, ?)");

            query->addBindValue(rand() % 1280);
            QString buf;
            for(int now = 0; now < 50; now++)
            {
                buf.append('a' + (rand() % 26));
            }
            query->addBindValue(buf);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }
        };
        auto delete_ = [&]()
        {
            auto query(control.query());

            query->prepare("delete from Test1 where data = ?");

            query->addBindValue(rand() % 1280);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }

            query->clear();

            query->prepare("delete from Test2 where data1 = ?");

            query->addBindValue(rand() % 1280);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }
        };
        auto update = [&]()
        {
            auto query(control.query());

            query->prepare("update Test1 set data = ? where data = ?");

            query->addBindValue(rand() % 1280);
            query->addBindValue(rand() % 1280);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }

            query->clear();

            query->prepare("update Test2 set data1 = ?, data2 = ? where data1 = ?");

            query->addBindValue(rand() % 1280 + 1);
            QString buf;
            for(int now = 0; now < 50; now++)
            {
                buf.append('a' + (rand() % 26));
            }
            query->addBindValue(buf);
            query->addBindValue(rand() % 1280 + 1);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }
        };
        auto select = [&]()
        {
            auto query(control.query());

            query->prepare("select * from Test1 where data = ?");

            query->addBindValue(rand() % 1280);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }

            query->clear();

            query->prepare("select * from Test2 where data1 = ?");

            query->addBindValue(rand() % 1280);

            if(!query->exec())
            {
                qDebug() << "Error" << __LINE__;
            }
        };

        volatile int count = 0, last = 0;

        QTime time;
        time.start();

        QThreadPool::globalInstance()->setMaxThreadCount(10);

        for(int now = 0; now < 3; now++) // 开启3个线程测试
        {
            QtConcurrent::run([&]()
            {
                while(true)
                {
                    count++;
                    if(!(count % 1000))
                    {
                        const auto &&now = time.elapsed();
                        qDebug() << now - last; // 打印每完成1000语句的时间
                        last = now;
                    }

                    switch(rand() % 20)
                    {
                        case 0:  { insert(); break; }
                        case 1:  { delete_(); break; }
                        case 2:  { update(); break; }
                        default: { select(); break; }
                    }
                }
                QThread::msleep(10);
            });
        }


    return a.exec();
}
