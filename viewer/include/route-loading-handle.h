#ifndef     ROUTE_LOADING_HANDLE_H
#define     ROUTE_LOADING_HANDLE_H

#include    <osgGA/GUIEventHandler>
#include    <osgViewer/Viewer>

#include    "route-info.h"

class RouteLoadingHandle : public osgGA::GUIEventHandler
{
public:

    RouteLoadingHandle(osg::Switch *root);

    virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa);

private:

    osg::ref_ptr<osg::Switch> root;

    osg::ref_ptr<osg::Group> routeRoot;

    bool                      is_loaded;

    osgGA::GUIEventHandler *cameraHandler;

    unsigned int current_route_id;

    std::map<unsigned int, route_info_t> routes_info;


    /// Load routes info list
    bool loadRoutesInfo(std::string path);

    /// Load route form directory
    bool loadRoute(const std::string &routeDir, osgViewer::Viewer *viewer);

    /// Load route by ID
    bool loadRouteByID(unsigned int id, osgViewer::Viewer *viewer);

    /// Init common graphical engine settings
    bool initEngineSettings(osg::Group *routeRoot);
};

#endif // ROUTE_LOADING_HANDLE_H
