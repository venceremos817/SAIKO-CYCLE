#ifndef __DIRECT_X_H__
#define __DIRECT_X_H__

#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")

#define SAFE_RELEASE(p) if(p){p->Release(); p = NULL;}
#define UNINIT_DELETE(p)	if(p){p->Uninit(); delete p; p=nullptr;}

enum BlendMode
{
	BLEND_ALPHA,
	BLEND_ADD,
	BLEND_MAX
};

enum CullingMode
{
	CULL_DEFAULT,
	CULL_NONE,
	CULL_WIREFRAME,

	CULL_MAX
};

HRESULT InitDX(HWND hWnd, UINT width, UINT height, bool fullscreen);
void UninitDX();
void BeginDrawDX();
void EndDrawDX();

ID3D11Device *GetDevice();
ID3D11DeviceContext *GetContext();

void SetBlendMode(BlendMode blend);
// 特定の面を映らないようにする処理をカリング(Culling)という
void SetCullingMode(CullingMode cullMode);
// Zバッファの有効/無効を切り替える
void EnableZBuffer(bool enable);

#endif // __DIRECT_X_H__