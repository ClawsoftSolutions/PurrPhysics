#define SDL_MAIN_HANDLED

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <glm/vec3.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

#include "PurrPhysics/PurrPhysics.hpp"

void renderBodies(SDL_Renderer* renderer, const std::vector<RigidBody>& bodies) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White bodies

    for (const RigidBody& body : bodies) {
        SDL_Rect rect;
        rect.x = static_cast<int>(body.position.x) - static_cast<int>(body.halfSize.x);
        rect.y = static_cast<int>(body.position.y) - static_cast<int>(body.halfSize.y);
        rect.w = static_cast<int>(body.halfSize.x * 2);
        rect.h = static_cast<int>(body.halfSize.y * 2);
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Physics Engine", 
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                          WINDOW_WIDTH, WINDOW_HEIGHT, 
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    std::vector<RigidBody> bodies;
    bodies.emplace_back(1.0f, glm::vec3(400.0f, 300.0f, 0.0f), glm::vec3(25.0f, 25.0f, 0.0f));

    std::vector<const Force*> forces;
    GravityForce gravity(glm::vec3(0.0f, 100.0f, 0.0f));
    forces.push_back(&gravity);

    float deltaTime = 0.016f; // Simulating at ~60 FPS
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        updatePhysics(bodies, forces, deltaTime);
        renderBodies(renderer, bodies);

        SDL_Delay(16); // Simulate ~60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
