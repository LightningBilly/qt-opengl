#include "widget.h"

#include <QApplication>

#include<QSplitter>
#include<QTextCodec>
#include<QTextEdit>
#include<QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QFont font("宋体", 15);

//    // 主窗口
//    QSplitter *splitterMain = new QSplitter(Qt::Horizontal, 0);
//    QTextEdit *textLeft = new QTextEdit(QObject::tr("左边窗口"), splitterMain);
//    textLeft->setAlignment(Qt::AlignCenter);

//    // 右窗口
//    QSplitter *splitterRight = new QSplitter(Qt::Vertical, splitterMain);
//    // 设拖曳
//    splitterRight->setOpaqueResize(false);

//    QTextEdit *textUp = new QTextEdit(QObject::tr("右边上半部窗"), splitterRight);
//    textUp->setAlignment(Qt::AlignCenter);


//    QTextEdit *textDown = new QTextEdit(QObject::tr("右边下半部窗"), splitterRight);
//    textDown->setAlignment(Qt::AlignCenter);

//    QTextEdit *textDown2 = new QTextEdit(QObject::tr("右边下半部窗2"), splitterRight);
//    textDown2->setAlignment(Qt::AlignCenter);

//    splitterMain->setStretchFactor(1,1);
//    splitterMain->show();
    return a.exec();
}
