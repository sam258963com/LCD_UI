#ifndef PATH_H
#define PATH_H

#include "stringlist.h"

class path : public stringlist
{
    public:
        char* fullpath();
        bool fullpath(char *,size_t);

    protected:
    private:
};

#endif // PATH_H
