#pragma once

#include <SDL3/SDL.h>
#include <unordered_map>
#include <string>

enum class KeyCode {
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_SPACE,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ESCAPE,
    MOUSE_LEFT,
    MOUSE_MOTION,
    Default
};

enum class KeyState {
    Normal,
    Press,
    Down,
    Up
};

struct Key {
    Key(){}
    Key(KeyCode key_code) {}

    KeyCode key_code = KeyCode::Default;
    KeyState key_state = KeyState::Normal;
};

class InputSystem final
{
public:

    explicit InputSystem(SDL_Event* sdl_event):sdl_event(sdl_event) {}
    ~InputSystem() = default;

    void Input();

    void BindKeyCode(const std::string& name, KeyCode key_code);

    bool isPress(const std::string& name);
    bool isPress(KeyCode key_code);

    bool isDown(const std::string& name);
    bool isDown(KeyCode key_code);

private:
	SDL_Event* sdl_event = nullptr;
    std::unordered_map<std::string, Key> keyMap;

    Key keyArr[34];
    bool KeyStateRequire[34] = { false };
};