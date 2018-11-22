#ifndef     TEXTURE_LOADER_H
#define     TEXTURE_LOADER_H

#include    <osg/Texture2D>
#include    <osgDB/ReadFile>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
class LoadTextureCallback : public osg::StateAttributeCallback
{
public:

    LoadTextureCallback(std::string texture_path)
        : texture_path(texture_path)
        , is_textured(false)
    {

    }

    virtual void operator() (osg::StateAttribute *, osg::NodeVisitor *);

protected:

    std::string texture_path;
    bool is_textured;
};

#endif // TEXTURE_LOADER_H
