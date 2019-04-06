#include "adifreader.h"
#include <QFile>

QStringList records;
int i_idx = 0;

ADIFReader::ADIFReader()
{


}

QString ADIFReader::ReadLog(const QString &file)
{
        QFile f(file);
        if (!f.open(QFile::ReadOnly | QFile::Text))
        {
            return "";

        }else
        {
            QTextStream in(&f);
            QString content =  in.readAll();
            f.close();
            records = content.split("<EOR>");
            return content;
        }

        //qDebug() << f.size() << ;

}

QString ADIFReader::Value(int idx=0)
{
    return records[idx];
}

QString ADIFReader::Value(const QString &field,int idx=0)
{
    QString line = records[idx];

    QString myvalue = line.mid(line.indexOf("<"+field));

    myvalue = myvalue.mid(myvalue.indexOf(">")+1);
    myvalue = myvalue.left(myvalue.indexOf("<"));
    return myvalue;
    //return "";

}

int ADIFReader::getCount()
{
    return records.length();
}
