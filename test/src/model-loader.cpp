#include    "model-loader.h"

#include    <osg/Texture2D>
#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>
#include    <osgDB/ImageOptions>

#include    "file-funcs.h"
#include    "texture-loader.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void createTexture(const std::string &texture_path, osg::Texture2D *texture)
{
    if (texture_path.empty())
        return;

    std::string fileName = osgDB::findDataFile(texture_path,
                                               osgDB::CaseSensitivity::CASE_INSENSITIVE);

    if (fileName.empty())
        return;

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(fileName);

    if (!image.valid())
        return;

    std::string ext = osgDB::getLowerCaseFileExtension(fileName);

    if (ext == "bmp")
        image->flipVertical();    

    /*if (ext == "tga")
        texture->setInternalFormatMode(osg::Texture2D::USE_S3TC_DXT5_COMPRESSION);
    else
        texture->setInternalFormatMode(osg::Texture2D::USE_S3TC_DXT1_COMPRESSION);*/

    texture->setImage(image.get());
    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::REPEAT);    
    texture->setUnRefImageDataAfterApply(true);    
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::PagedLOD *createLODNode(const model_info_t &model_info)
{
    std::string fileName = osgDB::findDataFile(model_info.filepath,
                                               osgDB::CaseSensitivity::CASE_INSENSITIVE);

    if (fileName.empty())
        return nullptr;

    // Prepare model loading
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    pagedLOD->addDescription(model_info.name);
    pagedLOD->setFileName(0, fileName);
    pagedLOD->setRange(0, 0.0f, model_info.view_distance);

    // Apply texture
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

    pagedLOD->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    // Apply transparency settings
    std::string ext = osgDB::getLowerCaseFileExtension(model_info.texture_path);
    if (ext == "tga")
        pagedLOD->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    else
        pagedLOD->getOrCreateStateSet()->setRenderingHint(osg::StateSet::OPAQUE_BIN);

    pagedLOD->setCullCallback(new TextureLoader(model_info.texture_path));

    return pagedLOD.release();
}
