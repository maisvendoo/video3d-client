#include    "model-loader.h"

#include    <osg/Texture2D>
#include    <osgDB/FileUtils>
#include    <osgDB/FileNameUtils>

#include    "file-funcs.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::Texture2D *createTexture(const std::string &texture_path)
{
    if (texture_path.empty())
        return nullptr;

    std::string fileName = osgDB::findDataFile(texture_path, osgDB::CaseSensitivity::CASE_INSENSITIVE);

    if (fileName.empty())
        return nullptr;

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile(fileName);

    if (!image.valid())
        return nullptr;

    std::string ext = osgDB::getLowerCaseFileExtension(fileName);

    if (ext == "bmp")
        image->flipVertical();

    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;

    if (ext == "tga")
        texture->setInternalFormatMode(osg::Texture2D::USE_S3TC_DXT5_COMPRESSION);
    else
        texture->setInternalFormatMode(osg::Texture2D::USE_S3TC_DXT1_COMPRESSION);

    texture->setImage(image.get());
    texture->setWrap(osg::Texture2D::WRAP_T, osg::Texture::REPEAT);
    texture->setWrap(osg::Texture2D::WRAP_S, osg::Texture::REPEAT);
    texture->setResizeNonPowerOfTwoHint(false);
    texture->setUnRefImageDataAfterApply(true);

    return texture.release();
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
osg::PagedLOD *createLODNode(const model_info_t &model_info)
{
    std::string fileName = osgDB::findDataFile(model_info.filepath, osgDB::CaseSensitivity::CASE_INSENSITIVE);

    if (fileName.empty())
        return nullptr;

    // Prepare model loading
    osg::ref_ptr<osg::PagedLOD> pagedLOD = new osg::PagedLOD;
    pagedLOD->setFileName(0, fileName);
    pagedLOD->setRange(0, 0.0f, model_info.view_distance);

    // Apply texture
    osg::ref_ptr<osg::Texture2D> texture = createTexture(model_info.texture_path);
    pagedLOD->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    // Apply transparency settings
    std::string ext = osgDB::getLowerCaseFileExtension(model_info.texture_path);
    if (ext == "tga")
        pagedLOD->getOrCreateStateSet()->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    else
        pagedLOD->getOrCreateStateSet()->setRenderingHint(osg::StateSet::OPAQUE_BIN);    

    return pagedLOD.release();
}
