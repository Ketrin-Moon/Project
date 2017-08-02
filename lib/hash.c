#include "../include/header.h"
/*
uint32_t jenkins_hash(char *key, size_t len)
{
uint32_t hash, i;
for(hash=i=0; i<len; ++i){
hash+=key[i];
hash+=(hash<<10);
hash^=(hash>>6);
}
hash+=(hash<<3);
hash^=(hash>>11);
hash+=(hash<<15);
return hash%HASHTAB_SIZE;
}
*/
uint32_t jenkins_hash(char *key, size_t len){
unsigned int h=0;
char *p;
for(p=key;*p!='\0';p++){
	h=h*31+(unsigned int)*p;
}
return h%HASHTAB_SIZE;
}
