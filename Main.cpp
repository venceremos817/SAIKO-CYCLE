#include "Main.h"
#include "DirectX.h"
#include "Texture.h"
#include "Input.h"
#include "Shader.h"
#include "Defines.h"
#include "FBX/FBXLoader.h"

#include "SceneMgr.h"
#include "Controller.h"
#include "Sound.h"
#include "Player.h"

SceneMgr *g_pSceneMgr;
Controller *g_pController;
HWND g_hWnd;

HRESULT ErrorBox(HRESULT hr, const char* message)
{
	MessageBox(NULL, message, "Error", MB_OK);
	return hr;
}


HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;

	g_hWnd = hWnd;

	//FBXsdkの初期化
	ggfbx::Initialize();

	// DirectX
	hr = InitDX(hWnd, width, height, false);
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to DirectX."); }

	// キーボード
	hr = InitKeyboard();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }

	// シェーダ
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }

	// サウンド
	hr = InitSound();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Sound."); }

	g_pController = new Controller;
	g_pSceneMgr = new SceneMgr;
	g_pSceneMgr->Init();
	if (g_pController->Init() == S_OK)
	{
		Player::SetControler(g_pController);
	}
	else
	{
		Player::SetControler(nullptr);
	}
	srand(timeGetTime());
	return hr;
}


void Uninit()
{
	g_pSceneMgr->Uninit();
	delete g_pSceneMgr;
	delete g_pController;

	UninitSound();
	SHADER->Uninit();
	UninitKeyboard();
	UninitDX();
	ggfbx::Terminate();
}


void Update()
{
	//キーボードの更新
	UpdateKeyboard();
	g_pController->Update();

	g_pSceneMgr->Update();
}


void Draw()
{
	BeginDrawDX();
	//----ここから

	g_pSceneMgr->Draw();
	
	//----ここまで描画

	DrawKeyboard();
	EndDrawDX();
}

HWND GetWHND(void)
{
	return g_hWnd;
}

Controller* GetController()
{
	return g_pController;
}


// EOF