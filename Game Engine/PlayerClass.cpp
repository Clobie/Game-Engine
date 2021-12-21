/////////////////////////////////////////////////////////////////////////
// PlayerClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "PlayerClass.h"


PlayerClass::PlayerClass(void)
{	
	m_playerHealth = 0;
	m_playerMaxSpeed.x = 0.0f;
	m_playerMaxSpeed.y = 0.0f;
	m_playerMaxSpeed.z = 0.0f;
	m_playerAngularSpeed = 0.0f;
	m_playerAcceleration = 0.0f;
	m_playerVelocity.x = 0.0f;
	m_playerVelocity.y = 0.0f;
	m_playerVelocity.z = 0.0f;
	m_playerAngle = 3.14159265f;

	m_windowWidth = 0.0f;
	m_windowHeight = 0.0f;

	m_bulletSprite = 0;
}

PlayerClass::PlayerClass(PlayerClass& other)
{

}

PlayerClass::~PlayerClass(void)
{
	if(m_bulletSprite)
	{
		m_bulletSprite->Shutdown();
		delete m_bulletSprite;
		m_bulletSprite = 0;
	}
}

bool PlayerClass::Initialize(LPDIRECT3DDEVICE9 device, std::string filename, int width, int height, 
							 float health, float acceleration, D3DXVECTOR3 maxSpeed, float angularSpeed, float windowWidth, float windowHeight)
{
	//Same functionality as D3DXCreateTextureFromFile EXCEPT width and height are manually entered
	if(!SUCCEEDED(D3DXCreateTextureFromFileEx(device, filename.c_str(), 
		width, height, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, 
		D3DX_DEFAULT, 0, NULL, NULL, &m_texture)))
	{
		std::string s = "There was an issue creating the Texture.  Make sure the requested image is available.  Requested image: " + filename;
		MessageBox(NULL, s.c_str(), NULL, NULL); 
		return false;
	}

	//Attempt to create the sprite
	if(!SUCCEEDED(D3DXCreateSprite(device, &m_sprite)))
	{
		MessageBox(NULL, "There was an issue creating the Sprite.", NULL, NULL);
		return false;
	}

	m_spriteWidth = (float)width;
	m_spriteHeight = (float)height;

	m_playerHealth = health;
	m_playerAcceleration = acceleration;
	m_playerMaxSpeed = maxSpeed;
	m_playerAngularSpeed = angularSpeed;

	m_bulletSprite = new SpriteClass;
	if(!m_bulletSprite)
	{
		return false;
	}

	m_bulletSprite->Initialize(device, "Bullet.png", 2, 2);

	D3DXVECTOR3 nullvec(0.0f, 0.0f, 0.0f);
	for(int i = 0; i < TOTAL_BULLETS-1; i++)
	{
		m_bullet[i].m_active = false;
		m_bullet[i].m_bulletPosition = nullvec;
		m_bullet[i].m_bulletVelocity = nullvec;
	}

	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	initialized = true;
	return true;
}

void PlayerClass::OnLoop(float dt)
{
	m_bulletTimer += dt*10.0f;
	D3DXVECTOR3 updatedPosition;
	for(int i = 0; i < TOTAL_BULLETS-1; i++)
	{
		if(m_bullet[i].m_active == true)
		{
			m_bullet[i].m_bulletPosition += (m_bullet[i].m_bulletVelocity * dt);
			m_bulletSprite->Update(dt, m_bullet[i].m_bulletPosition, 0.0f, D3DCOLOR_ARGB(255, 255, 255, 255));
			m_bulletSprite->Draw(dt);
		}

		
		if(m_bullet[i].m_bulletPosition.x > m_windowWidth ||
			m_bullet[i].m_bulletPosition.x < 0 ||
			m_bullet[i].m_bulletPosition.y > m_windowHeight ||
			m_bullet[i].m_bulletPosition.y < 0)
		{
			m_bullet[i].m_active = false;
			m_bullet[i].m_bulletPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			m_bullet[i].m_bulletVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		

		/*
		if(m_bullet[i].m_bulletPosition.x > m_windowWidth)
			m_bullet[i].m_bulletPosition.x = 0.0f;
		if(m_bullet[i].m_bulletPosition.x < 0)
			m_bullet[i].m_bulletPosition.x = m_windowWidth;
		if(m_bullet[i].m_bulletPosition.y < 0.0f)
			m_bullet[i].m_bulletPosition.y = m_windowHeight;
		if(m_bullet[i].m_bulletPosition.y > m_windowHeight)
			m_bullet[i].m_bulletPosition.y = 0.0f;
		*/
	}
}

D3DXVECTOR3 PlayerClass::GetAimVector()
{
	D3DXVECTOR3 vec;
	vec.x = cos(m_spriteAngle + 1.57079633f);
	vec.y = sin(m_spriteAngle + 1.57079633f);
	vec.z = 0.0f;
	return vec;
}

bool PlayerClass::CheckBulletCollision(D3DXVECTOR3 target, float spriteWidth, float spriteHeight)
{
	for(int i = 0; i < TOTAL_BULLETS-1; i++)
	{
		if(m_bullet[i].m_active == true)
		{
			if(m_bullet[i].m_bulletPosition.x > target.x && 
				m_bullet[i].m_bulletPosition.x < target.x + spriteWidth &&
				m_bullet[i].m_bulletPosition.y > target.y &&
				m_bullet[i].m_bulletPosition.y < target.y + spriteHeight)
			{
				return true;
			}
		}
	}
	return false;
}

void PlayerClass::Forward(float dt)
{
	m_playerVelocity.x += (cos(m_spriteAngle+1.57079633f) / (10 - m_playerAcceleration * dt));
	m_playerVelocity.y += (sin(m_spriteAngle+1.57079633f) / (10 - m_playerAcceleration * dt));

	if(m_playerVelocity.x > m_playerMaxSpeed.x)
	{
		m_playerVelocity.x = m_playerMaxSpeed.x;
	}
	if(m_playerVelocity.x < -m_playerMaxSpeed.x)
	{
		m_playerVelocity.x = -m_playerMaxSpeed.x;
	}
	if(m_playerVelocity.y > m_playerMaxSpeed.y)
	{
		m_playerVelocity.y = m_playerMaxSpeed.y;
	}
	if(m_playerVelocity.y < -m_playerMaxSpeed.y)
	{
		m_playerVelocity.y = -m_playerMaxSpeed.y;
	}
}

void PlayerClass::Backward(float dt)
{
	m_playerVelocity.x -= (cos(m_spriteAngle+1.57079633f) / (27 - m_playerAcceleration * dt));
	m_playerVelocity.y -= (sin(m_spriteAngle+1.57079633f) / (27 - m_playerAcceleration * dt));
}

void PlayerClass::TurnLeft(float dt)
{
	m_playerAngle = (m_playerAngle - (dt * m_playerAngularSpeed));
}

void PlayerClass::TurnRight(float dt)
{
	m_playerAngle = (m_playerAngle + (dt * m_playerAngularSpeed));
}

void PlayerClass::Fire(float dt)
{
	if(m_bulletTimer > 2.0f)
	{
		m_bulletTimer = 0.0f;
		for(int i = 0; i < TOTAL_BULLETS-1; i++)
		{
			if(m_bullet[i].m_active == false)
			{
				m_bullet[i].m_active = true;
				m_bullet[i].m_bulletPosition.x = (m_spritePosition.x + GetWidth()/2);
				m_bullet[i].m_bulletPosition.y = (m_spritePosition.y + GetHeight()/2);
				m_bullet[i].m_bulletVelocity = D3DXVECTOR3(GetAimVector().x * (50000.0f * dt), GetAimVector().y * (50000.0f * dt), 0.0f);
				return;
			}
		}
	}
}