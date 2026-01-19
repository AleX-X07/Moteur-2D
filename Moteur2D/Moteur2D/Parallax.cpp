#include "Parallax.h"
#include "Camera.h"


Parallax::Parallax(SDL_Renderer* _renderer, float screenW, float screenH) {
    renderer = _renderer;
}


void Parallax::addLayer(SDL_Texture* tex, float speed)
{
    ParallaxLayer layer;
    layer.texture = tex;
    layer.speed = speed;
    layer.offsetX = 0.0f;
    layer.offsetY = 0.0f;
    float w;
    float h;
    SDL_GetTextureSize(tex, &w, &h);
    layer.rect = { 0,0,w,h };
    layers.push_back(layer);
}

void Parallax::update(float playerX, float playerY)
{
    for (auto& layer : layers)
    {
        layer.offsetX = -playerX * layer.speed;
    }
}

void Parallax::render(Camera& camera)
{   
    for (auto& layer : layers)
    {
        SDL_FRect screenRect = camera.worldToScreen(layer.rect);

        layer.offsetX = -camera.sizeC.x;

        float normalizedOffset = layer.offsetX - (camera.sizeC.x * layer.speed);
        if (layer.rect.w > 0) {
            normalizedOffset = fmod(layer.offsetX, layer.rect.w);
            if (normalizedOffset > 0) normalizedOffset -= layer.rect.w;
        }

        float startX = normalizedOffset;

        for (float x = startX; x < levelWidth; x += layer.rect.w)
        {
            SDL_FRect dst{
                x,
                levelHeight - layer.rect.h/1.5 - camera.sizeC.y * layer.speed,
                layer.rect.w,
                layer.rect.h
            };

            SDL_RenderTexture(renderer, layer.texture, nullptr, &dst);
        }
    }
};

Parallax::~Parallax() {

}