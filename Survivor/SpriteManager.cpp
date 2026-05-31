#include "SpriteManager.h"

SpriteManager::~SpriteManager()
{
    if (!is_clear) Clean();
}

bool SpriteManager::Init()
{
    if (!LoadSprite("sunflower", "assets/sunflower.png")) return false;
    return true;
}

bool SpriteManager::LoadSprite(const std::string& name, const std::string& path)
{
    if (sprite_pool.find(name) != sprite_pool.end()) return false;
    SDL_Texture* texture = IMG_LoadTexture(sdl_renderer, path.c_str());
    if (!texture) return false;
    sprite_pool.emplace(name, std::unique_ptr<SDL_Texture, TextureDeleter>{texture});
    return true;
}

SDL_Texture* SpriteManager::GetSprite(const std::string& name)
{
    if (sprite_pool.find(name) == sprite_pool.end()) return nullptr;
    return sprite_pool[name].get();
}

void SpriteManager::Clean()
{
    is_clear = true;
    sprite_pool.clear();
}
