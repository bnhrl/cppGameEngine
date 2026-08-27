#pragma once
#include "Framework/Object.h"

#include "Math/Transform.h"
#include "Renderer/Mesh.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
#include "Resources/ResourceManager.h"
#include "Resources/Resource.h"
#include "Components/Component.h"

namespace bnhe {
    class Scene; // Forward declaration

    class Actor : public Object {
    public:
        Actor() = default;
        Actor(const Transform& transform, const Model& model) : m_transform{ transform } {}
        Actor(const Transform& transform, const res_t<Texture> texture) : m_transform{ transform } {}
        Actor(const Actor& other);

        virtual void Read(const json::value_t& value);

        virtual void Update(float delta);
        virtual void Draw(const class Renderer& renderer) const;

        virtual void OnStart();
        virtual void OnDestroy();

        void AddComponent(std::unique_ptr<Component> component);

        const Transform& GetTransform() { return m_transform; }
        const Vector2 GetVelocity() { return m_velocity; }
        const Color GetModulate() { return m_modulate; }
        Scene* GetScene() const { return m_scene; }
        friend class Scene;

        virtual void OnCollision(Actor* actor);
        virtual void Destroy();
        bool IsDestroyed() { return destroyed; }

        float GetPersistent() { return m_persistent; }

        void SetTransform(const Transform transform) { m_transform = transform; }
        void SetPosition(const Vector2 position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(const Vector2 scale) { m_transform.scale = scale; }
        void SetVelocity(const Vector2 velocity) { m_velocity = velocity; }
        void SetModulate(const Color color) { m_modulate = color; }

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

        template<std::derived_from<Component> T>
        T* GetComponent();

    protected:
        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };
        Color m_modulate = Color(1.f);
        bool destroyed = false;
        float m_persistent = 0.f;

        std::vector<std::string> m_tags;
        std::vector<std::unique_ptr<Component>> m_components;

        Scene* m_scene = nullptr;
    };

    template<std::derived_from<Component> T>
    inline T* Actor::GetComponent()
    {
        for (auto& component : m_components) {
            auto result = dynamic_cast<T*>(component.get());
            if (result) return result;
        }
        return nullptr;
    }
}