//////////////////////////////////////////////////////////////////////////////
//
//  --- Angel.h ---
//
//   The main header file for all examples from Angel 6th Edition
//
//   Modified by David M. Reed to make it simpler
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

//----------------------------------------------------------------------------
//
// --- Include system headers ---
//

#include <GL/glew.h>

#include <cmath>
#include <iostream>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET( offset )   ((GLvoid*) (offset))

//----------------------------------------------------------------------------
//
//  --- Include our class libraries and constants ---
//

const GLfloat  DivideByZeroTolerance = GLfloat(1.0e-07);

//  Degrees-to-radians constant
const GLfloat  DegreesToRadians = GLfloat(M_PI / 180.0);


#include "vec.h"
#include "mat.h"

