//! @date 20160714 1400
//! @author mail@marcelpetrick.it
//! @brief: compare the content of two files; per line one item as
//!         ISBN (number; 13 digits; no leading or trailing whitespace (remove this));
//!         print every item of input0 which is not contained in input1
//! @version 0.01 unreleased
//! @file main.cpp

//Qt-includes
#include <QCoreApplication> //for arg-list
#include <QTextStream> //read file
#include <QFileInfo> //for the file-existance-check
#include <QDebug> //! @todo remove later
#include <QStringList>

QStringList readFile(QString fileName)
{
    QStringList returnValue;

    QFile inputFile(fileName);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        static int lineNumber(1); //because pluma numbers starting with 1
        QTextStream inputStream(&inputFile);
        while(!inputStream.atEnd())
        {
            QString const line = inputStream.readLine().trimmed(); //maybe also check simplified()
            qDebug() << "line " << QString(lineNumber < 10 ? "0" : "").append(QString::number(lineNumber)) << ": #" << line << "#"; //enclosed to proof for correct trimming
            if(!line.isEmpty())
            {
                returnValue.append(line); //! insert
            }

            lineNumber++;
        }

        qDebug() << "readFile(): read " << lineNumber;
        lineNumber= 0;

        inputFile.close();
    }

    //! sort
    returnValue.sort(Qt::CaseSensitive); //just to make it clear; default is CS anyway

    //! remove duplicates and if something happened: report this!
    long removedDuplicates = returnValue.removeDuplicates();
    qDebug() << "readFile(): removed " << removedDuplicates << " Duplicates" << endl;

    //! hand over
    return returnValue;
}

QStringList processFile(QString path)
{
    QStringList returnValue;

    QFileInfo fileInfo(path);
    if(fileInfo.exists())
    {
        //! read content of current file
        returnValue = readFile(path);
    }
    else
    {
        qDebug() << "processFile(): the file DOES NOT exist! path was \"" << path << "\"" << endl;
    }

    //! hand over
    return returnValue;
}

QStringList filterAgainst(QStringList list0, QStringList list1)
{
    QStringList returnValue;

//    qDebug() << "filterAgainst(): reached" << endl;

    foreach(QString item, list0)
    {
        bool const contained(list1.contains(item));
        if(!contained)
        {
            returnValue.append(item);
        }
    }

    //! hand over
    return returnValue;
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
        QStringList list0 = processFile(argList[1]); //first "real" arg; first argument is the binary-name itself
        QStringList list1 = processFile(argList[2]); //second

        //! @todo do some more stuff
        QStringList result = filterAgainst(list0, list1);

        //print filtered result: not "filter" by contain, but "!contained"
        foreach(QString item, result)
        {
            qDebug() << "result: " << item;
        }
    }
    else
    {
        qDebug() << "main(): not enough arguments: exactly two filenames needed! given were: " << argList.size() << endl;
    }

    return 0; //for success
}
