//--------------------------------------------
//FileName:MissionStar.h
//--------------------------------------------
//内容：項目ごとの評価で使う星の処理
//--------------------------------------------
//作成者：伊藤颯
//--------------------------------------------
//==更新履歴==
//  2020/12/10   | 作成開始
//--------------------------------------------
#ifndef ___MISSIONSTAR_H_
#define ___MISSIONSTAR_H_

#include "board.h"
#include "Texture.h"

//------定数定義------
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
