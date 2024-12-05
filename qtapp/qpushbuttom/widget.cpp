#include "widget.h"
#include <qpushbutton.h>
#include <qapplication.h>
#include <qmenu.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //setMinimumSize(300,150);
    //setMaximumSize(300,150);

    QPushButton *qQuit = new QPushButton("Quit", this);
    qQuit->setGeometry(60,40,80,30);
    //qQuit->move(10,20);
    qQuit->setFont(QFont( "Times", 16, QFont::Light));

    //connect(qQuit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(qQuit, &QPushButton:: clicked, this, &QWidget::close);
    //qQuit->show();
    QMenu *pm = new QMenu;
    pm->addAction("F1");

    //qQuit->setMenu(pm);
}

Widget::~Widget()
{
}

