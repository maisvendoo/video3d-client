#include    "library.h"
#include    "filesystem.h"

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
#if __unix__

    if (_path.empty())
        return false;

    _lib_ptr = dlopen(_path.c_str(), RTLD_LAZY);

    if (_lib_ptr != nullptr)
        return true;

    return false;

#else

#endif
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void *Library::resolve(std::string func_name)
{
#if __unix__

    return dlsym(_lib_ptr, func_name.c_str());

#else

#endif
}
