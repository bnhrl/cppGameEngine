#include "pch.h"
#include "Actor.h"

#include "Renderer.h"
#include "MathUtils.h"

namespace bnhe
{
    void Actor::Update(float delta)
    {
        if (destroyed) return;

        m_transform.position += (m_velocity * delta);
        m_velocity = m_velocity.Lerp(Vector2(0, 0), 6.7f, delta);

        m_transform.position.x = math::Wrap(m_transform.position.x, 0.0f, (float)Renderer::GetWidth());
        m_transform.position.y = math::Wrap(m_transform.position.y, 0.0f, (float)Renderer::GetHeight());
    }

    void Actor::Draw(const class Renderer& renderer) const
    {
        if (destroyed) return;
        renderer.DrawModel(m_model, m_transform);
    }

    float Actor::GetRadius() const {
        return m_model.GetRadius() * m_transform.scale.Length() * 0.9f;
    }

    void Actor::OnCollision(Actor* actor) {}

    void Actor::Destroy() { destroyed = true; }
}