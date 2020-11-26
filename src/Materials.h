#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glu.h>

// Setting up material properties
typedef struct materialStruct {
  GLfloat ambient[4];
  GLfloat diffuse[4];
  GLfloat specular[4];
  GLfloat shininess;
} materialStruct;

static materialStruct ironMaterials = {
  { 0.33, 0.33, 0.33, 1.0},
  { 0.57, 0.57, 0.57, 1.0},
  { 0.99, 0.91, 0.81, 1.0},
  27.8 
};

// static materialStruct brassMaterials = {
//   { 0.33, 0.22, 0.03, 1.0},
//   { 0.78, 0.57, 0.11, 1.0},
//   { 0.99, 0.91, 0.81, 1.0},
//   27.8 
// };

// static materialStruct whiteShinyMaterials = {
//   { 1.0, 1.0, 1.0, 1.0},
//   { 1.0, 1.0, 1.0, 1.0},
//   { 1.0, 1.0, 1.0, 1.0},
//   100.0 
// };


// static materialStruct blueShinyMaterials = {
//   { 0.0, 0.0, 0.5, 0.0},
//   { 0.0, 0.0, 1.0, 0.0},
//   { 0.0, 0.0, 1.0, 0.0},
//   100.0 
// };


// static materialStruct greenShinyMaterials = {
//   { 0.0, 0.0, 0.0, 0.0},
//   { 1.0, 1.0, 1.0, 1.0},
//   { 0.0, 0.0, 0.0, 0.0},
//   100.0 
// };


// static materialStruct redShinyMaterials = {
//   { 1.0, 0.0, 0.0, 0.0},
//   { 1.0, 0.0, 0.0, 0.0},
//   { 1.0, 0.0, 0.0, 0.0},
//   100.0 
// };

#endif