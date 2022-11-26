#pragma once
#include <string>
#include <vector>
#include "Vector3.h"

class FrameworkFont
{
public:
	std::string font = "data/ui/framework/font/";
	std::string m_text = "";
	Vector3 * position;
	float size;
	Vector3 * spacing;

	std::vector<__int64> m_uiObjects;

	FrameworkFont()
	{
		m_text = "";
		position = new Vector3(0, 0, 0);
		size = 10;
		spacing = new Vector3(2, 2, 0);
	}
	
	static void LoadDefaultFont(__int64 a1);

	void SetText(std::string text, float posx, float posy);
	void RecalculatePosition();

	void SetSize(float s)
	{
		size = s;
		RecalculatePosition();
	}

	void SetPosition(float x, float y)
	{
		*position = Vector3(x, y, 0);
		RecalculatePosition();
	}

	void Clear();
	
	std::string getCharacterPath(char actual)
	{
		std::string path = "";

		if (actual >= 0x61 && actual <= 0x6E) path = "font_an_s.xfbin";
		else if (actual >= 0x6F && actual <= 0x7A) path = "font_oz_s.xfbin";
		else if (actual >= 0x41 && actual <= 0x4E) path = "font_an.xfbin";
		else if (actual >= 0x4F && actual <= 0x5A) path = "font_oz.xfbin";
		else if (actual >= 0x30 && actual <= 0x39) path = "font_number.xfbin";
		else path = "font_symbol.xfbin";

		return path;
	}

	std::string getCharacterSymbol(char actual)
	{
		std::string letter = "";

		switch (actual)
		{
		default:
			letter = actual;
			break;
		case ',':
			letter = "comma";
			break;
		case '.':
			letter = "dot";
			break;
		case ':':
			letter = "doubledot";
			break;
		case '!':
			letter = "exclamat";
			break;
		case '-':
			letter = "hyphen";
			break;
		case '(':
			letter = "parleft";
			break;
		case ')':
			letter = "parright";
			break;
		case '>':
			letter = "ptrleft";
			break;
		case '<':
			letter = "ptrright";
			break;
		case '?':
			letter = "question";
			break;
		case '/':
			letter = "slash";
			break;
		case '%':
			letter = "per";
			break;
		case '_':
			letter = "underscore";
			break;
		}

		return letter;
	}
};

