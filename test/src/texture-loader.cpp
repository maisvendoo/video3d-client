#include    "texture-loader.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void LoadTextureCallback::operator()(osg::StateAttribute *sa, osg::NodeVisitor *nv)
{
    (void) nv;

    if (is_textured)
        return;

    if (texture_path.empty())
        return;

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(texture_path);

    if (image.valid())
    {
        osg::Texture2D *texture = static_cast<osg::Texture2D *>(sa);
        texture->setImage(image.get());
        is_textured = true;
    }
}
