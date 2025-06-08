#pragma once

#include "Scene.h"

class CSceneMenu : public CScene
{
public:
    enum MENU_ITEMS { MENU_TUTORIAL = 0, MENU_LEVEL1, MENU_LEVEL2, MENU_START, MENU_END, MENU_COUNT };

    CSceneMenu(CPlayer* pPlayer);
    virtual ~CSceneMenu();

    virtual void BuildObjects() override;
    virtual void Animate(float fElapsedTime) override;
    virtual void Render(HDC hDCFrameBuffer, CCamera* pCamera) override;
    virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam) override;

    bool IsStartSelected() const { return m_bStartSelected; }

private:
    bool  m_bStartSelected = false;
    RECT  m_rcMenuItems[MENU_COUNT];
    int   m_nCurrentSelection = MENU_TUTORIAL;
};
