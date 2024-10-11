#pragma once

#include "Scene.h"
#include "BackGround.h"

#include "Player.h"

#include "WhiteSuit.h"
#include "ShotGun.h"  
#include "BlackMan.h"    
#include "FlyingDrone.h" 
#include "SpiderDrone.h" 
#include "DogDrone.h"	 
#include "Ammo.h"
#include "Missile.h"
#include "Laser.h"
#include "MiniGun.h"
#include "Boss_Humanoid.h"
#include "Boss_Robot.h"
#include "Shield.h"
#include "Knife.h"
#include "Axe.h"
#include "DrinkMachine.h"
#include "Trigger.h"//10.06

#include "Terrain.h"
#include "SkyBox.h"
#include "Floor.h"
#include "Wall.h"
#include "Door.h"

class CGameStage3 :
    public CScene
{
private:
	explicit CGameStage3(LPDIRECT3DDEVICE9 _pGraphicDev);
	virtual ~CGameStage3();

public:
	static CGameStage3* Create(LPDIRECT3DDEVICE9 _pGraphicDev);

public:
	virtual HRESULT	Ready_Scene();
	virtual _int Update_Scene(const _float& _fTimeDelta);
	virtual void LateUpdate_Scene();
	virtual void Render_Scene();

private:
	HRESULT Ready_LightInfo();
	HRESULT Ready_Layer_Environment(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_GameLogic(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_Player(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_MonsterBullet(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_UI(const _tchar* _pLayerTag);
	HRESULT Ready_Layer_Effect(const _tchar* _pLayerTag);

private:
	void Set_Collision();
	// ���̾� ã������ �뵵 - ����
	CLayer* Find_Layer(const _tchar* _pLayerTag);
	// �� �ҷ����� - ����
	void MapLoad2(CLayer* _pLayer, CLayer* _pLayer2, CLayer* _pLayer3);

private:
	virtual void Free();

private:
	CPlayer* m_pPlayer;
};

