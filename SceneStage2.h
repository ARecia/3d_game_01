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
    virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;

    bool IsFinished() const { return m_bWin; }
    bool GoToMenu() const { return m_bBackToMenu; }

protected:
    static const int ENEMY_COUNT = 10;
    static const int OBSTACLE_COUNT = 5;

    bool m_bWin = false;
    bool m_bBackToMenu = false;
};
