﻿//-----------------------------------------------------------------------------
// File: CGameFramework.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameFramework.h"
#include "SceneTitle.h"
#include "SceneMenu.h"  // 이후 메뉴 씬도 만들어야 함
#include "SceneStage1.h"
#include "SceneStage2.h"


void CGameFramework::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	::srand(timeGetTime());

	m_hInstance = hInstance;
	m_hWnd = hMainWnd;

	BuildFrameBuffer(); 

	BuildObjects(); 

	_tcscpy_s(m_pszFrameRate, _T("LabProject ("));
}

void CGameFramework::OnDestroy()
{
	ReleaseObjects();

	if (m_hBitmapFrameBuffer) ::DeleteObject(m_hBitmapFrameBuffer);
	if (m_hDCFrameBuffer) ::DeleteDC(m_hDCFrameBuffer);
}

void CGameFramework::BuildFrameBuffer()
{
	::GetClientRect(m_hWnd, &m_rcClient);

	HDC hDC = ::GetDC(m_hWnd);

    m_hDCFrameBuffer = ::CreateCompatibleDC(hDC);
	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top);
    ::SelectObject(m_hDCFrameBuffer, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
    ::SetBkMode(m_hDCFrameBuffer, TRANSPARENT);
}

void CGameFramework::ClearFrameBuffer(DWORD dwColor)
{
	HPEN hPen = ::CreatePen(PS_SOLID, 0, dwColor);
	HPEN hOldPen = (HPEN)::SelectObject(m_hDCFrameBuffer, hPen);
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hDCFrameBuffer, hBrush);
	::Rectangle(m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);
	::SelectObject(m_hDCFrameBuffer, hOldBrush);
	::SelectObject(m_hDCFrameBuffer, hOldPen);
	::DeleteObject(hPen);
	::DeleteObject(hBrush);
}

void CGameFramework::PresentFrameBuffer()
{    
    HDC hDC = ::GetDC(m_hWnd);
    ::BitBlt(hDC, m_rcClient.left, m_rcClient.top, m_rcClient.right - m_rcClient.left, m_rcClient.bottom - m_rcClient.top, m_hDCFrameBuffer, m_rcClient.left, m_rcClient.top, SRCCOPY);
    ::ReleaseDC(m_hWnd, hDC);
}

void CGameFramework::BuildObjects()
{
	CCamera* pCamera = new CCamera();
	pCamera->SetViewport(0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
	pCamera->GeneratePerspectiveProjectionMatrix(1.01f, 500.0f, 60.0f);
	pCamera->SetFOVAngle(60.0f);

	pCamera->GenerateOrthographicProjectionMatrix(1.01f, 50.0f, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);

	CAirplaneMesh* pAirplaneMesh = new CAirplaneMesh(6.0f, 6.0f, 1.0f);

	m_pPlayer = new CAirplanePlayer();
	m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
	m_pPlayer->SetMesh(pAirplaneMesh);
	m_pPlayer->SetColor(RGB(0, 0, 255));
	m_pPlayer->SetCamera(pCamera);
	m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));

	m_pScene = new CSceneTitle(m_pPlayer);
	m_pScene->BuildObjects();
}

void CGameFramework::ReleaseObjects()
{
	if (m_pScene)
	{
		m_pScene->ReleaseObjects();
		delete m_pScene;
	}

	if (m_pPlayer) delete m_pPlayer;
}

void CGameFramework::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{
	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		::SetCapture(hWnd);
		::GetCursorPos(&m_ptOldCursorPos);
		if (nMessageID == WM_RBUTTONDOWN) m_pLockedObject = m_pScene->PickObjectPointedByCursor(LOWORD(lParam), HIWORD(lParam), m_pPlayer->m_pCamera);
		break;
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		::ReleaseCapture();
		break;
	case WM_MOUSEMOVE:
		break;
	default:
		break;
	}
}

void CGameFramework::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (m_pScene) m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);

	switch (nMessageID)
	{
       case WM_KEYDOWN:
               switch (wParam)
               {
               case VK_ESCAPE:
                       m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
                       break;
               case VK_RETURN:
                       break;
               case VK_CONTROL:
               {
                       CAirplanePlayer* pAir = dynamic_cast<CAirplanePlayer*>(m_pPlayer);
                       if (pAir) pAir->FireBullet(m_pLockedObject);
                       m_pLockedObject = NULL;
                       break;
               }
               case 'A':
                       m_bAutoAttack = !m_bAutoAttack;
                       break;
               case 'S':
                       m_bShield = !m_bShield;
                       break;
               default:
                       m_pScene->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
                       break;
               }
               break;
	default:
		break;
	}
}

LRESULT CALLBACK CGameFramework::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
	case WM_ACTIVATE:
	{
		if (LOWORD(wParam) == WA_INACTIVE)
			m_GameTimer.Stop();
		else
			m_GameTimer.Start();
		break;
	}
	case WM_SIZE:
		break;
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}
	return(0);
}

void CGameFramework::ProcessInput()
{
	static UCHAR pKeyBuffer[256];
	if (GetKeyboardState(pKeyBuffer))
	{
               DWORD dwDirection = 0;
               if (pKeyBuffer[VK_UP] & 0xF0 || pKeyBuffer['W'] & 0xF0) dwDirection |= DIR_FORWARD;
               if (pKeyBuffer[VK_DOWN] & 0xF0 || pKeyBuffer['S'] & 0xF0) dwDirection |= DIR_BACKWARD;
               if (pKeyBuffer[VK_LEFT] & 0xF0 || pKeyBuffer['A'] & 0xF0) dwDirection |= DIR_LEFT;
               if (pKeyBuffer[VK_RIGHT] & 0xF0 || pKeyBuffer['D'] & 0xF0) dwDirection |= DIR_RIGHT;
               if (pKeyBuffer[VK_PRIOR] & 0xF0) dwDirection |= DIR_UP;
               if (pKeyBuffer[VK_NEXT] & 0xF0) dwDirection |= DIR_DOWN;

                if (dwDirection)
                {
                        if (CTankPlayer* pTank = dynamic_cast<CTankPlayer*>(m_pPlayer))
                                pTank->Move(dwDirection, 0.15f);
                        else
                                m_pPlayer->Move(dwDirection, 0.15f);
                }
	}

	if (GetCapture() == m_hWnd)
	{
		SetCursor(NULL);
		POINT ptCursorPos;
		GetCursorPos(&ptCursorPos);
		float cxMouseDelta = (float)(ptCursorPos.x - m_ptOldCursorPos.x) / 3.0f;
		float cyMouseDelta = (float)(ptCursorPos.y - m_ptOldCursorPos.y) / 3.0f;
		SetCursorPos(m_ptOldCursorPos.x, m_ptOldCursorPos.y);
		if (cxMouseDelta || cyMouseDelta)
		{
			if (pKeyBuffer[VK_RBUTTON] & 0xF0)
				m_pPlayer->Rotate(cyMouseDelta, 0.0f, -cxMouseDelta);
			else
				m_pPlayer->Rotate(cyMouseDelta, cxMouseDelta, 0.0f);
		}
	}


       if (m_bAutoAttack)
       {
               m_fAutoAttackTime += m_GameTimer.GetTimeElapsed();
               if (m_fAutoAttackTime > 0.3f)
               {
                       CAirplanePlayer* pAir = dynamic_cast<CAirplanePlayer*>(m_pPlayer);
                       if (pAir) pAir->FireBullet(m_pLockedObject);
                       m_fAutoAttackTime = 0.0f;
               }
       }

       m_pPlayer->Update(m_GameTimer.GetTimeElapsed());
}

void CGameFramework::AnimateObjects()
{
	float fTimeElapsed = m_GameTimer.GetTimeElapsed();
	if (m_pPlayer) m_pPlayer->Animate(fTimeElapsed);
	if (m_pScene) m_pScene->Animate(fTimeElapsed);
}

void CGameFramework::FrameAdvance()
{
	m_GameTimer.Tick(60.0f);

	ProcessInput();
	AnimateObjects();

	ClearFrameBuffer(RGB(255, 255, 255));

	CCamera* pCamera = m_pPlayer->GetCamera();
	if (m_pScene) m_pScene->Render(m_hDCFrameBuffer, pCamera);

	// 1. 타이틀 → 메뉴 전환
	if (dynamic_cast<CSceneTitle*>(m_pScene) != nullptr)
	{
		CSceneTitle* pTitle = static_cast<CSceneTitle*>(m_pScene);
		if (pTitle->IsFinished())
		{
			m_pScene->ReleaseObjects();
			delete m_pScene;
			m_pScene = new CSceneMenu(m_pPlayer); // 메뉴 씬으로 전환
			m_pScene->BuildObjects();
		}
	}


        // 2. 메뉴 선택 처리
        if (dynamic_cast<CSceneMenu*>(m_pScene) != nullptr)
        {
                CSceneMenu* pMenu = static_cast<CSceneMenu*>(m_pScene);
                if (pMenu->IsTutorialSelected())
                {
                        m_pScene->ReleaseObjects();
                        delete m_pScene;
                        m_pScene = new CScene(m_pPlayer); // Tutorial scene
                        m_pScene->BuildObjects();
                }
                else if (pMenu->IsLevel1Selected() || pMenu->IsStartSelected())
                {
                        m_pScene->ReleaseObjects();
                        delete m_pScene;
                        m_pScene = new CSceneStage1(m_pPlayer);
                        m_pScene->BuildObjects();
                }
                else if (pMenu->IsLevel2Selected())
                {
                        m_pScene->ReleaseObjects();
                        delete m_pScene;
                        m_pScene = new CSceneStage2(m_pPlayer);
                        m_pScene->BuildObjects();
                }
                else if (pMenu->IsEndSelected())
                {
                        DestroyWindow(m_hWnd);
                        return;
                }
        }
	// 3. Level-1 → Level-2 전환
        if (dynamic_cast<CSceneStage1*>(m_pScene) != nullptr)
        {
                CSceneStage1* pStage1 = static_cast<CSceneStage1*>(m_pScene);

               if (pStage1->IsFinished())
               {
                        m_pScene->ReleaseObjects();
                        delete m_pScene;

                        CCamera* pCamera = m_pPlayer->GetCamera();
                        delete m_pPlayer;
                        m_pPlayer = new CTankPlayer();
                        m_pPlayer->SetPosition(0.0f, 0.0f, 0.0f);
                        CCubeMesh* pTankMesh = new CCubeMesh(6.0f, 3.0f, 8.0f);
                        m_pPlayer->SetMesh(pTankMesh);
                        m_pPlayer->SetColor(RGB(0, 128, 0));
                        m_pPlayer->SetCamera(pCamera);
                        m_pPlayer->SetCameraOffset(XMFLOAT3(0.0f, 5.0f, -15.0f));

                        m_pScene = new CSceneStage2(m_pPlayer);
                        m_pScene->BuildObjects();
               }
		else if (pStage1->GoToMenu())
		{
			m_pScene->ReleaseObjects();
			delete m_pScene;
			m_pScene = new CSceneMenu(m_pPlayer);
			m_pScene->BuildObjects();
                }
        }

        // 4. Level-2 → Menu 전환
        if (dynamic_cast<CSceneStage2*>(m_pScene) != nullptr)
        {
                CSceneStage2* pStage2 = static_cast<CSceneStage2*>(m_pScene);

                if (pStage2->GoToMenu())
                {
                        m_pScene->ReleaseObjects();
                        delete m_pScene;
                        m_pScene = new CSceneMenu(m_pPlayer);
                        m_pScene->BuildObjects();
                }
        }


	// ✅ 그다음 렌더링 결과 표시
	PresentFrameBuffer();

	m_GameTimer.GetFrameRate(m_pszFrameRate + 12, 37);
	::SetWindowText(m_hWnd, m_pszFrameRate);
}




