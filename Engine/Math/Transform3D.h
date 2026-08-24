#pragma once

#include "Vector3.h"

namespace bnhe {
    struct Transform3D {
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;
    };
}