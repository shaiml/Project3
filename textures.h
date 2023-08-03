/*copyright: professor fox */

/*
 * how to use this:
 * sf::Sprite sprite;
 * sprite.setTexture(TextureManager::GetTexture("filename"));
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
class TextureManager {
protected:
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string textureName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear();
};

