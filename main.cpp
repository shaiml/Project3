#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "textures.h"
using namespace std;

class Text {
private:
    bool mousePress = true;
    bool otherMousePress = true;
public:
    vector<sf::Text> genreTextBoxes;
    vector<sf::Text> typeBoxes;
    bool selectedGenre = false;
    bool selectedType = false;

    void setText (sf::Text& text, sf::Font& font, const string& str, unsigned int characterSize, const sf::Color& fillColor) {
        text.setFont(font);
        text.setString(str);
        text.setCharacterSize(characterSize);
        text.setFillColor(fillColor);
    }
    void genreOutLineFunction (sf::RenderWindow& window, sf::Event event) {  // handles outline for genre selection
        sf::RectangleShape outline;
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineThickness(4.f);
        outline.setOutlineColor(sf::Color::Green);

        sf::Text &selected = genreTextBoxes[0]; // initializer

        for (const auto &i: genreTextBoxes) {
            window.draw(i);
            if (i.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                outline.setSize(sf::Vector2f(i.getGlobalBounds().width + 20.f, i.getGlobalBounds().height + 20.f));
                outline.setPosition(i.getPosition() - sf::Vector2f(4.f, 4.f));
                window.draw(i);
                window.draw(outline);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (mousePress) {
                        if (i.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            selectedGenre = true;
                            selected = i;
                        }
                        mousePress = false;
                    }
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    mousePress = true;
                }
            }
        }
        if (selectedGenre) {  // if genre selected continue display outline
            outline.setSize(sf::Vector2f(selected.getGlobalBounds().width + 20.f, selected.getGlobalBounds().height + 20.f));
            outline.setPosition(selected.getPosition() - sf::Vector2f(4.f, 4.f));
            window.draw(outline);
        }
    }
    void typeOutlineFunction(sf::RenderWindow& window, sf::Event event) {  // handles outline for type selection
        sf::RectangleShape outline;
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineThickness(4.f);
        outline.setOutlineColor(sf::Color::Green);

        sf::Text &typeSelected = typeBoxes[0];

        for (const auto& i: typeBoxes) {
            window.draw(i);
            if (i.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))) {
                outline.setSize(
                        sf::Vector2f(i.getGlobalBounds().width + 20.f, i.getGlobalBounds().height + 20.f));
                outline.setPosition(i.getPosition() - sf::Vector2f(4.f, 4.f));
                window.draw(outline);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (otherMousePress) {
                        if (i.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            selectedType = true;
                            typeSelected = i;
                        }
                        otherMousePress = false;
                    }
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    otherMousePress = true;
                }
            }
        }

        if (selectedType) { // if genre selected continue display outline
            outline.setSize(sf::Vector2f(typeSelected.getGlobalBounds().width + 20.f, typeSelected.getGlobalBounds().height + 20.f));
            outline.setPosition(typeSelected.getPosition() - sf::Vector2f(4.f, 4.f));
            window.draw(outline);
        }
    }
};

int main() {
    Text text;
    float width = 1500;
    float height = 1500;
    sf::RenderWindow window(sf::VideoMode(width, height), "Beat Builders");
    sf::Color lightGreen(162, 252, 162);

    sf::Font pixel;
    sf::Font semiBold;
    sf::Font otherPixel;

    pixel.loadFromFile("files/VPPixel-Simplified.otf");
    semiBold.loadFromFile("files/Panton-Trial-SemiBold.ttf");
    otherPixel.loadFromFile("files/Big Pixel demo.otf");

    sf::Sprite headphones;
    headphones.setScale(.20f, .20f);
    headphones.setTexture(TextureManager::GetTexture("headphones"));
    headphones.setPosition(width / 8.0f - 30, height / 5.0f - 175);

    sf::Text titleText;
    text.setText(titleText, pixel, "Create Your Playlist!", 90, sf::Color::Black);
    titleText.setStyle(sf::Text::Underlined);
    titleText.setPosition(width / 2.0f + 50, height / 4.0f - 200);

    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top  + titleRect.height/2.0f);

    // Genre Selection
    sf::Text genreText;
    text.setText(genreText, otherPixel, "Select Your Genre", 50, sf::Color::Black);
    genreText.setStyle(sf::Text::Bold);
    genreText.setPosition(width / 3.0f - 50, height / 4.0f - 100);

    sf::Text reference;  // used as an initializer
    text.setText(reference, otherPixel, "", 40, sf::Color::Black);
    reference.setPosition(width / 2.0f + 355, height / 3.0f - 20);
    text.genreTextBoxes.push_back(reference);

    sf::Text darkTrap;
    text.setText(darkTrap, otherPixel, "Dark Trap", 40, sf::Color::Black);
    darkTrap.setPosition(width / 9.0f - 50, height / 4.0f + 10);
    text.genreTextBoxes.push_back(darkTrap);

    sf::Text hipHop;
    text.setText(hipHop, otherPixel, "Hip-Hop", 40, sf::Color::Black);
    hipHop.setPosition(width / 3.0f, height / 4.0f + 10);
    text.genreTextBoxes.push_back(hipHop);

    sf::Text emo;
    text.setText(emo, otherPixel, "Emo", 40, sf::Color::Black);
    emo.setPosition(width / 2.0f + 125, height / 4.0f + 10);
    text.genreTextBoxes.push_back(emo);

    sf::Text trapMetal;
    text.setText(trapMetal, otherPixel, "Trap Metal", 40, sf::Color::Black);
    trapMetal.setPosition(width / 2.0f + 350, height / 4.0f + 10);
    text.genreTextBoxes.push_back(trapMetal);

    sf::Text rap;
    text.setText(rap, otherPixel, "Rap", 40, sf::Color::Black);
    rap.setPosition(width / 9.0f - 50, height / 3.0f - 20);
    text.genreTextBoxes.push_back(rap);

    sf::Text underGround;
    text.setText(underGround, otherPixel, "Underground", 40, sf::Color::Black);
    underGround.setPosition(width / 3.0f - 50, height / 3.0f - 20);
    text.genreTextBoxes.push_back(underGround);

    sf::Text rnb;
    text.setText(rnb, otherPixel, "RNB", 40, sf::Color::Black);
    rnb.setPosition(width / 2.0f + 125, height / 3.0f - 20);
    text.genreTextBoxes.push_back(rnb);

    sf::Text pop;
    text.setText(pop, otherPixel, "Pop", 40, sf::Color::Black);
    pop.setPosition(width / 2.0f + 355, height / 3.0f - 20);
    text.genreTextBoxes.push_back(pop);

    // Playlist Type Selection
    sf::Text playListType;
    text.setText(playListType, otherPixel, "Select Your Playlist Type", 50, sf::Color::Black);
    playListType.setStyle(sf::Text::Bold);
    playListType.setPosition(width / 4.0f - 50, height / 3.0f + 75);

    sf::Text otherReference; // used as an initializer
    text.setText(otherReference, otherPixel, "", 40, sf::Color::Black);
    otherReference.setPosition(width / 2.0f + 355, height / 3.0f - 20);
    text.typeBoxes.push_back(otherReference);

    sf::Text constType;
    text.setText(constType, otherPixel, "Constant", 40, sf::Color::Black);
    constType.setPosition(width / 3.0f - 50, height / 2.0f - 80);
    text.typeBoxes.push_back(constType);

    sf::Text rangeType;
    text.setText(rangeType, otherPixel, "Range", 40, sf::Color::Black);
    rangeType.setPosition(width / 2.0f + 50, height / 2.0f - 80);
    text.typeBoxes.push_back(rangeType);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(lightGreen);
        window.draw(titleText);
        window.draw(genreText);
        window.draw(headphones);
        text.genreOutLineFunction(window, event);
        if (text.selectedGenre) {
            window.draw(playListType);
            text.typeOutlineFunction(window, event);
        }
        window.display();
    }

    return 0;
}
