#include <iostream>
#include <string>
#include <cassert>
#include<fstream>
#include "../include/zip.hpp"

enum ZIP_ACTION
{
    COMPRESS,
    DECOMPRESS
};
void whatUserWant(ZIP_ACTION &ACTION);

void Compress();
void Decompress();
int main()
{
    ZIP_ACTION Action{};
    whatUserWant(Action);
    if (Action==COMPRESS)
    {
        Compress();
    }else
    {
        Decompress();
    }
    return 0;
};

void Compress()
{
    std::cout<<"Enter The File path u want to compress in : ";
    std::string file_name{};
    std::getline(std::cin,file_name);
    FILE* file;
    file=fopen(file_name.c_str(),"r");
    if(file)
    {
        char c{};
        c=getc(file);
        std::string data{};
        while(c!=EOF)
        {
            data+=c;
            c=getc(file);
        };
        std::cout<<"ouput zip file name you want : ";
        std::string zip_file_name{};
        std::getline(std::cin,zip_file_name);
        miniz_cpp::zip_file output{};
        output.write(file_name,data);
        output.save(zip_file_name);
        fclose(file);
    }else
    {
        std::cout<<"[error] Failed to Open File!\n";
        return;
    };
};

void Decompress()
{
    std::cout<<"Enter the file path you want to decompress : ";
    std::string file_name{};
    std::getline(std::cin,file_name);
    //continue ...
};

void whatUserWant(ZIP_ACTION &Action)
{
    while (true)
    {
        std::cout << "What Do you want[Compress-0/Decompress-1]:";
        uint16_t input{};
        std::cin >> input;
        if (input == (0)) [[likely]]
        {
            Action = COMPRESS;
            break;
        }
        else if (input == (1)) [[likely]]
        {
            Action = DECOMPRESS;
            break;
        }
        else [[unlikely]]
        {
            std::cout << "[error] Invalid Input!\n";
            continue;
        };
    };
    std::cin.clear();
    std::cin.ignore();
};
