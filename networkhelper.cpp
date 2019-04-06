#include "networkhelper.h"
#include "QtNetwork/QNetworkAccessManager"
//#include "QTextEdit.h"
#include <qfile.h>
#include <QJsonDocument>
#include <mainwindow.h>

QString sreply;
QString session;
QString action;
MainWindow *mw;

NetworkHelper::NetworkHelper()
{
    m_manager = new QNetworkAccessManager(this);
    //connect(m_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
    //connect(m_manager, &QNetworkReply::readyRead, this, &NetworkHelper::replyFinished);
}
/*
void NetworkHelper::postHttp(const QString &url)
{
    //,payload
    QNetworkRequest request;
    request.setUrl(url);

    QVariantMap feed;
    //feed.insert(“field1”,QVariant(tval).toString());
    //feed.insert(“field2”,QVariant(hval).toString());
    //feed.insert(“field3”,Qvariant(pval).toString());
    QByteArray payload=QJsonDocument::fromVariant(feed).toJson();


    m_manager = new QNetworkAccessManager(this); //constructor
    connect(m_manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));

    request.setHeader(QNetworkRequest::ContentTypeHeader,
        "application/xml");

    QNetworkReply *reply = m_manager->post(request,payload);

    qDebug() << reply->readAll();

}
*/

void NetworkHelper::fetch(const QString &surl)
{    
    try
    {
        //qDebug()<<surl;
        m_manager->get(QNetworkRequest(QUrl(surl)));
    } catch(std::exception e)
    {
       NetworkHelper::log(e.what());
    }
}

void NetworkHelper::log(const QString &s)
{
    QFile file("/home/waynem/QT/nerr.log");
       if (!file.open(QIODevice::WriteOnly))
           return;
       file.write(s.toUtf8());
       file.close();
}

void NetworkHelper::replyFinished(QNetworkReply* pReply)
{

    QByteArray data=pReply->readAll();
    QString str(data);

    qDebug()<<data;

    int x = QString::compare(action, "session", Qt::CaseInsensitive);
    if (x==0)
    {
        QString key ="Key";
        QString ss=NetworkHelper::parseXML(data,key);
        //w.accptSession(ss);

        mw->acceptSession(ss);
    }
    int x1 = QString::compare(action, "search", Qt::CaseInsensitive);
    if (x1==0)
    {
        qDebug()<<data;
        //this->sreply = data;
        QString email = NetworkHelper::parseXML(data,"email");
        mw->setReply(email);
        qDebug()<<email;
    }

    //sreply = data;
    //reply_text.setText(sreply);
    //process str any way you like!

}

//find the first instance of the field and return its value
QString NetworkHelper::parseXML(const QString &xml,const QString &fld)
{
    if (xml.indexOf(fld)>-1)
    {
        int startx = xml.indexOf(fld);
        QString ss = xml.mid(startx+fld.length()+1);
        QString ss1 = ss.left(ss.indexOf(fld)-2);
        qDebug()<<ss1;
        NetworkHelper::setSession(ss1);
        return ss1;
    }else
    {
        return "";
    }


}

void NetworkHelper::setSession(const QString &s)
{
    this->session = s;
}

