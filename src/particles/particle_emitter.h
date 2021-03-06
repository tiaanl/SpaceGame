// Copyright (c) 2015, Tiaan Louw
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef PARTICLES_PARTICLE_EMITTER_H_
#define PARTICLES_PARTICLE_EMITTER_H_

#include <functional>
#include <vector>

#include <nucleus/macros.h>
#include <SFML/Graphics/Drawable.hpp>

class Particle;

class ParticleEmitter : public sf::Drawable {
public:
  using ParticleFactory =
      std::function<Particle*(ParticleEmitter*, const sf::Vector2f&)>;

  explicit ParticleEmitter(const ParticleFactory& factory);
  ~ParticleEmitter();

  // Get/set our position.
  const sf::Vector2f& getPos() const { return m_pos; }
  void setPos(const sf::Vector2f& pos);

  // Tick the emitter.
  void tick(float adjustment);

  // Override: sf::Drawable
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  // Creates a new particle and add it to our list of particles.
  void createParticle(const sf::Vector2f& pos);
  
  // The factory function we use to create particles.
  ParticleFactory m_factory;

  // Our position.
  sf::Vector2f m_pos;

  // The time since the last particle was emitted.
  float m_timeSinceLastParticle{0.f};

  // All the particles we are rendering.
  std::vector<Particle*> m_particles;

  DISALLOW_COPY_AND_ASSIGN(ParticleEmitter);
};

#endif  // PARTICLES_PARTICLE_EMITTER_H_
