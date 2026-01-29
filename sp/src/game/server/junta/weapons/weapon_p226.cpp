#include "cbase.h"
#include "basehlcombatweapon.h"
#include "soundent.h"
#include "npcevent.h"
#include "ai_basenpc.h"
#include "tier0/memdbgon.h"

#include "in_buttons.h"

class CWeaponP226 : public CBaseHLCombatWeapon
{
public:
	DECLARE_CLASS(CWeaponP226, CBaseHLCombatWeapon);

	CWeaponP226();

	DECLARE_SERVERCLASS()

	void PrimaryAttack(void);

	void ItemPostFrame(void);

	float	GetFireRate(void) { return 0.109f; }

	//do later
	//void FireNPCPrimaryAttack(CBaseCombatCharacter* pOperator, Vector& vecShootOrigin, Vector& vecShootDir);
	//void Operator_ForceNPCFire(CBaseCombatCharacter* pOperator, bool bSecondary);
	//void Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator);

	int		CapabilitiesGet(void) { return bits_CAP_WEAPON_RANGE_ATTACK1; }

	virtual const Vector& GetBulletSpread(void)
	{
		static Vector cone = VECTOR_CONE_5DEGREES;
		return cone;
	}

	DECLARE_DATADESC();

private:
	// Tracks if the primary attack button is held after firing.
	bool m_bIsPrimaryAttackHeld;
};

IMPLEMENT_SERVERCLASS_ST(CWeaponP226, DT_WeaponP226)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS(weapon_p226, CWeaponP226);
PRECACHE_WEAPON_REGISTER(weapon_p226);

BEGIN_DATADESC(CWeaponP226)
DEFINE_FIELD(m_bIsPrimaryAttackHeld, FIELD_BOOLEAN),
END_DATADESC()

CWeaponP226::CWeaponP226() : m_bIsPrimaryAttackHeld(false) {}

void CWeaponP226::ItemPostFrame(void)
{
	CBasePlayer* pOwner = ToBasePlayer(GetOwner());
	if (!pOwner)
	{
		BaseClass::ItemPostFrame();
		return;
	}

	if (pOwner->m_nButtons & IN_ATTACK)
	{
		if (m_flNextPrimaryAttack <= gpGlobals->curtime)
		{
			// Fire only if the button wasn't held from the previous frame.
			if (!m_bIsPrimaryAttackHeld)
			{
				PrimaryAttack();
			}
		}
	}
	else
	{
		// Reset the lock when the button is released.
		m_bIsPrimaryAttackHeld = false;
	}

	BaseClass::ItemPostFrame();
}

void CWeaponP226::PrimaryAttack(void)
{
	// Prevents firing if the button is still held down from a previous shot.
	if (m_bIsPrimaryAttackHeld)
	{
		return;
	}

	CBasePlayer* pPlayer = ToBasePlayer(GetOwner());

	if (!pPlayer)
	{
		return;
	}

	// 1. Check for no ammo/reload
	if (UsesClipsForAmmo1() && !m_iClip1)
	{
		// Let the base class handle the dry fire sound and reload attempt
		BaseClass::PrimaryAttack();
		// Lock the button even on dry fire to prevent spam
		m_bIsPrimaryAttackHeld = true;
		return;
	}

	// 2. We have ammo: Perform the single shot manually to control sound and rate

	pPlayer->DoMuzzleFlash();

	SendWeaponAnim(GetPrimaryAttackActivity());

	pPlayer->SetAnimation(PLAYER_ATTACK1);

	// Set next shot time using GetFireRate() now
	m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate();

	// Play the custom sound once
	WeaponSound(SINGLE);

	FireBulletsInfo_t info;
	info.m_vecSrc = pPlayer->Weapon_ShootPosition();
	info.m_vecDirShooting = pPlayer->GetAutoaimVector(AUTOAIM_SCALE_DEFAULT);
	info.m_iShots = 1; // Always 1 shot
	info.m_flDistance = MAX_TRACE_LENGTH;
	info.m_iAmmoType = m_iPrimaryAmmoType;
	info.m_iTracerFreq = 2;

	// Decrement the clip by 1
	if (UsesClipsForAmmo1())
	{
		m_iClip1--;
	}
	else
	{
		pPlayer->RemoveAmmo(1, m_iPrimaryAmmoType);
	}

#if !defined( CLIENT_DLL )
	info.m_vecSpread = pPlayer->GetAttackSpread(this);
#else
	info.m_vecSpread = GetActiveWeapon()->GetBulletSpread();
#endif // CLIENT_DLL

	pPlayer->FireBullets(info);

	// Add view kick
	AddViewKick();

	// Lock the weapon to prevent repeat fire until button release.
	m_bIsPrimaryAttackHeld = true;
}

/*
void CWeaponP226::FireNPCPrimaryAttack(CBaseCombatCharacter* pOperator, Vector& vecShootOrigin, Vector& vecShootDir)
{
	WeaponSoundRealtime(SINGLE_NPC);

	CSoundEnt::InsertSound(SOUND_COMBAT | SOUND_CONTEXT_GUNFIRE, pOperator->GetAbsOrigin(), SOUNDENT_VOLUME_MACHINEGUN, 0.2, pOperator, SOUNDENT_CHANNEL_WEAPON, pOperator->GetEnemy());
	pOperator->FireBullets(1, vecShootOrigin, vecShootDir, VECTOR_CONE_PRECALCULATED,
		MAX_TRACE_LENGTH, m_iPrimaryAmmoType, 2, entindex(), 0);

	pOperator->DoMuzzleFlash();
	m_iClip1--;
}

void CWeaponP226::Operator_ForceNPCFire(CBaseCombatCharacter* pOperator, bool bSecondary)
{
	// Ensure we have enough rounds in the clip
	m_iClip1++;

	Vector vecShootOrigin, vecShootDir;
	QAngle	angShootDir;
	GetAttachment(LookupAttachment("muzzle"), vecShootOrigin, angShootDir);
	AngleVectors(angShootDir, &vecShootDir);
	FireNPCPrimaryAttack(pOperator, vecShootOrigin, vecShootDir);
}

void CWeaponP226::Operator_HandleAnimEvent(animevent_t* pEvent, CBaseCombatCharacter* pOperator)
{
	switch (pEvent->event)
	{
	case EVENT_weapon_p226:
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
