#pragma once
#include "Object.h"

#include "Transform.h"
#include "Mesh.h"
#include "Model.h"
#include "Texture.h"

namespace bnhe {
    class Scene; // Forward declaration

    class Actor : public Object {
    public:
        Actor() = default;
        Actor(const Transform& transform, const Model& model) : m_transform{ transform }, m_model{ model } {}
        Actor(const Transform& transform, const res_t<Texture> texture) : m_transform{ transform }, m_texture{ texture } {}

        virtual void Update(float delta);
        virtual void Draw(const class Renderer& renderer) const;

        const Transform& GetTransform() { return m_transform; }
        const Vector2 GetVelocity() { return m_velocity; }
        Model GetModel() const { return m_model; }
        Scene* GetScene() const { return m_scene; }
        friend class Scene;

        void SetPosition(const Vector2 position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(const Vector2 scale) { m_transform.scale = scale; }
        void SetVelocity(const Vector2 velocity) { m_velocity = velocity; }
        void SetModel(const Model& model) { m_model = model; }

        bool HasTag(std::string tag) { 
            if (m_tags.size() <= 0) return false;
            auto found = std::find(m_tags.begin(), m_tags.end(), tag);
            if (found != m_tags.end()) { return true; }
            return false;
        }
        void AddTag(std::string tag) { m_tags.push_back(tag); }
        bool RemoveTag(std::string tag) {
            if (!HasTag(tag)) return false;
            std::erase(m_tags, tag);
            return true;
        }

        float GetRadius() const;
        virtual void OnCollision(Actor* actor);
        virtual void Destroy();
        bool IsDestroyed() { return destroyed; }

    protected:
        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        Model m_model;
        res_t<Texture> m_texture;
        Color m_modulate = Color(1.f);
        bool destroyed = false;

        std::vector<std::string> m_tags;

        Scene* m_scene = nullptr;
    };
}