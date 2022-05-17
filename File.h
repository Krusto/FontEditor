#pragma once
#include <string> // библиотека за текст
#include <vector> // библиотека за низове
#include <fstream> // библиотека за файлове
#include <filesystem> // библиотека за файлова система
namespace fs = std::filesystem;

namespace Util {
    enum class FileDataType {
        None,
        Binary,
        Text
    };
    enum FileOperationFlags {
        None = 0,
        Read = 1,
        Write = 2,
        CreateIfNotExist = 4,
    };
    class File {
    public:
        File() = default;
        ~File() {}

        void CreateNew(const char* path);
        File(const char* path,FileDataType dataType,FileOperationFlags fileOperationFlags);
        void Reload();

        operator std::fstream&() { return *file; }

        void Open(const char* path, FileDataType dataType, FileOperationFlags fileOperationFlags)
        {
            *this = File(path, dataType, fileOperationFlags);
        }
        void Free() {
            this->~File();
        }
        
        void SaveData(std::vector<std::vector<char>>& data) {
            if (mode == 2) {
                file->close();
                delete file;
                std::filesystem::remove(Path + "\\" + Name);
                 file = new std::fstream(Path, std::ios::out);
            }
            for (size_t i = 0; i < data.size(); i++)
            {
                std::string line;
                for (size_t j = 0; j < data[i].size(); j++)
                {
                    line += data[i][j];
                }
                line += '\n';
                file->write(line.data(),line.size());
            }
            file->flush();
            file->close();
            delete file;
        }
        void GetData(std::vector<std::vector<char>>& data,uint32_t width) {
            for (size_t y = 0; y < data.size(); y++)
            {
                for (size_t x = 0; x < data[y].size(); x++)
                {
                    data[y][x] = this->data[y * (width+1) + x];
                }
            }
        }
        std::string Name = "";
        std::string Path = "";
        std::vector<uint8_t> data;
        int mode{};
        std::fstream* file;
        uint64_t FileSize = 0;
        FileDataType dataType = FileDataType::None;
        FileOperationFlags fileOperationFlags = FileOperationFlags::None;
    };
}

