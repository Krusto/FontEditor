#include "File.h"
#include <fstream>
#include <iostream>


Util::File::File(const char* path, FileDataType dataType,FileOperationFlags fileOperationFlags)
{
    if(fs::exists(path) == false){
            std::cout<<"File "<<path<<" does not exist\n";
            exit(-1);
    }

	this->dataType = dataType;
	this->fileOperationFlags = fileOperationFlags;
	this->Name = fs::path(path).filename().string();
	this->Path = std::string(path);


	if (fileOperationFlags & FileOperationFlags::Read) {
		FileSize = fs::file_size(path);
		data.resize(FileSize);

		if (dataType == FileDataType::Binary) {
			this->file = new std::fstream(path, std::ios::in | std::ios::binary);

            if(this->file->good() == false){
                std::cout<<"File with name: "<<path<<" does not exist!\n";
                exit(-1);
            }
			file->read((char*)data.data(), FileSize);
		}else if (dataType == FileDataType::Text) {
			this->file = new std::fstream(path, std::ios::in | std::ios::out);
			file->read((char*)data.data(), FileSize);
		}
	}

}

void Util::File::CreateNew(const char* path){
   if(fs::exists(path) == true){
        std::cout<<"File "<<path<<" already exists!\n";
        exit(-1);
    }
   this->dataType = FileDataType::Text;
   this->fileOperationFlags = FileOperationFlags::Write;
   this->Name = fs::path(path).filename().string();
   this->Path = std::string(fs::current_path().string());

   this->file = new std::fstream((Path+"//"+Name), std::ios::out);
   this->FileSize = 0;
}
void Util::File::Reload()
{
	delete this->file;
	*this = File(*this);
}
