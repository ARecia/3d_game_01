#include "stdafx.h"
#include "SceneStage2.h"

CSceneStage2::CSceneStage2(CPlayer* pPlayer) : CScene(pPlayer)
{
    BuildObjects();
}

CSceneStage2::~CSceneStage2()
{
}

void CSceneStage2::BuildObjects()
{
    CExplosiveObject::PrepareExplosion();

    float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 200.0f;
    CWallMesh* pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 30);

    m_pWallsObject = new CWallsObject();
    m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
    m_pWallsObject->SetMesh(pWallCubeMesh);
    m_pWallsObject->SetColor(RGB(0, 0, 0));
    m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
    m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
    m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
    m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
    m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
    m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);
    m_pWallsObject->m_xmOOBBPlayerMoveCheck = BoundingOrientedBox(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth * 0.05f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

    CCubeMesh* pCubeMesh = new CCubeMesh(4.0f, 4.0f, 4.0f);

    m_nObjects = ENEMY_COUNT + OBSTACLE_COUNT;
    m_ppObjects = new CGameObject * [m_nObjects];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        CTankObject* pTank = new CTankObject();
        pTank->SetMesh(pCubeMesh);
        pTank->SetColor(RGB(255, 0, 0));
        float fx = -20.0f + (float)(i % 5) * 10.0f;
        float fz = -20.0f + (float)(i / 5) * 20.0f;
        pTank->SetPosition(fx, 0.0f, fz);
        m_ppObjects[i] = pTank;
    }

    for (int i = 0; i < OBSTACLE_COUNT; i++)
    {
        CGameObject* pObstacle = new CGameObject();
        pObstacle->SetMesh(pCubeMesh);
        pObstacle->SetColor(RGB(128, 128, 128));
        float fx = -30.0f + (float)i * 15.0f;
        pObstacle->SetPosition(fx, 0.0f, 30.0f);
        m_ppObjects[ENEMY_COUNT + i] = pObstacle;
    }
}

void CSceneStage2::Animate(float fElapsedTime)
{
    CScene::Animate(fElapsedTime);

    bool bAllDestroyed = true;
    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        CTankObject* pTank = static_cast<CTankObject*>(m_ppObjects[i]);
        if (!pTank->m_bDestroyed) { bAllDestroyed = false; break; }
    }

    if (bAllDestroyed) m_bWin = true;
}

void CSceneStage2::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(255, 0, 0));

    if (m_bWin)
    {
        TextOut(hDCFrameBuffer, FRAMEBUFFER_WIDTH / 2 - 40,
            FRAMEBUFFER_HEIGHT / 2,
            _T("You Win!"), lstrlen(_T("You Win!")));
    }
    else
    {
        TextOut(hDCFrameBuffer, 10, 10, _T("ESC: Menu"), lstrlen(_T("ESC: Menu")));
    }

    CScene::Render(hDCFrameBuffer, pCamera);
}

void CSceneStage2::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
    CScene::OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
    if (nMessageID == WM_KEYDOWN)
    {
        if (wParam == VK_ESCAPE) m_bBackToMenu = true;
        else if (wParam == 'W') m_bWin = true;
    }
}
