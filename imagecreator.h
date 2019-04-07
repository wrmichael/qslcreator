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

    QString CreateQSO(const QString&, const QString&,const QString&,const QString&,const QString&, const QString&, const QString&);
    void setImagePath(const QString&);

signals:

public slots:

};

#endif // IMAGECREATOR_H
