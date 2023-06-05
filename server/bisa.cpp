////////
/// protobuf versi 3.21.12
/// grcp versi 1.53.0
///
#include "bisa.h"
#include <QDebug>
#include "stdio.h"
bisa::bisa(QObject *parent) : QObject(parent)
{

}

bisa::~bisa()
{

}

void bisa::mulai()
{

}

void bisa::check_db_exist(QString filename, int count_db, QByteArray data)
{
    QFile file(filename);

    if(file.exists()== true)
    {
        this->load_database(filename,count_db++, data);
    }
    else
    {
        return;
    }
}

static char buf_command[4096];

int proses_q( QSqlQuery *q, const char *s, ...)
{
    QSqlError er;
    va_list args;

    va_start (args, s);

    vsprintf (buf_command, s, args);
    va_end (args);

    if (!q->exec( buf_command ))
    {
        er = q->lastError();
        qDebug() << "(debug 58) Querry Error : Data not Found! 1";
        qDebug("%s(): ERR : %s", __FUNCTION__, er.text().toUtf8().data());
        return -1;
    }
    else
    {

    }
    return 0;
}

void bisa::load_database(QString filename, int count_db, QByteArray data)
{
    QString con_name;
    con_name = QString("LOC_DB%1").arg(count_db);
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE",con_name);
    db.setDatabaseName(filename);
    QByteArray data1;

    if(!db.open())
    {
        qDebug()<<"db gak kebukak";
        return;
    }
    else
    {
        qDebug()<<"db buka";
        QSqlQuery buka(db);
       // buka.prepare("select data from data_41_tipe where id=:id");
        buka.prepare("select data from hallo where size_data=:size_data");
        buka.bindValue(":size_data", 1000000);
        if(!buka.exec()){

        }
        else{
            while( buka.next() )
            {
                data1 = buka.value("data").toByteArray();
                qDebug()<<data1.size();
                qDebug()<<"---------------------------------------";
                memcpy( &data,(char *) &data1, sizeof(data1.data()));
                qDebug()<<data.size();
            }
        }
    }

}
