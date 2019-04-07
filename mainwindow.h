#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QtNetwork/QNetworkAccessManager>
#include <QTextEdit>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

public slots:
    void handleClick();
    void handleQuit();
    void handleSearch();
    void handleLoad();
    void handleBrowse();
    void handleImageBrowse();
    void loadDefaults();
    void saveDefaults();
    void acceptSession(const QString&);
    void setReply(const QString&);
    void loadImage(const QString&);
    void handleProcess();
    void handleSaveDefaults();
    void handleTestImage();

    QString fixDate(QString&);
    QString fixTime(QString&);

};

\
#endif // MAINWINDOW_H
