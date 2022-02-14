#ifndef __STAGE_H__
#define __STAGE_H__

//===== インクルード部 =====
#include "Field.h"
#include "List.h"
#include "TargetPoint.h"
#include "Obstacle.h"


class Stage
{
public:
	Stage();
	virtual ~Stage();

	HRESULT Init();
	void	Uninit();
	void	Update();
	void	Draw();

	static List<Field> *GetFieldList();

	struct FieldSetting
	{
		Field::E_FIELD_KIND kind;
		DirectX::XMFLOAT3 pos;
	};
	struct FieldSettingFromFile
	{
		Field::E_FIELD_KIND kind;
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
		DirectX::XMFLOAT3 rot;
	};

private:
	void LoadStageFromFile(const char* pFileName);
	void LoadTargetPointFromFile(const char* pFileName, E_RANE rane);
	static List<Field>		*m_pFieldList;
	List<TargetPoint> *m_pTargetPointList[E_RANE::MAX_RANE];
};

#endif // !__STAGE_H__
