/////////////////////////////////////////////////////////////////////////
// SpriteClass.cpp
/////////////////////////////////////////////////////////////////////////
#include "SpriteClass.h"


SpriteClass::SpriteClass(void)
{
	//Default the sprite to position (0, 0, 0)
	m_spritePosition.x = 0;
	m_spritePosition.y = 0;
	m_spritePosition.z = 0;

	//Default angle
	m_spriteAngle = 0.0f; // 180 degrees in radians

	//When color is set to white, what you see is exactly what the image looks like.
	m_spriteColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	//default w&h
	m_spriteWidth = 0;
	m_spriteHeight = 0;

	//We are not initialized yet
	initialized = false;
}

SpriteClass::SpriteClass(float x, float y)
{
	//Set the position to the programmer's requested X and Y coordinates.  
	//Default Z to 0
	m_spritePosition.x = x;
	m_spritePosition.y = y;
	m_spritePosition.z = 0;

	//Default angle
	m_spriteAngle = 3.14159265f; // 180 degrees in radians

	//When color is set to white, what you see is exactly what the image looks like.
	m_spriteColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	//default w&h
	m_spriteWidth = 0;
	m_spriteHeight = 0;

	//We are not initialized yet
	initialized = false;
}

SpriteClass::SpriteClass(SpriteClass& other)
{

}

SpriteClass::~SpriteClass(void)
{
	if(m_sprite)
	{
		m_sprite->Release();
		m_sprite = 0;
	}

	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}

void SpriteClass::Shutdown()
{
	if(m_sprite)
	{
		m_sprite->Release();
		m_sprite = 0;
	}

	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}
}

bool SpriteClass::Initialize(LPDIRECT3DDEVICE9 device, std::string filename, int width, int height)
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

	initialized = true;

	return true;
}

void SpriteClass::Update(float gameTime)
{
	
}

void SpriteClass::Update(float gameTime, D3DXVECTOR3 spriteVelocity)
{
	m_spritePosition += spriteVelocity;
}

void SpriteClass::Update(float gameTime, float spriteAngle)
{

}

void SpriteClass::Update(float gameTime, D3DXVECTOR3 spritePosition, float spriteAngle, D3DXCOLOR m_spriteColor)
{
	
	m_spritePosition = spritePosition;
	m_spriteAngle = spriteAngle;
}

void SpriteClass::Update(float gameTime, D3DXVECTOR3 spritePositionOffset, float spriteAngleOffset)
{
	m_spritePosition += spritePositionOffset;
	m_spriteAngle += spriteAngleOffset;
}

void SpriteClass::Draw(float gameTime)
{
	if(m_sprite && m_texture)
	{
		m_sprite->Begin(D3DXSPRITE_ALPHABLEND);

		D3DXMATRIX matRotate;
		D3DXVECTOR2 vCenter(m_spriteWidth/2, m_spriteHeight/2);
		D3DXVECTOR2 vPosition(m_spritePosition.x, m_spritePosition.y);

		D3DXMatrixTransformation2D(&matRotate, NULL, NULL, NULL, &vCenter, m_spriteAngle, &vPosition);
		m_sprite->SetTransform(&matRotate);

		m_sprite->Draw(m_texture, NULL, NULL, NULL, m_spriteColor);
		
		D3DXMatrixRotationZ(&matRotate, 0);
		m_sprite->SetTransform(&matRotate);

		m_sprite->End();
	}
}