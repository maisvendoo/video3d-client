#include    "abstract-loader.h"

AbstractLoader::AbstractLoader(std::string routeDir)
    : routeDir(routeDir)
    , root(new osg::Group)
{

}

osg::Group *AbstractLoader::getRoot()
{
    if (root.valid())
        return root.release();
    else
        return nullptr;
}
