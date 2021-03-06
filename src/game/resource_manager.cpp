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

#include "game/resource_manager.h"

#include <nucleus/logging.h>

#include "resources/sfml_loaders.h"

namespace {

static const struct {
  ResourceManager::Texture texture;
  const char* filename;
} kTextures[] = {
    {ResourceManager::Texture::CommandCenter,
     "images\\objects\\command_center.png"},
    {ResourceManager::Texture::Asteroid1, "images\\objects\\asteroid_1.png"},
    {ResourceManager::Texture::Asteroid2, "images\\objects\\asteroid_2.png"},
    {ResourceManager::Texture::Asteroid3, "images\\objects\\asteroid_3.png"},
};

}  // namespace

ResourceManager::ResourceManager() {
}

ResourceManager::~ResourceManager() {
}

bool ResourceManager::loadAll(const std::string& root) {
  if (!m_fontStore.load(Font::Default, loaders::fromFile<sf::Font>(
                                           root + "fonts\\arial.ttf"))) {
    LOG(Error) << "Could not load default font.";
    return false;
  }

  for (size_t i = 0; i < ARRAY_SIZE(kTextures); ++i) {
    if (!m_textureStore.load(kTextures[i].texture,
                             loaders::fromFile<sf::Texture>(
                                 root + std::string(kTextures[i].filename)))) {
      LOG(Error) << "Could not load texture. (" << kTextures[i].filename << ")";
      return false;
    }
  }

  return true;
}

sf::Font* ResourceManager::getFont(Font font) {
  return m_fontStore.get(font);
}

sf::Texture* ResourceManager::getTexture(Texture texture) {
  return m_textureStore.get(texture);
}
