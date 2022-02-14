//--------------------------------------------
//FileName:Text.h
//--------------------------------------------
//���e�F�e�L�X�g�̊��
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/12/05   | �쐬�J�n
//--------------------------------------------
#ifndef ___TEXT_H_
#define ___TEXT_H_

#include "Shader.h"
#include "board.h"

typedef struct
{
	Board *pBoard;
	ID3D11ShaderResourceView *pTextTexture;

	DirectX::XMFLOAT2 m_fTextSize;
	DirectX::XMFLOAT3 m_fTextPos;
}TEXT;


class Text
{
public:
	Text(void);
	~Text(void);

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	int GetSelect(void);
	void SetSelect(int);

public:
	int m_nSelect;
	int m_nOldSelect;

};



#endif // !___TEXT_H_

