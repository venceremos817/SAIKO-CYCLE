#ifndef __MODEL_H__
#define __MODEL_H__

//===== �C���N���[�h�� =====
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

	// �A�j���[�V����
	void PlayAnime(ANIME_INDEX anime, bool loop = false, float speed = (1.0F));
	void StepAnime(float speed = 1.0f);

	FBXPlayer* GetFBXPlayer();

private:
	// �Q�[���̃L�����N�^�[�͕����̃p�[�c�Ő��藧���Ă���B���̃p�[�c�������b�V���ƌĂԁB
	// ��{�I�Ɉ�̃��b�V���ň�̒��_�o�b�t�@�����B���f�����ƂɃ��b�V���̐����قȂ邽�߁A���_�o�b�t�@�𓮓I�Ɋm�ۂ���
	DrawBuffer*	m_pBuffer;

	FBXPlayer*	m_pFbx;		// FBX�t�@�C������N���X

	// �A�j���[�V����
};

#endif // !__MODEL_H__
