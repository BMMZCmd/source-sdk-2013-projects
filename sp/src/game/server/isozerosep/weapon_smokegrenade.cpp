#include "cbase.h"
#include "weapon_smokegrenade.h"
#include "tier0/memdbgon.h"
#include "particle_parse.h"
#include <soundent.h>
#include <npcevent.h>

IMPLEMENT_SERVERCLASS_ST(CWeaponSmokeGrenade, DT_WeaponSmokeGrenade)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_smokegrenade, CWeaponSmokeGrenade);
PRECACHE_WEAPON_REGISTER(weapon_smokegrenade);

BEGIN_DATADESC(CWeaponSmokeGrenade)
END_DATADESC()

CWeaponSmokeGrenade::CWeaponSmokeGrenade()
{
    m_iszSmokeEffect = MAKE_STRING("striderbuster_explode_smoke");
}

void CWeaponSmokeGrenade::Precache(void)
{
    PrecacheParticleSystem("striderbuster_explode_smoke");
    PrecacheScriptSound("Weapon_SmokeGrenade.Throw");
}

void CWeaponSmokeGrenade::PrimaryAttack(void)
{
    // Ensure we have grenades to throw
    if (m_iClip1 <= 0)
    {
        return;
    }

    Vector vecForward;
    QAngle angThrow;

    // Get the player's forward vector and throwing angle
    GetVectors(&vecForward, NULL, NULL);
    angThrow = GetOwner()->EyeAngles();

    // Create the smoke grenade entity
    CBaseEntity* pGrenade = CreateEntityByName("grenade_smoke");
    pGrenade->SetAbsOrigin(GetOwner()->GetAbsOrigin() + vecForward * 10.0f);
    pGrenade->SetAbsVelocity(vecForward * 1000.0f);

    // Spawn and activate the grenade
    DispatchSpawn(pGrenade);
    pGrenade->Activate();

    // Create the smoke effect at the grenade location
    DispatchParticleEffect("striderbuster_explode_smoke", pGrenade->GetAbsOrigin(), angThrow);

    // Emit the throw sound
    EmitSound("Weapon_SmokeGrenade.Throw");

    // Decrease ammo for the grenade
    m_iClip1--;

    // Set idle time for the weapon to avoid spam
    m_flNextPrimaryAttack = gpGlobals->curtime + 1.0f;
}

void CWeaponSmokeGrenade::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
{
    CBasePlayer* pOwner = ToBasePlayer(GetOwner());
    bool fThrewGrenade = false;

    switch (pEvent->event)
    {
    case EVENT_WEAPON_THROW: // Normal throw
        PrimaryAttack();
        fThrewGrenade = true;
        break;

    default:
        BaseClass::Operator_HandleAnimEvent(pEvent, pOperator);
        break;
    }

#define SMOKE_THROW_DELAY 0.5
    if (fThrewGrenade)
    {
        // Set cooldowns after throwing
        m_flNextPrimaryAttack = gpGlobals->curtime + SMOKE_THROW_DELAY;
        m_flTimeWeaponIdle = FLT_MAX;

        // Emit sound to alert nearby enemies (optional)
        if (pOwner)
        {
            Vector vecSrc = pOwner->Weapon_ShootPosition();
            Vector vecDir;

            AngleVectors(pOwner->EyeAngles(), &vecDir);

            trace_t tr;
            UTIL_TraceLine(vecSrc, vecSrc + vecDir * 1024, MASK_SOLID_BRUSHONLY, pOwner, COLLISION_GROUP_NONE, &tr);

            CSoundEnt::InsertSound(SOUND_DANGER_SNIPERONLY, tr.endpos, 384, 0.2f, pOwner);
        }
    }
}
