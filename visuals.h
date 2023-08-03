#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#pragma once
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
    bool selectedAmount = false;

    string genre;
    string type;
    int constLevel;
    int rangeOne;
    int rangeTwo;

    void setText(sf::Text &text, sf::Font &font, const string &str, unsigned int characterSize, const sf::Color &fillColor);
    void genreOutLineFunction (sf::RenderWindow& window, sf::Event event); // handles outline for genre selection
    void typeOutlineFunction(sf::RenderWindow& window, sf::Event event);  // handles outline for type selection
    void energyOutlineFunction(sf::RenderWindow& window, sf::Event event);  // handles outline for energy level

};

