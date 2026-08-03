#pragma once

#include "Vector2.h"
namespace bnhe
{
    struct Transform {
        Vector2 position;
        float rotation = 0.f;
        Vector2 scale;
    };
}