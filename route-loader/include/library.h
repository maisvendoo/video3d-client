#ifndef         LIBRARY_H
#define         LIBRARY_H

#if __unix__
    #include    <dlfcn.h>
#else
    #include   <windows.h>
#endif

#include        <string>

class Library
{
public:

    Library(const std::string &path, const std::string &name);
    ~Library();

    bool load();

    void *resolve(std::string func_name);

private:

    std::string _path;

    void        *_lib_ptr;
};

#endif // LIBRARY_H
