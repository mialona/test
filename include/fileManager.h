// $Header$
//------------------------------------------------------------------------------
// FileManager
//------------------------------------------------------------------------------
// ConwayGame: Conway's Game of Life.
//
// Under the MIT License © 2020.
//
// Created: 2020/03/24
//
/** @file fileManager.h
 *  @brief This header file contains the file manager operations.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#ifndef _FILEMANAGER_
#define _FILEMANAGER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


//------------------------------------------------------------------------------
// file_to_matrix(LPCTSTR pszFileName, int ***M, int n)
//------------------------------------------------------------------------------
/**
 * @brief Read from file to matrix.
 *
 *  @param [in] pszFileName Name of the file.
 *  @param [out] M Matrix.
 *  @param [in] n Order.
 *  @return Success.
 */
//------------------------------------------------------------------------------ 
int file_to_matrix(LPCTSTR pszFileName, int ***M, int n);

//------------------------------------------------------------------------------
// matrix_to_file(LPCTSTR pszFileName, int **M, int n)
//------------------------------------------------------------------------------
/**
 * @brief Write from matrix to file.
 *
 *  @param [in] pszFileName Name of the file.
 *  @param [in] M Matrix.
 *  @param [in] n Order.
 *  @return Success.
 */
//------------------------------------------------------------------------------ 
int matrix_to_file(LPCTSTR pszFileName, int **M, int n);


#endif