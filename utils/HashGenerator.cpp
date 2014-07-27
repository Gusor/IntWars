#include "../gamed/include/stdafx.h"



/** Functions made by Intline9 **/
unsigned int getHash(const char *str)
{
	unsigned int hash = 0;
	unsigned int mask = 0xF0000000;
	for(unsigned int i = 0; i < strlen(str); i++)
	{
		hash = tolower(str[i]) + (0x10 * hash);
		if(hash & mask)
			hash ^= hash & mask ^ ((hash & mask) >> 24);
	}
	return hash;
}

/** Functions made by Intline9 **/
unsigned int getHashObject(const char *str)
{
	unsigned int hash = 0;
	const char* gobj = "_gobj";
	for(unsigned int i = 0; i < strlen(str); i++)
		hash = tolower(str[i]) + (0x1003F * hash);
	for(unsigned int i = 0; i < strlen(gobj); i++)
		hash = tolower(gobj[i]) + (0x1003F * hash);
	return hash;
}

int main(int argc, char **argv)
{
      if (argc < 2) { 
    fprintf(stderr, "Usage: %s spell name(for example SummonerRevive)\n", argv[0]); 
    exit(1); 
  }
      

      
  fprintf(stderr,"%08X\n", getHash(argv[1]));
  
  
  unsigned short a = 0x108F;
  float aa = (float)a;
  fprintf(stderr,"%f", aa);
}