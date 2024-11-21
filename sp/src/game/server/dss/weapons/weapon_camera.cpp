#include "cbase.h"
#include "basehlcombatweapon.h"
#include "in_buttons.h"

// blah blah blah last include
#include "tier0/memdbgon.h"

class CWeaponCamera : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();

public:
	DECLARE_CLASS(CWeaponCamera, CBaseHLCombatWeapon);

	CWeaponCamera(void);

	DECLARE_SERVERCLASS();

	void PrimaryAttack(void);
	void ItemPostFrame(void);

	DECLARE_ACTTABLE();

private:
	float m_flNextPrimaryAttack;
};

IMPLEMENT_SERVERCLASS_ST(CWeaponCamera, DT_WeaponCamera)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_camera, CWeaponCamera);
PRECACHE_WEAPON_REGISTER(weapon_camera);

BEGIN_DATADESC(CWeaponCamera)
	DEFINE_FIELD(m_flNextPrimaryAttack, FIELD_TIME),
END_DATADESC()

acttable_t CWeaponCamera::m_acttable[] =
{
	{ ACT_VM_IDLE, ACT_VM_PRIMARYATTACK, true }
};

IMPLEMENT_ACTTABLE(CWeaponCamera);

CWeaponCamera::CWeaponCamera(void)
{
	m_flNextPrimaryAttack = 0.0f; // initialize delay timer
}

void CWeaponCamera::PrimaryAttack(void)
{
	if (gpGlobals->curtime < m_flNextPrimaryAttack)
		return;

	SendWeaponAnim(ACT_VM_PRIMARYATTACK);

	m_flNextPrimaryAttack = gpGlobals->curtime + 1.0f; // adjust delay as needed
}

void CWeaponCamera::ItemPostFrame(void)
{
	// check if the owner is still holding down the attack button
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (pPlayer && pPlayer->IsAlive() && pPlayer->GetActiveWeapon() == this)
	{
		if (pPlayer->m_nButtons & IN_ATTACK)
		{
			// Call PrimaryAttack if the attack button is held
			PrimaryAttack();
		}
	}

	BaseClass::ItemPostFrame(); // call the base class version
}