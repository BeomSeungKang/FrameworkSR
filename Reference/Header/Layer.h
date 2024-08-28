#pragma once

#include "Base.h"
#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CLayer 
	: public CBase
{
private :
	explicit CLayer();
	virtual ~CLayer();

public :
	CComponent* Get_Component(COMPONENTID _eID, const _tchar* _pObjTag, const _tchar* _pComponentTag);

public :
	static CLayer* Create();

public :
	HRESULT	Add_GameObject(const _tchar* _pObjTag, CGameObject* _pGameObject);

public :
	HRESULT	Ready_Layer();
	_int Update_Layer(const _float& _fTimeDelta);
	void LateUpdate_Layer();

private :
	virtual void Free();

private :
	map<const _tchar*, CGameObject*> m_mapObject;
};

END