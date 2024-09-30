 #include "pch.h"
#include "..\Header\Monster.h"
#include "Export_Utility.h"
#include "Export_System.h" // Jonghan Change

CMonster::CMonster(LPDIRECT3DDEVICE9 _pGraphicDev)
	: Engine::CCharacter(_pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTransformCom(nullptr)
	, m_pCalculatorCom(nullptr)
	, m_pColliderCom(nullptr)
	, m_pAnimatorCom(nullptr)
	, m_pHitBufferCom(nullptr)
	, m_pHeadHit(nullptr)
	, m_pCriticalHit(nullptr)
	, m_bIsDead(false)
	, vKnockBackForce({ 0.f,0.f,0.f })
{
}

CMonster::~CMonster()
{
}

_int CMonster::Update_GameObject(const _float& _fTimeDelta)
{
	//Jonghan Monster Change Start

	if (!m_bIsDead)
		Attack(_fTimeDelta);

	KnockBack(_fTimeDelta);
	_int iExit = Engine::CGameObject::Update_GameObject(_fTimeDelta);

	_matrix		matWorld, matView, matBill, matResult;
	m_pTransformCom->Get_WorldMatrix(&matWorld);

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixIdentity(&matBill);

	matBill._11 = matView._11;
	matBill._13 = matView._13;
	matBill._31 = matView._31;
	matBill._33 = matView._33;

	D3DXMatrixInverse(&matBill, 0, &matBill);

	matResult = matBill * matWorld;

	m_pTransformCom->Set_WorldMatrix(&(matResult));

	Add_RenderGroup(RENDERID::RENDER_ALPHA, this);
	Engine::Add_Collider(m_pColliderCom);

	//Jonghan Monster Change End

	return iExit;
}

void CMonster::LateUpdate_GameObject()
{
	//Jonghan Monster Change Start
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO::INFO_POS, &vPos);

	CTerrainTex* pTerrainBufferCom = dynamic_cast<CTerrainTex*>(Engine::Get_Component(COMPONENTID::ID_STATIC, L"Layer_GameLogic", L"Terrain", L"Com_Buffer"));
	NULL_CHECK(pTerrainBufferCom);

	_float fY = m_pCalculatorCom->Compute_HeightOnTerrain(&vPos, pTerrainBufferCom->Get_VtxPos(), VTXCNTX, VTXCNTZ);

	m_pTransformCom->Set_Pos(vPos.x, fY + 1.f, vPos.z);

	CGameObject::Compute_ViewZ(&vPos);

	//Change_State();

	State_Check();

	//Jonghan Monster Change End
	Engine::CGameObject::LateUpdate_GameObject();
}

void CMonster::Damaged(const DAMAGED_STATE& _eDamagedState, const _float& _fAttackDamage)
{
	CMonster::MONSTERBODY eTemp = MONSTERBODY_END;
	switch (_eDamagedState)
	{
	case DAMAGED_STATE::DAMAGED_HEADSHOT: eTemp = MONSTERBODY_HEAD;
		break;
	case DAMAGED_STATE::DAMAGED_BULLSHOT: eTemp = MONSTERBODY_BULL;
		break;
	default:eTemp = MONSTERBODY_BODY;
		break;
	}
	Damaged_By_Player(eTemp, _fAttackDamage);

	m_pColliderCom->SetActive(false); //To BeomSeung, Check RcCol from collider active plz
}

void CMonster::AddForce(_float pPower, _vec3 vLook)
{
	D3DXVec3Normalize(&vLook, &vLook);
	vLook *= pPower;
	vKnockBackForce = vLook;
}

void CMonster::KnockBack(const _float& _fTimeDelta)
{
	_float vLength = D3DXVec3Length(&vKnockBackForce);
	vLength -= 1.f;
	if (vLength <= 0)
	{
		vLength = 0;
	}
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO::INFO_POS, &vPos);
	vPos += vKnockBackForce * _fTimeDelta;
	m_pTransformCom->Set_Pos(vPos);
	D3DXVec3Normalize(&vKnockBackForce, &vKnockBackForce);
	vKnockBackForce *= vLength;
}

void CMonster::Free()
{
	Engine::CGameObject::Free();
}