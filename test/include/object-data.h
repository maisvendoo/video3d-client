#ifndef     OBJECT_DATA_H
#define     OBJECT_DATA_H

#include    <string>

#include    <osg/Geometry>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct object_ref_t
{
    std::string     name;
    std::string     mode;
    std::string     model_path;
    std::string     texture_path;

    object_ref_t()
        : name("")
        , mode("")
        , model_path("")
        , texture_path("")
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct object_map_t
{
    std::string name;
    osg::Vec3   position;
    osg::Vec3   attitude;
    std::string caption;

    object_map_t()
        : name("")
        , position(osg::Vec3())
        , attitude(osg::Vec3())
        , caption("")
    {

    }
};

#endif // OBJECT_DATA_H
