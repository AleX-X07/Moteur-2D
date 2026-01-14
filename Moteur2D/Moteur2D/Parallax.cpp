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
    layer.offset = 0.0f;
    layers.push_back(layer);
}

void Parallax::update(float deltaTime)
{
    for (auto& layer : layers)
    {
        layer.offset += layer.speed * deltaTime;

        // On garde offset dans [0, textureWidth) pour éviter les gros nombres
        float texW = 0, texH = 0;
        SDL_GetTextureSize(layer.texture, &texW, &texH);

        if (texW > 0)
        {
            // wrap
            while (layer.offset >= texW) layer.offset -= texW;
            while (layer.offset <= -texW) layer.offset += texW;
        }
    }
}

void Parallax::render()
{
    for (auto& layer : layers)
    {
        if (!layer.texture) continue;

        float texW = 0, texH = 0;
        SDL_GetTextureSize(layer.texture, &texW, &texH);

        if (texW == 0 || texH == 0)
            continue;

        // On part de -texW jusqu'à couvrir tout l'écran
        // La première “tuile” commence à -texW + offset
        float startX = -texW + layer.offset;

        for (float x = startX; x < screenWidth; x += texW)
        {
            SDL_FRect dst{
                x,
                static_cast<float>(screenHeight - texH), // collé en bas, adapte selon ton layout
                static_cast<float>(texW),
                static_cast<float>(texH)
            };

            SDL_RenderTexture(renderer, layer.texture, nullptr, &dst);
        }
    }
};

Parallax::~Parallax() {

}