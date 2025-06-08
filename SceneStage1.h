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
    CGameObject* m_pTrack = nullptr;

    static const int TRACK_POINTS = 12;
    XMFLOAT3 m_xmf3Track[TRACK_POINTS];
    float m_fSegmentLengths[TRACK_POINTS - 1];
    int m_nCurrentSegment = 0;
    float m_fSegmentPosition = 0.0f;
    float m_fTrackSpeed = 20.0f;
    bool m_bFinished = false;
    bool m_bBackToMenu = false;
};
