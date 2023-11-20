#include <iostream>
#include "FileManager.h"


int main()
{
    std::string folderName;
    std::cout << "Choose folder to compress." << std::endl;
    std::cin >> folderName;

    FileManager fileManager;
    fileManager.compressFolder(folderName);
    
    return 0;
}