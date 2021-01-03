#ifndef __SC18J3J_MATERIALS__
#define __SC18J3J_MATERIALS__
#include "Shapes.h"

static materialStruct woodMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.6, 0.5, 0.4, 1.0},
    { 0.0, 0.0, 0.0, 1.0},
    20.0
};

static materialStruct whitePaintMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.5, 0.5, 0.5, 1.0},
    { 0.5, 0.5, 0.5, 1.0},
    50.0
};

static materialStruct blackPlasticMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.1, 0.1, 0.1, 1.0},
    { 0.6, 0.6, 0.6, 1.0},
    50.0
};

static materialStruct glassMaterials = {
    { 0.0, 0.0, 0.0, 1.0},
    { 0.6, 0.7, 0.8, 0.2},
    { 0.6, 0.7, 0.8, 0.2},
    100.0
};

static materialStruct warmLightMaterials = {
    { 1.0, 1.0, 0, 1.0},
    { 1.0, 1.0, 0, 0.9},
    { 1.0, 1.0, 0, 1.0},
    100.0
};

static materialStruct backgroundMaterials = {
    { 1, 1, 1, 1.0},
    { 0, 0, 0, 1.0},
    { 0, 0, 0, 1.0},
    100.0
};

#endif