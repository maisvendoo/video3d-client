#ifndef     TEXTURE_LOADER_H
#define     TEXTURE_LOADER_H

#include    <osg/NodeCallback>
#include    <osg/PagedLOD>
#include    <osg/Texture2D>

#include    "model-loader.h"

class TextureLoader : public osg::NodeCallback
{
public:

    TextureLoader(const std::string &texture_path)
        : texture_path(texture_path)
        , _is_textured(false)
    {

    }

    virtual void operator() (osg::Node *node, osg::NodeVisitor *nv)
    {
        (void) nv;

        if (!_is_textured)
        {
            osg::PagedLOD *pagedLOD = static_cast<osg::PagedLOD *>(node);

            std::string description = pagedLOD->getDescription(0);

            if (pagedLOD->isCullingActive())
            {
                osg::Texture2D *texture = static_cast<osg::Texture2D *>(pagedLOD->getOrCreateStateSet()->getTextureAttribute(0, osg::StateAttribute::TEXTURE));

                if (texture)
                {
                    createTexture(texture_path, texture);
                }

                _is_textured = true;
            }
        }

        traverse(node, nv);
    }

private:

    std::string texture_path;
    bool _is_textured;
};

#endif // TEXTURE_LOADER_H
