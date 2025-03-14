// $Source$
//------------------------------------------------------------------------------
// FileManager
//------------------------------------------------------------------------------
// ConwayGame: Conway's Game of Life.
//
// Under the MIT License © 2020.
//
// Created: 2020/03/24
//
/** @file fileManager.c
 *  @brief File manager operations.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#include "fileManager.h"
#include "conwayGame.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int file_to_matrix(LPCTSTR pszFileName, int ***M, int n) {
	int **L = initiate(n);
	
    HANDLE hFile; 
    int success = 0; 

    hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL); 
    if(hFile != INVALID_HANDLE_VALUE) { 
        DWORD dwFileSize; 

        dwFileSize = GetFileSize (hFile, NULL); 
        if(dwFileSize != 0xFFFFFFFF) { 
            char* fileText; 

            fileText = GlobalAlloc(GPTR, dwFileSize); 
            if(fileText != NULL) { 
                DWORD dwRead; 

                if(ReadFile(hFile, fileText, dwFileSize, &dwRead, NULL)) {
					int nCells = 0;
					char *cells[n*n];
					
					char *cell = strtok(fileText, ";");
					while(cell != NULL) {
						cells[nCells] = cell;
						nCells++;
						
						cell = strtok(NULL, ";");
					}
					
					for(int i = 0; i < nCells; i++) {
						char *coorY, *coorX;
						if((coorY = strtok(cells[i], ","))) {
							if((coorX = strtok(NULL, ","))) {
								L = change_dead_alive(L,n,atoi(coorY),atoi(coorX));
							}
							else {
								return success;
							}
						}
						else {
							return success;
						}
					}
					
					*M = L;
					success = TRUE;
                } 
                GlobalFree(fileText);
            } 
        } 
        CloseHandle (hFile); 
    } 
    return success; 
}

int matrix_to_file(LPCTSTR pszFileName, int **M, int n) {
	HANDLE hFile; 
    int success = 0;
	
	int coors[(n-2)*(n-2)], nCoors = 0;
	for(int i = 1; i < n-1; i++) {
		for(int j = 1; j < n-1; j++) {
			if(M[i][j] == 1) {
				coors[nCoors*2] = i;
				coors[nCoors*2+1] = j;
				
				nCoors++;
			}
		}
	}
	
	if(nCoors > 0) {
		int nMatrixText = 0;
		char* matrixText = malloc(nCoors*6-1);
		char str1[1], str2[2];
		
		if(coors[0] < 10) {
			sprintf(str1, "%d", coors[0]);
			strcpy(matrixText, str1);
			nMatrixText++;
		}
		else {
			sprintf(str2, "%d", coors[0]);
			strcpy(matrixText, str2);
			nMatrixText = nMatrixText + 2;
		}
		strcat(matrixText, ",");
		nMatrixText++;
		if(coors[1] < 10) {
			sprintf(str1, "%d", coors[1]);
			strcat(matrixText, str1);
			nMatrixText++;
		}
		else {
			sprintf(str2, "%d", coors[1]);
			strcat(matrixText, str2);
			nMatrixText = nMatrixText + 2;
		}
		
		for(int i = 1; i < nCoors; i++) {
			strcat(matrixText, ";");
			nMatrixText++;
			if(coors[i*2] < 10) {
				sprintf(str1, "%d", coors[i*2]);
				strcat(matrixText, str1);
				nMatrixText++;
			}
			else {
				sprintf(str2, "%d", coors[i*2]);
				strcat(matrixText, str2);
				nMatrixText = nMatrixText + 2;
			}
			strcat(matrixText, ",");
			nMatrixText++;
			if(coors[i*2+1] < 10) {
				sprintf(str1, "%d", coors[i*2+1]);
				strcat(matrixText, str1);
				nMatrixText++;
			}
			else {
				sprintf(str2, "%d", coors[i*2+1]);
				strcat(matrixText, str2);
				nMatrixText = nMatrixText + 2;
			}
		}

		hFile = CreateFile(pszFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); 
		if(hFile != INVALID_HANDLE_VALUE) { 
			DWORD dwFileSize; 
 
			if(nMatrixText > 0) {
				if(matrixText != NULL){
					DWORD dwWritten; 

					if (WriteFile (hFile, matrixText, nMatrixText, &dwWritten, NULL)) {
						success = TRUE;
					}
				}
			} 
			CloseHandle(hFile); 
		} 
		
		GlobalFree(matrixText);
	}
	
    return success; 
}