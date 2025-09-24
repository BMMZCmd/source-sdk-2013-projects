#ifndef WEAPON_SMOKEGRENADE_H
#define WEAPON_SMOKEGRENADE_H
#ifdef _WIN32
#pragma once
#endif

#include "basehlcombatweapon.h"

class CWeaponSmokeGrenade : public CBaseHLCombatWeapon
{
public:
    DECLARE_CLASS(CWeaponSmokeGrenade, CBaseHLCombatWeapon);
    DECLARE_SERVERCLASS();
    DECLARE_DATADESC();

    CWeaponSmokeGrenade();

    void Precache(void) override;
    void PrimaryAttack(void) override;
    void Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

    DECLARE_ACTTABLE();

private:
    string_t m_iszSmokeEffect;
};

#endif
