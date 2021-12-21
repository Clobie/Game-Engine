/////////////////////////////////////////////////////////////////////////
// GameClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "GameClass.h"

GameClass::GameClass(void)
{
	m_pGraphics = 0;
	m_pInput = 0;
	m_pTimer = 0;
	m_windowWidth = 0;
	m_windowHeight = 0;

	m_player = 0;
	m_backgroundSprite = 0;
	m_enemySprite = 0;
}

GameClass::GameClass(GameClass& other)
{

}

GameClass::~GameClass(void)
{
	if(m_player)
	{
		m_player->Shutdown();
		delete m_player;
		m_player = 0;
	}
	if(m_backgroundSprite)
	{
		m_backgroundSprite->Shutdown();
		delete m_backgroundSprite;
		m_backgroundSprite = 0;
	}
	if(m_enemySprite)
	{
		m_enemySprite->Shutdown();
		delete m_enemySprite;
		m_enemySprite = 0;
	}
}

bool GameClass::Initialize(GraphicsClass* pGraphics, InputClass* pInput, TimerClass* pTimer)
{

	// Transfer our pointers to this game class
	m_pGraphics = pGraphics;
	m_pInput = pInput;
	m_pTimer = pTimer;
	if(!m_pGraphics || !m_pInput || !m_pTimer)
	{
		return false;
	}

	// Randomness
	srand( time(NULL) );

	// Save window height and width
	m_windowHeight = m_pGraphics->GetWindowHeight();
	m_windowWidth = m_pGraphics->GetWindowWidth();

	// Player
	m_player		= new PlayerClass;
	if(!m_player)
	{
		return false;
	}
	bool result = m_player->Initialize(m_pGraphics->GetDevice(), "Ship.png", 50, 29, 
										100.0f, 10.0f, D3DXVECTOR3(15.0f, 15.0f, 0.0f), 3.0f, m_windowWidth, m_windowHeight);
	if(!result)
	{
		return false;
	}
	else
	{
		m_player->Update(0.0f, D3DXVECTOR3(m_pGraphics->GetWindowWidth()/2, m_pGraphics->GetWindowHeight()/2, 0.0f), 3.14159f, D3DCOLOR_ARGB(255,255,255,255));
	}

	// Enemy
	m_enemySprite = new SpriteClass;
	if(!m_enemySprite)
	{
		return false;
	}
	result = m_enemySprite->Initialize(m_pGraphics->GetDevice(), "Enemy.png", 104, 63);
	if(!result)
	{
		return false;
	}

	float myrand1 = 0.0f, myrand2 = 0.0f, myrand3 = 0.0f;
	for(int i = 0; i < TOTAL_ENEMIES-1; i++)
	{
		m_enemy[i].m_active = true;
		m_enemy[i].m_health = 100.0f;
		m_enemy[i].m_position = D3DXVECTOR3((float)(rand() % m_windowWidth+1), (float)(rand() % m_windowHeight+1), 0.0f);

		myrand1 = (float)(rand() % 5) - 2.5f;
		myrand2 = (float)(rand() % 5) - 2.5f;
		myrand3 = (float)(rand() % 11);

		while(myrand1 < 0.1f && myrand1 > -0.1f) 
			myrand1 = (float)(rand() % 6) - 2.5f;
		while(myrand2 < 0.1f && myrand2 > -0.1f) 
			myrand2 = (float)(rand() % 6) - 2.5f;
		while(myrand3 < 0.1f && myrand3 > -0.1f)
			myrand3 = (float)(rand() % 11) - 5.0f;

		m_enemy[i].m_velocity = D3DXVECTOR3(myrand1, myrand2, 0.0f);
		m_enemy[i].m_rotationAngle = (myrand3) / 3;
		m_enemy[i].m_currentAngle = 0.0f;
	}


	ShowWindow(m_pGraphics->GetHWND(), SW_HIDE);
	m_pGraphics->CaptureScreen();
	ShowWindow(m_pGraphics->GetHWND(), SW_SHOW);

	m_backgroundSprite = new SpriteClass;
	result = m_backgroundSprite->Initialize(m_pGraphics->GetDevice(), "Space.png", m_windowWidth, m_windowHeight);
	if(!result)
	{
		return false;
	}
	m_backgroundSprite->Update(0.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255));


	return true;
}

bool GameClass::Frame()
{
	bool result;

	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}
	return true;
}

bool GameClass::Render()
{
	m_pGraphics->Clear(D3DCOLOR_XRGB(0, 0, 0));
	OnLoop();
	m_pGraphics->Present();
	return true;
}

bool GameClass::OnLoop()
{
	m_pTimer->Update();
	float dt = m_pTimer->GetDeltaTimer();
	m_backgroundSprite->Draw(dt);

	D3DXVECTOR3 updatedPos;
	for(int i = 0; i < TOTAL_ENEMIES-1; i++)
	{
		if(m_enemy[i].m_active == true)
		{
			m_enemy[i].m_position += m_enemy[i].m_velocity;

			if(m_enemy[i].m_position.x > m_windowWidth)
				m_enemy[i].m_position.x = (m_enemySprite->GetWidth() * -1);
			else
			if(m_enemy[i].m_position.x < -m_enemySprite->GetWidth())
				m_enemy[i].m_position.x = m_windowWidth;

			if(m_enemy[i].m_position.y > m_windowHeight)
				m_enemy[i].m_position.y = (m_enemySprite->GetHeight() * -1);
			else
			if(m_enemy[i].m_position.y < -m_enemySprite->GetHeight())
				m_enemy[i].m_position.y = m_windowHeight;


			if(m_player->CheckBulletCollision(m_enemy[i].m_position, m_enemySprite->GetWidth(), m_enemySprite->GetHeight()))
			{
				m_enemy[i].m_active = false;
			}
			else
			{
				m_enemy[i].m_currentAngle += (m_enemy[i].m_rotationAngle * dt);
				if(m_enemy[i].m_currentAngle > 6.28318531f)
					m_enemy[i].m_currentAngle = 0.0f;
				if(m_enemy[i].m_currentAngle < 0.0f)
					m_enemy[i].m_currentAngle = 6.28318531f;

				m_enemySprite->Update(dt, m_enemy[i].m_position, m_enemy[i].m_currentAngle, D3DCOLOR_ARGB(255, 255, 255, 255));
				m_enemySprite->Draw(dt);
			}
		}
	}


	if(m_pInput->IsKeyDown(VK_UP))
	{
		m_player->Forward(dt);
	}
	if(m_pInput->IsKeyDown(VK_DOWN))
	{
		m_player->Backward(dt);
	}
	if(m_pInput->IsKeyDown(VK_LEFT))
	{
		m_player->TurnLeft(dt);
	}
	if(m_pInput->IsKeyDown(VK_RIGHT))
	{
		m_player->TurnRight(dt);
	}
	if(m_pInput->IsKeyDown(VK_SPACE))
	{
		m_player->Fire(dt);
	}
	
	updatedPos = m_player->GetPosition() + m_player->GetVelocity();

	if(updatedPos.x > m_windowWidth)
	{
		updatedPos.x = (m_player->GetWidth() * -1);
	}
	if(updatedPos.x < (m_player->GetWidth() * -1))
	{
		updatedPos.x = m_windowWidth;
	}
	if(updatedPos.y > m_windowHeight)
	{
		updatedPos.y = (m_player->GetHeight() * -1);
	}
	if(updatedPos.y < (m_player->GetHeight() * -1))
	{
		updatedPos.y = m_windowHeight;
	}

	m_player->Update(dt, updatedPos, m_player->GetAngle(), D3DCOLOR_ARGB(255, 255, 255, 255));

	m_player->OnLoop(dt);

	m_player->Draw(dt);

	return true;
}