#include "FontManager.h"

bool FontManager::InitResources()
{
	if (!LoadFont("silver", "assets/fonts/Silver.ttf", 32))
		return false;

	return true;
}

bool FontManager::LoadFont(const std::string& name, const std::string& path, float size)
{
	if (fontMap.find(name) != fontMap.end()) return true; // ◊÷ÃÂ“—º”‘ÿ

	TTF_Font* font = TTF_OpenFont(path.c_str(), size);
	if (font)
		fontMap[name] = std::unique_ptr<TTF_Font, FontDeleter>{font};

	return true;
}

TTF_Font* FontManager::GetFont(const std::string& name) const
{
	if (fontMap.find(name) != fontMap.end())
		return fontMap.at(name).get();
	else
		return nullptr;
}

void FontManager::Clear()
{
	fontMap.clear();
}


