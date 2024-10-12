#include "pch.h"
#include "..\Header\UIFloor.h"
#include "..\Header\UIFloorBase.h"

CUIFloor::CUIFloor(LPDIRECT3DDEVICE9 _pGraphicDev)
	: CUI(_pGraphicDev)
	, m_pUIFloorBase(nullptr)
{
	m_eUIType = UITYPE::UI_FLOOR;
}

CUIFloor::~CUIFloor()
{
}

CUIFloor* CUIFloor::Create(LPDIRECT3DDEVICE9 _pGraphicDev)
{
	CUIFloor* pUIFloor = new CUIFloor(_pGraphicDev);

	if (FAILED(pUIFloor->Ready_UI()))
	{
		Safe_Release(pUIFloor);
		MSG_BOX("UIFloor create Failed");
		return nullptr;
	}

	return pUIFloor;
}

HRESULT CUIFloor::Ready_UI()
{
	FAILED_CHECK_RETURN(Add_Unit(), E_FAIL);

	return S_OK;
}

_int CUIFloor::Update_UI(const _float& _fTimeDelta)
{
	return Engine::CUI::Update_UI(_fTimeDelta);
}

void CUIFloor::LateUpdate_UI()
{
	Engine::CUI::LateUpdate_UI();
}

void CUIFloor::Render_UI()
{
	Engine::CUI::Render_UI();
}

HRESULT CUIFloor::Add_Unit()
{
	m_pUIFloorBase = CUIFloorBase::Create(m_pGraphicDev);
	m_pUIFloorBase->Set_OwnerUI(this);
	m_vecUIUnit.push_back(m_pUIFloorBase);

	return S_OK;
}

void CUIFloor::Free()
{
	Engine::CUI::Free();
}