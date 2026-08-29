#include "pch.h"
#include "Framework/Actor.h"

#include "Core/Factory.h"
#include "Renderer/Renderer.h"
#include "Math/MathUtils.h"
#include "Framework/Scene.h"                
#include "Components/RendererComponent.h"

namespace bnhe
{
    FACTORY_REGISTER(Actor);
   
    Actor::Actor(const Actor& other) :
        Object{ other },
        m_transform{other.m_transform },
        m_velocity{other.m_velocity },
        m_modulate{other.m_modulate },
        destroyed{other.destroyed },
        m_tags{other.m_tags}
    {
        for (const auto& component : other.m_components) {
            auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>((component->Clone().release())));
            AddComponent(std::move(clone));
        }
    }

    void Actor::Read(const json::value_t& value)
    {
        Object::Read(value);

        if (JSON_HAS_NAME(value, "transform")) m_transform.Read(value["transform"]);
        if (JSON_HAS_NAME(value, "velocity")) JSON_READ_NAME(value, "velocity", m_velocity);
        if (JSON_HAS_NAME(value, "modulate")) JSON_READ_NAME(value, "modulate", m_modulate);
        if (JSON_HAS_NAME(value, "persistent")) JSON_READ_NAME(value, "persistent", m_persistent);
        if (JSON_HAS_NAME(value, "lifespan")) JSON_READ_NAME(value, "lifespan", m_lifespan);
        if (JSON_HAS_NAME(value, "tags")) { JSON_READ_NAME(value, "tags", m_tags); } 

        if (JSON_HAS_NAME(value, "components")) {
            for (auto& componentValue : JSON_GET_NAME(value, "components").GetArray()) {
                std::string typeName;
                JSON_READ_NAME(componentValue, "type", typeName);

                //std::cout << "Loading component type: " << typeName << std::endl;

                std::unique_ptr<Component> component = Factory::Instance().Create<Component>(typeName);
                if (component) {
                    component->Read(componentValue);
                    AddComponent(std::move(component));
                }
            }
        }

        //// Debug
        //for (const auto& component : m_components) {
        //    std::cout << component.get();
        //} std::cout << std::endl;
    }

    void Actor::Update(float delta)
    {
        if (destroyed) return;

        m_transform.position += (m_velocity * delta);
        m_velocity = m_velocity.Lerp(Vector2(0, 0), 6.7f, delta);

        //m_transform.position.x = math::Wrap(m_transform.position.x, 0.0f, (float)Renderer::GetWidth());
        //m_transform.position.y = math::Wrap(m_transform.position.y, 0.0f, (float)Renderer::GetHeight());

        for (auto& component : m_components) {
            component->Update(delta);
        }

        if (m_lifespan > 0.f) {
            m_lifespan -= delta;
            if (m_lifespan < 0.f) Destroy();
        }
    }

    void Actor::Draw(const class Renderer& renderer) const
    {
        if (destroyed) return;

        for (const auto& component : m_components) {
            // Check if component is a renderer component
            auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
            if (rendererComponent)
                rendererComponent->Draw(renderer);
        }
    }

    void Actor::AddComponent(std::unique_ptr<Component> component)
    {
        component->SetOwner(this);
        m_components.push_back(std::move(component));
    }

    void Actor::OnStart() 
    {
        for (auto& component : m_components) {
            component->OnStart();
        }
    }

    void Actor::OnDestroy() 
    {
        for (auto& component : m_components) {
            component->OnDestroy();
        }
    }

    void Actor::OnCollision(Actor* actor) {}

    void Actor::Destroy() 
    { 
        destroyed = true;
    }
}