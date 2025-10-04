#pragma once

#include "hudelement.h"
#include <vgui_controls/Panel.h>
#include <vgui_controls/Label.h>

using namespace vgui;

class CHudObjectives : public CHudElement, public Panel
{
	DECLARE_CLASS_SIMPLE(CHudObjectives, Panel);

public:
	CHudObjectives(const char *pElementName);
	void Init() override;
	void Reset() override;
	void OnThink() override;
	bool ShouldDraw() override;
	void Paint() override;

	void SetObjectiveText(const char *text);
	void HideObjective();

private:
	Label *m_pObjectiveLabel;
	char m_szObjectiveText[512];
	bool m_bVisible;
};
