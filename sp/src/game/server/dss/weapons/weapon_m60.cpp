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

	void AddViewKick(void);

	int CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual const Vector& GetBulletSpread(void) 
	{
		static const Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	DECLARE_ACTTABLE();
};

CWeaponM60::CWeaponM60() 
{

}

void CWeaponM60::AddViewKick()
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