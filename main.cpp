//! @date 20160709 0033
//! @author mail@marcelpetrick.it
//! @brief: compare the content of two files; per line one item as
//!         ISBN (number; 13 digits; no leading or trailing whitespace (remove this));
//!         print every item of input0 which is not contained in input1
//! @version 0.01 unreleased
//! @file main.cpp

//Qt-includes
#include <QCoreApplication> //for arg-list
#include <QTextStream>
#include <QStringList>
#include <QFileInfo> //for the file-existance-check

#include <QDebug> //maybe remove later

////C++
//#include <iostream> //cerr/cout
//using namespace std;

void readFile(QString fileName)
{
    QFile inputFile(fileName);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        static int lineNumber(1); //because pluma numbers starting with 1
        QTextStream inputStream(&inputFile);
        while(!inputStream.atEnd())
        {
            QString const line = inputStream.readLine().trimmed(); //maybe also check simplified()
            qDebug() << "line " << QString::number(lineNumber) << ": #" << line << "#"; //enclosed to proof for correct trimming

            lineNumber++;
        }

        qDebug() << "readFile(): read " << lineNumber << endl;
        lineNumber= 0;

        inputFile.close();
    }
}

void processFile(QString path)
{
    QFileInfo fileInfo(path);
    if(fileInfo.exists())
    {
        //! read content of current file
        readFile(path);
    }
    else
    {
        qDebug() << "processFile(): the file DOES NOT exist! path was \"" << path << "\"" << endl;
    }
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    //QTextStream cerr(stderr);
    QStringList argList(app.arguments());

    //check the arguments
    {
        qDebug() << "main(): argc = " << argc << endl;
        // print the current argument list
        for(int i = 0; i < argList.size(); ++i)
        {
            qDebug() << QString("argv #%1 is %2").arg(i).arg(argList[i]) << endl;
        }
    }

    if(argList.size() == 3) //check for existance of at least one "real" parameter
    {
        //call for each file the read-in
        processFile(argList[1]); //first "real" arg; first argument is the binary-name itself
        processFile(argList[2]); //second
    }
    else
    {
        qDebug() << "main(): not enough arguments: exactly two filenames needed! given were: " << argList.size() << endl;
    }

    return 0; //for success
}
