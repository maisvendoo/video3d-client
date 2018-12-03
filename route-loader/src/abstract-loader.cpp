#include    "abstract-loader.h"

#include    "library.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RouteLoader::RouteLoader()
    : routeDir("")
    , root(new osg::Group)
{

}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Group *RouteLoader::getRoot()
{
    if (root.valid())
        return root.release();
    else
        return nullptr;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
RouteLoader *loadRouteLoader(const std::string &path, const std::string &name)
{
    RouteLoader *loader = nullptr;

    Library lib(path, name);

    if (lib.load())
    {
        GetRouteLoader getRouteLoader = (GetRouteLoader) lib.resolve("getRouteLoader");

        if (getRouteLoader)
        {
            loader = getRouteLoader();
        }
    }

    return loader;
}
