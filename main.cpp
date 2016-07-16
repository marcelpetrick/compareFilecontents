//! @date 20160714 1500
//! @author mail@marcelpetrick.it
//! @brief: compare the content of two files; one item per line as
//!         ISBN (number; 13 digits; no leading or trailing whitespace (remove this));
//!         print every item of input0 which is not contained in input1 to std::cerr.
//! @version 0.01
//! @file main.cpp

//Qt-includes
#include <QCoreApplication> //for arg-list
#include <QTextStream> //for reading the files
#include <QFileInfo> //for the file-existance-check
#include <QDebug> //! @todo remove later
#include <QStringList>

//! @brief  TODO
QStringList readFile(QString fileName)
{
    QStringList returnValue;

    QFile inputFile(fileName);
    if(inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
//        static int lineNumber(1); //because pluma numbers starting with 1
        QTextStream inputStream(&inputFile);
        while(!inputStream.atEnd())
        {
            QString const line = inputStream.readLine().trimmed(); //remove whitespace
//            qDebug() << "line " << QString(lineNumber < 10 ? "0" : "").append(QString::number(lineNumber))
//                << ": #" << line << "#"; //enclosed to proof for correct trimming
            if(!line.isEmpty())
            {
                returnValue.append(line); //! insert
            }

//            lineNumber++;
        }

//        qDebug() << "readFile(): read " << lineNumber;
//        lineNumber= 0;

        inputFile.close();
    }

    //! sort: not really necessary because of the check via "contains" ..
    returnValue.sort(Qt::CaseSensitive); //just to make it clear; default is CS anyway

    //! remove duplicates and if something happened: report this!
    /*long removedDuplicates = */returnValue.removeDuplicates();
//    qDebug() << "readFile(): removed " << removedDuplicates << " Duplicates" << endl;

    //! hand over
    return returnValue;
}

//! @brief  TODO
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

    return returnValue;
}

//! @brief  Check for each item of input0 if it is not contained in input1: append to returned QStringList.
QStringList filterAgainst(QStringList list0, QStringList list1)
{
    QStringList returnValue;

    foreach(QString item, list0)
    {
        bool const contained(list1.contains(item));
        if(!contained)
        {
            returnValue.append(item);
        }
    }

    return returnValue;
}

//! @brief  TODO
int main(int argc, char* argv[])
{
    //for easier access to the arguments; without real parsing
    QCoreApplication app(argc, argv);
    QStringList argList(app.arguments());

//    //check the arguments
//    {
//        qDebug() << "main(): argc = " << argc << endl;
//        // print the current argument list
//        for(int i = 0; i < argList.size(); ++i)
//        {
//            qDebug() << QString("argv #%1 is %2").arg(i).arg(argList[i]) << endl;
//        }
//    }

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
