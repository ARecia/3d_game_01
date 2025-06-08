#pragma once

#include "Scene.h"

class CSceneMenu : public CScene
{
public:
    CSceneMenu(CPlayer* pPlayer);
    virtual ~CSceneMenu();

    virtual void BuildObjects() override;
    virtual void Animate(float fElapsedTime) override;
    virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera) override;
    virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;

    bool IsStartSelected() const { return m_bStartSelected; }

private:
    bool m_bStartSelected = false;
};
