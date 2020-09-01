//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//

#include "cbase.h"
#include "weapon_sdkbase.h"

#if defined( CLIENT_DLL )

	#define CWeaponAK47 C_WeaponAK47
	#include "c_sdk_player.h"

#else

	#include "sdk_player.h"

#endif


class CWeaponAK47 : public CWeaponSDKBase
{
public:
	DECLARE_CLASS( CWeaponAK47, CWeaponSDKBase );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_ACTTABLE();
	
	CWeaponAK47();

	virtual SDKWeaponID GetWeaponID( void ) const		{ return SDK_WEAPON_AK47; }

private:

	CWeaponAK47( const CWeaponAK47 & );
};

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponAK47, DT_WeaponAK47 )

BEGIN_NETWORK_TABLE( CWeaponAK47, DT_WeaponAK47 )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponAK47 )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( weapon_ak47, CWeaponAK47 );
PRECACHE_WEAPON_REGISTER( weapon_ak47 );



CWeaponAK47::CWeaponAK47()
{
}

//Tony; todo; add ACT_MP_PRONE* activities, so we have them.
acttable_t CWeaponAK47::m_acttable[] = 
{
	{ ACT_MP_STAND_IDLE,					ACT_DOD_STAND_IDLE_TOMMY,				false },
	{ ACT_MP_CROUCH_IDLE,					ACT_DOD_CROUCH_IDLE_TOMMY,				false },
	{ ACT_MP_PRONE_IDLE,					ACT_DOD_PRONE_AIM_TOMMY,				false },

	{ ACT_MP_RUN,							ACT_DOD_RUN_AIM_TOMMY,					false },
	{ ACT_MP_WALK,							ACT_DOD_WALK_AIM_TOMMY,					false },
	{ ACT_MP_CROUCHWALK,					ACT_DOD_CROUCHWALK_AIM_TOMMY,			false },
	{ ACT_MP_PRONE_CRAWL,					ACT_DOD_PRONEWALK_IDLE_TOMMY,			false },
	{ ACT_SPRINT,							ACT_DOD_SPRINT_IDLE_TOMMY,				false },

	{ ACT_MP_ATTACK_STAND_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_TOMMY,			false },
	{ ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_TOMMY,			false },
	{ ACT_MP_ATTACK_PRONE_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_PRONE_TOMMY,		false },
	{ ACT_MP_ATTACK_STAND_SECONDARYFIRE,	ACT_DOD_SECONDARYATTACK_TOMMY,			false },
	{ ACT_MP_ATTACK_CROUCH_SECONDARYFIRE,	ACT_DOD_SECONDARYATTACK_CROUCH_TOMMY,	false },
	{ ACT_MP_ATTACK_PRONE_SECONDARYFIRE,	ACT_DOD_SECONDARYATTACK_PRONE_TOMMY,	false },

	{ ACT_MP_RELOAD_STAND,					ACT_DOD_RELOAD_TOMMY,					false },
	{ ACT_MP_RELOAD_CROUCH,					ACT_DOD_RELOAD_CROUCH_TOMMY,			false },
	{ ACT_MP_RELOAD_PRONE,					ACT_DOD_RELOAD_PRONE_TOMMY,				false },

};

IMPLEMENT_ACTTABLE( CWeaponAK47 );

