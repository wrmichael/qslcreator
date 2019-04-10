#ifndef IMAGECREATOR_H
#define IMAGECREATOR_H

#include <QObject>
#include <QPainter>

class ImageCreator : public QObject
{
    Q_OBJECT
public:
    explicit ImageCreator(QObject *parent = nullptr);
    QString templateImage;
    QString qsoImage;
    QString line1;
    QString line2;
    QString line3;
    QString line4;

    int YourCallSignLoc;
    int YourCallSignSize;
    int line1_size;
    int line2_size;
    int line3_size;
    int line4_size;

    int line1_loc;
    int line2_loc;
    int line3_loc;
    int line4_loc;

    QString CreateQSO(const QString&, const QString&,const QString&,const QString&,const QString&, const QString&, const QString&);
    void setImagePath(const QString&);

signals:

public slots:

};

#endif // IMAGECREATOR_H
