#include "RAFFile.h"
#include <stdio.h>
#include "miniz.h"

#define BUF_SIZE 1024*1024

using namespace std;

RAFFile::RAFFile(const std::string& filename) : rafHeaderFile(filename), rafDataFile(filename+".dat") {
   rafHeaderFile >> header;
   
   if(header.magicNumber != 0x18be0ef0) {
      return;
   }
   
   uint32 fileCount;
   
   rafHeaderFile.seek(header.fileListOffset);
   rafHeaderFile >> fileCount;
   
   for(int i = 0; i < fileCount; ++i) {
      FileEntry entry;
      uint32 hash;
      
      rafHeaderFile >> hash >> entry;
      // printf("Hash : %08X ; Offset : %08X ; Size : %08X ; Index : %08x\n", hash, entry.offset, entry.size, entry.fileNameStringTableIndex);
      fileEntries[hash] = entry;
   }   
}

uint32 RAFFile::getHash(const std::string& path) {
	unsigned int hash = 0;
	unsigned int mask = 0xF0000000;
	for(unsigned int i = 0; i < path.length(); i++)
	{
		hash = tolower(path[i]) + (0x10 * hash);
		if(hash & mask)
			hash ^= hash & mask ^ ((hash & mask) >> 24);
	}
	return hash;
}

bool RAFFile::readFile(const std::string& path, vector<unsigned char>& toFill) {
   uint32 hash = getHash(path);
   vector<unsigned char> compressedFile;
   
   map<uint32, FileEntry>::iterator entry = fileEntries.find(hash);
   
   if(entry == fileEntries.end()) {
      return false;
   }
   
   rafDataFile.seek(entry->second.offset);
   rafDataFile.read(compressedFile, entry->second.size);
   
   z_stream stream;
   uint8 s_outbuf[BUF_SIZE]; // 1MB
   
   // Init the z_stream
   memset(&stream, 0, sizeof(stream));
   stream.next_in = &compressedFile[0];
   stream.avail_in = compressedFile.size();
   stream.next_out = s_outbuf;
   stream.avail_out = BUF_SIZE;
   
   if (inflateInit(&stream))
   {
      printf("inflateInit() failed!\n");
      return false;
   }

   for ( ; ; )
   {
      int status;

      status = inflate(&stream, Z_SYNC_FLUSH);

      if ((status == Z_STREAM_END) || (!stream.avail_out))
      {
         toFill.insert(toFill.end(), s_outbuf, s_outbuf + BUF_SIZE - stream.avail_out);
         stream.avail_out = BUF_SIZE;
         stream.next_out = s_outbuf;
      }

      if (status == Z_STREAM_END)
         break;  
      
      if (status != Z_OK)
      {
         printf("inflate() failed with status %i!\n", status);
         return false;
      }
   }

    if (inflateEnd(&stream) != Z_OK)
    {
      printf("inflateEnd() failed!\n");
      return false;
    }
   
   return true;
}