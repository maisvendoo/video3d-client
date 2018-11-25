#include    "texture-loader.h"

#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

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

    std::string fileName = osgDB::findDataFile(texture_path);

    if (fileName.empty())
        return;

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(fileName);

    std::string ext = osgDB::getLowerCaseFileExtension(fileName);

    if (image.valid())
    {
        if (ext == "bmp")
        {
            image->flipVertical();
        }

        osg::Texture2D *texture = static_cast<osg::Texture2D *>(sa);
        texture->setImage(image.get());
        is_textured = true;
    }
}
