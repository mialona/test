// $Source$
//------------------------------------------------------------------------------
// ConwayGame
//------------------------------------------------------------------------------
// ConwayGame: Conway's Game of Life.
//
// Under the MIT License © 2020.
//
// Created: 2020/03/24
//
/** @file conwayGame.c
 *  @brief Provides basic operations for the game logic.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#include "../include/conwayGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **initiate(int n) {
	int **L = (int **)malloc(n*sizeof(int *));
	for(int i = 0; i < n; i++)
		L[i] = (int *) malloc(n*sizeof(int));
	
    if (L == NULL)
        exit(EXIT_FAILURE);
	
	for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
			L[i][j] = 0;
		}
	}
	
	return L;
}

int **next_step(int **M, int n) {
	int **L = (int **)malloc(n*sizeof(int *));
	for(int i = 0; i < n; i++)
		L[i] = (int *) malloc(n*sizeof(int));
	
    if (L == NULL)
        exit(EXIT_FAILURE);
	
	int sum;
	for(int i = 1; i < n-1; i++) {
        for(int j = 1; j < n-1; j++) {
			sum = M[i-1][j-1]+M[i-1][j]+M[i][j-1]+M[i-1][j+1]+
					M[i+1][j+1]+M[i+1][j]+M[i][j+1]+M[i+1][j-1];
			
			if(M[i][j] == 0) {
				if(sum == 3) {
					L[i][j] = 1;
				}
				else {
					L[i][j] = 0;
				}
			}
			else {
				if(sum < 2 || sum > 3) {
					L[i][j] = 0;
				}
				else {
					L[i][j] = 1;
				}
			}
		}
	}
	
	for(int k = 0; k < n; k++) {
        L[0][k] = 0;
        L[n-1][k] = 0;
        L[k][0] = 0;
        L[k][n-1] = 0;
	}
	
	return L;
}

int **change_dead_alive(int **M, int n, int f, int c) {
	if(f > 0 && f < n && c > 0 && c < n) {
		M[f][c] = !M[f][c];
	}
	
	return M;
}