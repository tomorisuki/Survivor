#pragma once
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <unordered_map>
#include <string>
#include <memory>

class TextureManager
{
private:
	//SDL_Texture删除器
	struct TextureDeleter {
		void operator()(SDL_Texture* sdl_texture) {
			if (sdl_texture)
				SDL_DestroyTexture(sdl_texture);
		}
	};

public:
	TextureManager(SDL_Renderer* sdl_renderer):sdl_renderer(sdl_renderer) {}
	~TextureManager();

	bool Init();

	bool LoadTexture(const std::string& name, const std::string& path);

	SDL_Texture* GetTexture(const std::string& name);



private:
	void Clean();
	SDL_Renderer* sdl_renderer = nullptr;
	std::unordered_map<std::string, std::unique_ptr<SDL_Texture,TextureDeleter>> texture_pool;
	bool is_clear = false;
};

