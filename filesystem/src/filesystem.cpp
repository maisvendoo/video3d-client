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
void FileSystem::setConfigDir(const std::string &path)
{
    configDir = getNativePath(path);
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
std::string FileSystem::getConfigDir() const
{
    return configDir;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FileSystem::getNativePath(const std::string &path)
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

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
std::string FileSystem::getLevelUpDirectory(std::string path, int num_levels)
{
    std::vector<std::string> path_elems;
    osgDB::getPathElements(path, path_elems);

 #if __unix__
    std::string tmp = "/";
#else
    std::string tmp = "";
#endif

    for (auto it = path_elems.begin(); it != path_elems.end() - num_levels; ++it)
    {
        tmp += (*it) + separator();
    }

    return tmp;
}
