#ifndef     SETTINGS_H
#define     SETTINGS_H

#include    <string>

struct settings_t
{
    std::string     route_dir;
    std::string     host_addr;
    int             port;
    int             width;
    int             height;
    bool            fullscreen;
    bool            localmode;

    settings_t()
        : route_dir("")
        , host_addr("127.0.0.1")
        , port(1992)
        , width(1366)
        , height(768)
        , fullscreen(false)
        , localmode(false)
    {

    }
};

#endif // SETTINGS_H
