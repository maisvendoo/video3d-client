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

    /// Get instance byt filesystem singleton
    static FileSystem &getInstance()
    {
        static FileSystem instance;
        return instance;
    }

    /// Set route direcory path in paltform native format
    void setRouteRootDir(const std::string &path)
    {
        routeRootDir = getNativePath(path);
    }

    /// Get route directory path
    std::string getRouteRootDir() const
    {
        return routeRootDir;
    }

    /// Convert file path to native format
    std::string getNativePath(const std::string &path) const
    {
        return osgDB::convertFileNameToNativeStyle(path);
    }

    /// Get native path separator
    char separator() const
    {
        return osgDB::getNativePathSeparator();
    }

private:

    std::string routeRootDir;

    FileSystem() {}
    FileSystem(const FileSystem &) = delete;
    FileSystem &operator=(FileSystem &) = delete;
};

#endif
