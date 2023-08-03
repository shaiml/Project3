#include "visuals.h"

void Text::setText(sf::Text &text, sf::Font &font, const string &str, unsigned int characterSize, const sf::Color &fillColor) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(characterSize);
    text.setFillColor(fillColor);
}

void Text::genreOutLineFunction(sf::RenderWindow &window, sf::Event event) {
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

void Text::typeOutlineFunction(sf::RenderWindow &window, sf::Event event) {
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

void Text::energyOutlineFunction(sf::RenderWindow &window, sf::Event event) {
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


