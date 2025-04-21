/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

 //---Piece Starts to Fall When Game Starts---//

 /*
 Name: Muhammad Bilal Tariq
 Roll  no: 22I-1297	*/

#include <SFML/Graphics.hpp>
#include<iostream>
using namespace std;
using namespace sf;
void fallingPiece(float& timer, float& delay, int& colorNum, int level, int& nextColor,int& nextPiece) {
	int n;
	if (timer > delay) {
		for (int i = 0; i < 4; i++) {
			point_2[i][0] = point_1[i][0];
			point_2[i][1] = point_1[i][1];
			point_1[i][1] += 1;                   //How much units downward
		}

		if (!anamoly()) {
			for (int i = 0; i < 4; i++)
				gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
			
			colorNum = nextColor;
			n = nextPiece;

			nextColor = 1 + rand() % 7;

			if (level == 1)
				nextPiece = rand() % 4;
			else
				nextPiece = rand() % 7;

			//--- Un-Comment this Part When You Make BLOCKS array---//

			for (int i = 0; i < 4; i++) {
				point_1[i][0] = BLOCKS[n][i] % 2;
				point_1[i][1] = BLOCKS[n][i] / 2;
			}

		}
		timer = 0;
	}
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///


/*//----------For movement ---------//


	delta_x will be added to x_axis position of block
	and will mive it right or left*/
void Move(int x_axis)
{
	for (int i = 0; i < 4; i++)
	{
		point_2[i][0] = point_1[i][0];
		point_2[i][1] = point_1[i][1];
		point_1[i][0] += x_axis;
	}
	if (!anamoly()) {	///to stop moving in other boxes and wall
		for (int i = 0; i < 4; i++)
		{
			point_1[i][0] = point_2[i][0];
			point_1[i][1] = point_2[i][1];
		}
	}
}

//----------- For Rotation------------ //
/*	Taking center of rotation of every block and subtracting
	it from evey part to rotate it completely*/
void Rotate() {
	int tmp1 = 0, tmp2 = 0;
	tmp1 = point_1[1][0];
	tmp2 = point_1[1][1];
	for (int i = 0; i < 4; i++)
	{
		int x = point_1[i][1] - tmp2;
		int y = point_1[i][0] - tmp1;
		point_1[i][0] = tmp1 - x;
		point_1[i][1] = tmp2 + y;
	}
	if (!anamoly()) {	///to stop rotating in other boxes and wall
		for (int i = 0; i < 4; i++)
		{
			point_1[i][0] = point_2[i][0];
			point_1[i][1] = point_2[i][1];
		}
	}
}

//------To remove lines, count score, and count lines-------//
/*	This Function will check for every row and every column.
	If All Blocks are filled then line will be deleted*/
void Remove_Line(int& lines_cleared, int& score_count)
{
	int k = M - 1, c, clear = 0;	//c is for each block clear is to check line cleared
	for (int i = M - 1; i > 0; i--)
	{
		c = 0;
		clear = 0;
		for (int j = 0; j < N; j++) {
			if (gameGrid[i][j])
			{
				c++;
			}
			gameGrid[k][j] = gameGrid[i][j];
		}
		if (c < N)		//If all blocks are not filled
		{
			k--;
		}
		if (c == N)	//If All blocks are filled then line number will increase
		{
			lines_cleared++;
			clear++;
		}
		//To count score according to lines cleared
		if (clear == 1)
		{
			score_count += 10;
		}
		else if (clear == 2)
		{
			score_count += 20;
		}
		else if (clear == 3)
		{
			score_count += 30;
		}
		else if (clear >= 4)
		{
			score_count += 40;
		}
	}
}

//------------To Reset All Values----------//
/*This function will rest all values back to initial values*/
void Reset(int& delta_x, float& delay, bool& rotate, int level)
{
	delta_x = 0;
	delay = (0.5 / level) + 0.1;	//speed will change with level
	rotate = false;
}
//----------------To Store Score-----------------//
/*	This function will take all stored score and display it on screen*/
void ScoreText(Text& score, int lines_cleared, int level, int score_count)
{
	score.setString("Lines: " + std::to_string(lines_cleared) + "\nLevel: " + std::to_string(level) + "\nScore: " + std::to_string(score_count));
}
//--------------Game Over-------------------//
/*If blocks rach at the top of frame than function will retun 0 else it will return 1*/

void DrawNextPiece(RenderWindow& window, int& nextColor,int& nextPiece, Texture& obj1) {
	Sprite sprite(obj1);
	sprite.setTextureRect(IntRect(nextColor * 18, 0, 18, 18));
	for (int i = 0; i < 4; i++) {
		int x = BLOCKS[nextPiece][i] % 2;
		int y = BLOCKS[nextPiece][i] / 2;
		sprite.setPosition(250 + x * 18, 130 + y * 18);  // Adjust position to fit in the rectangle.
		window.draw(sprite);
	}
}

void HardDrop(int& colorNum,int& nextColor,int& nextPiece,int level) {
	while (true) {
		// Save the current position
		for (int i = 0; i < 4; i++) {
			point_2[i][0] = point_1[i][0];
			point_2[i][1] = point_1[i][1];
		}

		// Move the piece down
		for (int i = 0; i < 4; i++) {
			point_1[i][1] += 1;
		}

		// Check if the piece collides
		if (!anamoly()) {
			// Revert to the last valid position
			for (int i = 0; i < 4; i++) {
				point_1[i][0] = point_2[i][0];
				point_1[i][1] = point_2[i][1];
			}

			// Lock the piece into the grid
			for (int i = 0; i < 4; i++) {
				gameGrid[point_1[i][1]][point_1[i][0]] = colorNum;
			}

			// Reset for the next piece
			nextColor = 1 + rand() % 7;

			if (level == 1)
				nextPiece = rand() % 4;
			else
				nextPiece = rand() % 7;
			colorNum = nextColor;
			int n = nextPiece;

			for (int i = 0; i < 4; i++) {
				point_1[i][0] = BLOCKS[n][i] % 2;
				point_1[i][1] = BLOCKS[n][i] / 2;
			}

			break;
		}
	}
}


bool GameOver()
{
	for (int i = 0; i < 4; i++)
	{
		if (gameGrid[point_1[i][1]][point_1[i][0]] != 0)
		{
			return 0;
		}
	}
	return 1;
}



///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
