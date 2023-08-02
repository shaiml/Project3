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
    bool scaleMousePress = true;
public:
    vector<sf::Text> genreTextBoxes;
    vector<sf::Text> typeBoxes;
    vector<sf::Text> scaleBoxes;
    bool selectedGenre = false;
    bool selectedType = false;
    bool selectedScale = false;

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
            if (i.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)))  && !selectedScale) {
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
            if (i.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && !selectedScale) {
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

    void energyOutlineFunction(sf::RenderWindow& window, sf::Event event) {
        sf::RectangleShape outline;
        outline.setFillColor(sf::Color::Transparent);
        outline.setOutlineThickness(4.f);
        outline.setOutlineColor(sf::Color::Green);

        sf::Text &selected = scaleBoxes[0];

        for (const auto& i: scaleBoxes) {
            window.draw(i);
            if (i.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))) && !selectedScale) {
                outline.setSize(sf::Vector2f(i.getGlobalBounds().width + 20.f, i.getGlobalBounds().height + 20.f));
                outline.setPosition(i.getPosition() - sf::Vector2f(4.f, 4.f));
                window.draw(outline);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (scaleMousePress) {
                        if (i.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            selectedScale = true;
                            selected = i;
                        }
                        scaleMousePress = false;
                    }
                } else if (event.type == sf::Event::MouseButtonReleased) {
                    scaleMousePress = true;
                }
            }
        }

        if (selectedScale) { // if genre selected continue display outline
            outline.setSize(sf::Vector2f(selected.getGlobalBounds().width + 20.f, selected.getGlobalBounds().height + 20.f));
            outline.setPosition(selected.getPosition() - sf::Vector2f(4.f, 4.f));
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
    headphones.setPosition(width / 8.0f - 30, height / 5.0f - 225);

    // Title
    sf::Text titleText;
    text.setText(titleText, pixel, "Create Your Playlist!", 90, sf::Color::Black);
    titleText.setStyle(sf::Text::Underlined);
    titleText.setPosition(width / 2.0f + 50, height / 4.0f - 250);

    sf::FloatRect titleRect = titleText.getLocalBounds();
    titleText.setOrigin(titleRect.left + titleRect.width/2.0f, titleRect.top  + titleRect.height/2.0f);

    // Genre Selection Text
    sf::Text genreText;
    text.setText(genreText, otherPixel, "Select Your Genre", 50, sf::Color::Black);
    genreText.setStyle(sf::Text::Bold);
    genreText.setPosition(width / 3.0f - 50, height / 4.0f - 150);

    sf::Text reference;  // used as an initializer
    text.setText(reference, otherPixel, "", 40, sf::Color::Black);
    reference.setPosition(width / 2.0f + 355, height / 3.0f - 20);
    text.genreTextBoxes.push_back(reference);

    // Genres
    sf::Text darkTrap, hipHop, emo, trapMetal, rap, underGround, rnb, pop;
    text.setText(darkTrap, otherPixel, "Dark Trap", 40, sf::Color::Black);
    darkTrap.setPosition(width / 9.0f - 50, height / 5.0f + 10);
    text.genreTextBoxes.push_back(darkTrap);

    text.setText(hipHop, otherPixel, "Hip-Hop", 40, sf::Color::Black);
    hipHop.setPosition(width / 3.0f, height / 5.0f + 10);
    text.genreTextBoxes.push_back(hipHop);

    text.setText(emo, otherPixel, "Emo", 40, sf::Color::Black);
    emo.setPosition(width / 2.0f + 125, height / 5.0f + 10);
    text.genreTextBoxes.push_back(emo);

    text.setText(trapMetal, otherPixel, "Trap Metal", 40, sf::Color::Black);
    trapMetal.setPosition(width / 2.0f + 350, height / 5.0f + 10);
    text.genreTextBoxes.push_back(trapMetal);

    text.setText(rap, otherPixel, "Rap", 40, sf::Color::Black);
    rap.setPosition(width / 9.0f - 50, height / 4.0f + 20);
    text.genreTextBoxes.push_back(rap);

    text.setText(underGround, otherPixel, "Underground", 40, sf::Color::Black);
    underGround.setPosition(width / 3.0f - 50, height / 4.0f + 20);
    text.genreTextBoxes.push_back(underGround);

    text.setText(rnb, otherPixel, "RNB", 40, sf::Color::Black);
    rnb.setPosition(width / 2.0f + 125, height / 4.0f + 20);
    text.genreTextBoxes.push_back(rnb);

    text.setText(pop, otherPixel, "Pop", 40, sf::Color::Black);
    pop.setPosition(width / 2.0f + 355, height / 4.0f + 20);
    text.genreTextBoxes.push_back(pop);

    // Playlist Type Selection
    sf::Text playListType, otherReference, constType, rangeType;
    text.setText(playListType, otherPixel, "Select Your Playlist Type", 50, sf::Color::Black);
    playListType.setStyle(sf::Text::Bold);
    playListType.setPosition(width / 4.0f - 50, height / 3.0f);

    text.setText(otherReference, otherPixel, "", 40, sf::Color::Black);
    otherReference.setPosition(width / 2.0f + 355, height / 3.0f - 20);
    text.typeBoxes.push_back(otherReference);

    text.setText(constType, otherPixel, "Constant", 40, sf::Color::Black);
    constType.setPosition(width / 3.0f - 10, height / 3.0f + 100);
    text.typeBoxes.push_back(constType);

    text.setText(rangeType, otherPixel, "Range", 40, sf::Color::Black);
    rangeType.setPosition(width / 2.0f + 100, height / 3.0f + 100);
    text.typeBoxes.push_back(rangeType);

    // Energy Level Selection
    sf::Text attributes, scale, energy;
    text.setText(attributes, otherPixel, "Select Your Energy Level", 50, sf::Color::Black);
    attributes.setStyle(sf::Text::Bold);
    attributes.setPosition(width / 5.0f + 35, height / 2.0f - 50);

    text.setText(scale, otherPixel, "(Lowest: 1 Highest: 10)", 30, sf::Color::Black);
    scale.setPosition(width / 3.0, height / 2.0f + 25);

    text.setText(energy, otherPixel, "Energy -", 40, sf::Color::Black);
    energy.setPosition(width / 9.0 - 50, height / 2.0f + 100);

    // Levels
    sf::Text one, two, three, four, five, six, seven, eight, nine, ten, scaleReference;
    text.setText(one, otherPixel, "1", 40, sf::Color::Black);
    text.setText(two, otherPixel, "2", 40, sf::Color::Black);
    text.setText(three, otherPixel, "3", 40, sf::Color::Black);
    text.setText(four, otherPixel, "4", 40, sf::Color::Black);
    text.setText(five, otherPixel, "5", 40, sf::Color::Black);
    text.setText(six, otherPixel, "6", 40, sf::Color::Black);
    text.setText(seven, otherPixel, "7", 40, sf::Color::Black);
    text.setText(eight, otherPixel, "8", 40, sf::Color::Black);
    text.setText(nine, otherPixel, "9", 40, sf::Color::Black);
    text.setText(ten, otherPixel, "10", 40, sf::Color::Black);

    one.setPosition(width / 5.0 + 100, height / 2.0f + 100);
    two.setPosition(width / 5.0 + 200, height / 2.0f + 100);
    three.setPosition(width / 5.0 + 300, height / 2.0f + 100);
    four.setPosition(width / 5.0 + 400, height / 2.0f + 100);
    five.setPosition(width / 5.0 + 500, height / 2.0f + 100);
    six.setPosition(width / 5.0 + 600, height / 2.0f + 100);
    seven.setPosition(width / 5.0 + 700, height / 2.0f + 100);
    eight.setPosition(width / 5.0 + 800, height / 2.0f + 100);
    nine.setPosition(width / 5.0 + 900, height / 2.0f + 100);
    ten.setPosition(width / 5.0 + 1000, height / 2.0f + 100);

    text.setText(scaleReference, otherPixel, "", 40, sf::Color::Black);
    scaleReference.setPosition(width / 2.0f + 355, height / 3.0f - 20);
    text.scaleBoxes.push_back(scaleReference);

    text.scaleBoxes.push_back(one);
    text.scaleBoxes.push_back(two);
    text.scaleBoxes.push_back(three);
    text.scaleBoxes.push_back(four);
    text.scaleBoxes.push_back(five);
    text.scaleBoxes.push_back(six);
    text.scaleBoxes.push_back(seven);
    text.scaleBoxes.push_back(eight);
    text.scaleBoxes.push_back(nine);
    text.scaleBoxes.push_back(ten);

    // Generate PlayList
    sf::Text generate;
    text.setText(generate, otherPixel, "Generating Playlist", 50, sf::Color::Black);
    generate.setStyle(sf::Text::Bold);
    generate.setPosition(width / 8.0 - 75, height / 2.0f + 300);

    // Loading Dots
    window.setFramerateLimit(3);
    sf::Text dotOne, dotTwo, dotThree;
    text.setText(dotOne, semiBold, ".", 100, sf::Color::Black);
    text.setText(dotTwo, semiBold, ".", 100, sf::Color::Black);
    text.setText(dotThree, semiBold, ".", 100, sf::Color::Black);

    dotOne.setPosition(width / 2.0 + 100, height / 2.0f + 250);
    dotTwo.setPosition(width / 2.0 + 200, height / 2.0f + 250);
    dotThree.setPosition(width / 2.0 + 300, height / 2.0f + 250);

    int loading = 0;
    bool isVisible = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (isVisible) {
            isVisible = false;
        }
        else {
            isVisible = true;
            loading = (loading % 3) + 1;
        }
        switch (loading) {
            case 1:
                dotOne.setString(".");
                dotTwo.setString("");
                dotThree.setString("");
                break;
            case 2:
                dotOne.setString(".");
                dotTwo.setString(".");
                dotThree.setString("");
                break;
            case 3:
                dotOne.setString(".");
                dotTwo.setString(".");
                dotThree.setString(".");
                break;
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
        if (text.selectedType) {
            window.draw(attributes);
            window.draw(scale);
            window.draw(energy);
            text.energyOutlineFunction(window, event);
        }
        if (text.selectedScale) {
            window.draw(generate);
            if (isVisible) {
                window.draw(dotOne);
                window.draw(dotTwo);
                window.draw(dotThree);
            }
        }
        window.display();
        sf::sleep(sf::seconds(0.5f));
    }

    return 0;
}
