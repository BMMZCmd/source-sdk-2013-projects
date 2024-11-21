//=============================================================================//
//
// Purpose: CS:S weapons recreated from scratch in Source SDK 2013 for usage in a Half-Life 2 setting.
//
// Author: Blixibon
//
//=============================================================================//

#include "cbase.h"
#include "weapon_css_base.h"

//-----------------------------------------------------------------------------
// Cweapon_m60_experimental
//-----------------------------------------------------------------------------
class CWeaponM60Experimental : public CBase_CSS_HL2_Rifle
{
public:
	DECLARE_CLASS(CWeaponM60Experimental, CBase_CSS_HL2_Rifle);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CWeaponM60Experimental(void);

	virtual CSS_HL2_WeaponActClass		GetCSSWeaponActClass() { return CSSHL2_WEAPON_AR1; }

	virtual float GetViewKickBase() { return 0.0f; }

	virtual const Vector& GetBulletSpread(void)
	{
		static const Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	virtual int	GetMinBurst() { return 7; }
	virtual int	GetMaxBurst() { return 10; }

	virtual float GetFireRate(void) { return 0.08f; }
};

IMPLEMENT_NETWORKCLASS_DT(CWeaponM60Experimental, DT_WeaponM60Experimental)
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS(weapon_m60_experimental, CWeaponM60Experimental);
#if PRECACHE_REGISTER_CSS_WEAPONS == 1
PRECACHE_WEAPON_REGISTER(weapon_m60_experimental);
#endif

BEGIN_DATADESC(CWeaponM60Experimental)
END_DATADESC()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA(CWeaponM60Experimental)
END_PREDICTION_DATA()
#endif

//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
CWeaponM60Experimental::CWeaponM60Experimental(void)
{
	m_fMinRange1 = 24;
	m_fMaxRange1 = 1500;
	m_fMinRange2 = 24;
	m_fMaxRange2 = 200;

	m_bFiresUnderwater = true;
}
