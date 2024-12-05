#include "mainwidget.h"
#include "ui_mainwidget.h"

bool isNum(char ch);
bool isOperator(char ch);
int ilevel(char ch);
double dscd(string str);
double getvalues(vector<string> V);
vector<string>midtopost(string str);

void MainWidget::pressNum(char ch) {
    if(strInput == "0") strInput = ch;
    else strInput += ch;
    ui->lineEdit->setText(strInput);
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::on_pushButton_1_clicked()
{
    pressNum('1');
}


void MainWidget::on_pushButton_2_clicked()
{
    pressNum('2');
}


void MainWidget::on_pushButton_3_clicked()
{
    pressNum('3');
}


void MainWidget::on_pushButton_4_clicked()
{
pressNum('4');
}

void MainWidget::on_pushButton_5_clicked()
{
    pressNum('5');
}


void MainWidget::on_pushButton_6_clicked()
{
    pressNum('6');
}


void MainWidget::on_pushButton_7_clicked()
{
pressNum('7');
}


void MainWidget::on_pushButton_8_clicked()
{
pressNum('8');
}


void MainWidget::on_pushButton_9_clicked()
{
pressNum('9');
}


void MainWidget::on_pushButton_0_clicked()
{
pressNum('0');
}


void MainWidget::on_pushButton_dot_clicked()
{
pressNum('.');
}


void MainWidget::on_pushButton_minus_clicked()
{
    pressNum('-');
}


void MainWidget::on_pushButton_equal_clicked()
{

}


void MainWidget::on_pushButton_left_clicked()
{
pressNum('(');
}


void MainWidget::on_pushButton_right_clicked()
{
pressNum(')');
}


void MainWidget::on_pushButton_add_clicked()
{
    pressNum('+');
}


void MainWidget::on_pushButton_multi_clicked()
{
    pressNum('*');
}


void MainWidget::on_pushButton_devide_clicked()
{
    pressNum('/');
}


void MainWidget::on_pushButton_ce_clicked()
{
    strInput = strInput.left(strInput.length()-1);
    ui->lineEdit->setText(strInput);
}


void MainWidget::on_pushButton_clr_clicked()
{
    strInput = "0";
    ui->lineEdit->setText(strInput);
}


bool isNum(char ch){
    return ch>='0' && ch<='9';
}
bool isOperator(char ch) {
    return ch == '+' ||ch == '-' ||ch == '*' ||ch == '/' ||ch == '(' ||ch == ')';
}
int ilevel(char ch) {

}
double dscd(string str);
double getvalues();

