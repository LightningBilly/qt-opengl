#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include <QString>
#include <QStack>
#include <iterator>
#include <QLineEdit>
#include <QTime>

#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

    QString strInput ="0";
    bool flags = false;

    void pressNum(char ch);

private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_0_clicked();

    void on_pushButton_dot_clicked();

    void on_pushButton_minus_clicked();

    void on_pushButton_equal_clicked();

    void on_pushButton_left_clicked();

    void on_pushButton_right_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_multi_clicked();

    void on_pushButton_devide_clicked();

    void on_pushButton_ce_clicked();

    void on_pushButton_clr_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H
