/*copyright: professor fox */
#include "textures.h"
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string fileName) {
    string path = "files/images/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
    if (textures.find(textureName) == textures.end()) {
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear();
}
