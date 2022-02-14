#ifndef ___SCENE_H_
#define ___SCENE_H_
#include <iostream>

#define BACKGROUND_HEIGHT (5.78f)
#define BACKGROUND_WIDTH (10.27f)

typedef enum
{
	SCENE_NONE,

	SCENE_TITLE,
	SCENE_CUSTAM,
	SCENE_STAGESELECT,
	SCENE_GAME,
	SCENE_RESULT,


	SCENE_MAX
}E_SCENE_KIND;


class Scene 
{
public:
	virtual void Init(void);
	virtual void Uninit(void);
	virtual E_SCENE_KIND Update(void);
	virtual void Draw(void);

	virtual float SetScore(void);
	virtual void GetScore(float);

	virtual float SetTime(void);
	virtual void GetTime(float);


	float m_fScore;
	float m_fTime;
};



#endif // !___SCENE_H_
