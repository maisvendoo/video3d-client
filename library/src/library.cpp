#include    "library.h"
#include    "filesystem.h"

#include    <cstdlib>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Library::Library(const std::string &path, const std::string &name)
    : _path("")
    , _lib_ptr(nullptr)
{
    FileSystem &fs = FileSystem::getInstance();

    _path = fs.getNativePath(path) + fs.separator() + name;

#if __unix__
    _path += ".so";
#else
    _path += ".dll";
#endif
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
Library::~Library()
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
bool Library::load()
{
    if (_path.empty())
        return false;

#if __unix__    

    _lib_ptr = dlopen(_path.c_str(), RTLD_LAZY);

    if (_lib_ptr != nullptr)
        return true;

#else

    wchar_t *path = new wchar_t[_path.size()];
    std::mbstowcs(path, _path.c_str(), _path.size());
    _lib_ptr = LoadLibrary(path);

    delete [] path;

    if (_lib_ptr != nullptr)
        return true;
#endif

    return false;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void *Library::resolve(std::string func_name)
{
#if __unix__

    return dlsym(_lib_ptr, func_name.c_str());

#else

    return (void*) GetProcAddress((HMODULE) _lib_ptr, func_name.c_str());

#endif
}
