#include "InputSystem.h"

//test
#include <iostream>

void InputSystem::Input(SDL_Event& sdl_event)
{
    switch (sdl_event.type) {
    case SDL_EVENT_MOUSE_MOTION:
        mousePosition.x = sdl_event.motion.x;
        mousePosition.y = sdl_event.motion.y;
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        mousePosition.x = sdl_event.motion.x;
        mousePosition.y = sdl_event.motion.y;
        mouseClick = true;
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        mousePosition.x = sdl_event.motion.x;
        mousePosition.y = sdl_event.motion.y;
        mouseClick = false;
        break;
    case SDL_EVENT_KEY_DOWN:
        switch (sdl_event.key.key) {
        case SDLK_A:      KeyStateRequire[static_cast<int>(KeyCode::KEY_A)] = true; break;
        case SDLK_B:      KeyStateRequire[static_cast<int>(KeyCode::KEY_B)] = true; break;
        case SDLK_C:      KeyStateRequire[static_cast<int>(KeyCode::KEY_C)] = true; break;
        case SDLK_D:      KeyStateRequire[static_cast<int>(KeyCode::KEY_D)] = true; break;
        case SDLK_E:      KeyStateRequire[static_cast<int>(KeyCode::KEY_E)] = true; break;
        case SDLK_F:      KeyStateRequire[static_cast<int>(KeyCode::KEY_F)] = true; break;
        case SDLK_G:      KeyStateRequire[static_cast<int>(KeyCode::KEY_G)] = true; break;
        case SDLK_H:      KeyStateRequire[static_cast<int>(KeyCode::KEY_H)] = true; break;
        case SDLK_I:      KeyStateRequire[static_cast<int>(KeyCode::KEY_I)] = true; break;
        case SDLK_J:      KeyStateRequire[static_cast<int>(KeyCode::KEY_J)] = true; break;
        case SDLK_K:      KeyStateRequire[static_cast<int>(KeyCode::KEY_K)] = true; break;
        case SDLK_L:      KeyStateRequire[static_cast<int>(KeyCode::KEY_L)] = true; break;
        case SDLK_M:      KeyStateRequire[static_cast<int>(KeyCode::KEY_M)] = true; break;
        case SDLK_N:      KeyStateRequire[static_cast<int>(KeyCode::KEY_N)] = true; break;
        case SDLK_O:      KeyStateRequire[static_cast<int>(KeyCode::KEY_O)] = true; break;
        case SDLK_P:      KeyStateRequire[static_cast<int>(KeyCode::KEY_P)] = true; break;
        case SDLK_Q:      KeyStateRequire[static_cast<int>(KeyCode::KEY_Q)] = true; break;
        case SDLK_R:      KeyStateRequire[static_cast<int>(KeyCode::KEY_R)] = true; break;
        case SDLK_S:      KeyStateRequire[static_cast<int>(KeyCode::KEY_S)] = true; break;
        case SDLK_T:      KeyStateRequire[static_cast<int>(KeyCode::KEY_T)] = true; break;
        case SDLK_U:      KeyStateRequire[static_cast<int>(KeyCode::KEY_U)] = true; break;
        case SDLK_V:      KeyStateRequire[static_cast<int>(KeyCode::KEY_V)] = true; break;
        case SDLK_W:      KeyStateRequire[static_cast<int>(KeyCode::KEY_W)] = true; break;
        case SDLK_X:      KeyStateRequire[static_cast<int>(KeyCode::KEY_X)] = true; break;
        case SDLK_Y:      KeyStateRequire[static_cast<int>(KeyCode::KEY_Y)] = true; break;
        case SDLK_Z:      KeyStateRequire[static_cast<int>(KeyCode::KEY_Z)] = true; break;
        case SDLK_SPACE:  KeyStateRequire[static_cast<int>(KeyCode::KEY_SPACE)] = true; break;
        case SDLK_UP:     KeyStateRequire[static_cast<int>(KeyCode::KEY_UP)] = true; break;
        case SDLK_DOWN:   KeyStateRequire[static_cast<int>(KeyCode::KEY_DOWN)] = true; break;
        case SDLK_LEFT:   KeyStateRequire[static_cast<int>(KeyCode::KEY_LEFT)] = true; break;
        case SDLK_RIGHT:  KeyStateRequire[static_cast<int>(KeyCode::KEY_RIGHT)] = true; break;
        case SDLK_ESCAPE: KeyStateRequire[static_cast<int>(KeyCode::KEY_ESCAPE)] = true; break;
        }
        break;

    case SDL_EVENT_KEY_UP:
        switch (sdl_event.key.key) {
        case SDLK_A:      KeyStateRequire[static_cast<int>(KeyCode::KEY_A)] = false; break;
        case SDLK_B:      KeyStateRequire[static_cast<int>(KeyCode::KEY_B)] = false; break;
        case SDLK_C:      KeyStateRequire[static_cast<int>(KeyCode::KEY_C)] = false; break;
        case SDLK_D:      KeyStateRequire[static_cast<int>(KeyCode::KEY_D)] = false; break;
        case SDLK_E:      KeyStateRequire[static_cast<int>(KeyCode::KEY_E)] = false; break;
        case SDLK_F:      KeyStateRequire[static_cast<int>(KeyCode::KEY_F)] = false; break;
        case SDLK_G:      KeyStateRequire[static_cast<int>(KeyCode::KEY_G)] = false; break;
        case SDLK_H:      KeyStateRequire[static_cast<int>(KeyCode::KEY_H)] = false; break;
        case SDLK_I:      KeyStateRequire[static_cast<int>(KeyCode::KEY_I)] = false; break;
        case SDLK_J:      KeyStateRequire[static_cast<int>(KeyCode::KEY_J)] = false; break;
        case SDLK_K:      KeyStateRequire[static_cast<int>(KeyCode::KEY_K)] = false; break;
        case SDLK_L:      KeyStateRequire[static_cast<int>(KeyCode::KEY_L)] = false; break;
        case SDLK_M:      KeyStateRequire[static_cast<int>(KeyCode::KEY_M)] = false; break;
        case SDLK_N:      KeyStateRequire[static_cast<int>(KeyCode::KEY_N)] = false; break;
        case SDLK_O:      KeyStateRequire[static_cast<int>(KeyCode::KEY_O)] = false; break;
        case SDLK_P:      KeyStateRequire[static_cast<int>(KeyCode::KEY_P)] = false; break;
        case SDLK_Q:      KeyStateRequire[static_cast<int>(KeyCode::KEY_Q)] = false; break;
        case SDLK_R:      KeyStateRequire[static_cast<int>(KeyCode::KEY_R)] = false; break;
        case SDLK_S:      KeyStateRequire[static_cast<int>(KeyCode::KEY_S)] = false; break;
        case SDLK_T:      KeyStateRequire[static_cast<int>(KeyCode::KEY_T)] = false; break;
        case SDLK_U:      KeyStateRequire[static_cast<int>(KeyCode::KEY_U)] = false; break;
        case SDLK_V:      KeyStateRequire[static_cast<int>(KeyCode::KEY_V)] = false; break;
        case SDLK_W:      KeyStateRequire[static_cast<int>(KeyCode::KEY_W)] = false; break;
        case SDLK_X:      KeyStateRequire[static_cast<int>(KeyCode::KEY_X)] = false; break;
        case SDLK_Y:      KeyStateRequire[static_cast<int>(KeyCode::KEY_Y)] = false; break;
        case SDLK_Z:      KeyStateRequire[static_cast<int>(KeyCode::KEY_Z)] = false; break;
        case SDLK_SPACE:  KeyStateRequire[static_cast<int>(KeyCode::KEY_SPACE)] = false; break;
        case SDLK_UP:     KeyStateRequire[static_cast<int>(KeyCode::KEY_UP)] = false; break;
        case SDLK_DOWN:   KeyStateRequire[static_cast<int>(KeyCode::KEY_DOWN)] = false; break;
        case SDLK_LEFT:   KeyStateRequire[static_cast<int>(KeyCode::KEY_LEFT)] = false; break;
        case SDLK_RIGHT:  KeyStateRequire[static_cast<int>(KeyCode::KEY_RIGHT)] = false; break;
        case SDLK_ESCAPE: KeyStateRequire[static_cast<int>(KeyCode::KEY_ESCAPE)] = false; break;
        }
        break;
    }


}

void InputSystem::Update()
{
    for (auto& key : keyMap) {
        key.second.previous = key.second.current;
        key.second.current = KeyStateRequire[static_cast<int>(key.second.key_code)];
    }
}

void InputSystem::BindKeyCode(const std::string& name, KeyCode key_code)
{
	keyMap.emplace(name, Key(key_code));
}

bool InputSystem::isPress(const std::string& name)
{
    return keyMap[name].current && !keyMap[name].previous;
    ////如果按键的状态为true
    //if (KeyStateRequire[static_cast<int>(keyMap[name].key_code)] &&
    //    (keyMap[name].key_state != KeyState::Press)) {
    //    keyMap[name].key_state = KeyState::Press;
    //    return true;
    //}
    //return false;
}

bool InputSystem::isPress(KeyCode key_code) const
{

	return false;
}

bool InputSystem::isDown(const std::string& name)
{
    return keyMap[name].current;
   /* if (KeyStateRequire[static_cast<int>(keyMap[name].key_code)] &&
        (keyMap[name].key_state == KeyState::Press || keyMap[name].key_state == KeyState::Down)) {
        keyMap[name].key_state = KeyState::Down;
        return true;
    }
    return false;*/
}

bool InputSystem::isDown(KeyCode key_code) const
{
	return KeyStateRequire[static_cast<int>(key_code)];
}

bool InputSystem::isUp(const std::string& name)
{
    return !keyMap[name].current && keyMap[name].previous;
   /* if (!KeyStateRequire[static_cast<int>(keyMap[name].key_code)] &&
        (keyMap[name].key_state == KeyState::Down)) {
        keyMap[name].key_state = KeyState::Up;
        return true;
    }
    return false;*/
}

bool InputSystem::isUp(KeyCode key_code)
{
    return false;
}

Vector2D InputSystem::MousePos() const
{
    return mousePosition;
}

bool InputSystem::MouseLeftDown() const
{
    return mouseClick;
}

bool InputSystem::MouseLeftUp() const
{
    return mouseClick;
}


