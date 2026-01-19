#include "Parallax.h"

Parallax::Parallax(SDL_Renderer* _renderer, float screenW, float screenH) {
    renderer = _renderer;
    screenWidth = screenW;
    screenHeight = screenH;
}


void Parallax::addLayer(SDL_Texture* tex, float speed)
{
    ParallaxLayer layer;
    layer.texture = tex;
    layer.speed = speed;
    layer.offsetX = 0.0f;
    layer.offsetY = 0.0f;
    layers.push_back(layer);
}

void Parallax::update(float playerX, float playerY)
{
    for (auto& layer : layers)
    {
        layer.offsetX = -playerX * layer.speed;

        float texW = 0;
        float texH = 0;
        SDL_GetTextureSize(layer.texture, &texW, &texH);

        if (texW > 0)
        {
            while (layer.offsetX >= texW) layer.offsetX -= texW;
            while (layer.offsetX <= -texW) layer.offsetX += texW;
        }

        if (texH > 0)
        {
            while (layer.offsetY >= texH) layer.offsetY -= texH;
            while (layer.offsetY <= -texH) layer.offsetY += texH;
        }
    }
}

void Parallax::render()
{
    for (auto& layer : layers)
    {
        if (!layer.texture) continue;

        float texW = 0;
        float texH = 0;
        SDL_GetTextureSize(layer.texture, &texW, &texH);

        if (texW == 0 || texH == 0)
            continue;

        // Normaliser l'offset pour le wrap
        float normalizedOffset = layer.offsetX;
        if (texW > 0) {
            normalizedOffset = fmod(layer.offsetX, texW);
            if (normalizedOffset > 0) normalizedOffset -= texW;
        }

        // Dessiner en mode tuile pour couvrir tout l'écran
        float startX = normalizedOffset;

        for (float x = startX; x < screenWidth; x += texW)
        {
            SDL_FRect dst{
                x,
                screenHeight - texH,
                texW,
                texH
            };

            SDL_RenderTexture(renderer, layer.texture, nullptr, &dst);
        }
    }
};

Parallax::~Parallax() {

}