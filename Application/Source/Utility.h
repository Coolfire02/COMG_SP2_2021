#ifndef UTILITY_H
#define UTILITY_H

#include "Vertex.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\file	Utility.h
\author Mr Tang Weng Sheng
\brief
Used to Multiply Mtx44s with Position
*/
/******************************************************************************/

Position operator*(const Mtx44& lhs, const Position& rhs);

#endif