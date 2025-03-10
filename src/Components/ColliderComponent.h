#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../Component.h"
#include "../Constants.h"
#include "../Components/TransformComponent.h"

class ColliderComponent: public Component {
    public:
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRectangle;
        SDL_Rect destinationRectangle;
        TransformComponent* transform;

        ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
            this->colliderTag = colliderTag;
            this->collider = { x, y, width, height };
        }

        void Initialize() override {
            if (owner->HasComponent<TransformComponent>()) {
                transform = owner->GetComponent<TransformComponent>();
                sourceRectangle = { 0, 0, transform->width, transform->height };
                destinationRectangle = { collider.x, collider.y, collider.w, collider.h };
            }
        }

        void Update(float deltaTime) override {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);

            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;

            destinationRectangle.x = collider.x - Game::camera.x;
            destinationRectangle.y = collider.y - Game::camera.y;

        }

        void Render() override {
            SDL_SetRenderDrawColor(Game::renderer, GREEN_COLOR.r, GREEN_COLOR.g, GREEN_COLOR.b, GREEN_COLOR.a);
            SDL_RenderDrawRect(Game::renderer,&destinationRectangle);
        }


};

#endif