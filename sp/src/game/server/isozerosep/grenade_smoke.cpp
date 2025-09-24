#include "cbase.h"
#include "grenade_smoke.h"
#include "tier0/memdbgon.h"
#include "particle_parse.h"

LINK_ENTITY_TO_CLASS(grenade_smoke, CGrenadeSmoke);

CGrenadeSmoke::CGrenadeSmoke()
{
    SetMoveType(MOVETYPE_FLY);
    SetSolid(SOLID_BBOX);
    m_bIsSmokeGrenade = true;
}

void CGrenadeSmoke::Spawn(void)
{
    Precache();
    SetModel("models/props_c17/oildrum001.mdl");
    SetSize(Vector(-4, -4, -4), Vector(4, 4, 4));

    // Add smoke when the grenade explodes
    SetThink(&CGrenadeSmoke::Detonate);
    SetNextThink(gpGlobals->curtime + 3.0f);  // time to detonate after 3 seconds
}

void CGrenadeSmoke::Precache(void)
{
    PrecacheModel("models/props_c17/oildrum001.mdl");
    PrecacheParticleSystem("striderbuster_explode_smoke");
}

void CGrenadeSmoke::Detonate(void)
{
    // Create the smoke when grenade detonates
    DispatchParticleEffect("striderbuster_explode_smoke", GetAbsOrigin(), QAngle(0, 0, 0));

    // Optional: Delay before removal to let smoke effect play out
    SetThink(&CGrenadeSmoke::SUB_Remove);
    SetNextThink(gpGlobals->curtime + 0.1f);  // Slight delay before removal
}
