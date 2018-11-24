#ifndef     MODEL_LOADER_H
#define     MODEL_LOADER_H

#include    <osg/PagedLOD>
#include    <osgDB/ReadFile>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct model_info_t
{
    float       view_distance;
    std::string filepath;
    std::string texture_path;    

    model_info_t()
        : view_distance(1000.0f)
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::PagedLOD *createLODNode(const model_info_t &model_info);

#endif // MODEL_LOADER_H
