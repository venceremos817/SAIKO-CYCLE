//--------------------------------------------
//FileName:MissionStar.h
//--------------------------------------------
//���e�F���ڂ��Ƃ̕]���Ŏg�����̏���
//--------------------------------------------
//�쐬�ҁF�ɓ��D
//--------------------------------------------
//==�X�V����==
//  2020/12/10   | �쐬�J�n
//--------------------------------------------
#ifndef ___MISSIONSTAR_H_
#define ___MISSIONSTAR_H_

#include "board.h"
#include "Texture.h"

//------�萔��`------
#define STAR_NUM (3)


typedef struct
{
	Board *p_Star;
	bool m_bStarflg;
	DirectX::XMFLOAT2 fStarSize;

}STAR;

typedef struct
{
	ID3D11ShaderResourceView *p_SuccessStarTex;
	ID3D11ShaderResourceView *p_FailureStarTex;
}STARTEX;


class MissionStar
{
public:
	MissionStar(void);
	~MissionStar(void);

	void Init(void);
	void Uninit(void);
	void Draw(void);

	void SetFlg(int, bool);


private:
	STAR m_pStar[STAR_NUM];
	STARTEX m_pStarTex;
};



#endif // !___MISSIONSTAR_H_
