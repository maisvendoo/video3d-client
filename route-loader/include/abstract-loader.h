#ifndef		ABSTRACT_LOADER_H
#define		ABSTRACT_LOADER_H

#include    <osg/Referenced>
#include    <osg/Group>
#include    <osgGA/GUIEventHandler>

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
class OSG_EXPORT RouteLoader : public osg::Referenced
{
public:

    /// Cjnstructor
    RouteLoader();

    /// Load route
    virtual void load(std::string routeDir) = 0;

    /// Get route scene group node
    virtual osg::Group *getRoot();

    /// Get camera events handler
    virtual osgGA::GUIEventHandler *getCameraEventHandler(int direction, float camera_height) = 0;

protected:    

    /// Route directory
    std::string routeDir;

    /// Route static scene root node
    osg::ref_ptr<osg::Group>    root;

    /// Destructor
    virtual ~RouteLoader() {}

    /// Load data from route config file
    virtual ReadResult loadDataFile(const std::string &filepath) = 0;
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
typedef RouteLoader* (*GetRouteLoader)();

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
#define GET_ROUTE_LOADER(ClassName) \
    extern "C" OSG_EXPORT RouteLoader *getRouteLoader() \
    {\
        return new (ClassName)(); \
    }

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
extern "C" OSG_EXPORT RouteLoader *loadRouteLoader(const std::string &path, const std::string &name);

#endif