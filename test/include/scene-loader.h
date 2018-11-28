//------------------------------------------------------------------------------
//
//      Loader for ZDSimulator routes
//      (c) maisvendoo, 26/11/2018
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief Loader for ZDSimulator routes
 * \copyright maisvendoo
 * \author maisvendoo
 * \date 26/11/2018
 */

#ifndef     SCENE_LOADER_H
#define     SCENE_LOADER_H

#include    <string>
#include    <map>
#include    <vector>
#include    <fstream>

#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

#include    "object-data.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
enum ReadResult
{
    FILE_READ_SUCCESS,
    FILE_NOT_FOUND,
    FILE_NOT_HANDLED
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class SceneLoader
{
public:

    /// Default constructor
    SceneLoader() {}

    /// Constructor for load route
    SceneLoader(std::string routeDir);

    /// Destructor
    ~SceneLoader() {}

    /// Get route scene group node
    osg::Group *getRoot();

protected:

    /// Route directory
    std::string routeDir;

    /// List objects from file objects.ref
    std::map<std::string, object_ref_t> objectRef;

    /// List objects from file route1.map
    std::vector<object_map_t> objectMap;

    /// Root group node of scene
    osg::ref_ptr<osg::Group> root;

    /// Load data from route files
    ReadResult loadDataFile(const std::string &filepath);

    /// Load data from *.ref file
    ReadResult loadObjectRef(std::istream &stream);

    /// Load data from *map file
    ReadResult loadObjectMap(std::istream &stream);
};

#endif // SCENE_LOADER_H
