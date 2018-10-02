//
//  main.cpp
//  TicTacTo
//
//  Created by Tarek Abdelrahman on 2018-05-15.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <cmath>
#include <tic-tac-toe/playMove.h>

using namespace std;
using namespace sf;


int main() {

    /************************************************************************************************************/
    /* The following variables define the state of the game                                                     */
    /************************************************************************************************************/

    // You should complete the following declarations
    // Make sure to initalize the variables

    // The game board array
    int gameBoard[3][3] = {Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty,Empty};
    // An boolean that represents the turn in the game
    bool turn = true;
    // A boolean to represent if the move is valid
    bool validMove = true;
    // A boolean to represent if the game is over
    bool is_game_over = false;

    // An integer that represents the win code
    int winCode = 0;
    /************************************************************************************************************/
    /* Insert code that loads the various images used by the game and creates the sprites                       */
    /* The loading of the X image is shown. Repreat for the rest of the images                                  */
    /************************************************************************************************************/

    // Get the X image
    sf::Texture X_texture;
    if (!X_texture.loadFromFile("X.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite X_sprite(X_texture);

    // Get the O image
    sf::Texture O_texture;
    if (!O_texture.loadFromFile("O.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite O_sprite(O_texture);
    
    // Get the blank image
    sf::Texture blank_texture;
    if (!blank_texture.loadFromFile("blank.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite blank_sprite(blank_texture);
    
    /************************************************************************************************************/
    /* Insert code that creates the window and displays it                                                      */
    /************************************************************************************************************/
    
    // First, we find the sizes of the images so we can determine the size of the window we must create
    // The images (X, O and Black) are assumed to be square are are all of the same size
    // Thus, we just find the size of one of them
    
    // The tile size is the size of the images
    const int tileSize = blank_texture.getSize().x;

    // The cell borders (thick lines) are rectangles
    // The size of these rectangles is 1/20th of the size of the tile by 3 cell sizes plus 2 barWidth's
    const int barWidth = tileSize/20;
    const int barHeight = boardSize*tileSize + (boardSize-1)*barWidth;

    // The size of the window in pixels can now be calculated
    const int windowSize = boardSize*tileSize + (boardSize-1)*barWidth;

    // Create the main window: it has a title bar and a close button, but is not resizable
    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "ECE244 Tic-Tac-Toe", sf::Style::Titlebar | sf::Style::Close);

    // Set the Icon that appears in the task bar when the window is minimized
    // Insert you code here, see the lab handout
    sf::Image minimizeIcon;
    if(!minimizeIcon.loadFromFile("icon.jpg")){
        return EXIT_FAILURE;
    }
    window.setIcon(minimizeIcon.getSize().x, minimizeIcon.getSize().y, minimizeIcon.getPixelsPtr());
    // Create the horizonal (vertical) borders as rectangles of sizes barWidth and barHeight (berHeight and barWidth)
    // Insert your code here
    //
    sf:: RectangleShape verticleRectangle0(sf::Vector2f(barWidth, barHeight));
        verticleRectangle0.setPosition(windowSize/3 - tileSize/20, 0);
        verticleRectangle0.setFillColor(sf::Color::Black);
    
    sf:: RectangleShape verticleRectangle1(sf::Vector2f(barWidth, barHeight));
        verticleRectangle1.setPosition(windowSize*2/3, 0);
        verticleRectangle1.setFillColor(sf::Color::Black);
    
    sf:: RectangleShape horizontalRectangle0(sf::Vector2f(barHeight, barWidth));
        horizontalRectangle0.setPosition(0, windowSize/3 - tileSize/20);
        horizontalRectangle0.setFillColor(sf::Color::Black);
        
    sf:: RectangleShape horizontalRectangle1(sf::Vector2f(barHeight, barWidth));
        horizontalRectangle1.setPosition(0, windowSize*2/3);
        horizontalRectangle1.setFillColor(sf::Color::Black);
        
        //white rectangles
        
    sf:: RectangleShape rec1(sf::Vector2f(barHeight, barWidth));
        rec1.setPosition(0, windowSize/6 - tileSize/20);
        rec1.setFillColor(sf::Color::White);
        
    sf:: RectangleShape rec2(sf::Vector2f(barHeight, barWidth));
        rec2.setPosition(0, windowSize/2 - tileSize/20);
        rec2.setFillColor(sf::Color::White);
        
    sf:: RectangleShape rec3(sf::Vector2f(barHeight, barWidth));
        rec3.setPosition(0, windowSize*5/6);
        rec3.setFillColor(sf::Color::White);
        
    sf:: RectangleShape rec4(sf::Vector2f(barWidth, barHeight));
        rec4.setPosition(windowSize/6 - tileSize/20, 0);
        rec4.setFillColor(sf::Color::White);
        
    sf:: RectangleShape rec5(sf::Vector2f(barWidth, barHeight));
        rec5.setPosition(windowSize/2 - tileSize/25, 0);
        rec5.setFillColor(sf::Color::White);
    
    sf:: RectangleShape rec6(sf::Vector2f(barWidth, barHeight));
        rec6.setPosition(windowSize*5/6, 0);
        rec6.setFillColor(sf::Color::White);
        
    sf:: RectangleShape rec7(sf::Vector2f(barWidth*sqrt(2), barHeight*sqrt(2)));
        rec7.setPosition(0, 0);
        rec7.setFillColor(sf::Color::White);
        rec7.rotate(-45);
        
     sf:: RectangleShape rec8(sf::Vector2f(barWidth*sqrt(2), barHeight*sqrt(2)));
        rec8.setPosition(windowSize,0);
        rec8.setFillColor(sf::Color::White);
        rec8.rotate(45);
    
    /************************************************************************************************************/
    /* This is the main event loop of the code                                                                  */
    /************************************************************************************************************/

    // Start the game loop that runs as long as the window is open
    while (window.isOpen()) {
        // The event
        sf::Event event;

        // Process the events
        while (window.pollEvent(event)) {

            // This is the handling of the close window event
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            // Left mouse button pressed: get the click position and play the move
            // is_game_over is a variable you should define above
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                // left mouse button is pressed: get the coordinates in pixels
                // Insert your code to get the coordinates here
                sf::Vector2i localPosition = Mouse::getPosition(window);
                int xPosition = localPosition.x;
                int yPosition = localPosition.y;
                // Convert the pixel coordinates into game board rows and columns
                // Just divide by tileSize
                // Observe that the x axis is the rows and the y axis is the columns
                // Also make sure that row and column values are valid
                // Insert your code below
                int row = yPosition/tileSize;
                int col = xPosition/tileSize;
                // Play the move by calling the playMove function
                // Insert your code below
                playMove(gameBoard, row, col, turn, validMove, is_game_over, winCode);
            }
        }

        // Insert code to draw the tiles using the sprites created earlier
        // You must determine the position of each cell on the grid, taking into account the width of
        // the border and then position the sprite there and draw it.
        // Draw the entire board, cell borders included,
        // reflecting any move that has just happened (check the gameBoard array)
        // Further, if the game is over and one player wins, you must create and draw a rectangle of
        // windowSize width and 10 pixels height to indicate the winning marks
        // The fill of this rectangle should be white
        
        
        // Insert your code here
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (gameBoard[j][i] == 0)
                {
                    blank_sprite.setPosition(i*tileSize+(i)*tileSize/20, j*tileSize+(j)*tileSize/20);
                    window.draw(blank_sprite);
                }
                else if (gameBoard [j][i] == 1)
                {
                    X_sprite.setPosition(i*tileSize+(i)*tileSize/20, j*tileSize +(j)*tileSize/20);
                    window.draw(X_sprite);
                }
                else
                {
                    O_sprite.setPosition(i*tileSize +(i)*tileSize/20, j*tileSize+(j)*tileSize/20);
                    window.draw(O_sprite);
                }
            }
        }
       window.draw(verticleRectangle0);
       window.draw(verticleRectangle1);
       window.draw(horizontalRectangle0);
       window.draw(horizontalRectangle1);
        
        if(winCode == 1)
        {
            window.draw(rec1);
        }
        else if(winCode == 2)
        {
            window.draw(rec2);
        }
        else if(winCode == 3)
        {
            window.draw(rec3);
        }
        else if(winCode == 4)
        {
            window.draw(rec4);
        }
        else if(winCode == 5)
        {
            window.draw(rec5);
        }
        else if(winCode == 6)
        {
            window.draw(rec6);
        }
        else if(winCode == 7)
        {
            window.draw(rec7);
        }
        else if (winCode == 8)
        {
            window.draw(rec8);
        }
        
        window.display();
        // Display to the window
    }

    return EXIT_SUCCESS;
}
