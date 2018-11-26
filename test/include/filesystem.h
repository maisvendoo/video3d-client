#ifndef		FILESYSTEM_H
#define		FILESYSTEM_H

#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class FileSystem
{
public:

    static FileSystem &getInstance()
    {
        static FileSystem instance;
        return instance;
    }

    void setRouteRootDir(const std::string &path);

private:

    std::string routeRootDir;

    FileSystem() {}
    FileSystem(const FileSystem &) = delete;
    FileSystem &operator=(FileSystem &) = delete;
};

#endif
