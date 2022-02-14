//===== �C���N���[�h�� =====
#include "Model.h"
#include "Shader.h"




Model::Model()
	: m_pFbx(nullptr)
	, m_pBuffer(NULL)
{
	m_pFbx = new FBXPlayer;
}


Model::~Model()
{
	if (m_pFbx != nullptr)
	{
		delete m_pFbx;
	}

	if(m_pBuffer!=NULL)
	{
		delete[] m_pBuffer;
	}
}



HRESULT Model::LoadModel(const char* pFilePath, bool isMirror)
{
	HRESULT hr;
	// ���f���t�@�C���ǂݍ���
	hr = m_pFbx->LoadModel(pFilePath, isMirror);
	if (FAILED(hr))
	{
		return false;
	}

	// ���f���̃��b�V���������_�o�b�t�@�쐬
	int meshNum = m_pFbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; ++i)
	{
		// ���b�V�����Ƃɒ��_�o�b�t�@�쐬
		hr = m_pBuffer[i].CreateVertexBuffer(
			m_pFbx->GetVertexData(i),
			m_pFbx->GetVertexSize(i),
			m_pFbx->GetVertexCount(i)
		);
		if (FAILED(hr))
		{
			//return hr;;
		}

		// �C���f�b�N�X�o�b�t�@�쐬
		hr = m_pBuffer->CreateIndexBuffer(
			m_pFbx->GetIndexData(i),
			m_pFbx->GetIndexCount(i)
		);
		if (FAILED(hr))
		{
			//return hr;
		}

	}

	return hr;
}


ANIME_INDEX Model::LoadAnimation(const char* anime, bool isMirror)
{
	return m_pFbx->LoadAnimation(anime, isMirror);
}


void Model::Draw()
{
	int meshNum = m_pFbx->GetMeshNum();

	for (int i = 0; i < meshNum; i++)
	{
		SHADER->SetTexture(m_pFbx->GetTexture(i));		// �e�N�X�`���̐ݒ�
		SHADER->SetAnimation(m_pFbx->GetAnimeMatrix(i), m_pFbx->GetAnimeMatrixNum(i));
		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}


void Model::PlayAnime(ANIME_INDEX anime, bool loop, float speed)
{
	m_pFbx->Play(anime, loop, speed);
}

void Model::StepAnime(float speed)
{
	m_pFbx->Step(speed);
}


FBXPlayer* Model::GetFBXPlayer()
{
	return m_pFbx;
}