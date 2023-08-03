#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "textures.h"
#include "visuals.h"
using namespace std;

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
    scale.setPosition(width / 3.0f, height / 2.0f + 25);

    text.setText(energy, otherPixel, "Energy -", 40, sf::Color::Black);
    energy.setPosition(width / 9.0f - 50, height / 2.0f + 100);

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

    one.setPosition(width / 5.0f + 100, height / 2.0f + 100);
    two.setPosition(width / 5.0f + 200, height / 2.0f + 100);
    three.setPosition(width / 5.0f + 300, height / 2.0f + 100);
    four.setPosition(width / 5.0f + 400, height / 2.0f + 100);
    five.setPosition(width / 5.0f + 500, height / 2.0f + 100);
    six.setPosition(width / 5.0f + 600, height / 2.0f + 100);
    seven.setPosition(width / 5.0f + 700, height / 2.0f + 100);
    eight.setPosition(width / 5.0f + 800, height / 2.0f + 100);
    nine.setPosition(width / 5.0f + 900, height / 2.0f + 100);
    ten.setPosition(width / 5.0f + 1000, height / 2.0f + 100);

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

    // Number of Songs Prompt
    sf::Text numSongs;
    text.setText(numSongs, otherPixel, "Enter Number of Songs (1-50): ", 50, sf::Color::Black);
    numSongs.setStyle(sf::Text::Bold);
    numSongs.setPosition(width / 8.0 - 75, height / 2.0f + 200);

    // User Input
    sf::Text userInput;
    userInput.setFont(otherPixel);
    userInput.setCharacterSize(50);
    userInput.setPosition(width / 2.0 + 430, height / 2.0f + 235);
    userInput.setFillColor(sf::Color::Black);

    string num;
    userInput.setString(""); // initial cursor
    sf::FloatRect userInputRect = userInput.getLocalBounds();
    userInput.setOrigin(userInputRect.left + userInputRect.width/2.0f, userInputRect.top  + userInputRect.height/2.0f);

    // Generate PlayList Text
    sf::Text generate;
    text.setText(generate, otherPixel, "Generating Playlist", 50, sf::Color::Black);
    generate.setStyle(sf::Text::Bold);
    generate.setPosition(width / 8.0f - 75, height / 2.0f + 300);

    // Loading Dots
    window.setFramerateLimit(3);
    sf::Text dotOne, dotTwo, dotThree;
    text.setText(dotOne, semiBold, ".", 100, sf::Color::Black);
    text.setText(dotTwo, semiBold, ".", 100, sf::Color::Black);
    text.setText(dotThree, semiBold, ".", 100, sf::Color::Black);

    dotOne.setPosition(width / 2.0f + 100, height / 2.0f + 250);
    dotTwo.setPosition(width / 2.0f + 200, height / 2.0f + 250);
    dotThree.setPosition(width / 2.0f + 300, height / 2.0f + 250);

    int loading = 0;
    int enteredNumber;
    bool isVisible = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered) { // Allow Digits and Delete or Backspace
                if ((event.text.unicode >= 0x30 && event.text.unicode <= 0x39) || event.text.unicode == 127) {
                    if (num.size() < 2) {
                        num += static_cast<char>(event.text.unicode);
                        userInput.setString(num); // Name + cursor
                        enteredNumber = stoi(num);
                        sf::FloatRect inputRect = userInput.getLocalBounds(); // Center text
                        userInput.setOrigin(inputRect.left + inputRect.width / 2.0f,inputRect.top + inputRect.height / 2.0f);
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::BackSpace) {
                    if (!num.empty()) {
                        num.pop_back();
                        userInput.setString(num);
                        // Center text
                        sf::FloatRect inputRect = userInput.getLocalBounds();
                        userInput.setOrigin(inputRect.left + inputRect.width/2.0f, inputRect.top  + inputRect.height/2.0f);
                    }
                }
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                if (enteredNumber >= 1 && enteredNumber <= 50) {
                    text.selectedAmount = true;
                }
            }
        }
        if (isVisible) {
            isVisible = false;
        }
        else {
            isVisible = true;
            loading = (loading % 3) + 1;
        }
        switch (loading) {  // display dots in loading sequence
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

        text.genreOutLineFunction(window, event); // displays genre outline and text

        if (text.selectedGenre) {
            window.draw(playListType);
            text.typeOutlineFunction(window, event);  // displays playlist type outline and text
        }
        if (text.selectedType) {
            window.draw(attributes);
            window.draw(scale);
            window.draw(energy);
            text.energyOutlineFunction(window, event);  // displays energy level outline and text
        }
        if (text.selectedScale) {  // displays number of songs prompt
            window.draw(numSongs);
            window.draw(userInput);
        }

        if (text.selectedAmount) {  // all selections made, generate playlist
            window.draw(generate);
            if (isVisible) {
                window.draw(dotOne);
                window.draw(dotTwo);
                window.draw(dotThree);
            }
        }
        window.display();
        sf::sleep(sf::seconds(0.5f));  // sets animation speed
    }
    return 0;
}
