#include "stdafx.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "Mesh.h"
#include "SceneMenu.h"

// SceneStage1.cpp
CSceneStage1::CSceneStage1(CPlayer* pPlayer) : CScene(pPlayer)
{
    BuildObjects();
}


CSceneStage1::~CSceneStage1()
{
    if (m_pAirplane) delete m_pAirplane;
    if (m_pTrack) delete m_pTrack;
}

void CSceneStage1::BuildObjects()
{
    for (int i = 0; i < TRACK_POINTS; i++)
    {
        float t = (float)i / (float)(TRACK_POINTS - 1);
        float z = 50.0f * i;
        float x = 10.0f * sinf(t * XM_PI * 2.0f);
        float y = 5.0f * cosf(t * XM_PI * 4.0f);
        m_xmf3Track[i] = XMFLOAT3(x, y, z);
    }
    for (int i = 0; i < TRACK_POINTS - 1; i++)
    {
        XMVECTOR v0 = XMLoadFloat3(&m_xmf3Track[i]);
        XMVECTOR v1 = XMLoadFloat3(&m_xmf3Track[i + 1]);
        m_fSegmentLengths[i] = XMVectorGetX(XMVector3Length(XMVectorSubtract(v1, v0)));
    }

    m_pTrack = new CGameObject();
    CRollerCoasterMesh* pTrackMesh = new CRollerCoasterMesh(m_xmf3Track, TRACK_POINTS, 4.0f);
    m_pTrack->SetMesh(pTrackMesh);
    m_pTrack->SetColor(RGB(128, 128, 128));

    m_pAirplane->SetPosition(m_xmf3Track[0].x, m_xmf3Track[0].y, m_xmf3Track[0].z);

        OutputDebugString(L"[ERROR] m_pPlayer Ǵ GetCamera() nullԴϴ!\n");
    m_nObjects = 2;
    m_ppObjects[0] = m_pTrack;
    m_ppObjects[1] = m_pAirplane;

    if (m_pAirplane && !m_bFinished)
        float move = m_fTrackSpeed * fElapsedTime;
        while (move > 0.0f && !m_bFinished)
            float remain = m_fSegmentLengths[m_nCurrentSegment] - m_fSegmentPosition;
            if (move < remain)
            {
                m_fSegmentPosition += move;
                move = 0.0f;
            }
            else
            {
                move -= remain;
                m_nCurrentSegment++;
                m_fSegmentPosition = 0.0f;
                if (m_nCurrentSegment >= TRACK_POINTS - 1)
                {
                    m_bFinished = true;
                    m_nCurrentSegment = TRACK_POINTS - 2;
                    m_fSegmentPosition = m_fSegmentLengths[m_nCurrentSegment];
                }
            }

        XMFLOAT3 p0 = m_xmf3Track[m_nCurrentSegment];
        XMFLOAT3 p1 = m_xmf3Track[m_nCurrentSegment + 1];
        float t = (m_fSegmentLengths[m_nCurrentSegment] <= 0.0f) ? 0.0f : (m_fSegmentPosition / m_fSegmentLengths[m_nCurrentSegment]);
        XMFLOAT3 dir = Vector3::Subtract(p1, p0);
        XMFLOAT3 pos = Vector3::Add(p0, Vector3::ScalarProduct(dir, t, false));

        m_pAirplane->SetPosition(pos.x, pos.y, pos.z);
        XMFLOAT3 target = Vector3::Add(pos, dir);
        m_pAirplane->LookAt(target, XMFLOAT3(0.0f, 1.0f, 0.0f));
        m_pAirplane->Animate(fElapsedTime);




    m_ppObjects = new CGameObject * [m_nObjects];
    m_ppObjects[0] = m_pAirplane;

    OutputDebugString(L"[DEBUG] CSceneStage1::BuildObjects 완료됨\n");
}



void CSceneStage1::Animate(float fElapsedTime)
{
    if (m_pAirplane)
    {
        m_pAirplane->Move(0.0f, 0.0f, 20.0f * fElapsedTime);  // 직진
        m_pAirplane->Animate(fElapsedTime);

        // 도착 조건
        if (m_pAirplane->GetPosition().z >= 500.0f)
        {
            m_bFinished = true;
        }
    }

    CScene::Animate(fElapsedTime);
}

void CSceneStage1::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(0, 0, 255));

    TextOut(hDCFrameBuffer, 10, 10, _T("Press N: Next Level | ESC: Menu"), 34);

    CScene::Render(hDCFrameBuffer, pCamera);
}

void CSceneStage1::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    if (nMessageID == WM_KEYDOWN)
    {
        if (wParam == 'N') m_bFinished = true;
        else if (wParam == VK_ESCAPE) m_bBackToMenu = true;
    }
}
