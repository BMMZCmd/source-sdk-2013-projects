//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "c_weapon__stubs.h"
#include "basehlcombatweapon_shared.h"
#include "c_basehlcombatweapon.h"
#include "weapon_css_base.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

STUB_WEAPON_CLASS( cycler_weapon, WeaponCycler, C_BaseCombatWeapon );


STUB_WEAPON_CLASS( weapon_binoculars, WeaponBinoculars, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_bugbait, WeaponBugBait, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_flaregun, Flaregun, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_annabelle, WeaponAnnabelle, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_gauss, WeaponGaussGun, C_BaseHLCombatWeapon );

STUB_WEAPON_CLASS( weapon_cubemap, WeaponCubemap, C_BaseCombatWeapon );

STUB_WEAPON_CLASS( weapon_alyxgun, WeaponAlyxGun, C_HLSelectFireMachineGun );
STUB_WEAPON_CLASS( weapon_citizenpackage, WeaponCitizenPackage, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_citizensuitcase, WeaponCitizenSuitcase, C_WeaponCitizenPackage );


#ifndef HL2MP

STUB_WEAPON_CLASS( weapon_ar2, WeaponAR2, C_HLMachineGun );
STUB_WEAPON_CLASS( weapon_frag, WeaponFrag, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_rpg, WeaponRPG, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_pistol, WeaponPistol, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_shotgun, WeaponShotgun, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_smg1, WeaponSMG1, C_HLSelectFireMachineGun );
STUB_WEAPON_CLASS( weapon_357, Weapon357, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_crossbow, WeaponCrossbow, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_slam, Weapon_SLAM, C_BaseHLCombatWeapon );
STUB_WEAPON_CLASS( weapon_crowbar, WeaponCrowbar, C_BaseHLBludgeonWeapon );

#ifdef HL2_EPISODIC
STUB_WEAPON_CLASS( weapon_hopwire, WeaponHopwire, C_BaseHLCombatWeapon );
//STUB_WEAPON_CLASS( weapon_proto1, WeaponProto1, C_BaseHLCombatWeapon );
#endif
#ifdef HL2_LOSTCOAST
STUB_WEAPON_CLASS( weapon_oldmanharpoon, WeaponOldManHarpoon, C_WeaponCitizenPackage );
#endif

#ifdef CSS_WEAPONS_IN_HL2
// Pistols
STUB_WEAPON_CLASS(weapon_css_glock, WeaponCSSGlock, CBase_CSS_HL2_BurstableWeapon<CBase_CSS_HL2_Pistol>);
STUB_WEAPON_CLASS(weapon_css_usp, WeaponCSSUSP, CBase_CSS_HL2_SilencedWeapon<CBase_CSS_HL2_Pistol>);
STUB_WEAPON_CLASS(weapon_css_p228, WeaponCSSP228, CBase_CSS_HL2_Pistol);
STUB_WEAPON_CLASS(weapon_css_deagle, WeaponCSSDeagle, CBase_CSS_HL2_Pistol);
STUB_WEAPON_CLASS(weapon_css_fiveseven, WeaponCSSFiveSeveN, CBase_CSS_HL2_Pistol);
STUB_WEAPON_CLASS(weapon_css_elite, WeaponCSSElite, CBase_CSS_HL2_Pistol);

// SMGs (Sub-Machine Guns/Small Machine Guns)
STUB_WEAPON_CLASS(weapon_css_tmp, WeaponCSSTMP, CBase_CSS_HL2_SMG);
STUB_WEAPON_CLASS(weapon_css_mp5navy, WeaponCSSMP5Navy, CBase_CSS_HL2_SMG);
STUB_WEAPON_CLASS(weapon_css_ump45, WeaponCSSUMP45, CBase_CSS_HL2_SMG);
STUB_WEAPON_CLASS(weapon_css_p90, WeaponCSSP90, CBase_CSS_HL2_SMG);
STUB_WEAPON_CLASS(weapon_css_mac10, WeaponCSSMac10, CBase_CSS_HL2_SMG);

// Shotguns
STUB_WEAPON_CLASS(weapon_css_m3, WeaponCSSM3, CBase_CSS_HL2_Shotgun);
STUB_WEAPON_CLASS(weapon_css_xm1014, WeaponCSSXM1014, CBase_CSS_HL2_Shotgun);

// Rifles
STUB_WEAPON_CLASS(weapon_css_famas, WeaponCSSFamas, CBase_CSS_HL2_BurstableWeapon<CBase_CSS_HL2_Rifle>);
STUB_WEAPON_CLASS(weapon_css_aug, WeaponCSSAUG, CBase_CSS_HL2_ScopeableWeapon<CBase_CSS_HL2_Rifle>);
STUB_WEAPON_CLASS(weapon_css_sg552, WeaponCSS_SG552, CBase_CSS_HL2_ScopeableWeapon<CBase_CSS_HL2_Rifle>);
STUB_WEAPON_CLASS(weapon_css_galil, WeaponCSSGalil, CBase_CSS_HL2_Rifle);
STUB_WEAPON_CLASS(weapon_css_ak47, WeaponCSSAK47, CBase_CSS_HL2_Rifle);
STUB_WEAPON_CLASS(weapon_css_scout, WeaponCSS_Scout, CBase_CSS_HL2_SniperRifle);
STUB_WEAPON_CLASS(weapon_css_sg550, WeaponCSS_SG550, CBase_CSS_HL2_SniperRifle);
STUB_WEAPON_CLASS(weapon_css_awp, WeaponCSSAWP, CBase_CSS_HL2_SniperRifle);
STUB_WEAPON_CLASS(weapon_css_g3sg1, WeaponCSSG3SG1, CBase_CSS_HL2_SniperRifle);

// MISC (Machine Gun)
STUB_WEAPON_CLASS(weapon_css_m249, WeaponCSSM249, CBase_CSS_HL2_Rifle);
//done

#endif

#ifdef DSS
// DSS stuff
STUB_WEAPON_CLASS(weapon_blowtorch, WeaponBlowtorch, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_briefcase, WeaponBriefcase, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_camera, WeaponCamera, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_radio, WeaponRadio, C_BaseHLCombatWeapon);
STUB_WEAPON_CLASS(weapon_m60, WeaponM60, CBase_CSS_HL2_Rifle);
// what do you think?
#endif

#endif
