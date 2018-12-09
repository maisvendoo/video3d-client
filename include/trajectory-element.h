//------------------------------------------------------------------------------
//
//      Current trajectory element for lineaer approximate of camera motion
//      (c) maisvendoo
//
//------------------------------------------------------------------------------
/*!
 * \file
 * \brief Current trajectory element for lineaer approximate of camera motion
 * \copyright maisvendoo
 * \author maisvendoo
 */

#ifndef     TRAJECTORY_ELEMENT_H
#define     TRAJECTORY_ELEMENT_H

/*!
 * \struct
 * \brief Trajectory element
 */
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct traj_element_t
{
    float   coord_begin;
    float   coord_end;
    float   delta_time;

    traj_element_t()
        : coord_begin(1000.0f)
        , coord_end(250100.0f)
        , delta_time(3600.0f)
    {

    }
};

#endif // TRAJECTORY_ELEMENT_H
