#include "path.h"
#include <limits.h>

char* path::fullpath()
{
    size_t length = 1;
    for(int i=0;i<this->size();i++)
    {
        length+=strlen(this->get(i))+1;
    }
    char *fpath = new char[length+1];
    strcat(fpath,"/");
    for(int i=0;i<this->size();i++)
    {
        strcat(fpath,this->get(i));
        strcat(fpath,"/");
    }
    return fpath;
}

bool path::fullpath(char* fpath,size_t buflength)
{
    size_t length = 1;
    for(int i=0;i<this->size();i++)
    {
        length+=strlen(this->get(i))+1;
    }
    if(length>buflength) return false;
    strcat(fpath,"/");
    for(int i=0;i<this->size();i++)
    {
        strcat(fpath,this->get(i));
        strcat(fpath,"/");
    }
    return true;
}
