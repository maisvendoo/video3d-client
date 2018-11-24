#include    "scene-loader.h"
#include    "model-loader.h"
#include    "string-funcs.h"

#include    <sstream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
SceneLoader::SceneLoader(std::string routeDir)
    : routeDir(routeDir)
{
    loadDataFile(this->routeDir + "/objects.ref");
    loadDataFile(this->routeDir + "/route1.map");
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ReadResult SceneLoader::loadDataFile(const std::string &filepath)
{
    std::string fileName = osgDB::findDataFile(filepath);

    if (fileName.empty())
        return FILE_NOT_FOUND;

    std::ifstream stream(fileName.c_str(), std::ios::in);

    if (!stream)
        return FILE_NOT_HANDLED;

    std::string ext = osgDB::getLowerCaseFileExtension(fileName);

    if (ext == "ref")
    {
        return loadObjectRef(stream);
    }

    if (ext == "map")
    {
        return loadObjectMap(stream);
    }

    return FILE_NOT_HANDLED;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ReadResult SceneLoader::loadObjectRef(std::istream &stream)
{
    std::string mode = "";

    while (!stream.eof())
    {
        std::string line;
        std::getline(stream, line);

        if (line.empty())
            continue;

        if (line.at(0) == ';')
            continue;

        if (line.at(0) == '[')
        {
            std::string tmp = delete_symbol(line, '[');
            tmp = delete_symbol(tmp, ']');
            mode = delete_symbol(tmp, '\r');
            continue;
        }

        std::string tmp = delete_symbol(line, '\r');
        std::replace(tmp.begin(), tmp.end(), '\t', ' ');

        std::istringstream ss(tmp);

        object_ref_t object;

        ss >> object.name >> object.model_path >> object.texture_path;

        std::replace(object.model_path.begin(), object.model_path.end(), '\\', '/');
        std::replace(object.texture_path.begin(), object.texture_path.end(), '\\', '/');
        object.model_path = routeDir + object.model_path;
        object.texture_path = routeDir + object.texture_path;

        objectRef.insert(std::pair<std::string, object_ref_t>(object.name, object));
    }

    return READ_SUCCESS;
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
ReadResult SceneLoader::loadObjectMap(std::istream &stream)
{
    while (!stream.eof())
    {
        std::string line = "";
        std::getline(stream, line);

        if (line.at(0) == ';')
            continue;

        std::string tmp = delete_symbol(line, '\r');
        tmp = delete_symbol(tmp, ';');
        std::replace(tmp.begin(), tmp.end(), ',', ' ');

        std::istringstream ss(tmp);

        object_map_t object;

        ss >> object.name
           >> object.position.x() >> object.position.y() >> object.position.z()
           >> object.attitude.x() >> object.attitude.y() >> object.attitude.z();

        std::getline(stream, line);

        object.caption = delete_symbol(line, '\r');

        objectMap.insert(std::pair<std::string, object_map_t>(object.name, object));
    }

    return READ_SUCCESS;
}
