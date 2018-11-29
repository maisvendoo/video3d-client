#ifndef     MODEL_LOADER_H
#define     MODEL_LOADER_H

#include    <osg/PagedLOD>
#include    <osg/ProxyNode>
#include    <osgDB/ReadFile>

#include    <osg/Texture2D>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct model_info_t
{
    float       view_distance;
    std::string name;
    std::string filepath;
    std::string texture_path;
    bool        mipmap;

    model_info_t()
        : view_distance(800.0f)
    {

    }
};

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::PagedLOD *createLODNode(const model_info_t &model_info);

void createTexture(const std::string &texture_path, osg::Texture2D *texture);

#endif // MODEL_LOADER_H
