//============================================================================
//	Hassan Shahzad
//	18i-0441
//	FAST-NUCES
//	Brick Slayer Project
//	Contact at : chhxnshah@gmail.com
//============================================================================

#ifndef BSLAYER_CPP_
#define BSLAYER_CPP_
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
int a=40, b=300,c=3;
int direct=1;	//direction of ball
int direct1=2;	//direction of ball 2
int sball=2;	//speed of ball
int l,w,length,height;
int brick[100][3];
int ctimer;	//current time
int stimer;	//sliders time
int ltimer;	//sliders length timer
int slider[2];	//array of slider
int ball[10];	//array of ball
int ln = 90;	//increase in length of slider
int sl=0;	//color of slider
int br= 5;	//color of bricks
int bl= 3;	//color of ball
int midx=400, midy=50;	//initial position of the ball1
int midx1=100, midy1=50;	//initial position of the ball2
int col;	//color
float theta1, theta2;	//angles
int count=0;	//counter variable
bool levelup = false;	//levels

/*________________________________________________________________________________________________________________________________
*/


//defining some MACROS

#define MAX(A,B) ((A) > (B) ? (A):(B)) // finds max of two numbers
#define MIN(A,B) ((A) < (B) ? (A):(B)) // find min of two numbers
#define ABS(A) ((A) < (0) ? -(A):(A))  // find ABS of a given number


#define FPS 1000 // frame per seconds

// define another constant to hold ASCII for Escape key.
#define KEY_ESC 27 // A

// define some colors as 2D arrays, we have five pre-defined colors here..
// you can add many more if you wish..

/*________________________________________________________________________________________________________________________________
*/


float colors[5][3] = { { 1 / 255.0, 164 / 255.0, 164 / 255.0 }, { 215 / 255.0, 0
		/ 255.0, 96 / 255.0 }, { 208 / 255.0, 209 / 255.0, 2 / 255.0 }, { 0
		/ 255.0, 161 / 255.0, 203 / 255.0 }, { 50 / 255.0, 116 / 255.0, 44
		/ 255.0 } };


/*________________________________________________________________________________________________________________________________
*/


// This function converts an input angle from degree to radians
float Deg2rad(float degree) {
	return (degree / 180.0) * M_PI;
}

/*________________________________________________________________________________________________________________________________
*/

// seed the random numbers generator by current time
void InitRandomizer() {
	srand((unsigned int) time(0)); // time(0) returns number of seconds elapsed since January 1, 1970.
}

/*________________________________________________________________________________________________________________________________
*/

//This function returns a random value within the specified range of [rmin, rmax] ...
long GetRandInRange(const long &rmin, const long &rmax) {
	long range = rmax - rmin; // find the range
	long value = (rand() % (long) range) + rmin; // translate the generated number ...
//	cout << value << endl << flush;
	return value;
}

/*________________________________________________________________________________________________________________________________
*/


void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,
		float color[]) {
	glColor3fv(color); // Set the triangle colour
	// ask library to draw triangle at given position...

	glBegin(GL_TRIANGLES);
	/*Draw triangle using given three vertices...*/
	glVertex4i(x1, y1, 0, 1);
	glVertex4i(x2, y2, 0, 1);
	glVertex4i(x3, y3, 0, 1);
	glEnd();
}
/*________________________________________________________________________________________________________________________________
*/

void DrawRectangle1( int length, int height)
{
	
		
	DrawTriangle(length, height, length, height+10, length+ln, height, colors[sl]);	// 1= starting point, 2= height, 3= length
	DrawTriangle(length, height+10, length+ln, height+10, length+ln, height, colors[sl]);	// 1= starting point, 2= same height (increased length), 3= same length (decreased height)

		if ( time(NULL) - ltimer >=45 )
		{
			ln+=20;
			ltimer = time(NULL);
		}

		if ( time(NULL) - stimer >=15 )
		{
			sl++;
			stimer = time(NULL);
		}


	if ( sl >=6)
	{
		sl = 0;
	}
	
}


/*________________________________________________________________________________________________________________________________
*/

void DrawRectangle(int l, int w)
{
	DrawTriangle(l, w, l, w+40, l+100, w, colors[br]);	// 1= starting point, 2= height, 3= length
	DrawTriangle(l, w+40, l+100, w+40, l+100, w, colors[br]);	// 1= starting point, 2= same height (increased length), 3= same length (decreased height)

	if ( time(NULL) - ctimer >=30 )
		{
			br--;
			ctimer = time(NULL);
		}


	if ( br <0)
	{
		br = 5;
	}
}

/*________________________________________________________________________________________________________________________________
*/


void SetBricks()
{	
	int tempx=80; int tempy=125;
	for (int a=0; a<28; a++) {
		if (a%4==0) {
			tempy += 50;
			tempx = 80;
		}
		brick[a][0] = tempx;
		brick[a][1] = tempy;
		brick[a][2] = 1;
		tempx+=110;
	}
}	

/*________________________________________________________________________________________________________________________________
*/

void DisplayBrick()
{
	for (int i = 0 ; i<28 ; i++ )
    {
		{	
			DrawRectangle(brick[i][0], brick[i][1]);
		}
    }
}

/*________________________________________________________________________________________________________________________________
*/

void ReDisplayBricks()
{
	if ( time(NULL) - ctimer >=10)
	{
		for (int i = 0 ; i<28 ; i++ )
    {
		{	
			DrawRectangle(brick[i][0], brick[i][1]);
		}
    }
		
	}
}




/*________________________________________________________________________________________________________________________________
*/


void SetSlider()
{
	slider[0] = 300 ;
	slider[1] = 10;
}

/*________________________________________________________________________________________________________________________________
*/

void DrawSlider()
{
	DrawRectangle1( slider[0] , slider[1]);
}

/*_______________________________________________________________________________________________________________________________
*/

void DrawCircle(int midx, int midy)
{
	theta1 = Deg2rad(10);
	theta2 = Deg2rad(30);

	while (theta1 <=330)
	{
		DrawTriangle (midx, midy, midx + 10 * cos(theta1), midy +10 * sin(theta1), midx + 10 * cos(theta2), midy + 10 * sin(theta2), colors[bl]);
	
	theta1 += 10;
	theta2 += 10;
	}
}

/*________________________________________________________________________________________________________________________________
*/

void DrawBall(int a, int b)
{
	DrawCircle(	a, b);
}

/*________________________________________________________________________________________________________________________________
*/

void BoundaryCollision()
{
	if (midx+10 >= 600)
	{
		if (direct == 1)
		{
			direct = 2;
		}
		else if (direct  == 4)
		{
			direct = 3;
		}	
	}

	if (midx-10 <= 0)
	{
		if (direct == 3)
		{
			direct = 4;
		}
		else if (direct  == 2)
		{
			direct = 1;
		}
	}

	if (midy+10 >= 600)
	{
		if (direct == 1)
		{
			direct = 4;
		}
		else if (direct  == 2)
		{
			direct = 3;
		}

		
	}

	if (midy <= 0)
	{
		exit(1);
	}
}

/*________________________________________________________________________________________________________________________________
*/

void SliderCollision()
{
	if(midy-10 == (slider[1]+10) and midx-10 <= (slider[0]+ln) and midx-10>= slider[0])
	{
		if ( direct ==3)
		{
			direct = 2;
			cout<<"\a";
		}

		else if ( direct == 4)
		{
			direct = 1;
			cout<<"\a";		
		}
			
	}
}

/*________________________________________________________________________________________________________________________________
*/

void BallDirection()
{
		switch(direct)
	{
		
		case 1: midx+=sball; midy+=sball;
		break;
		case 2: midx-=sball; midy+=sball;
		break;
		case 3: midx-=sball; midy-=sball;
		break;
		case 4: midx+=sball; midy-=sball;
		break;
	}

if ( time(NULL) - ctimer >= 30)
	{	
		sball++;
		ctimer= time(NULL);
	}

	
}

/*________________________________________________________________________________________________________________________________
*/

void BrickCollision()
{
	for (int i=0; i<28; i++)
	{
		if ((midx+10 >= brick[i][0]) and (midx-10 <= brick[i][0]+100) and (midy+10 >= brick[i][1]) and (midy-10 <= brick[i][1]+40 ))
		{
			
			cout<<'\a';
			cout<<"\a";
			if (direct == 1)
			{
				direct = 4;
			}

			else if (direct == 2)
			{
				direct = 3;
			}

			else if (direct == 3)
			{
				direct = 2;
			}

			else if (direct == 4)
			{
				direct = 1;
			}
			bl++;
			if (bl >=6)
			{
				bl=0;
			}
			cout<<'\a';
			cout<<"\a";
			brick[i][1] = -650;	//disappearing bricks 
			count++;


			if (count == 28)
			{
				levelup = true;
				SetBricks();
			}
		}
	} 

}

/*________________________________________________________________________________________________________________________________
*/

void DrawBall2( int aa, int bb)
{
	DrawCircle (aa,bb);
}

/*________________________________________________________________________________________________________________________________
*/

void DrawRectangle2( int length, int height)
{
	
		
	DrawTriangle(length, height, length, height+10, length+ln, height, colors[sl]);	// 1= starting point, 2= height, 3= length
	DrawTriangle(length, height+10, length+ln, height+10, length+ln, height, colors[sl]);	// 1= starting point, 2= same height (increased length), 3= same length (decreased height)

		if ( time(NULL) - ltimer >=45 )
		{
			ln+=30;
			ltimer = time(NULL);
		}

		if ( time(NULL) - stimer >=15 )
		{
			sl++;
			stimer = time(NULL);
		}


	if ( sl >=6)
	{
		sl = 0;
	}
	
}

/*________________________________________________________________________________________________________________________________
*/

void DrawSlider1()
{
	DrawRectangle2( slider[0] , slider[1]);
}

/*________________________________________________________________________________________________________________________________
*/

void BallDirection2()
{
	switch(direct1)
	{
		
		case 1: midx1+=sball; midy1+=sball;
		break;
		case 2: midx1-=sball; midy1+=sball;
		break;
		case 3: midx1-=sball; midy1-=sball;
		break;
		case 4: midx1+=sball; midy1-=sball;
		break;
	}

}

/*________________________________________________________________________________________________________________________________
*/
	
void BoundaryCollision2()
{
		if (midx1+10 >= 600)
		{
			if (direct1 == 1)
			{
				direct1 = 2;
			}
			else if (direct1  == 4)
			{
				direct1 = 3;
			}	
		}

		if (midx1-10 <= 0)
		{
			if (direct1 == 3)
			{
				direct1 = 4;
			}
			else if (direct1  == 2)
			{
				direct1 = 1;
			}
		}

		if (midy1+10 >= 600)
		{	
			if (direct1 == 1)
			{
				direct1 = 4;
			}
			else if (direct1  == 2)
			{
				direct1 = 3;
			}
		}	

}

/*________________________________________________________________________________________________________________________________
*/

void SliderCollision1()
{
	if(midy-10 == (slider[1]+10) and midx-10 <= (slider[0]+ln) and midx-10>= slider[0])
	{
		if ( direct ==3)
		{
			direct = 2;
			cout<<"\a";
		}

		else if ( direct == 4)
		{
			direct = 1;
			cout<<"\a";		
		}
			
	}

}


/*________________________________________________________________________________________________________________________________
*/

void SliderCollision2()
{
	if(midy1-10 == (slider[1]+10) and midx1-10 <= (slider[0]+ln) and midx1-10>= slider[0])
	{
		if ( direct1 ==3)
		{
			direct1 = 2;
		}

		else if ( direct1 == 4)
		{
			direct1 = 1;		
		}
			
	}

}
  
/*________________________________________________________________________________________________________________________________
*/

void BrickCollision1()
{
	for (int i=0; i<28; i++)
	{
		if ((midx+10 >= brick[i][0]) and (midx-10 <= brick[i][0]+100) and (midy+10 >= brick[i][1]) and (midy-10 <= brick[i][1]+40 ))
		{
			
			cout<<'\a';
			cout<<"\a";
			if (direct == 1)
			{
				direct = 4;
			}

			else if (direct == 2)
			{
				direct = 3;
			}

			else if (direct == 3)
			{
				direct = 2;
			}

			else if (direct == 4)
			{
				direct = 1;
			}
			bl++;
			if (bl >=6)
			{
				bl=0;
			}
			
			brick[i][1] = -650;	//disappearing bricks 
			
		}
	} 

}






/*________________________________________________________________________________________________________________________________
*/

void BrickCollision2()
{
	for (int i=0; i<28; i++)
	{
		if ((midx1+10 >= brick[i][0]) and (midx1-10 <= brick[i][0]+100) and (midy1+10 >= brick[i][1]) and (midy1-10 <= brick[i][1]+40 ))
		{
			
			if (direct1 == 1)
			{
				direct1 = 4;
			}

			else if (direct1 == 2)
			{
				direct1 = 3;
			}

			else if (direct1 == 3)
			{
				direct1 = 2;
			}

			else if (direct1 == 4)
			{
				direct1 = 1;
			}
			bl++;
			if (bl >=6)
			{
				bl=0;
			}
			brick[i][1] = -650;	//disappearing bricks 
			
		}
	} 

}


/*________________________________________________________________________________________________________________________________
*/

void DisplayBricks1()
{
	for (int i = 0 ; i<28 ; i++ )
    {
		{	
			DrawRectangle(brick[i][0], brick[i][1]);
		}
    }
}

/*________________________________________________________________________________________________________________________________
*/

void Display()
{
	if (levelup == false)
	{
		glClearColor(1/*Red Component*/, 1.0/*Green Component*/,
				1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors
		
		DisplayBrick();
		DrawBall(midx, midy);
		DrawSlider();
		BallDirection();
		BoundaryCollision();
		SliderCollision();
		BrickCollision();
		glutPostRedisplay();
		glutSwapBuffers(); // do not modify this line..
	}
	
	else if (levelup == true)
	{
		glClearColor(1/*Red Component*/, 1.0/*Green Component*/,
				1.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT); //Update the colors
		
		DisplayBricks1();
		DrawBall(midx, midy);
		DrawBall2(midx1, midy1);
		DrawSlider1();
		BallDirection();
		BallDirection2();
		BoundaryCollision();
		BoundaryCollision2();
		SliderCollision1();
		SliderCollision2();
		BrickCollision1();
		BrickCollision2();
		glutPostRedisplay();
		glutSwapBuffers(); // do not modify this line..
	}
}
		
		
/*________________________________________________________________________________________________________________________________
*/


void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
}


/*________________________________________________________________________________________________________________________________
*/


void NonPrintableKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		if (slider[0] >= 10)
		slider[0] -=20;
	} else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		if (slider[0]+ln <=590)	
		slider[0] +=20;
	} else if (key == GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key == GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}
	
	 glutPostRedisplay();
	 
}

/*________________________________________________________________________________________________________________________________
*/

void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
}

/*________________________________________________________________________________________________________________________________
*/

void Timer(int m) {

	// implement your functionality here
	Display();
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0 / FPS, Timer, 0);
	
}

/*________________________________________________________________________________________________________________________________
*/

int main(int argc, char*argv[]) {
	int width = 600, height = 600; // i have set my window size to be 800 x 600
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("ITCs Brick Slayer"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...
	SetSlider();
	SetBricks();

	ctimer = time(NULL);
	stimer = time(NULL);
	ltimer = time(NULL);
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0 / FPS, Timer, 0);
	glutMainLoop();
	return 1;
}
#endif /* BSLAYER_CPP_ */
