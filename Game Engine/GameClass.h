/////////////////////////////////////////////////////////////////////////
// GameClass.h
/////////////////////////////////////////////////////////////////////////
#include <math.h>
#include "GraphicsClass.h"
#include "InputClass.h"
#include "TimerClass.h"
#include "PlayerClass.h"
#include <sstream>
#include <time.h>
#pragma once

#define TOTAL_ENEMIES 19

class GameClass
{
public:
	GameClass(void);
	GameClass(GameClass& other);
	~GameClass(void);

	bool Initialize(GraphicsClass* pGraphics, InputClass* pInput, TimerClass* pTimer);
	void Shutdown();

	bool Frame();

private:
	bool Render();
	bool OnLoop();
#
private:
	GraphicsClass* m_pGraphics;
	InputClass* m_pInput;
	TimerClass* m_pTimer;
	int m_windowWidth;
	int m_windowHeight;

private:
	PlayerClass* m_player;
	SpriteClass* m_backgroundSprite;
	SpriteClass* m_enemySprite;
	struct enemy_t
	{
		bool m_active;
		float m_health;
		D3DXVECTOR3 m_position;
		D3DXVECTOR3 m_velocity;
		float m_rotationAngle;
		float m_currentAngle;
	}m_enemy[TOTAL_ENEMIES];
};

