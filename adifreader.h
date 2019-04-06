#ifndef ADIFREADER_H
#define ADIFREADER_H

#include <QMainWindow>
#include <QPushButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QTextEdit>

class ADIFReader
{
public:
    ADIFReader();
    QString ReadLog(const QString&);
    QString Value(int idx);
    QString Value(const QString&,int idx);
    int getCount();
};

#endif // ADIFREADER_H
