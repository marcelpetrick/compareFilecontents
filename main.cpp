//! @date 20160709 0033
//! @author mail@marcelpetrick.it
//! topic: compare the content of two files; per line one item as ISBN (number; 13 digits; no leading or trailing whitespace (remove this)); print every item of input0 which is not contained in input1

//#include <QCoreApplication>

#include <iostream>

//! @todo check how argc, argv work
//!
int main(int argc, char *argv[])
{
//    QCoreApplication a(argc, argv);

    if(argc != 3)
    {
        std::cout << "invalid number of arguments: provide two filenames" << std::endl;
    }
    else
    {
        std::cout << "correct number" << std::endl;
        std::cout << "argc:" << argc << std::endl;
        std::cout << "argv:" << argv[0] << std::endl;
        std::cout << "argv:" << argv[1] << std::endl;
        std::cout << "argv:" << argv[2] << std::endl;

        //open file0 and file1
        //sort contents?
        //take first


    }

    return 0;
//    return a.exec();
}
