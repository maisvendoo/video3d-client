#ifndef		LIGHTING_H
#define		LIGHTING_H

#include    <osg/Light>
#include    <osg/LightSource>

void initEnvironmentLight(osg::Group *root, osg::Vec4 color, float power, float psi, float theta);

#endif
