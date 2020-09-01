//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//

#include "cbase.h"
#include "weapon_sdkbase.h"

#if defined( CLIENT_DLL )

#define CWeaponSawnoff C_WeaponSawnoff
#include "c_sdk_player.h"

#else

#include "sdk_player.h"

#endif


class CWeaponSawnoff : public CWeaponSDKBase
{
public:
	DECLARE_CLASS(CWeaponSawnoff, CWeaponSDKBase);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_ACTTABLE();

	CWeaponSawnoff();

	virtual SDKWeaponID GetWeaponID(void) const { return SDK_WEAPON_SAWNOFF; }
	virtual int GetFireMode() const { return FM_SEMIAUTOMATIC; }
	virtual void PrimaryAttack();


private:

	CWeaponSawnoff(const CWeaponSawnoff&);
};

IMPLEMENT_NETWORKCLASS_ALIASED(WeaponSawnoff, DT_WeaponSawnoff)

BEGIN_NETWORK_TABLE(CWeaponSawnoff, DT_WeaponSawnoff)
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA(CWeaponSawnoff)
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS(weapon_sawnoff, CWeaponSawnoff);
PRECACHE_WEAPON_REGISTER(weapon_sawnoff);

void CWeaponSawnoff::PrimaryAttack()
{
	CSDKPlayer* pPlayer = GetPlayerOwner();
	if (!pPlayer)
		return;

	// don't fire underwater
	if (pPlayer->GetWaterLevel() == 3)
	{
		PlayEmptySound();
		m_flNextPrimaryAttack = gpGlobals->curtime + 0.15;
		return;
	}
	bool doPunch = true;
	if (m_iClip1 <= 0)
		doPunch = false;

	BaseClass::PrimaryAttack();

	if (doPunch)
	{
	//	m_iInSpecialReload = 0;

		// Update punch angles.
		QAngle angle = pPlayer->GetPunchAngle();

		if (pPlayer->GetFlags() & FL_ONGROUND)
		{
			angle.x -= SharedRandomInt("ShotgunPunchAngleGround", 4, 6);
		}
		else
		{
			angle.x -= SharedRandomInt("ShotgunPunchAngleAir", 8, 11);
		}

		pPlayer->SetPunchAngle(angle);
	}
}


CWeaponSawnoff::CWeaponSawnoff()
{
}

//Tony; todo; add ACT_MP_PRONE* activities, so we have them.
acttable_t CWeaponSawnoff::m_acttable[] =
{
	{ ACT_MP_STAND_IDLE,					ACT_DOD_STAND_IDLE_PISTOL,				false },
	{ ACT_MP_CROUCH_IDLE,					ACT_DOD_CROUCH_IDLE_PISTOL,				false },
	{ ACT_MP_PRONE_IDLE,					ACT_DOD_PRONE_AIM_PISTOL,				false },

	{ ACT_MP_RUN,							ACT_DOD_RUN_AIM_PISTOL,					false },
	{ ACT_MP_WALK,							ACT_DOD_WALK_AIM_PISTOL,				false },
	{ ACT_MP_CROUCHWALK,					ACT_DOD_CROUCHWALK_AIM_PISTOL,			false },
	{ ACT_MP_PRONE_CRAWL,					ACT_DOD_PRONEWALK_IDLE_PISTOL,			false },
	{ ACT_SPRINT,							ACT_DOD_SPRINT_IDLE_PISTOL,				false },

	{ ACT_MP_ATTACK_STAND_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_PISTOL,			false },
	{ ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_PISTOL,			false },
	{ ACT_MP_ATTACK_PRONE_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_PRONE_PISTOL,		false },

	{ ACT_MP_RELOAD_STAND,					ACT_DOD_RELOAD_PISTOL,					false },
	{ ACT_MP_RELOAD_CROUCH,					ACT_DOD_RELOAD_CROUCH_PISTOL,			false },
	{ ACT_MP_RELOAD_PRONE,					ACT_DOD_RELOAD_PRONE_PISTOL,			false },
};

IMPLEMENT_ACTTABLE(CWeaponSawnoff);

