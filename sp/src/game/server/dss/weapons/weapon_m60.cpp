#include "cbase.h"
#include "basehlcombatweapon.h"
#include "tier0/memdbgon.h"

class CWeaponM60 : public CHLMachineGun 
{
	DECLARE_DATADESC();

public:
	DECLARE_CLASS(CWeaponM60, CHLMachineGun);

	CWeaponM60();

	DECLARE_SERVERCLASS();

	virtual float	GetFireRate(void) { return 0.1f; };
	virtual bool	Deploy(void);

	void AddViewKick(void);

	int CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual const Vector& GetBulletSpread(void) 
	{
		static const Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}
};

LINK_ENTITY_TO_CLASS(weapon_m60, CWeaponM60);
PRECACHE_WEAPON_REGISTER(weapon_m60);

IMPLEMENT_SERVERCLASS_ST(CWeaponM60, DT_WeaponM60)
END_SEND_TABLE()

BEGIN_DATADESC(CWeaponM60)
END_DATADESC()

CWeaponM60::CWeaponM60() 
{
}

bool CWeaponM60::Deploy(void)
{
	return BaseClass::Deploy();
}

void CWeaponM60::AddViewKick(void)
{
	float flEasyDampen = 0.1f;
	float flMaxVerticalKick = 20.0f;	//Degrees
	float flSlideLimit = 5.0f;	//Seconds

	//Get the view kick
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());

	if (!pPlayer)
		return;

	DoMachineGunKick(pPlayer, flEasyDampen, flMaxVerticalKick, m_fFireDuration, flSlideLimit);
}