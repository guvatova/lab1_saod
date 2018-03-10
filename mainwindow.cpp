#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <fstream>
#include <iostream>
#include <ctime>

const int n = 45000;
int rStupid = 0, cStupid = 0, rInsert = 0, cInsert = 0,
rShell = 0, cShell = 0, rMerge = 0, cMerge = 0;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void Shell(int arrInt[n])
{
    int i,j,k,t;
    for(k = n/2; k > 0; k /=2)
        for(i = k; i < n; i++)
        {
            t = arrInt[i];
            for(j = i; j>=k; j-=k)
            {
                if(t < arrInt[j-k])
                {
                    cShell++;
                    arrInt[j] = arrInt[j-k];
                    rShell++;
                }
                else
                    break;
            }
            arrInt[j] = t;
            rShell++;
        }
}
void Shell(string arrString[n])
{
    int i,j,k;
    string t;
    for(k = n/2; k > 0; k /=2)
        for(i = k; i < n; i++)
        {
            t = arrString[i];
            for(j = i; j>=k; j-=k)
            {
                if(t < arrString[j-k])
                {
                    cShell++;
                    arrString[j] = arrString[j-k];
                    rShell++;
                }
                else
                    break;
            }
            arrString[j] = t;
            rShell++;
        }
}

void Stupid(int arrInt[n])
{
    int k = 2000;
    int i = 0, tmp;
    while (i<k-1)
    {
            if (arrInt[i+1]<arrInt[i])
            {
                cStupid++;
                tmp = arrInt[i];
                arrInt[i] = arrInt[i+1];
                arrInt[i+1]=tmp;
                i=0;
                rStupid+=3;
            }
            else i++;
    }
}
void Stupid(string arrString[n])
    {
        int i,k = 2000;
        string tmp;
        while (i<k-1)
        {
                if (arrString[i+1]<arrString[i])
                {
                    cStupid++;
                    tmp = arrString[i];
                    arrString[i] = arrString[i+1];
                    arrString[i+1]=tmp;
                    i=0;
                    rStupid+=3;
                }
                else i++;
        }
    }

void Merge(int arrInt[n], int l, int r)
{
    int tmp;
    int maxn = n;
    if (r==l)
        return;
    if (r-1 == 1)
    {
        if (arrInt[r]<arrInt[l]){
            cMerge++;
            tmp = arrInt[r];
            arrInt[r]=arrInt[l];
            arrInt[l]=tmp;
            rMerge+=3;
        }
        return;
    }
    int m = (r+l)/2;
    Merge(arrInt, l, m);
    Merge(arrInt, m+1,r);
    int buf[maxn];
    int xl = l;
    int xr = m+1;
    int cur = 0;
    while ((r - l + 1)!= cur){
        if (xl>m){
            cMerge++;
            buf[cur++] = arrInt[xr++];
            rMerge++;}
        else if (xr>r){
            cMerge++;
            buf[cur++] = arrInt[xl++];
            rMerge++;}
         else if (arrInt[xl]>arrInt[xr]){
            cMerge++;
            buf[cur++] = arrInt[xr++];
            rMerge++;}
        else {buf[cur++] = arrInt[xl++];
              rMerge++;}
    }
    for (int i = 0; i<cur; i++)
        arrInt[i+l]=buf[i];
}
void Merge(string arrString[n], int l, int r)
{
    string tmp;
    int maxn = n;
    if (r==l)
        return;
    if (r-1 == 1)
    {
        if (arrString[r]<arrString[l])
        {
            cMerge++;
            tmp = arrString[r];
            arrString[r]=arrString[l];
            arrString[l]=tmp;
            rMerge+=3;
        }
        return;
    }
    int m = (r+l)/2;
    Merge(arrString,l,m);
    Merge(arrString, m+1,r);
    string buf[maxn];
    int xl = l;
    int xr = m+1;
    int cur = 0;
    while (r - l + 1!= cur){
        if (xl>m){
            cMerge++;
            buf[cur++] = arrString[xr++];
            rMerge++;}
        else if (xr>r){
            cMerge++;
            buf[cur++] = arrString[xl++];
            rMerge++;}
         else if (arrString[xl]>arrString[xr]){
            cMerge++;
            buf[cur++] = arrString[xr++];
            rMerge++;}
        else {
            buf[cur++] = arrString[xl++];
            rMerge++;}
    }
    for (int i = 0; i<cur; i++)
         arrString[i+l]=buf[i];
}

void Insert(int arrInt[n])
{
    int temp;   //временная переменная для хранения значения элемента сортируемого массива
    int item;   //индекс предыдущего элемента
    for (int i = 1; i < n; i++)
    {
     temp = arrInt[i];
     item = i - 1;
     while ((item >= 0) && (arrInt[item] > temp))  //пока индекс не равен нулю и предыдущий элемент больше текущего
     {
         cInsert++;
         arrInt[item+1] = arrInt[item];   //перестановка элементов массива
         arrInt[item] = temp;
         item--;
         rInsert+=2;
     }
    }
}
void Insert(string arrString[n])
{
    string temp;   //временная переменная для хранения значения элемента сортируемого массива
    int item;   //индекс предыдущего элемента
    for (int i = 1; i < n; i++)
    {
     temp = arrString[i];
     item = i - 1;
     while ((item >= 0) && (arrString[item] > temp))  //пока индекс не равен нулю и предыдущий элемент больше текущего
     {
         cInsert++;
         arrString[item+1] = arrString[item];   //перестановка элементов массива
         arrString[item] = temp;
         item--;
         rInsert+=2;
     }
    }
}

void MainWindow::on_pushLoad_clicked()
{
    if(!ui->checkBox_1->isChecked() && !ui->checkBox_2->isChecked())
    {
        QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of data!");
    }
    else if ((ui->checkBox_1->isChecked()) && (ui->checkBox_2->isChecked()))
        {
            QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of data!");
        }
        else if(ui->checkBox_1->isChecked())
        {
            QFile file("C://Qt//lab1_saod//inputNum.txt");
            if (!file.open(QIODevice::ReadOnly))
                QMessageBox::information(0, "Information", "File can not be opened!");
            QTextStream in(&file);
            ui->textInput->setText((in.readAll()));
        }
        else if (ui->checkBox_2->isChecked())
        {
            QFile file("C://Qt//lab1_saod//inputStr.txt");
            if (!file.open(QIODevice::ReadOnly))
                QMessageBox::information(0, "Information", "File can not be opened!");
            QTextStream in(&file);
            ui->textInput->setText((in.readAll()));
        }
}

void MainWindow::on_pushDone_clicked()
{
    if(!ui->radioInsert->isChecked() && !ui->radioMerge->isChecked() &&
       !ui->radioShell->isChecked() && !ui->radioStupid->isChecked())
    {
        QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of sort!");
    }
    else if(ui->radioInsert->isChecked())
        {
            if ((ui->checkBox_1->isChecked()) && (ui->checkBox_2->isChecked()))
            {
                QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of data!");
            }
            else if (ui->checkBox_1->isChecked())
            {
                int arrInt[n];
                cInsert = 0; rInsert = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputNum.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrInt[i];
                }
                clock_t start = clock();
                Insert(arrInt);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outNumInsert.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrInt[i] << "\n";
                }
                double InsertTime = double(double(end - start)/CLOCKS_PER_SEC)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(InsertTime, 'f', 7));
                ui->textRearrange->setText(QString::number(rInsert));
                ui->textCompare->setText(QString::number(cInsert));

                QFile file("C://Qt//lab1_saod//outNumInsert.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
            else if(ui->checkBox_2->isChecked())
            {
                string arrString[n];
                cInsert = 0; rInsert = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputStr.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrString[i];
                }
                clock_t start = clock();
                Insert(arrString);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outTextInsert.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrString[i] << "\n";
                }
                double InsertTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(InsertTime, 'f', 7));
                ui->textRearrange->setText(QString::number(rInsert));
                ui->textCompare->setText(QString::number(cInsert));
                QFile file("C://Qt//lab1_saod//outTextInsert.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
        }
    else if(ui->radioStupid->isChecked())
        {
            if ((ui->checkBox_1->isChecked()) && (ui->checkBox_2->isChecked()))
            {
                QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of data!");
            }
            else if (ui->checkBox_1->isChecked())
            {
                int arrInt[n];
                cStupid = 0; rStupid = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputNum.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrInt[i];
                }
                clock_t start = clock();
                Stupid(arrInt);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outNumStupid.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrInt[i] << "\n";
                }
                double StupidTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(StupidTime, 'f', 7));
                ui->textRearrange->setText(QString::number(rStupid));
                ui->textCompare->setText(QString::number(cStupid));

                QFile file("C://Qt//lab1_saod//outNumStupid.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
            else if(ui->checkBox_2->isChecked())
            {
                string arrString[n];
                cStupid = 0; rStupid = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputStr.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrString[i];
                }
                clock_t start = clock();
                Stupid(arrString);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outTextStupid.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrString[i] << "\n";
                }
                double StupidTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(StupidTime, 'f', 7));
                ui->textRearrange->setText(QString::number(rStupid));
                ui->textCompare->setText(QString::number(cStupid));
                QFile file("C://Qt//lab1_saod//outTextStupid.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
        }
    else if(ui->radioShell->isChecked())
        {
            if ((ui->checkBox_1->isChecked()) && (ui->checkBox_2->isChecked()))
            {
                QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of data!");
            }
            else if (ui->checkBox_1->isChecked())
            {
                int arrInt[n];
                cShell = 0; rShell = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputNum.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrInt[i];
                }
                clock_t start = clock();
                Shell(arrInt);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outNumShell.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrInt[i] << "\n";
                }
                double ShellTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(ShellTime, 'f', 3));
                ui->textRearrange->setText(QString::number(rShell));
                ui->textCompare->setText(QString::number(cShell));

                QFile file("C://Qt//lab1_saod//outNumShell.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
            else if(ui->checkBox_2->isChecked())
            {
                string arrString[n];
                cShell = 0; rShell = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputStr.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrString[i];
                }
                clock_t start = clock();
                Shell(arrString);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outTextShell.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrString[i] << "\n";
                }
                double ShellTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(ShellTime, 'f', 3));
                ui->textRearrange->setText(QString::number(rShell));
                ui->textCompare->setText(QString::number(cShell));
                QFile file("C://Qt//lab1_saod//outTextShell.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
        }
    else if(ui->radioMerge->isChecked())
        {
            if ((ui->checkBox_1->isChecked()) && (ui->checkBox_2->isChecked()))
            {
                QMessageBox::warning(this, "Warning","Incorrect! Please, choose one type of data!");
            }
            else if (ui->checkBox_1->isChecked())
            {
                int arrInt[n];
                int l = 0, r = n-1;
                cMerge = 0; rMerge = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputNum.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrInt[i];
                }
                clock_t start = clock();
                Merge(arrInt,l,r);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outNumMerge.txt");
                for (int i = 1; i < n; i++)
                {
                    fileOut << arrInt[i] << "\n";
                }
                double MergeTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(MergeTime, 'f', 7));
                ui->textRearrange->setText(QString::number(rMerge));
                ui->textCompare->setText(QString::number(cMerge));

                QFile file("C://Qt//lab1_saod//outNumMerge.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
            else if(ui->checkBox_2->isChecked())
            {
                string arrString[n];
                int l = 0, r = n-1;
                cMerge = 0; rMerge = 0;
                ifstream fileIn ("C://Qt//lab1_saod//inputStr.txt");
                for (int i = 0; i < n; i++)
                {
                    fileIn >> arrString[i];
                }
                clock_t start = clock();
                Merge(arrString,l,r);
                clock_t end = clock();
                ofstream fileOut ("C://Qt//lab1_saod//outTextMerge.txt");
                for (int i = 0; i < n; i++)
                {
                    fileOut << arrString[i] << "\n";
                }
                double MergeTime = double(end - start)/CLOCKS_PER_SEC;
                ui->textTime->setText(QString::number(MergeTime, 'f', 7));
                ui->textRearrange->setText(QString::number(rMerge));
                ui->textCompare->setText(QString::number(cMerge));
                QFile file("C://Qt//lab1_saod//outTextMerge.txt");
                if (!file.open(QIODevice::ReadOnly))
                    QMessageBox::information(0, "Information", "File can not be opened!");
                QTextStream out(&file);
                ui->textOutput->setText((out.readAll()));
            }
        }
}
