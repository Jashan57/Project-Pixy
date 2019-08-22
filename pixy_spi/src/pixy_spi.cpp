//============================================================================
// Name        : pixy_spi.cpp
// Author      : jashan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include <iostream>
#include"Pixy2BBB.h"
#include"uart.h"

using namespace std;

Uart send2lpc;
Pixy2BBB pixy;



int signature = 0;
int x = 0;                      //positon x axis
int y = 0;                      //position y axis
unsigned int width = 0;         //object's width
unsigned int height = 0;        //object's height
unsigned int area = 0;		//object's area
unsigned int newarea = 0;	//object's newarea
int Xmin = 100;                  //min x position
int Xmax = 200;			//max x position
int maxArea = 0;		//max area
int minArea = 0;		//min area
static int i = 0;

int main()
{

pixy.init();

	send2lpc.Init(Uart04,9600);
	uint16_t blocks;
while(1)
{

    blocks = pixy.ccc.getBlocks();  //receive data from pixy
    signature = pixy.ccc.blocks[i].m_signature; //get object's signature

	x = pixy.ccc.blocks[i].m_x;                    //get x position
  printf("x is : %d    ",x);

	y = pixy.ccc.blocks[i].m_y;                    //get y position
   // printf("y is : %d    ",y);


    width = pixy.ccc.blocks[i].m_width;            //get width
    //printf("width is : %d    ",width);

    height = pixy.ccc.blocks[i].m_height;          //get height
   // printf("height is : %d  ",height);


    area = width * height; //calculate the object area
    maxArea = area + 1000 ;//printf("max : %d   ",maxArea);
	minArea = area - 8000;//printf("min : %d   \n",minArea);

	 if(signature == 1) //looking for signature objects from 0 to 7
			  {
				//  pixy.setLamp(1,0);
				 // printf("object detected");
		          printf("sign is : %d     ",signature);
			    newarea = width * height; //calculate the object area

			      if (x < Xmin)//turn left if x position < max x position

			      {
			    	  printf("Left  \n");
			    	  send2lpc.send("L");
			    	  usleep(500000);

			      }
			      else if (x > Xmax) //turn right if x position > max x position
			      {
			    	 printf("right  \n");
			    	 send2lpc.send("R");
			    	 usleep(500000);

			      }
			      else if(newarea < minArea)//go forward if object too small
			      {
			    	  printf("forward  \n");
			    	  send2lpc.send("M");
			    	  usleep(500000);

			      }
			      else if(newarea > maxArea)//go backward if object too big
			      {
			    	  printf("reverse  \n");
			    	  send2lpc.send("B");
			    	  usleep(500000);

			      }
			      else
			      {
			    	  printf("Search for object \n");
			    	  send2lpc.send("S");
			    	  usleep(500000);
			    	  pixy.setLamp(0,0);

			      }

		}

}





return 0;
}

