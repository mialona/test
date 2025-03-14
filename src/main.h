// $Header$
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
// ConwayGame: Conway's Game of Life.
//
// Under the MIT License © 2020.
//
// Created: 2020/03/24
//
/** @file main.h
 *  @brief This header file contains the main program operations.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#ifndef _MAIN_
#define _MAIN_

#include <windows.h>


#define TAM 60
#define ID_NEW 3000
#define ID_OPEN 3001
#define ID_SAVE 3002
#define ID_EXIT 3003
#define ID_PLAY 3004
#define ID_PAUSE 3005
#define ID_HELP 3006
#define ID_ABOUT 3007


//------------------------------------------------------------------------------
// WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//------------------------------------------------------------------------------
/**
 * @brief Processing method of sent messages.
 *
 *  @param [in] hwnd Handle of the window to which the message is applied.
 *  @param [in] msg Messaje id.
 *  @param [in] wParam W-parameter.
 *  @param [in] lParam L-parameter.
 *  @return Result.
 */
//------------------------------------------------------------------------------ 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//------------------------------------------------------------------------------
// WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//------------------------------------------------------------------------------
/**
 * @brief Application entry point.
 *
 *  @param [in] hInstance Handle to the current instance of the application.
 *  @param [in] hPrevInstance Handle to the previous instance of the application.
 *  @param [in] lpCmdLine The command line for the application, excluding the program name.
 *  @param [in] nCmdShow Controls how the window is to be shown.
 *  @return If the function succeeds it should return the exit value contained in that message's wParam parameter.
 *  If the function terminates before entering the message loop, it should return zero.
 */
//------------------------------------------------------------------------------ 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);


#endif