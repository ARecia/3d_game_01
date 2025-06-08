#pragma once

#include "Scene.h"

class CSceneTitle : public CScene
{
public:
    CSceneTitle(CPlayer* pPlayer);
    virtual ~CSceneTitle();

    virtual void BuildObjects() override;
    virtual void Animate(float fElapsedTime) override;
    virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera) override;
    virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;

private:
    float m_fRotationAngle = 0.0f;
    CExplosiveObject* m_pExplosive = nullptr;
    bool m_bExploded = false;
    float m_fExplosionTime = 0.0f;
    bool m_bSceneFinished = false;

public:
    bool IsFinished() const { return m_bSceneFinished; }
};
