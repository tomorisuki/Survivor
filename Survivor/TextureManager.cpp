#include "TextureManager.h"

TextureManager::~TextureManager()
{
    if (!is_clear) Clean();
}

bool TextureManager::Init()
{
    if (!LoadTexture("sunflower", "assets/sunflower.png")) return false;
    return true;
}

bool TextureManager::LoadTexture(const std::string& name, const std::string& path)
{
    if (texture_pool.find(name) != texture_pool.end()) return false;
    SDL_Texture* texture = IMG_LoadTexture(sdl_renderer, path.c_str());
    if (!texture) return false;
    texture_pool.emplace(name, std::unique_ptr<SDL_Texture, TextureDeleter>{texture});
    return true;
}

SDL_Texture* TextureManager::GetTexture(const std::string& name)
{
    if (texture_pool.find(name) == texture_pool.end()) return nullptr;
    return texture_pool[name].get();
}

void TextureManager::Clean()
{
    is_clear = true;
    texture_pool.clear();
}
