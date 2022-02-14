#ifndef __MAIN_H__
#define __MAIN_H__

#include <Windows.h>
#include "Controller.h"

HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update();
void Draw();

HWND GetWHND(void);
Controller* GetController();

#endif // __MAIN_H__