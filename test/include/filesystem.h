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

    std::string getRouteRootDir() const;

    std::string getNativePath(const std::string &path) const;

    char separator() const;

private:

    std::string routeRootDir;

    FileSystem() {}
    FileSystem(const FileSystem &) = delete;
    FileSystem &operator=(FileSystem &) = delete;
};

#endif
