// $Header$
//------------------------------------------------------------------------------
// ConwayGame
//------------------------------------------------------------------------------
// ConwayGame: Conway's Game of Life.
//
// Under the MIT License © 2020.
//
// Created: 2020/03/24
//
/** @file conwayGame.h
 *  @brief This header file contains the basic operations for the game logic.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#ifndef _CONWAYGAME_
#define _CONWAYGAME_

#include <stdio.h>
#include <math.h>
#include <float.h>


//------------------------------------------------------------------------------
// initiate(int n)
//------------------------------------------------------------------------------
/**
 * @brief Creating a matrix of zeros of order n.
 *
 *  @param [in] n Order.
 *  @return Result matrix.
 */
//------------------------------------------------------------------------------ 
int **initiate(int n);

//------------------------------------------------------------------------------
// next_step(int **M, int n)
//------------------------------------------------------------------------------
/**
 * @brief Execute a automata step in the matrix.
 *
 *  @param [in] M Matrix.
 *  @param [in] n Order.
 *  @return Result matrix.
 */
//------------------------------------------------------------------------------ 
int **next_step(int **M, int n);

//------------------------------------------------------------------------------
// change_dead_alive(int **M, int n, int f, int c)
//------------------------------------------------------------------------------
/**
 * @brief Change a element in the matrix between 0 and 1.
 *
 *  @param [in] M Matrix.
 *  @param [in] n Order.
 *  @param [in] f Row.
 *  @param [in] c Column.
 *  @return Result matrix.
 */
//------------------------------------------------------------------------------ 
int **change_dead_alive(int **M, int n, int f, int c);


#endif