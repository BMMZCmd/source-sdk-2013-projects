#include "cbase.h"
#include "basehlcombatweapon.h"
#include "soundent.h"
#include "npcevent.h"
#include "ai_basenpc.h"
#include "tier0/memdbgon.h"

#if 0
class CWeaponSSG69 : public CBaseHLCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponSSG69, CBaseHLCombatWeapon);

	CWeaponSSG69();

	DECLARE_SERVERCLASS()

	void PrimaryAttack(void);

	//do later
	//void FireNPCPrimaryAttack(CBaseCombatCharacter* pOperator, Vector& vecShootOrigin, Vector& vecShootDir);
	//void Operator_ForceNPCFire(CBaseCombatCharacter* pOperator, bool bSecondary);
	//void Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

	float	GetFireRate(void)  { return 4.0f; }

	int		CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual const Vector& GetBulletSpread(void)
	{
		static Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	DECLARE_DATADESC();
};

IMPLEMENT_SERVERCLASS_ST(CWeaponSSG69, DT_WeaponSSG69)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_ssg69, CWeaponSSG69);
PRECACHE_WEAPON_REGISTER(weapon_ssg69);

BEGIN_DATADESC(CWeaponSSG69)
END_DATADESC()

CWeaponSSG69::CWeaponSSG69() {}

void CWeaponSSG69::PrimaryAttack(void)
{
	BaseClass::PrimaryAttack();
	WeaponSound(SINGLE);
}

/*
void CWeaponSSG69::FireNPCPrimaryAttack(CBaseCombatCharacter* pOperator, Vector& vecShootOrigin, Vector& vecShootDir)
{
	WeaponSoundRealtime(SINGLE_NPC);

	CSoundEnt::InsertSound(SOUND_COMBAT | SOUND_CONTEXT_GUNFIRE, pOperator->GetAbsOrigin(), SOUNDENT_VOLUME_MACHINEGUN, 0.2, pOperator, SOUNDENT_CHANNEL_WEAPON, pOperator->GetEnemy());
	pOperator->FireBullets(1, vecShootOrigin, vecShootDir, VECTOR_CONE_PRECALCULATED,
		MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 2, entindex(), 0);

	pOperator->DoMuzzleFlash();
	m_iClip1--;
}

void CWeaponSSG69::Operator_ForceNPCFire(CBaseCombatCharacter* pOperator, bool bSecondary)
{
	// Ensure we have enough rounds in the clip
	m_iClip1++;

	Vector vecShootOrigin, vecShootDir;
	QAngle	angShootDir;
	GetAttachment(LookupAttachment("muzzle"), vecShootOrigin, angShootDir);
	AngleVectors(angShootDir, &vecShootDir);
	FireNPCPrimaryAttack(pOperator, vecShootOrigin, vecShootDir);
}

void CWeaponSSG69::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
{
	switch (pEvent->event)
	{
	case EVENT_WEAPON_SSG69:
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