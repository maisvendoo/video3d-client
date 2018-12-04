#ifndef		FILESYSTEM_H
#define		FILESYSTEM_H

#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

#include    "import-export.h"

#ifdef FILESYSTEM_LIB
    #define FILESYSTEM_EXPORT   DECL_EXPORT
#else
    #define FILESYSTEM_EXPORT   DECL_IMPORT
#endif

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class FILESYSTEM_EXPORT FileSystem
{
public:

    /// Get instance byt filesystem singleton
    static FileSystem &getInstance()
    {
        static FileSystem instance;
        return instance;
    }

    /// Set route direcory path in paltform native format
    void setRouteRootDir(const std::string &path);

    std::string getNativePath(const std::string &path);

    /// Get route directory path
    std::string getRouteRootDir() const;    

    /// Get native path separator
    char separator() const;

private:

    std::string routeRootDir;

    FileSystem() {}
    FileSystem(const FileSystem &) = delete;
    FileSystem &operator=(FileSystem &) = delete;
};

#endif
