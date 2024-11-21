#include "cbase.h"
#include "basehlcombatweapon.h"
#include "IEffects.h"
#include "in_buttons.h"

//last include blah blah blah
#include "tier0/memdbgon.h"

#define BLOWTORCH_RANGE 150.0f
#define BLOWTORCH_DAMAGE 10.0f

class CWeaponBlowtorch : public CBaseHLCombatWeapon
{
	DECLARE_DATADESC();

public:
	DECLARE_CLASS(CWeaponBlowtorch, CBaseHLCombatWeapon);

	CWeaponBlowtorch(void);

	DECLARE_SERVERCLASS();

	void Precache(void);
	void PrimaryAttack(void);
	void ItemPostFrame(void);

	//Activity GetPrimaryAttackActivity(void);

	void ImpactEffect(trace_t &traceHit);

	void BTorchSpark(trace_t *traceHit);

private:
	float m_flNextAttackTime;
};

IMPLEMENT_SERVERCLASS_ST(CWeaponBlowtorch, DT_WeaponBlowtorch)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_blowtorch, CWeaponBlowtorch);
PRECACHE_WEAPON_REGISTER(weapon_blowtorch);

BEGIN_DATADESC(CWeaponBlowtorch)
END_DATADESC()

CWeaponBlowtorch::CWeaponBlowtorch(void)
{
	m_flNextAttackTime = gpGlobals->curtime;
}

void CWeaponBlowtorch::Precache(void)
{
	PrecacheScriptSound("Weapon_Blowtorch.Fire");
	BaseClass::Precache();
}

/*
Activity CWeaponBlowtorch::GetPrimaryAttackActivity(void)
{
	return 0;
}
*/

void CWeaponBlowtorch::PrimaryAttack(void)
{
	if (gpGlobals->curtime < m_flNextAttackTime)
		return;

	m_flNextAttackTime = gpGlobals->curtime + 0.1f;

	CBasePlayer* pPlayer = dynamic_cast<CBasePlayer*>(GetOwner());
	if (pPlayer) {
		Vector vecSrc = pPlayer->Weapon_ShootPosition();

		// Instead of using EyeVectors, get the player's angles and calculate the forward vector
		QAngle angles;

		Vector vecDirection;
		AngleVectors(GetAbsAngles(), &vecDirection);

		angles = GetAbsAngles();
		Vector vecAiming;
		AngleVectors(angles, &vecAiming);  // Convert angles to forward vector

		Vector vecEnd = vecSrc + vecAiming * BLOWTORCH_RANGE;

		CTraceFilterSkipTwoEntities traceFilter(this, pPlayer, COLLISION_GROUP_NONE);
		trace_t tr;
		UTIL_TraceLine(vecSrc, vecEnd, MASK_SHOT, &traceFilter, &tr);
		
		//VectorMA(vecSrc, 50, vecDirection, vecEnd);
		CBaseEntity *pHurt = pPlayer->CheckTraceHullAttack(vecSrc, vecEnd,
			Vector(-16, -16, -16), Vector() * BLOWTORCH_RANGE, BLOWTORCH_DAMAGE, DMG_BURN, 0.75);

		// did I hit someone?
		if (pHurt)
		{
			//Msg("damaged\n");
			UTIL_TraceLine(vecSrc, vecEnd, MASK_SHOT_HULL, pPlayer, COLLISION_GROUP_NONE, &tr);
			//UTIL_AddDebugLine(vecSrc, vecEnd, true, true);
			ImpactEffect(tr);
			BTorchSpark(&tr);

			EmitSound("Weapon_Blowtorch.Fire");

			SendWeaponAnim(ACT_VM_PRIMARYATTACK);
			m_flTimeWeaponIdle = gpGlobals->curtime + SequenceDuration();
		}
		else
		{
			//Msg("miss\n");

			if (tr.m_pEnt)
			{
				CTakeDamageInfo dmgInfo(this, pPlayer, BLOWTORCH_DAMAGE, DMG_BURN);
				tr.m_pEnt->TakeDamage(dmgInfo);

				UTIL_TraceLine(vecSrc, vecEnd, MASK_SHOT_HULL, pPlayer, COLLISION_GROUP_NONE, &tr);
				//UTIL_AddDebugLine(vecSrc, vecEnd, true, true);
				ImpactEffect(tr);
				BTorchSpark(&tr);
			}
		}
	}
	else {
		//i wanna log ig
		DevMsg("Owner is not a player!\n");
	}
}

void CWeaponBlowtorch::ImpactEffect(trace_t &traceHit)
{

	//FIXME: need new decals
	UTIL_DecalTrace(&traceHit, "RedGlowFade");

}

void CWeaponBlowtorch::BTorchSpark(trace_t *traceHit)
{

	g_pEffects->Sparks(traceHit->endpos, 1, 1.2, &traceHit->plane.normal);

}

void CWeaponBlowtorch::ItemPostFrame(void)
{
	// check if the owner is still holding down the attack button
	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());
	if (pPlayer && pPlayer->IsAlive() && pPlayer->GetActiveWeapon() == this)
	{
		if (pPlayer->m_nButtons & IN_ATTACK)
		{
			// Call PrimaryAttack if the attack button is held
			PrimaryAttack();
			GetPrimaryAttackActivity();
		}
	}

	BaseClass::ItemPostFrame(); // call the base class version
}