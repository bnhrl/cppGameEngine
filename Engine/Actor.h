#pragma once

#include "Transform.h"

namespace bnhe {
    class Actor {
    public:
        Actor(Transform transform, Vector2 size = Vector2(64, 64)) : m_transform{ transform }, m_size{ size } {}

        void Update(float delta);

        void Draw(const class Renderer& renderer);

        const Transform& GetTransform() { return m_transform; }
        const Vector2 GetSize() { return m_size; }
        const Vector2 GetVelocity() { return m_velocity; }

        void SetPosition(const Vector2 position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(const Vector2 scale) { m_transform.scale = scale; }

        void SetSize(const Vector2 size) { m_size = size; }
        void SetVelocity(const Vector2 velocity) { m_velocity = velocity; }

    protected:
        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        Vector2 m_size;
    };
}