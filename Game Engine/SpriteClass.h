/////////////////////////////////////////////////////////////////////////
// SpriteClass.h
/////////////////////////////////////////////////////////////////////////
#pragma once

#include <d3dx9.h>
#include <string>

class SpriteClass
{
public:
	SpriteClass(void);
	SpriteClass(float x, float y);
	SpriteClass(SpriteClass& other);
	~SpriteClass(void);

public:
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::string filename, int width, int height);
	void Shutdown();
	bool IsInitialized() {return initialized; };
	void Update(float gameTime);
	void Update(float gameTime, D3DXVECTOR3 spriteVelocity);
	void Update(float gameTime, float spriteAngle);
	void Update(float gameTime, D3DXVECTOR3 spritePosition, float spriteAngle, D3DXCOLOR m_spriteColor);
	void Update(float gameTime, D3DXVECTOR3 spritePositionOffset, float spriteAngleOffset);
	void Draw(float gameTime);

	float GetWidth() { return m_spriteWidth; };
	float GetHeight() { return m_spriteHeight; };
	virtual float GetAngle() { return m_spriteAngle; };
	D3DXCOLOR GetColor() { return m_spriteColor; };
	D3DXVECTOR3 GetPosition() { return m_spritePosition; };

public:
	LPD3DXSPRITE GetSprite() { return m_sprite; };
	LPDIRECT3DTEXTURE9 GetTexture() { return m_texture; };

protected:
	bool initialized;

	float m_spriteWidth;
	float m_spriteHeight;
	float m_spriteAngle;
	float m_spriteVelocity;

	D3DXVECTOR3 m_spritePosition;
	D3DXCOLOR m_spriteColor;
	LPDIRECT3DTEXTURE9 m_texture;
	LPD3DXSPRITE m_sprite;
};

