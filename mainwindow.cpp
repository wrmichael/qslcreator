#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networkhelper.h"
#include "QPainter"
#include "imagecreator.h"
#include <QFileDialog>
#include "adifreader.h"

NetworkHelper nh;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nh.mw =this;

    this->loadDefaults();

    /*
    //load default values
    ui->txtImage->setText("/home/waynem/Pictures/template.jpg");
    ui->txtInput->setText("/home/waynem/AC9HP450067.adi");
    ui->txtLine1->setText("Wayne Michael");
    ui->txtLine2->setText("1255 Weston Drive");
    ui->txtLine3->setText("Indianapolis IN 46234");
    ui->txtLine4->setText("Hendricks County EM69TS");
    */

}

void MainWindow::saveDefaults()
{


    QFile file("defaults");
    if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
    {
        return;
    }

    QTextStream out(&file);
    out<<ui->txtUserName->text()+"\r\n";
    out<<ui->txtYourCallSign->text()+"\r\n";
    out<<ui->txtImage->text()+"\r\n";
    out<<ui->txtInput->text()+"\r\n";
    out<<ui->txtLine1->text()+"\r\n";
    out<<ui->txtLine2->text()+"\r\n";
    out<<ui->txtLine3->text()+"\r\n";
    out<<ui->txtLine4->text()+"\r\n";
    out<<ui->txtYourCallSignLoc->text()+"\r\n";
    out<<ui->txtYourCallSignSize->text()+"\r\n";
    file.close();
}
void MainWindow::handleSaveDefaults()
{
    this->saveDefaults();
}
void MainWindow::loadDefaults()
{

    if (QFile::exists("defaults"))
    {
        QFile file("defaults");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return;
        }

        ui->txtUserName->setText(file.readLine().trimmed());
        ui->txtYourCallSign->setText(file.readLine().trimmed());
        ui->txtImage->setText(file.readLine().trimmed()); //image in
        ui->txtInput->setText(file.readLine().trimmed()); //log file
        ui->txtLine1->setText(file.readLine().trimmed()); //First line (Name)
        ui->txtLine2->setText(file.readLine().trimmed()); //second line name address line
        ui->txtLine3->setText(file.readLine().trimmed()); // third - city/state/zip
        ui->txtLine4->setText(file.readLine().trimmed()); //fourth county/locator
        ui->txtYourCallSignLoc->setText(file.readLine().trimmed());
        ui->txtYourCallSignSize->setText(file.readLine().trimmed());

        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleQuit()
{
    exit(0);

}

void MainWindow::handleClick()
 {

    QString username = ui->txtUserName->text();
    QString Password = ui->txtPassword->text();


    QString qs = QString("https://xmldata.qrz.com/xml/?username=" + username + ";password=" + Password);
    qDebug()<<qs;

    //get session


    nh.action = "session";
    nh.fetch(qs);

    //if no session found -- do nothing else...


    //http://xmldata.qrz.com/xml/current/?s=f894c4bd29f3923f3bacf02c532d7bd9;callsign=aa7bq

 }


void MainWindow::handleBrowse()
{

    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open ADFI"), "~", tr("Amateur Logs (*.adf *.adfi *.log *.adi)"));
    ui->txtInput->setText(fileName);


}

void MainWindow::handleProcess()
{
    // open ADI file

    ADIFReader ai;
    qDebug() << ui->txtInput->text();
    QString qs = ai.ReadLog(ui->txtInput->text());
    //ui->txtReply->setText(ai.Value("CALL",0));

    QString s="";
    QString call = "";
    QString mode = "";
    QString date = "";
    QString time = "";
    QString band = "";
    QString rst_sent = "";

    ImageCreator ic;
    ic.setImagePath(ui->txtImage->text());
    ic.YourCallSignLoc = ui->txtYourCallSignLoc->text().toInt();
    ic.YourCallSignSize = ui->txtYourCallSignSize->text().toInt();

    ic.line1 = ui->txtLine1->text();
    ic.line2 = ui->txtLine2->text();
    ic.line3 = ui->txtLine3->text();
    ic.line4 = ui->txtLine4->text();

    for(int a =0;a<ai.getCount();a++)
    {
        call = ai.Value("CALL",a);
        mode = ai.Value("MODE",a);
        band = ai.Value("BAND",a);
        date = ai.Value("QSO_DATE",a);
        time= ai.Value("TIME_ON",a);
        rst_sent = ai.Value("RST_SENT",a);

        s = s + call + " " + fixDate(date) + " " + fixTime(time) + " " + band + " " + mode +" " + rst_sent + "\r\n";
        ic.CreateQSO("AC9HP",call,"",rst_sent,fixDate(date) + " " + fixTime(time), band, mode);
        break;
    }
    ui->txtReply->setText(s);
    // split on records

    // parse info for each log entry

    // create card for each log entry (image)

    // save image based on QSL info


}

QString MainWindow::fixDate(QString &d)
{
    QString newDate;
    newDate = d.left(4) + "-" + d.mid(4,2) + "-" + d.mid(6,2);
    return newDate;

}

QString MainWindow::fixTime(QString &t)
{
    QString newDate;
    newDate = t.left(2) + ":" + t.mid(2,2);
    return newDate;

}

void MainWindow::handleImageBrowse()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open IMAGE"), "~", tr("Image (*.png *.jpg *.gif *.bmp)"));
    ui->txtImage->setText(fileName);

}

void MainWindow::loadImage(const QString &imageName)
{

    QString url = imageName;
    QPixmap image(url);

    ui->lblImage->setPixmap(image);

}

void MainWindow::handleSearch()
{

    QString searchCall = ui->txtCallsign->text();


    QString qs = QString("https://xmldata.qrz.com/xml/?s=" + nh.session + ";callsign=" + searchCall);
    qDebug()<<qs;

    //get session
    nh.action = "search";
    nh.fetch(qs);


}

void MainWindow::handleLoad()
{
    ImageCreator ic;
    ic.templateImage = R"(/home/waynem/Pictures/template.jpg)";


}


void MainWindow::acceptSession(const QString& s)
{
  ui->txtSession->setText(s);
}

void MainWindow::setReply(const QString& s)
{
    ui->txtReply->setText(s);
}
