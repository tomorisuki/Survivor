#include "Game.h"
#include <chrono>

bool Game::InitGame()
{
    // 初始化 SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return false;
    }

    // 初始化 SDL_ttf
    if (!TTF_Init())
    {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        return false;
    }

    SDL_CreateWindowAndRenderer("Survivor", WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_RESIZABLE, &sdl_window, &sdl_renderer);


    // 设置垂直同步（可选）
    SDL_SetRenderVSync(sdl_renderer, 1);


    sprite_manager = std::make_unique<SpriteManager>(sdl_renderer);
    if (!sprite_manager->Init()) return false;
    sprite = std::make_unique<Sprite>();
    sprite->SetTexture(sprite_manager->GetSprite("sunflower"));


    return true;
}



void Game::Run()
{
    if (!InitGame()) {
        Clean();
        return;
    }

    constexpr double fixed_dt = 1.0 / 60.0;
    double accumulator = 0.0;
    auto last = std::chrono::steady_clock::now();


    SDL_Event sdl_event;
	while (running) {

        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_EVENT_QUIT)
            {
                running = false;
                Clean();
                break;
            }
        }

        auto current = std::chrono::steady_clock::now();
        double frame_time = std::chrono::duration<double>(current - last).count();
        last = current;

        accumulator += frame_time;
        while (accumulator >= fixed_dt) {
            
            float game_dt = static_cast<float>(fixed_dt);


            //update

            accumulator -= fixed_dt;
        }

        SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
        SDL_RenderClear(sdl_renderer);
        //render
        SDL_FRect rect = { 200,200,64,89 };
        SDL_RenderTexture(sdl_renderer, sprite->GetTexture(), nullptr, &rect);

        SDL_RenderPresent(sdl_renderer);
	}
	
}

void Game::Clean()
{
    if (sdl_renderer) SDL_DestroyRenderer(sdl_renderer);
    if (sdl_window) SDL_DestroyWindow(sdl_window);

    TTF_Quit();
    SDL_Quit();
}

void Game::Exit()
{
}
