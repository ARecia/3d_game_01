#pragma once
#include "Scene.h"
#include "Player.h"

class CSceneStage1 : public CScene
{
public:
    CSceneStage1(CPlayer* pPlayer);
    virtual ~CSceneStage1();

    virtual void BuildObjects() override;
    virtual void Animate(float fElapsedTime) override;
    virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera) override;
    virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;

    bool IsFinished() const { return m_bFinished; }
    bool GoToMenu() const { return m_bBackToMenu; }

private:
    CAirplanePlayer* m_pAirplane = nullptr;
    bool m_bFinished = false;
    bool m_bBackToMenu = false;
};
