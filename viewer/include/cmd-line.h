//------------------------------------------------------------------------------
//
//      Command line options
//      (c) maisvendoo, 04/12/2018
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief Command line options
 * \copyright maisvendoo
 * \author maisvendoo
 * \date 04/12/2018
 */

#ifndef     CMD_LINE_H
#define     CMD_LINE_H

#include    <string>

/*!
 * \struct
 * \brief
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct cmd_line_t
{
    std::string     routeDir;

    cmd_line_t()
        : routeDir("")
    {

    }
};

#endif // CMD_LINE_H
