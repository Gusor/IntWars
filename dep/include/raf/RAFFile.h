#ifndef __H_RAFFILE
#define __H_RAFFILE

#include <map>
#include <vector>

#include "FileReader.h"
#include "stdafx.h"

struct RAFHeader {
   uint32 magicNumber;
   uint32 version;
   uint32 managerIndex;
   uint32 fileListOffset;
   uint32 pathListOffset;
};

struct FileEntry {
   uint32	offset;
	uint32	size;
	uint32	fileNameStringTableIndex;
};

class RAFFile {
public:
   RAFFile(const std::string& filename);
   bool readFile(const std::string& path, std::vector<unsigned char>& toFill);
   
   static uint32 getHash(const std::string& path);

private:
   FileReader rafHeaderFile;
   FileReader rafDataFile;
   
   RAFHeader header;
   std::map<uint32, FileEntry> fileEntries;

};

#endif