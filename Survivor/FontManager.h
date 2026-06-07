#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>
#include <string>
#include <memory>

class FontManager
{
private:
	struct FontDeleter
	{
		void operator()(TTF_Font* font) const
		{
			if (font)
				TTF_CloseFont(font);
		}
	};

public:

	bool InitResources();

	bool LoadFont(const std::string& name, const std::string& path, float size);

	TTF_Font* GetFont(const std::string& name) const;

	void Clear();

private:

	std::unordered_map<std::string, std::unique_ptr<TTF_Font,FontDeleter>> fontMap;
};

