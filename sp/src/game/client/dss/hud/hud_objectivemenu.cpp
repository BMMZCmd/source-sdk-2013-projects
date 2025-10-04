#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "iclientmode.h"
#include "cdll_client_int.h"
#include "vgui/ISurface.h"
#include "vgui/IVGui.h"
#include "hud_objectivemenu.h"

#include "tier0/memdbgon.h"

using namespace vgui;

DECLARE_HUDELEMENT(CHudObjectives);

CHudObjectives::CHudObjectives(const char* pElementName) : CHudElement(pElementName), BaseClass(NULL)
{
	Panel* pParent = g_pClientMode->GetViewport();
	SetParent(pParent);

	m_pObjectiveLabel = new Label(this, "ObjectiveLabel", "");
	m_pObjectiveLabel->SetFont(scheme()->GetIScheme(GetScheme())->GetFont("Trebuchet24", true));
	m_pObjectiveLabel->SetFgColor(Color(255, 255, 255, 255));
	m_pObjectiveLabel->SetBgColor(Color(0, 0, 0, 150));
	m_pObjectiveLabel->SetContentAlignment(Label::a_center);
	m_pObjectiveLabel->SetVisible(false);

	m_bVisible = false;
	m_szObjectiveText[0] = '\0';
}

void CHudObjectives::Init()
{
	Reset();
}

void CHudObjectives::Reset()
{
	HideObjective();
}

void CHudObjectives::OnThink()
{
	if (m_bVisible)
	{
		m_pObjectiveLabel->SetText(m_szObjectiveText);
		m_pObjectiveLabel->SetVisible(true);

		int wide = ScreenWidth() * 0.6f;
		int tall = 40;
		int x = (ScreenWidth() - wide) / 2;
		int y = ScreenHeight() * 0.1f;

		m_pObjectiveLabel->SetBounds(x, y, wide, tall);
	}
	else
	{
		m_pObjectiveLabel->SetVisible(false);
	}
}

bool CHudObjectives::ShouldDraw()
{
	return m_bVisible;
}

void CHudObjectives::Paint()
{
	// nothing custom here, label handles all paint
}

void CHudObjectives::SetObjectiveText(const char* text)
{
	Q_strncpy(m_szObjectiveText, text, sizeof(m_szObjectiveText));
	m_bVisible = true;
}

void CHudObjectives::HideObjective()
{
	m_szObjectiveText[0] = '\0';
	m_bVisible = false;
}
