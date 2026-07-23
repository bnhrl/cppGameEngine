#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "Model.h"
#

namespace bnhe {
    class Scene; // Forward declaration

    class Actor {
    public:
        Actor() = default;
        Actor(const Transform& transform, const Model& model) : m_transform{ transform }, m_model{ model } {}

        virtual void Update(float delta);

        virtual void Draw(const class Renderer& renderer) const;

        const Transform& GetTransform() { return m_transform; }
        const Vector2 GetVelocity() { return m_velocity; }

        void SetPosition(const Vector2 position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(const Vector2 scale) { m_transform.scale = scale; }
        void SetVelocity(const Vector2 velocity) { m_velocity = velocity; }
        void SetModel(const Model& model) { m_model = model; }

        Scene* GetScene() const { return m_scene; }
        friend class Scene;
        Model GetModel() const { return m_model; }

    protected:
        std::string m_name;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        Model m_model;

        Scene* m_scene = nullptr;
    };
}