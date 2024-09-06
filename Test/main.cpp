#define SDL_MAIN_HANDLED

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
#include <PurrPhysics/PurrPhysics.hpp>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

void drawLine(SDL_Renderer* renderer, const glm::vec3& point1, const glm::vec3& point2) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer,
                       static_cast<int>(point1.x), static_cast<int>(point1.y),
                       static_cast<int>(point2.x), static_cast<int>(point2.y));
}

void renderBodies(SDL_Renderer* renderer, const std::vector<RigidBodyComponent>& bodies) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const RigidBodyComponent& body : bodies) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        const auto& points = body.getPoints();

        for (const Point& point : points) {
            SDL_Rect pointRect;
            pointRect.x = static_cast<int>(point.position.x - 2.0f);
            pointRect.y = static_cast<int>(point.position.y - 2.0f);
            pointRect.w = 4;
            pointRect.h = 4;

            SDL_RenderFillRect(renderer, &pointRect);
        }

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        for (size_t i = 0; i < points.size(); ++i) {
            for (size_t j = i + 1; j < points.size(); ++j) {
                drawLine(renderer, points[i].position, points[j].position);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Physics Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

    std::vector<RigidBodyComponent> bodies;
    bodies.emplace_back(1.0f, glm::vec3(200.0f, 300.0f, 0.0f), glm::vec3(50.0f, 50.0f, 0.0f));

    bodies[0].addPoint(glm::vec3(200.0f, 300.0f, 0.0f));
    bodies[0].addPoint(glm::vec3(250.0f, 300.0f, 0.0f));
    bodies[0].addPoint(glm::vec3(250.0f, 250.0f, 0.0f));
    bodies[0].addPoint(glm::vec3(200.0f, 250.0f, 0.0f));

    float deltaTime = 0.016f;
    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        GravityForce<RigidBodyComponent> gravity(glm::vec3(0.0f, -9.8f, 0.0f));
        
        for (RigidBodyComponent& body : bodies) {
            gravity.apply(body);
            body.integrateForces(deltaTime);
            body.integrate(deltaTime);
        }

        renderBodies(renderer, bodies);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
