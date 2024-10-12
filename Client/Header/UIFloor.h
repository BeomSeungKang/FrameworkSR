#pragma once

#include "UI.h"

BEGIN(Engine)

class CUIUnit;

END

class CUIFloorBase;

class CUIFloor
	: public Engine::CUI
{
private:
	explicit CUIFloor(LPDIRECT3DDEVICE9 _pGraphicDev);
	virtual ~CUIFloor();

public:
	static CUIFloor* Create(LPDIRECT3DDEVICE9 _pGraphicDev);

public:
	HRESULT Ready_UI();
	virtual	_int Update_UI(const _float& _fTimeDelta);
	virtual	void LateUpdate_UI();
	virtual	void Render_UI();

private:
	HRESULT Add_Unit();

private:
	virtual void Free();

private:
	CUIFloorBase* m_pUIFloorBase;
};