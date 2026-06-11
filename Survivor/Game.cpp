#include "Game.h"
#include <chrono>

#include <imm.h>        //使用禁用输入法API
#pragma comment(lib, "imm32.lib")


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

    SDL_SetRenderLogicalPresentation(sdl_renderer, WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_LOGICAL_PRESENTATION_LETTERBOX);

    // 设置垂直同步（可选）
    SDL_SetRenderVSync(sdl_renderer, 1);

    SDL_PropertiesID windowProps = SDL_GetWindowProperties(sdl_window);

    hwnd = (HWND)SDL_GetPointerProperty(windowProps, SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);

    //禁用输入法
    HIMC himc = ImmAssociateContext(hwnd, NULL);

    //启用输入法
    //ImmAssociateContext(hwnd, himc);


    texture_manager = std::make_unique<TextureManager>(sdl_renderer);
    if (!texture_manager->Init()) return false;
    sprite = std::make_unique<Sprite>();
    sprite->SetTexture(texture_manager->GetTexture("sunflower"));

    SDL_zero(sdl_event);

    /*------------分配内存------------*/
    
    engine = std::make_unique<Engine>();

    input = std::make_unique<InputSystem>();

    render = std::make_unique<RenderSystem>(sdl_renderer);

    texture_manager = std::make_unique<TextureManager>(sdl_renderer);

    aniClipMgr = std::make_unique<AnimationClipManager>();

    collisionSystem = std::make_unique<CollisionSystem>();

	font_manager = std::make_unique<FontManager>();

    /*------------分配内存------------*/


    
    /*-----------设置参数-----------*/
    engine->RegisterInputSystem(input.get());
    engine->RegisterRenderSystem(render.get());
    engine->RegisterTextureManager(texture_manager.get());
    engine->RegisterAnimationClipMgr(aniClipMgr.get());
    engine->RegisterCollisionSystem(collisionSystem.get());
    engine->RegisterFontManager(font_manager.get());
    engine->SetWindowSize({ WINDOW_WIDTH,WINDOW_HEIGHT });
    /*-----------设置参数-----------*/



    /*------------初始化------------*/
    texture_manager->Init();
    aniClipMgr->InitResources(texture_manager.get());
    collisionSystem->Init();
    font_manager->InitResources();

    /*------------初始化------------*/
    scene = new TestScene();
    scene->SetEngine(engine.get());
    scene->Start();

    //engine->SetScene(scene);

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

    double fps_timer = 0.0;
    int logic_fps = 0;
    int render_fps = 0;
    
	while (running) {

        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_EVENT_QUIT)
            {
                running = false;
                break;
            }
            input->Input(sdl_event);
        }
        if (!running) break;
       
        
        auto current = std::chrono::steady_clock::now();
        double frame_time = std::chrono::duration<double>(current - last).count();
        last = current;

        accumulator += frame_time;
        fps_timer += frame_time;

        while (accumulator >= fixed_dt) {
            
            float game_delta = static_cast<float>(fixed_dt);
            input->Update();    //输入系统的更新

            scene->Update(game_delta);

            collisionSystem->Update(game_delta);

            //更新的最后一帧处理
            scene->ProcessPendingOperations();

            accumulator -= fixed_dt;
            logic_fps++;
        }
        float alpha = static_cast<float>(accumulator / fixed_dt);
        


        SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
        SDL_RenderClear(sdl_renderer);
        
        
        render->RenderClear();



        scene->Render();

        
        render->Render(alpha);
        render_fps++;
        SDL_RenderPresent(sdl_renderer);

        
        if (fps_timer >= 1.0) {
            engine->UpdateLogicFPS(logic_fps);
            logic_fps = 0;


            engine->UpdateRenderFPS(render_fps);
            render_fps = 0;

            fps_timer -= 1.0;
        }

	}
    Clean();
}

void Game::Clean()
{
    if (scene)
        delete scene;
    if (sdl_renderer) SDL_DestroyRenderer(sdl_renderer);
    if (sdl_window) SDL_DestroyWindow(sdl_window);
    
	font_manager->Clear();  //提前清理字体资源

    TTF_Quit();
    SDL_Quit();
}

void Game::Exit()
{
}
