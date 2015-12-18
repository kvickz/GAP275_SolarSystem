//Constants.h

//This file is for storing global constants

#ifndef CONSTANTS_H
#define CONSTANTS_H

//***********************************************
//  TYPE DEFINES
//***********************************************
typedef unsigned int ComponentID;
typedef unsigned int ObjectID;

//***********************************************
//  OBJECT IDS
//***********************************************
const ObjectID k_emptyObjectID = 0;
const ObjectID k_planetID = 1;
const ObjectID k_cameraID = 2;
const ObjectID k_pointLightID = 3;
//***********************************************

//***********************************************
//  COMPONENT IDS
//***********************************************
const ComponentID k_transformComponentID = 1;
const ComponentID k_renderComponentID = 2;
const ComponentID k_cameraComponentID = 3;
const ComponentID k_planetComponentID = 4;
const ComponentID k_pointLightComponentID = 5;
//***********************************************

//***********************************************
//  CONSTANT VALUES
//***********************************************
const int k_maxIntValue = 0x7fffffff;
//***********************************************

#endif // !CONSTANTS_H