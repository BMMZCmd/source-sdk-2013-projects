#include "cbase.h"
#include "basehlcombatweapon.h"
#include "soundent.h"
#include "npcevent.h"
#include "ai_basenpc.h"
#include "tier0/memdbgon.h"

#if 0
class CWeaponM76 : public CBaseHLCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponM76, CBaseHLCombatWeapon);

	CWeaponM76();

	DECLARE_SERVERCLASS()

	void PrimaryAttack(void);

	//do later
	//void FireNPCPrimaryAttack(CBaseCombatCharacter* pOperator, Vector& vecShootOrigin, Vector& vecShootDir);
	//void Operator_ForceNPCFire(CBaseCombatCharacter* pOperator, bool bSecondary);
	//void Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

	float	GetFireRate(void)  { return 2.0f; }

	int		CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual const Vector& GetBulletSpread(void)
	{
		static Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	DECLARE_DATADESC();
};

IMPLEMENT_SERVERCLASS_ST(CWeaponM76, DT_WeaponM76)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_m76, CWeaponM76);
PRECACHE_WEAPON_REGISTER(weapon_m76);

BEGIN_DATADESC(CWeaponM76)
END_DATADESC()

CWeaponM76::CWeaponM76() {}

void CWeaponM76::PrimaryAttack(void)
{
	BaseClass::PrimaryAttack();
	WeaponSound(SINGLE);
}

/*
void CWeaponM76::FireNPCPrimaryAttack(CBaseCombatCharacter* pOperator, Vector& vecShootOrigin, Vector& vecShootDir)
{
	WeaponSoundRealtime(SINGLE_NPC);

	CSoundEnt::InsertSound(SOUND_COMBAT | SOUND_CONTEXT_GUNFIRE, pOperator->GetAbsOrigin(), SOUNDENT_VOLUME_MACHINEGUN, 0.2, pOperator, SOUNDENT_CHANNEL_WEAPON, pOperator->GetEnemy());
	pOperator->FireBullets(1, vecShootOrigin, vecShootDir, VECTOR_CONE_PRECALCULATED,
		MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 2, entindex(), 0);

	pOperator->DoMuzzleFlash();
	m_iClip1--;
}

void CWeaponM76::Operator_ForceNPCFire(CBaseCombatCharacter* pOperator, bool bSecondary)
{
	// Ensure we have enough rounds in the clip
	m_iClip1++;

	Vector vecShootOrigin, vecShootDir;
	QAngle	angShootDir;
	GetAttachment(LookupAttachment("muzzle"), vecShootOrigin, angShootDir);
	AngleVectors(angShootDir, &vecShootDir);
	FireNPCPrimaryAttack(pOperator, vecShootOrigin, vecShootDir);
}

void CWeaponM76::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
{
	switch (pEvent->event)
	{
	case EVENT_WEAPON_M76:
	{
		Vector vecShootOrigin;
		QAngle angDiscard;

		// check if the anim event specifies an attachment
		if ((pEvent->options == NULL) || (pEvent->options[0] == '\0') ||
			(!pOperator->GetAttachment(pEvent->options, vecShootOrigin, angDiscard)))
		{
			vecShootOrigin = pOperator->Weapon_ShootPosition();
		}

		// get NPC pointer if this is an NPC
		CAI_BaseNPC* npc = pOperator->MyNPCPointer();
		ASSERT(npc != NULL);

		// calculate shooting direction
		Vector vecShootDir = npc->GetActualShootTrajectory(vecShootOrigin);
		FireNPCPrimaryAttack(pOperator, vecShootOrigin, vecShootDir);
	}
	break;

	default:
		BaseClass::Operator_HandleAnimEvent(pEvent, pOperator);
		break;
	}
	Msg("NPC fired!\n");

}
*/
#endif