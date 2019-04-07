#include "imagecreator.h"
#include <qdebug.h>

QString templateImage = R"(/home/waynem/Pictures/template.jpg)";
QString qsoImage = R"(/home/waynem/Pictures/out1.jpg)";
QString line1;
QString line2;
QString line3;
QString line4;
int YourCallSignLoc=0;
int YourCallSignSize=0;

ImageCreator::ImageCreator(QObject *parent) : QObject(parent)
{

}

QString ImageCreator::CreateQSO(const QString &senderCallSign,const QString &Callsign,const QString &rcvRpt,const QString &sndRpt,const QString &QSOEndTime, const QString &mode, const QString &band)
{
    qDebug() << templateImage;
    if (Callsign.length()==0)
    {
        return "";
    }
    //1365 x 2048
    QString url = templateImage;

    QImage image(url);
    QPainter p(&image);

    QRectF qr = QRectF(0,1000,image.width(),1365-1100);
  p.fillRect(qr,Qt::white);

  p.setPen(QPen(Qt::cyan));
  p.setFont(QFont("Times", YourCallSignSize, QFont::AbsoluteSpacing|QFont::Bold));

  p.drawText(YourCallSignLoc,YourCallSignSize,senderCallSign);


  p.setPen(QPen(Qt::white));
  p.setFont(QFont("Times", 48, QFont::AbsoluteSpacing));
  //p.drawText(image.rect(),  Qt::AlignBottom, "AC9HP");

  //char buffer[100];
  //int n;
  //n = sprintf(buffer,"AC9HP -[%d - %d]", image.height() , image.width());
  QString qso_line1 = "Confirming QSO from " + senderCallSign + " with " + Callsign + " on " + band + " using " + mode;
  QString qso_line2 = "Report Sent: " + sndRpt + " Date: " + QSOEndTime;

  p.drawText(10,200,line1);
  p.drawText(10,250,line2);
  p.drawText(10,300,line3);
  p.drawText(10,350,line4);

  p.setPen(QPen(Qt::blue));

  p.drawText(10,1100,qso_line1);
  p.drawText(10,1175,qso_line2);
  p.end();
  //QString path = R"(/home/waynem/Pictures/ac9hp.jpg)";
  QString file_datetime = QSOEndTime;
  file_datetime.replace(QString(" "),QString(""));
  file_datetime.replace(QString(":"),QString("-"));
  QString path = "/home/waynem/Pictures/" + Callsign + "_" + band + "_" + mode + "_" + file_datetime + ".jpg";



  qDebug() << path;
  qDebug() << qsoImage;
  image.save(path);
  return path;
}

void ImageCreator::setImagePath(const QString &imagePath)
{

    templateImage = imagePath;
}
