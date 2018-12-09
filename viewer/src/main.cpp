#include    "main.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    RouteViewer viewer(argc, argv);

    if (viewer.isReady())
        return viewer.run();

    return 0;
}


