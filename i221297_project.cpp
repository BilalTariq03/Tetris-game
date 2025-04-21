/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You don't need to change anything in the driver code/main function except the part(s) where instructed.
 * You are expected to define your functionalities in the "functionality.h" header and call them here in the instructed part(s).
 * The game is started with a small box, you need to create other possible in "pieces.h" file in form of array.
    E.g., Syntax for 2 pieces, each having four coordinates -> int Pieces[2][4];
 * Load the images into the textures objects from img directory.
 * Don't make any changes to the "utils.h" header file except for changing the coordinate of screen or global variables of the game.
 * SUGGESTION: If you want to make changes in "utils.h", do it once you complete rest of the functionalities.
 * TIP: You can study SFML for drawing scenes, sprites and window.
 * */


 /*
 Name: Muhammad Bilal Tariq
 Roll  no: 22I-1297	*/


#include <SFML/Graphics.hpp>
#include <time.h>
#include "utils.h"
#include "pieces.h"
#include "functionality.h"
#include<iostream>
using namespace sf;
int main() {
    srand(time(0));
    RenderWindow window(VideoMode(320, 480), title);
    Texture obj1, obj2, obj3, obj4, obj5;
    obj1.loadFromFile("img/tiles.png");
    obj2.loadFromFile("img/background.png");
    obj3.loadFromFile("img/frame.png");
    obj4.loadFromFile("img/game_over.png");
    obj5.loadFromFile("img/pause.jpg");
    /*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    //To display rectangle to show next piece
    RectangleShape rectangle(Vector2f(80, 150));
    rectangle.setFillColor(Color(10, 10, 10));
    rectangle.setOutlineColor(Color(250, 250, 250));
    rectangle.setOutlineThickness(5);
    rectangle.sf::Transformable::setPosition(230, 130);
    Sprite sprite(obj1), background(obj2), frame(obj3), end(obj4), pause(obj5);
    //For game over picture
    end.setTexture(obj4);
    end.setScale(Vector2f(0.6, 0.8));
    pause.setTexture(obj5);
    pause.setScale(Vector2f(0.6, 0.8));

    int delta_x = 0, nextColor = 1+ rand() % 7, colorNum = 1, nextPiece=1;
    float timer = 0, delay = 0.5;
    bool rotate = 0;

    int lines_cleared = 0, count = 0, a = 0;
    int level = 1, score_count = 0;
    float timer2 = 0;
    int stop = 0;
    Clock clock;

    if (stop == 0)

        while (window.isOpen()) {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            //---Event Listening Part---//
            Event e;
            while (window.pollEvent(e)) {                    //Event is occurring - until the game is in running state
                if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                    window.close();                            //Opened window disposes
                if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                    if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                        rotate = true;                         //Rotation gets on
                    else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                        delta_x = -1;                          //Change in X-Axis - Negative
                    else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                        delta_x = 1;                           //Change in X-Axis - Positive
                    if (e.key.code == sf::Keyboard::Space) {
                        HardDrop(colorNum, nextColor, nextPiece,level);
                        DrawNextPiece(window, nextColor, nextPiece, obj1);

                    }
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
                delay = 0.1;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05
            
            if (stop == 0) {
                if (Keyboard::isKeyPressed(Keyboard::H))
                {
                    stop = 1;

                }
            }
            else if (stop == 1)
            {
                if (Keyboard::isKeyPressed(Keyboard::H))
                {
                    stop = 0;

                }
            }
            ///////////////////////////////////////////////
            ///*** START CALLING YOUR FUNCTIONS HERE ***///


            fallingPiece(timer, delay, colorNum, level,nextColor,nextPiece);               //Example: fallingPiece() function is called here
            anamoly();
            if (rotate == true) {
                Rotate();	//calling rotate function to rotate blocks
            }
            Move(delta_x);	//calling move function to move blocks
            Reset(delta_x, delay, rotate, level);	//reseting all values
            Remove_Line(lines_cleared, score_count); //if line is completed it will be removed

            //To  calculate levels
            if (level <= 10)	//max levels are 10
            {
                Clock level_time;
                float elapsed = level_time.getElapsedTime().asSeconds();
                level_time.restart();
                timer2 += elapsed;
                if (timer2 >= 0.0288)	//one level will increase after 5 min
                {
                    level++;
                    timer2 = 0;
                }
            }

            //Setting score text style to display
            sf::Text score;
            sf::Font font;
            font.loadFromFile("img/Forwa_font.TTF"); //selecting font
            score.setFont(font);
            score.setCharacterSize(10); //selecting character size
            score.setFillColor(sf::Color::White); //selecting color
            score.setPosition(230, 310);	//position of text
            sf::Vector2<float> score_scale(1.5f, 1.5f);	//scale of text
            score.setScale(score_scale);

            ScoreText(score, lines_cleared, level, score_count); //calling score function to store all values





            ///*** YOUR CALLING STATEMENTS END HERE ***///
            //////////////////////////////////////////////


            window.clear(Color::Black);
            window.draw(background);

            DrawNextPiece(window, nextColor, nextPiece, obj1);


            for (int i = 0; i < M; i++) {
                for (int j = 0; j < N; j++) {
                    if (gameGrid[i][j] == 0)
                        continue;
                    sprite.setTextureRect(IntRect(gameGrid[i][j] * 18, 0, 18, 18));
                    sprite.setPosition(j * 18, i * 18);
                    sprite.move(28, 31); //offset
                    window.draw(sprite);
                }
            }
            for (int i = 0; i < 4; i++) {
                sprite.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
                sprite.setPosition(point_1[i][0] * 18, point_1[i][1] * 18);
                sprite.move(28, 31);
                window.draw(sprite);

            }


     //       window.draw(rectangle); //To draw rectangle on screen
            window.draw(score);	// to display final score text on screen
            //---The Final on Which Everything is Drawn Over is Loaded---//
            window.draw(frame);

            if (!GameOver()) //this will draw game over picture
            {
                window.clear();
                window.draw(end);
            }
            if (stop == 1)
            {
                window.clear();
                window.draw(pause);
            }
            //---The Window that now Contains the Frame is Displayed---//

            window.display();
        }
    return 0;
}
