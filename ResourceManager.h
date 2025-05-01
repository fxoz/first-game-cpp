#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <memory>
#include <iostream>
#include <cstdlib>

template <typename Resource>
class ResourceManager {
public:
    std::shared_ptr<Resource> get(const std::string &filename) {
        auto it = resources.find(filename);
        if (it != resources.end()) {
            return it->second;
        }

        std::shared_ptr<Resource> resource = std::make_shared<Resource>();
        if (!resource->loadFromFile(filename)) {
            std::cerr << "Error loading file: " << filename << std::endl;
            std::exit(EXIT_FAILURE);
        }
        resources[filename] = resource;
        return resource;
    }

private:
    std::map<std::string, std::shared_ptr<Resource>> resources;
};

class ResourceHolder {
public:
    static ResourceHolder& getInstance() {
        static ResourceHolder instance;
        return instance;
    }

    std::shared_ptr<sf::Texture> getTexture(const std::string &filename) {
        return textureManager.get(filename);
    }

    std::shared_ptr<sf::Font> getFont(const std::string &filename) {
        return fontManager.get(filename);
    }

    std::shared_ptr<sf::SoundBuffer> getSoundBuffer(const std::string &filename) {
        return soundBufferManager.get(filename);
    }

private:
    ResourceHolder() = default;
    ResourceHolder(const ResourceHolder&) = delete;
    ResourceHolder& operator=(const ResourceHolder&) = delete;

    ResourceManager<sf::Texture>       textureManager;
    ResourceManager<sf::Font>          fontManager;
    ResourceManager<sf::SoundBuffer>   soundBufferManager;
};
