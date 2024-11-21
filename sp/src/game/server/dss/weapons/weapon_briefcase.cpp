#include "cbase.h"
#include "basehlcombatweapon.h"
#include "in_buttons.h"

// blah blah blah last include
#include "tier0/memdbgon.h"

class CWeaponBriefcase : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();

public:
	DECLARE_CLASS(CWeaponBriefcase, CBaseHLCombatWeapon);

	CWeaponBriefcase(void);

	DECLARE_SERVERCLASS();

	void PrimaryAttack(void);
	void ItemPostFrame(void);

	DECLARE_ACTTABLE();

private:
	float m_flNextPrimaryAttack;
};

IMPLEMENT_SERVERCLASS_ST(CWeaponBriefcase, DT_WeaponBriefcase)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_briefcase, CWeaponBriefcase);
PRECACHE_WEAPON_REGISTER(weapon_briefcase);

BEGIN_DATADESC(CWeaponBriefcase)
	DEFINE_FIELD(m_flNextPrimaryAttack, FIELD_TIME),
END_DATADESC()

acttable_t CWeaponBriefcase::m_acttable[] =
{
	{ ACT_VM_IDLE, ACT_VM_PRIMARYATTACK, true }
};

IMPLEMENT_ACTTABLE(CWeaponBriefcase);

CWeaponBriefcase::CWeaponBriefcase(void)
{
	m_flNextPrimaryAttack = 0.0f; // initialize delay timer
}

void CWeaponBriefcase::PrimaryAttack(void)
{
	if (gpGlobals->curtime < m_flNextPrimaryAttack)
		return;

	SendWeaponAnim(ACT_VM_PRIMARYATTACK);

	m_flNextPrimaryAttack = gpGlobals->curtime + 1.0f; // adjust delay as needed
}

void CWeaponBriefcase::ItemPostFrame(void)
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