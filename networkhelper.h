#ifndef NETWORKHELPER_H
#define NETWORKHELPER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QTextEdit>
#include <QFile>
#include <mainwindow.h>

class NetworkHelper: public QObject
{

    Q_OBJECT

public:
    explicit NetworkHelper();

signals:

public:

    QString action;
    QString session;
    void setSession(const QString&);
    QString parseXML(const QString&,const QString&);
    void postHttp(const QString&);
    void fetch(const QString&);
    QString sreply;
    //QTextEdit reply_text;
    MainWindow* mw;

public slots:
    void replyFinished(QNetworkReply*);

private:
    QNetworkAccessManager* m_manager;
    void log(const QString&);

};


#endif // NETWORKHELPER_H
