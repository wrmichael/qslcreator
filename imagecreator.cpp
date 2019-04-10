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

int line1_size = 0;
int line2_size = 0;
int line3_size = 0;
int line4_size = 0;

int line1_loc = 0;
int line2_loc = 0;
int line3_loc = 0;
int line4_loc = 0;


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
  p.setFont(QFont("Times", line1_size, QFont::AbsoluteSpacing));
  //p.drawText(image.rect(),  Qt::AlignBottom, "AC9HP");

  //char buffer[100];
  //int n;
  //n = sprintf(buffer,"AC9HP -[%d - %d]", image.height() , image.width());
  QString qso_line1 = "Confirming QSO from " + senderCallSign + " with " + Callsign + " on " + band + " using " + mode;
  QString qso_line2 = "Report Sent: " + sndRpt + " Date: " + QSOEndTime;

  p.setPen(QPen(Qt::white));
  p.setFont(QFont("Times", line1_size, QFont::AbsoluteSpacing));
  p.drawText(10,line1_loc,line1);
  p.setPen(QPen(Qt::white));
  p.setFont(QFont("Times", line2_size, QFont::AbsoluteSpacing));
  p.drawText(10,line2_loc,line2);
  p.setPen(QPen(Qt::white));
  p.setFont(QFont("Times", line3_size, QFont::AbsoluteSpacing));
  p.drawText(10,line3_loc,line3);
  p.setPen(QPen(Qt::white));
  p.setFont(QFont("Times", line4_size, QFont::AbsoluteSpacing));
  p.drawText(10,line4_loc,line4);

  p.setPen(QPen(Qt::blue));

  p.setFont(QFont("Times", 48, QFont::AbsoluteSpacing));

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
