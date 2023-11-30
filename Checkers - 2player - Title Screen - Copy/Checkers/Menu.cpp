// Menu.cpp

#include "Menu.h"
#include "TextureLoader.h" // Assuming you have a texture loading utility

Menu::Menu(SDL_Renderer* renderer)
    : renderer(renderer), menuTexture(nullptr), startButtonRect({0, 0, 896, 448}), exitButtonRect({0, 448, 896, 448}) {
    loadMenuTexture();
}

Menu::~Menu() {
    // Clean up the menu texture if it has been loaded
    if (menuTexture != nullptr) {
        SDL_DestroyTexture(menuTexture);
        menuTexture = nullptr;
    }
}

void Menu::show() {
    // Render the menu texture if it's loaded
    if (menuTexture != nullptr) {
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
    }
}

Menu::MenuAction Menu::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (isWithinRect(x, y, startButtonRect)) {
            return MenuAction::StartGame;
        } else if (isWithinRect(x, y, exitButtonRect)) {
            return MenuAction::ExitProgram;
        }
    }
    return MenuAction::None;
}

void Menu::loadMenuTexture() {
    // Load the menu background texture using a utility function
    menuTexture = TextureLoader::loadTexture("Main menu.bmp", renderer);
}

bool Menu::isWithinRect(int x, int y, const SDL_Rect& rect) {
    return (x >= rect.x) && (x < (rect.x + rect.w)) && (y >= rect.y) && (y < (rect.y + rect.h));
}
