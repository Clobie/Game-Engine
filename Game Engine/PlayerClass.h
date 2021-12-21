/////////////////////////////////////////////////////////////////////////
// PlayerClass.h
/////////////////////////////////////////////////////////////////////////
#pragma once
#include "SpriteClass.h"

#define TOTAL_BULLETS 250

class PlayerClass : public SpriteClass
{
public:
	PlayerClass(void);
	PlayerClass(PlayerClass& other);
	~PlayerClass(void);

public:
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string filename, int width, int height, 
		float health, float acceleration, D3DXVECTOR3 maxSpeed, float angularSpeed, float windowWidth, float windowHeight);
	void OnLoop(float dt);

public:
	void Forward(float dt);
	void Backward(float dt);
	void TurnLeft(float dt);
	void TurnRight(float dt);
	void Fire(float dt);

	bool CheckBulletCollision(D3DXVECTOR3 target, float spriteWidth, float spriteHeight);

	D3DXVECTOR3 GetVelocity() { return m_playerVelocity; };
	float GetAngle() { return m_playerAngle; };
	D3DXVECTOR3 GetMaxSpeed() { return m_playerMaxSpeed; };
	D3DXVECTOR3 GetAimVector();

private:
	SpriteClass* m_bulletSprite;
	float m_bulletTimer;
	struct bullet_t
	{
		bool m_active;
		D3DXVECTOR3 m_bulletVelocity;
		D3DXVECTOR3 m_bulletPosition;
	}m_bullet[TOTAL_BULLETS];

private:
	float m_playerHealth;
	D3DXVECTOR3 m_playerMaxSpeed;
	float m_playerAngularSpeed;
	float m_playerAcceleration;
	D3DXVECTOR3 m_playerVelocity;
	float m_playerAngle;

private:
	float m_windowWidth;
	float m_windowHeight;
};

