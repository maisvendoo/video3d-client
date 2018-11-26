//------------------------------------------------------------------------------
//
//      Texture loader callback
//      (c) maisvendoo, 22/11/2018
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief Texture loader callback
 * \copyright maisvendoo
 * \author maisvendoo
 * \date 22/11/2018
 */

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
