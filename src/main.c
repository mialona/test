// $Source$
//------------------------------------------------------------------------------
// Main
//------------------------------------------------------------------------------
// ConwayGame: Conway's Game of Life.
//
// Under the MIT License © 2020.
//
// Created: 2020/03/24
//
/** @file main.c
 *  @brief Main program operations.
 *
 *  @author Miguel Alonso Angulo.
 *  @bug No known bugs.
 */
//------------------------------------------------------------------------------

#include "../include/main.h"
#include "../include/conwayGame.h"
#include "../include/fileManager.h"

#include <windows.h>
#include <time.h>

const char g_szClassName[] = "conwayGame";
HMENU hMenu;
HICON hIcon;
int running = 0;
int **game;


// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
		case WM_CREATE: {
				// Menu
				hMenu = CreateMenu();
				
				HMENU hGameMenu = CreatePopupMenu();
				AppendMenu(hGameMenu, MF_STRING, ID_NEW, "New");
				AppendMenu(hGameMenu, MF_STRING, ID_OPEN, "Open");
				AppendMenu(hGameMenu, MF_STRING, ID_SAVE, "Save");
				AppendMenu(hGameMenu, MF_STRING, ID_EXIT, "Exit");
				AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hGameMenu, "Game");
				
				AppendMenu(hMenu, MF_STRING, ID_PLAY, "Play");
				AppendMenu(hMenu, MF_STRING, ID_PAUSE, "Pause");
				
				HMENU hHelpMenu = CreatePopupMenu();
				AppendMenu(hHelpMenu, MF_STRING, ID_HELP, "Quick help");
				AppendMenu(hHelpMenu, MF_STRING, ID_ABOUT, "About...");
				AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hHelpMenu, "Help");
				SetMenu(hwnd, hMenu);
				
				EnableMenuItem(hMenu,2,MF_BYPOSITION|MF_GRAYED);
				
				// Icon
				hIcon = LoadImage(NULL, "resources/icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
				if(hIcon) {
					SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
				}
				else {
					MessageBox(hwnd, "Could not load large icon", "Error", MB_ICONERROR | MB_OK);
				}
			}
			break;
		case WM_PAINT: {
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd,&ps);
					SelectObject(hdc, GetStockObject(DC_PEN));
					SelectObject(hdc, GetStockObject(DC_BRUSH));
					SetDCPenColor(hdc, RGB(200,200,200));
					
					// Gray rectangles
					SetDCBrushColor(hdc, RGB(200,200,200));
					Rectangle(hdc,0,0,10,TAM*10);
					Rectangle(hdc,0,0,TAM*10,10);
					Rectangle(hdc,(TAM-1)*10,0,TAM*10,TAM*10);
					Rectangle(hdc,0,(TAM-1)*10,TAM*10,TAM*10);
					
					// Black rectangles
					SetDCBrushColor(hdc, RGB(0,0,0));
					for(int i = 1; i < TAM-1; i++) {
						for(int j = 1; j < TAM-1; j++) {
							if(game[j][i] == 1) {
								Rectangle(hdc,i*10,j*10,(i+1)*10,(j+1)*10);
							}
						}
					}
				EndPaint(hwnd, &ps);
				ReleaseDC(hwnd, hdc);
			}
			break;
		case WM_COMMAND:
            switch(LOWORD(wParam)){
				// New
				case ID_NEW:{
						running = 0;
						
						EnableMenuItem(hMenu,2,MF_BYPOSITION|MF_GRAYED);
						EnableMenuItem(hMenu,1,MF_BYPOSITION|MF_ENABLED);
						DrawMenuBar(hwnd);
						
						game = initiate(TAM);
			
						InvalidateRect(hwnd, NULL, TRUE);
						UpdateWindow(hwnd);
					}
					break;
				// Open
                case ID_OPEN:{
						OPENFILENAME ofn;
						char szFileName[MAX_PATH] = "";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = "Conway's Game of Life Files (*.cgof)\0*.cgof\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
						ofn.lpstrDefExt = "cgof";

						if(GetOpenFileName(&ofn))
						{
							running = 0;
							
							EnableMenuItem(hMenu,2,MF_BYPOSITION|MF_GRAYED);
							EnableMenuItem(hMenu,1,MF_BYPOSITION|MF_ENABLED);
							DrawMenuBar(hwnd);
							
							if(file_to_matrix(szFileName, &game, TAM)) {
								InvalidateRect(hwnd, NULL, TRUE);
								UpdateWindow(hwnd);
							}
							else {
								MessageBox(hwnd, "Could not read file", "Error", MB_ICONERROR | MB_OK);
							}
						}
						else {
							MessageBox(hwnd, "Could not find file", "Error", MB_ICONERROR | MB_OK);
						}
					}
					break;
				// Save
                case ID_SAVE:{
						OPENFILENAME ofn;
						char szFileName[MAX_PATH] = "";

						ZeroMemory(&ofn, sizeof(ofn));

						ofn.lStructSize = sizeof(ofn);
						ofn.hwndOwner = hwnd;
						ofn.lpstrFilter = "Conway's Game of Life Files (*.cgof)\0*.cgof\0All Files (*.*)\0*.*\0";
						ofn.lpstrFile = szFileName;
						ofn.nMaxFile = MAX_PATH;
						ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
						ofn.lpstrDefExt = "cgof";

						if(GetSaveFileName(&ofn))
						{
							running = 0;
							
							EnableMenuItem(hMenu,2,MF_BYPOSITION|MF_GRAYED);
							EnableMenuItem(hMenu,1,MF_BYPOSITION|MF_ENABLED);
							DrawMenuBar(hwnd);
							
							if(matrix_to_file(szFileName, game, TAM)) {
								InvalidateRect(hwnd, NULL, TRUE);
								UpdateWindow(hwnd);
							}
							else {
								MessageBox(hwnd, "Could not write file", "Error", MB_ICONERROR | MB_OK);
							}
						}
						else {
							MessageBox(hwnd, "Could not find file", "Error", MB_ICONERROR | MB_OK);
						}
					}
					break;
				// Exit
                case ID_EXIT:{
						PostMessage(hwnd, WM_CLOSE, 0, 0);
					}
					break;
				// Play
                case ID_PLAY:{
						running = 1;
						
						EnableMenuItem(hMenu,1,MF_BYPOSITION|MF_GRAYED);
						EnableMenuItem(hMenu,2,MF_BYPOSITION|MF_ENABLED);
						DrawMenuBar(hwnd);
					}
					break;
				// Pause
				case ID_PAUSE:{
						running = 0;
						
						EnableMenuItem(hMenu,2,MF_BYPOSITION|MF_GRAYED);
						EnableMenuItem(hMenu,1,MF_BYPOSITION|MF_ENABLED);
						DrawMenuBar(hwnd);
					}
					break;
				// Quick help
				case ID_HELP:{
						MessageBox(NULL,
							"Use:\n\n - Play: To start the simulation (steps).\n\n - Pause: To stop the simulation.\n\n - Left mouse click: To toggle a cell between 'alive' or 'dead'."
							,"Quick help",MB_OK);
					}
					break;
				// About
				case ID_ABOUT:{
						MessageBox(NULL,
							"Conway's Game of Life v1.1            (32-bits)\n\n\nUnder the MIT License.\nCopyright (c) 2020 by Melmal"
							,"About...",MB_OK);
					}
					break;
            }
			break;
		case WM_LBUTTONDOWN:{
				if(running == 0) {
					game = change_dead_alive(game,TAM,(int)HIWORD(lParam)/10,(int)LOWORD(lParam)/10);
					
					InvalidateRect(hwnd, NULL, TRUE);
					UpdateWindow(hwnd);
				}
			}
			break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
			break;
        case WM_DESTROY:
            PostQuitMessage(0);
			break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed", "Error",
            MB_ICONERROR | MB_OK);
        return 0;
    }

    // Creating the Window
    hwnd = CreateWindowEx(
        0,
        g_szClassName,
        "Conway's Game of Life",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 616, 660,
        NULL, NULL, hInstance, NULL);
	
	SetWindowLong(hwnd,GWL_STYLE,GetWindowLong(hwnd,GWL_STYLE)&~(WS_MAXIMIZEBOX));

    if(hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed", "Error",
            MB_ICONERROR | MB_OK);
        return 0;
    }
	
	// Initiate game
	game = initiate(TAM);
	
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

	
    // Message Loop
	clock_t t_ini = clock();
    while(1) {
		printf("hi");
		if(running == 1 && (double)(clock() - t_ini) / CLOCKS_PER_SEC > 0.25) {
			game = next_step(game,TAM);
			
			InvalidateRect(hwnd, NULL, TRUE);
			UpdateWindow(hwnd);
			
			t_ini = clock();
		}
		
		if(PeekMessageA(&Msg, NULL, 0, 0, PM_REMOVE) > 0) {
			if((&Msg)->message == WM_QUIT) {
				break;
			}
			
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
    }
    return Msg.wParam;
}