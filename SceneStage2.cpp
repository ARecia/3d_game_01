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
    // ���� ������Ʈ�� ���߿� �߰�
}

void CSceneStage2::Animate(float fElapsedTime)
{
    // �ʿ� �� �ִϸ��̼� �߰�
}

void CSceneStage2::Render(HDC hDCFrameBuffer, CCamera* pCamera)
{
    SetBkMode(hDCFrameBuffer, TRANSPARENT);
    SetTextColor(hDCFrameBuffer, RGB(255, 0, 0));

    TextOut(hDCFrameBuffer, FRAMEBUFFER_WIDTH / 2 - 100,
        FRAMEBUFFER_HEIGHT / 2,
        _T("Level-2 Scene Loaded!"), lstrlen(_T("Level-2 Scene Loaded!")));
}
