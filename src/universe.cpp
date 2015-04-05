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

#include "universe.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <base/logging.h>

Universe::Universe(const sf::Vector2f& viewportSize) {
}

Universe::~Universe() {
}

void Universe::handleInput(sf::Event& event) {
  m_camera.handleInput(event);
}

void Universe::tick(float adjustment) {
  m_camera.tick(adjustment);
}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // Store the original view state.
  sf::View origView = target.getView();

  sf::Vector2f viewportSize{static_cast<float>(target.getSize().x),
                            static_cast<float>(target.getSize().y)};

  // Set the new view to our camera view.
  target.setView(m_camera.calculateCameraView(viewportSize));

  // Render some reference object.
  sf::RectangleShape rectangle(sf::Vector2f(100.f, 100.f));
  rectangle.setOrigin(50.f, 50.f);
  rectangle.move(sf::Vector2f(10.f, 10.f));
  target.draw(rectangle);

  // Render the camera target.
  target.draw(m_camera);

  // Reset the target view.
  target.setView(origView);
}
