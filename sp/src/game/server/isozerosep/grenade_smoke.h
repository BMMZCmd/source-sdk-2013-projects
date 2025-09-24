#ifndef GRENADE_SMOKE_H
#define GRENADE_SMOKE_H
#ifdef _WIN32
#pragma once
#endif

#include "basegrenade_shared.h"

class CGrenadeSmoke : public CBaseGrenade
{
public:
    DECLARE_CLASS(CGrenadeSmoke, CBaseGrenade);

    CGrenadeSmoke();

    void Spawn(void) override;
    void Precache(void) override;
    void Detonate(void) override;

private:
    bool m_bIsSmokeGrenade;
};

#endif
