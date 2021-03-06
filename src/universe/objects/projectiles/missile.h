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

#ifndef UNIVERSE_OBJECTS_PROJECTILE_MISSILE_H_
#define UNIVERSE_OBJECTS_PROJECTILE_MISSILE_H_

#include "universe/objects/projectiles/projectile.h"

#include <SFML/Graphics/VertexArray.hpp>

#include "universe/observers.h"

class Missile : public Projectile {
public:
  Missile(Universe* universe, sf::Vector2f& pos, float direction);
  ~Missile() override;

  // Returns true if the missile has been launched and is in flight.
  bool isLaunched() const { return m_task > Task::Launching; }

  // Launch the missile at the given target.
  void launchAt(Object* target);

  // Override the direction the missile is currently facing.
  void setDirection(float direction);

  // Override: Projectile
  int32_t getDamageAmount() const override;
  sf::FloatRect getBounds() const override;
  void tick(float adjustment) override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
  enum class Task {
    Idle,
    Launching,
    Tracking,
    Exploding,
  };

  // Called when the universe removed an object.
  void onObjectRemoved(Object* object);

  // The direction we are currently travelling.
  float m_direction;

  // Our current task.
  Task m_task{Task::Idle};

  // The target we are attacking.
  Object* m_target{nullptr};

  // The speed we are travelling at.
  float m_speed{0.f};

  // The time that has passed since we were launched.
  float m_timeSinceLaunch{0.f};

  // Id for the ObjectRemoved slot.
  size_t m_objectRemovedSlotId;

  // The shape we use to render the missile.
  sf::VertexArray m_shape;

  DISALLOW_IMPLICIT_CONSTRUCTORS(Missile);
};

#endif  // UNIVERSE_OBJECTS_PROJECTILE_MISSILE_H_
