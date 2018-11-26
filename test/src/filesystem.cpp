#include    "filesystem.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void FileSystem::setRouteRootDir(const std::string &path)
{
    routeRootDir = getNativePath(path);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FileSystem::getRouteRootDir() const
{
    return routeRootDir;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FileSystem::getNativePath(const std::string &path) const
{
    return osgDB::convertFileNameToNativeStyle(path);
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
char FileSystem::separator() const
{
    return osgDB::getNativePathSeparator();
}
