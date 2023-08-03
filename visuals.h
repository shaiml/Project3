#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#pragma once
using namespace std;


class Text {
private:
    bool mousePress = true;
    bool otherMousePress = true;
    bool scaleMousePress = true;
    bool scaleMousePressTwo = true;
    sf::Text typeSelected;
    sf::Text typeSelectedTwo;
public:
    vector<sf::Text> genreTextBoxes;
    vector<sf::Text> typeBoxes;
    vector<sf::Text> scaleBoxes;
    vector<sf::Text> rangeBoxes;

    bool selectedGenre = false;
    bool selectedType = false;
    bool selectedScale = false;
    bool selectedScaleTwo = false;
    bool selectedAmount = false;

    string genre = "";
    string type = "";
    int constLevel = 1;
    int rangeOne = 1;
    int rangeTwo = 1;

    void setText(sf::Text &text, sf::Font &font, const string &str, unsigned int characterSize, const sf::Color &fillColor);
    void genreOutLineFunction (sf::RenderWindow& window, sf::Event event); // handles outline for genre selection
    void typeOutlineFunction(sf::RenderWindow& window, sf::Event event);  // handles outline for type selection
    void energyOutlineFunction(sf::RenderWindow& window, sf::Event event);  // handles outline for energy level
    void rangeOutlineFunction(sf::RenderWindow& window, sf::Event event);  // handles outline for energy level


};

