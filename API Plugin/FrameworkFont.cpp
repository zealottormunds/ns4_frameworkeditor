#include "FrameworkFont.h"
#include "Utilities.h"

void FrameworkFont::LoadDefaultFont(__int64 a1)
{
	ccFileLoadListForUi * a2 = (ccFileLoadListForUi*)a1;

	std::string font = "data/ui/framework/font/";
	ccFileLoadListForUi::LoadTh(a2, (font + "font_an_s.xfbin").c_str());
	ccFileLoadListForUi::LoadTh(a2, (font + "font_oz_s.xfbin").c_str());
	ccFileLoadListForUi::LoadTh(a2, (font + "font_an.xfbin").c_str());
	ccFileLoadListForUi::LoadTh(a2, (font + "font_oz.xfbin").c_str());
	ccFileLoadListForUi::LoadTh(a2, (font + "font_number.xfbin").c_str());
	ccFileLoadListForUi::LoadTh(a2, (font + "font_symbol.xfbin").c_str());
}

void FrameworkFont::SetText(std::string text, float posx, float posy)
{
	m_text = text;
	*position = Vector3(posx, posy, 0);

	float ax = posx;
	float ay = posy;

	for (int x = 0; x < m_text.length(); x++)
	{
		char actualLetter = m_text[x];

		__int64 uiobj;
		
		if (x >= m_uiObjects.size())
		{
			uiobj = ccUiSimpleDraw::ccCreateSimpleDrawUi("");
			m_uiObjects.push_back(uiobj);
		}
		else
		{
			uiobj = m_uiObjects[x];
		}

		ccUiTaskBase::SetEnableTask(uiobj, 0);

		std::string letterPath = font + getCharacterPath(actualLetter);
		std::string letterName = getCharacterSymbol(actualLetter);

		ccUiSimpleDraw::CreateUiObj(uiobj, letterPath.c_str(), letterName.c_str(), 2);
		ccUiTaskBase::SetEnableTask(uiobj, 1);

		//std::cout << "Creating: " << letterName << " at (" <<  
		//std::cout << "Creating " << letterPath << " : " << letterName << std::endl;
	}

	for (int x = m_text.length(); x < m_uiObjects.size(); x++)
	{
		__int64 uiobj = m_uiObjects[x];
		ccUiTaskBase::SetEnableTask(uiobj, 0);
		ccUiSimpleDraw::CreateUiObj(uiobj, "", "", 2);
		ccUiTaskBase::SetEnableTask(uiobj, 1);
	}

	RecalculatePosition();
}

void FrameworkFont::Clear()
{
	for (int x = 0; x < m_uiObjects.size(); x++)
	{
		__int64 uiobj = m_uiObjects[x];
		ccUiTaskBase::SetEnableTask(uiobj, 0);
		ccUiSimpleDraw::CreateUiObj(uiobj, "", "", 2);
	}
}

void FrameworkFont::RecalculatePosition()
{
	float ax = position->x;
	float ay = position->y;

	for (int x = 0; x < m_uiObjects.size(); x++)
	{
		__int64 uiobj = m_uiObjects[x];

		Nucc::Vector2::Div(uiobj, size, size * 1.4);
		ccUiSimpleDraw::SetPosSimple(uiobj, ax, ay);
		ax += size + spacing->x;
	}
}