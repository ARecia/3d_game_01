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
    bool IsTutorialSelected() const { return m_bTutorialSelected; }
    bool IsLevel1Selected() const { return m_bLevel1Selected; }
    bool IsLevel2Selected() const { return m_bLevel2Selected; }
    bool IsEndSelected() const { return m_bEndSelected; }

private:
    bool m_bStartSelected = false;
    bool m_bTutorialSelected = false;
    bool m_bLevel1Selected = false;
    bool m_bLevel2Selected = false;
    bool m_bEndSelected = false;
};
