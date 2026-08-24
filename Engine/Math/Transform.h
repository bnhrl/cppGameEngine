#pragma once

#include "Math/Vector2.h"
#include "Json.h"

namespace bnhe
{
    struct Transform {
        Vector2 position{ 0.f };
        float rotation  = 0.f;
        Vector2 scale   { 1.f };

        void Read(const json::value_t& value) {
            JSON_READ(value, position);
            JSON_READ(value, rotation);
            JSON_READ(value, scale);
        }
    };
}