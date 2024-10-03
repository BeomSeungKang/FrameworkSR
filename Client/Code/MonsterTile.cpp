#include "pch.h"
#include "../Header/MonsterTile.h"
#include "Export_System.h"
#include "Export_Utility.h"

CMonsterTile::CMonsterTile(LPDIRECT3DDEVICE9 _pGraphicDev)
	: Engine::CGameObject(_pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTransformCom(nullptr)
	, m_pTextureCom(nullptr)
{
	m_pName = L"Proto_Floor0";
}

CMonsterTile::~CMonsterTile()
{
}

CMonsterTile* CMonsterTile::Create(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	CMonsterTile* pMonster = new CMonsterTile(_pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("pTerrain Create Failed");

		return nullptr;
	}

	return pMonster;
}

CMonsterTile* CMonsterTile::Create_Pos(LPDIRECT3DDEVICE9 _pGraphicDev, _vec3 _vecPos)
{
	CMonsterTile* pMonster = new CMonsterTile(_pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("pWall Create Failed");
		return nullptr;
	}

	pMonster->Setup_Position(_vecPos);
	pMonster->m_vecPos = _vecPos;

	return pMonster;
}

CMonsterTile* CMonsterTile::Create_Rot(LPDIRECT3DDEVICE9 _pGraphicDev, _vec3 _vecPos, _vec3 _vecRot)
{
	CMonsterTile* pMonster = new CMonsterTile(_pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("pWall Create Failed");
		return nullptr;
	}

	pMonster->Setup_Position(_vecPos);
	pMonster->Setup_Angle(_vecRot);
	return pMonster;
}

CMonsterTile* CMonsterTile::Create_Info(LPDIRECT3DDEVICE9 _pGraphicDev, _vec3 _vecPos, const _tchar* _pName)
{
	CMonsterTile* pMonster = new CMonsterTile(_pGraphicDev);

	pMonster->Setup_ImageName(_pName);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("pTerrain Create Failed");
		return nullptr;
	}

	pMonster->Setup_Position(_vecPos);
	pMonster->m_vecPos = _vecPos;

	if (_pName == L"Proto_Monster1")
	{
		pMonster->Setup_ImageNumber(1);
	}
	else if (_pName == L"Proto_Monster2")
	{
		pMonster->Setup_ImageNumber(2);
	}
	else if (_pName == L"Proto_Monster3")
	{
		pMonster->Setup_ImageNumber(3);
	}
	else if (_pName == L"Proto_Monster4")
	{
		pMonster->Setup_ImageNumber(4);
	}
	else if (_pName == L"Proto_Monster5")
	{
		pMonster->Setup_ImageNumber(5);
	}
	else if (_pName == L"Proto_Monster6")
	{
		pMonster->Setup_ImageNumber(6);
	}

	return pMonster;
}

HRESULT CMonsterTile::Ready_GameObject()
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	_vec3 vUp, vLook, vRight;
	m_pTransformCom->Get_Info(INFO::INFO_UP, &vUp);
	m_pTransformCom->Get_Info(INFO::INFO_LOOK, &vLook);
	m_pTransformCom->Get_Info(INFO::INFO_RIGHT, &vRight);

	_vec3 vOffset = { vUp.x + vRight.x, vUp.y + vRight.y, vUp.z + vRight.z };


	return S_OK;
}

_int CMonsterTile::Update_GameObject(const _float& _fTimeDelta)
{
	Add_RenderGroup(RENDERID::RENDER_NONALPHA, this);


	return Engine::CGameObject::Update_GameObject(_fTimeDelta);
}

void CMonsterTile::LateUpdate_GameObject()
{
	Engine::CGameObject::LateUpdate_GameObject();
}

void CMonsterTile::Render_GameObject()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	FAILED_CHECK_RETURN(Setup_Material(), );

	m_pTextureCom->Set_Texture(0);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void CMonsterTile::Setup_ImageName(const _tchar* _pName)
{
	m_pName = _pName;
	
}

HRESULT CMonsterTile::Add_Component()
{
	CComponent* pComponent = NULL;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcSpriteTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(m_pName));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_STATIC].insert({ L"Com_Texture", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[(_uint)COMPONENTID::ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	return S_OK;
}

HRESULT CMonsterTile::Setup_Material()
{
	D3DMATERIAL9 tMtrl;
	ZeroMemory(&tMtrl, sizeof(D3DMATERIAL9));

	tMtrl.Diffuse = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Specular = { 1.f, 1.f, 1.f, 1.f };
	tMtrl.Ambient = { 1.f, 1.f, 1.f, 1.f };

	tMtrl.Emissive = { 0.f, 0.f, 0.f, 0.f };
	tMtrl.Power = 0.f;

	m_pGraphicDev->SetMaterial(&tMtrl);

	return S_OK;
}

void CMonsterTile::Setup_Position(_vec3 _vecPos)
{
	m_pTransformCom->Set_Pos(_vecPos.x, _vecPos.y, _vecPos.z);
}

void CMonsterTile::Setup_Angle(_vec3 _vecRot)
{
	m_pTransformCom->Set_Angle(_vecRot.x, _vecRot.y, _vecRot.z);
}

void CMonsterTile::Free()
{
	Engine::CGameObject::Free();
}
