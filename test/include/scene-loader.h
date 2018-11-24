#ifndef     SCENE_LOADER_H
#define     SCENE_LOADER_H

#include    <string>
#include    <map>
#include    <vector>
#include    <fstream>

#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

#include    "object-data.h"

enum ReadResult
{
    READ_SUCCESS,
    FILE_NOT_FOUND,
    FILE_NOT_HANDLED
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class SceneLoader
{
public:

    SceneLoader() {}
    SceneLoader(std::string routeDir);
    ~SceneLoader() {}

    osg::Group *getRoot();

protected:

    std::string routeDir;

    std::map<std::string, object_ref_t> objectRef;
    std::vector<object_map_t> objectMap;

    osg::ref_ptr<osg::Group> root;

    ReadResult loadDataFile(const std::string &filepath);

    ReadResult loadObjectRef(std::istream &stream);

    ReadResult loadObjectMap(std::istream &stream);
};

#endif // SCENE_LOADER_H
