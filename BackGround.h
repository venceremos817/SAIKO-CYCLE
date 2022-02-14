#ifndef ___BACKGROUND_H_
#define ___BACKGROUND_H_
#include "Shader.h"
#include "board.h"


class BackGround
{
public:
	Board *m_pBoard;
	ID3D11ShaderResourceView * m_pBGTexture;


public:
	BackGround(void);
	~BackGround(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


};

#endif // !___BACKGROUND_H_
