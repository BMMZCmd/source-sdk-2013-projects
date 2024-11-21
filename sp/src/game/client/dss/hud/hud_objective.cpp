#include "vgui/ISurface.h"
#include "vgui_controls/Panel.h"
#include "hudelement.h"
#include "iclientmode.h"
#include "hud.h"

#include <vector>
#include <string>
#include <locale>
#include <codecvt>

#include "tier0/memdbgon.h"

std::wstring ConvertToWString(const char* text)
{
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(text);
}

using namespace vgui;

DECLARE_HUDELEMENT(CHudObjective);

class CHudObjective : public CHudElement, public Panel
{
    DECLARE_CLASS_SIMPLE(CHudObjective, Panel);
public:
    CHudObjective(const char* pElementName);

protected:
    virtual void Paint();
    void AppendObjective(const char* newObjective);
    void OnAddObjective(const char* newObjective);

private:
    std::vector<std::string> m_objectiveList;
};

CHudObjective::CHudObjective(const char* pElementName) : CHudElement(pElementName), BaseClass(NULL, "HudObjective") 
{
    Panel* pParent = g_pClientMode->GetViewport();
    SetParent(pParent);
}

void CHudObjective::Paint() 
{
    IScheme* pScheme = scheme()->GetIScheme(GetScheme());
    HFont hFont = pScheme->GetFont("DefaultSmall");

    surface()->DrawSetTextFont(hFont);
    surface()->DrawSetTextColor(15, 166, 30, 200);
    int yPos = 50;
    for (size_t i = 0; i < m_objectiveList.size(); ++i)
    {
        // convert to wstring
        std::string numberedObjective = std::to_string(i + 1) + ". " + m_objectiveList[i];
        std::wstring wideObjective = ConvertToWString(numberedObjective.c_str());

        surface()->DrawSetTextPos(50, yPos); // x, y position
        surface()->DrawPrintText(wideObjective.c_str(), wideObjective.length());
        yPos += 20; // move to next line
    }
}

void CHudObjective::AppendObjective(const char* newObjective)
{
    m_objectiveList.push_back(newObjective);
    InvalidateLayout();
    Repaint();
}

void CHudObjective::OnAddObjective(const char* newObjective)
{
    AppendObjective(newObjective);
}