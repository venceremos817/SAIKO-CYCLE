#ifndef __MODEL_H__
#define __MODEL_H__

//===== インクルード部 =====
#include "DrawBuffer.h"
#include "FBX/FBXPlayer.h"


class Model
{
public:
	Model();
	~Model();

	HRESULT LoadModel(const char* pFilePath, bool isMirror = true);
	ANIME_INDEX LoadAnimation(const char* anime, bool isMirror = true);

	void Draw();

	// アニメーション
	void PlayAnime(ANIME_INDEX anime, bool loop = false, float speed = (1.0F));
	void StepAnime(float speed = 1.0f);

	FBXPlayer* GetFBXPlayer();

private:
	// ゲームのキャラクターは複数のパーツで成り立っている。そのパーツ一つ一つをメッシュと呼ぶ。
	// 基本的に一つのメッシュで一つの頂点バッファを持つ。モデルごとにメッシュの数が異なるため、頂点バッファを動的に確保する
	DrawBuffer*	m_pBuffer;

	FBXPlayer*	m_pFbx;		// FBXファイル操作クラス

	// アニメーション
};

#endif // !__MODEL_H__
