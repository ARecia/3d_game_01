#pragma once
#include "Scene.h"

class CSceneStage2 : public CScene
{
public:
    CSceneStage2(CPlayer* pPlayer);
    virtual ~CSceneStage2();

    virtual void BuildObjects() override;
    virtual void Animate(float fElapsedTime) override;
    virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera) override;
};
