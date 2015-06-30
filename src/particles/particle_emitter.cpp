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

#include "particles/particle_emitter.h"

#include <algorithm>

#include "particles/particle.h"

ParticleEmitter::ParticleEmitter(const ParticleFactory& factory)
  : m_factory(factory) {
}

ParticleEmitter::~ParticleEmitter() {
}

void ParticleEmitter::setPos(const ca::Vec2& pos) {
  m_pos = pos;
}

void ParticleEmitter::tick(f32 adjustment) {
  // Emit a particle every few moments.
  if (m_timeSinceLastParticle > 1.f) {
    createParticle(m_pos);
    m_timeSinceLastParticle = 0.f;
  } else {
    m_timeSinceLastParticle += adjustment;
  }

  // Tick all the particles.
  for (auto& particle : m_particles) {
    particle->tick(adjustment);
  }

  // Remove all the dead particles.
  m_particles.erase(
      std::remove_if(std::begin(m_particles), std::end(m_particles),
                     [](Particle* p) { return p->isDead(); }),
      std::end(m_particles));
}

void ParticleEmitter::render(ca::Canvas* canvas) const {
  for (const auto& particle : m_particles) {
    particle->render(canvas);
  }
}

void ParticleEmitter::createParticle(const ca::Vec2& pos) {
  Particle* p = m_factory(this, pos);
  m_particles.push_back(p);
}
