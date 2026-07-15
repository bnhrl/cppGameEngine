#include "pch.h"
#include "Actor.h"

#include "Renderer.h"
#include "MathUtils.h"

namespace bnhe
{
    void Actor::Update(float delta)
    {
        m_transform.position += (m_velocity * delta);
        m_velocity = m_velocity.Lerp(Vector2(0, 0), 6.7f, delta);

        m_transform.position.x = math::Wrap(m_transform.position.x, 0.0f, (float)Renderer::GetWidth());
        m_transform.position.y = math::Wrap(m_transform.position.y, 0.0f, (float)Renderer::GetHeight());
    }

    void Actor::Draw(const class Renderer& renderer) const
    {
        //renderer.SetColor(0, 1.f, 0);
        //renderer.DrawRect(m_transform.position, m_size * m_transform.scale);
        renderer.DrawModel(m_model, m_transform);
    }
}