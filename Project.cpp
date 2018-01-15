/*
 * Winston Moh Tangongho
 * CS 305 - Algorithmic Structures.
 * Assignment 1.
 * -------Hold shift and right click mouse to open command line in current directory.
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "Queue.h"
#include "Triple.h"
#include "CImg.h"
//#include "Pair.h"
using namespace std;
using namespace cimg_library;    //don't forget this.
//----------------------------------------------------------------------
string getUserInput(string prompt)
   {
      string t="";
      cout<<prompt;
      getline(cin,t);
      return t;
   }

void errorMsg(string msg, bool term)
   {
      cout<<msg<<endl;
      if (term)
         exit(0);
   }

bool isDigitString(string s)
   {
      if (!isdigit(s[0]) && s[0]!='+' && s[0]!='-')
         return false;
      for (unsigned int i=1;i<s.length();i++)
         if (!isdigit(s[i]))
            return false;
      return true;
   }

int getUserInteger(string prompt)
   {
      string t="billybob";

      while (!isDigitString(t))
         {
            t = getUserInput(prompt);
         }
      return atoi(t.c_str());
   }

string trimLeading(string s)
   {
      unsigned int i=0;
      while (i<s.length() && s[i]==' ')
         i++;
      if (i==s.length())
         return s;
      else
         return s.substr(i,s.length());
   }

string trimLine(string s)
   {
      s = trimLeading(s);
      if (s.length()>0 && s[0]=='%')
         return "";
      else
         return s;
   }
//----------------------------------------------------------------------

// Show us the original grid.
void dumpGrid(int rows, int cols, int **a, string msg)
   {
       if (msg.length()>0)
         cout<<msg<<endl;
	  cout<<" Here is the grid! "<<endl;
     cout<<"     ";
      for(int j=0;j<cols;j++)
         cout<<j<<' ';
      cout<<endl;
      cout<<"    ";
      for(int j=0;j<cols;j++)
         cout<<"--";
      cout<<endl;

      for (int i=0;i<rows;i++)
         {
            cout<<"  "<<i<<" |";
            for (int j=0;j<cols;j++)
               {
                  cout<<a[i][j];
                  cout<<' ';
               }
            cout<<endl;
         }
   }


// overloaded function from above to display current position in the grid
// if you don't like overloaded functions (I don't), you can rename it dumpGrid2()
// and change the call in main()
void dumpGrid2(int cr, int cc, int rows, int cols, int **a, string msg)
   {
     if (msg.length()>0)
         cout<<msg<<endl;

      cout<<"     ";
      for(int j=0;j<cols;j++)
         cout<<j<<' ';
      cout<<endl;
      cout<<"    ";
      for(int j=0;j<cols;j++)
         cout<<"--";
      cout<<endl;

      for (int i=0;i<rows;i++)
         {
            cout<<"  "<<i<<" |";
            for (int j=0;j<cols;j++)
               {
                  if (cr==i  && cc==j)
                     cout<<'*';
                  else
                     cout<<a[i][j];
                  cout<<' ';
               }
            cout<<endl;
         }
   }  // dumpGrid2()


// Make the grid of integers with 0's and 1's. 
int **makeGrid(int &rows, int &cols)
   {
      string fname = getUserInput("Enter File name with grid to run: ");
      if (fname.length()==0)
         errorMsg("No file...terminating",true);
         
      ifstream infile(fname.c_str());
      if (!infile)
         errorMsg("File not found",true);
         
      string s="",aline="";
      while (s.length()==0)
         {
            getline(infile,aline);
            s = trimLine(aline);               // trim off comments and leading spaces
         }
         
      stringstream ss(s);
      ss>>rows>>cols;                       // first non-blank/comment is rows and cols
      int d; 								// to be used to receive entries in grid.
      int **a = new int*[rows];
      int i=0,j;							// i = rows and j = columns.
      getline(infile,aline);				// get first line on grid from file.
      while (infile)
         {
			a[i] = new int[cols];
			j = 0;
            if (aline.length()>0)
               {
                  ss.str("");
                  ss.clear();
                  ss<<aline;
                  ss>>d;
                  while (ss)
                     {
                        a[i][j] = d;		//put entry in spot in array.
                        ss>>d;				// put next entry in stringstream
                        j++;				// increment number of columns.
                     }
               }
            i++;							// increment number of rows.
            getline(infile,aline);			// move to next line.
         }
         
      infile.close();						// close file.
      return a;								// return array.
   }



//----------------------------------------------------------------------
// You have to write these functions

bool isValidPosition(int r, int c, int rows, int cols, int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (r>rows-1 || c>cols-1 || grid[r][c] ==  1)
						return false;
		   }
	   }
	   return true;
   }

bool canGoUp(int r,int c,int rows,int cols, int** grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (r==0 || grid[r-1][c] ==  1)
					return false;
		   }
	   }
	   return true;	   
   }

bool canGoRight(int r, int c, int rows, int cols, int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (c+1==cols)
					return false;
			   else if (grid[r][c+1] ==  1)
					return false;
		   }
	   }
	   return true;	
   }

bool canGoDown(int r, int c, int rows,int cols, int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (r+1==rows) return false;
			   else if (grid[r+1][c] ==  1)
					return false;
		   }
	   }
	   return true;	
   }

bool canGoLeft(int r, int c, int rows, int cols, int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (c==0) return false;
			   else if (grid[r][c-1] ==  1)
					return false;
		   }
	   }
	   return true;	
   }

//----------------------------------------------------------------------
bool isEqual(Triple<int> lhs, Triple<int> rhs)
	{
		if (lhs.getFirst() == rhs.getFirst() && lhs.getSecond() == rhs.getSecond())
			{return true;}
		return false;
	}

string intPairToString(Triple<int> p)
   {
      stringstream ss;
      ss<<'('<<p.getFirst()<<','<<p.getSecond()<<')';
      return ss.str();
   }

// Make copy of array.
int **makeCopy(int **a, int rows, int cols)
	{
		int **copy = new int*[rows]; 
		for (int i=0; i < rows; i++)
		{
			copy[i] = new int[cols];
			for (int j=0; j < cols; j++)
				{
					copy[i][j] = a[i][j];
				}
		} 
		return copy;
	}

/** Make colors string
 */
char **makeColors(string (&clrs)[10])
   {
    int  rows=10, cols=23;
	
	// string of colors.
	string colors[10] = {" Color Choices  (RGB)       ",
						 "1) Blue    (0,0,255)   ",
						 "2) Green   (0,255,0)   ",
						 "3) Red     (255,0,0)   ",
						 "4) Orange  (255,128,0) ",
						 "5) Cyan    (0,255,255) ",
						 "6) Teal    (0,128,128) ",
						 "7) Yellow  (255,255,0) ",
						 "8) Magenta (255,0,255) ",
						 "9) Olive   (128,128,0) "};
	  //copy string.
	  for (int c=0; c<10; c++)
		{
			clrs[c] = colors[c];
		}
      char **a = new char*[rows];
      for (int i=0;i<rows;i++)
         {
            a[i] = new char[cols];
            for (int j=0;j<cols;j++)
               a[i][j] = colors[i][j];
         }
      return a;
   }

// Dump string of colors.
void dumpColors(char **a, string msg)
   {
	  int rows = 10, cols = 23;
      if (msg.length()>0)
         cout<<msg<<endl;

      for (int i=0;i<rows;i++)
         {
            for (int j=0;j<cols;j++)
               {
				cout<<a[i][j];
               }
            cout<<endl;
         }
   } 

/** Movement functions for working image.
 */
// check If we can go up.
bool canGoU(int r,int c,int rows,int cols,int r1,int g,int b,CImg<unsigned char> &workimage,int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (r==0) return false;
			   else if (grid[r-1][c] == 1)
						return false;			   
			   else if ((int)workimage(r-1,c,0,0) != r1 || 
						(int)workimage(r-1,c,0,1) != g ||
						(int)workimage(r-1,c,0,2) != b)
						return false;
		   }
	   }
	   return true;	   
   }

// check If we can go right.
bool canGoR(int r,int c,int rows,int cols,int r1,int g,int b,CImg<unsigned char> &workimage,int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (c+1==cols) return false;
			   else if (grid[r][c+1] ==  1) 
						return false;
			   else if ((int)workimage(r,c+1,0,0) != r1 || 
						(int)workimage(r,c+1,0,1) != g ||
						(int)workimage(r,c+1,0,2) != b)
						return false;
		   }
	   }
	   return true;	
   }

// check If we can go down.
bool canGoD(int r,int c,int rows,int cols,int r1,int g,int b,CImg<unsigned char> &workimage,int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (r+1==rows) return false;
			   else if (grid[r+1][c] ==  1)
						return false;
			   else if ((int)workimage(r+1,c,0,0) != r1 || 
						(int)workimage(r+1,c,0,1) != g ||
						(int)workimage(r+1,c,0,2) != b)
						return false;
		   }
	   }
	   return true;	
   }

// check If we can go left.
bool canGoL(int r,int c,int rows,int cols,int r1,int g,int b,CImg<unsigned char> &workimage,int **grid)
   {
	   for (int i=0;i<rows;i++)
	   { 
		   for (int j=0;j<cols;j++)
		   {
			   if (c==0) return false;
			   else if (grid[r][c-1] ==  1)
					return false;
			   else if ((int)workimage(r,c-1,0,0) != r1 || 
						(int)workimage(r,c-1,0,1) != g ||
						(int)workimage(r,c-1,0,2) != b)
					return false;
		   }
	   }
	   return true;	
   }

// Assign numbers to colors
// r : red, g : green, b : blue.
void assignColors(int ch,int &r, int &b, int &g)
	{
		switch (ch)
		{
			case 1:
				r = 0; g = 0; b = 255;
				break;
			case 2:
				r = 0; g = 255; b = 0;
				break;
			case 3:
				r = 255; g = 0; b = 0;
				break;
			case 4:
				r = 255; g = 128; b = 0;
				break;
			case 5:
				r = 0; g = 255; b = 255;
				break;
			case 6:
				r = 0; g = 128; b = 128;
				break;
			case 7:
				r = 255; g = 255; b = 0;
				break;
			case 8:
				r = 255; g = 0; b = 255;
				break;
			case 9:
				r = 128; g = 128; b = 0; 
				break;
			default:
				break;
		}
	}


/** Main function.
 */
int main(int argc, char *argv[])
   {
	  /** First Part
	   * Maze program.
	   */
	   if (getUserInput("Enter  Y/N to run maze program: ") == ("Y"))
	   {
		  int rows,cols;
		  int **a = makeGrid(rows,cols);
		  int **a_copy = makeCopy(a,rows,cols);

		  dumpGrid(rows,cols,a,"");

		  string s,s_end;
		  stringstream ss,ss_end;

		  int cr,cc,cr_end,cc_end;
		  int dist = 0;										// variable for distance;
		  Triple <int> pStart, pFinal, pp;
		  Queue<Triple<int> > q;						// Create a queue of Triple (Pairs with distances.)
		  
		  while (getUserInput("Enter  Y/N to run maze program: ") == ("Y"))    // run forever....use ctrl-c to kill it
			 {
				a = makeCopy(a_copy,rows,cols);	// Reset array.
				s = getUserInput("Enter start x y position (e.g. 3 5): ");
				ss.clear();
				ss<<s;
				ss>>cr>>cc; 
				pStart.setFirst(cr); pStart.setSecond(cc);
				s_end = getUserInput("Enter goal x y position (e.g. 3 5): ");
				ss_end.clear();
				ss_end<<s_end;
				ss_end>>cr_end>>cc_end; 
				pFinal.setFirst(cr_end); pFinal.setSecond(cc_end);
				q.enQ(pStart);							//Enqueue starting position.	
				if (!isValidPosition(cr,cc,rows,cols,a) || !isValidPosition(cr_end,cc_end,rows,cols,a))
				   cout<<"Invalid position!!"<<endl;
				else
				   {
					  while (!q.isEmpty())
					  {
					  q.deQ(pp);
					  cout<<"DeQueued "<<intPairToString(pp)<<endl;
					  cr = pp.getFirst(); cc = pp.getSecond(); dist = pp.getDistance();
					  dumpGrid2(pp.getFirst(),pp.getSecond(),rows,cols,a,"");
					  if (isEqual(pp,pFinal))
							break;
					  if (canGoUp(cr,cc,rows,cols,a))
							{
							Triple<int> pUp(cr-1,cc,dist+1);
							q.enQ(pUp);
							a[cr][cc] = 1;
							dumpGrid2(cr,cc,rows,cols,a,"");	
							cout<<"EnQueued "<<intPairToString(pUp)<<endl;					
							}
					  if (canGoRight(cr,cc,rows,cols,a))
							{
							Triple<int> pRight(cr,cc+1,dist+1);
							q.enQ(pRight);
							a[cr][cc] = 1;
							dumpGrid2(cr,cc,rows,cols,a,"");
							cout<<"EnQueued "<<intPairToString(pRight)<<endl;
							}
					  if (canGoDown(cr,cc,rows,cols,a))
							{
							Triple<int> pDown(cr+1,cc,dist+1);
							q.enQ(pDown);
							a[cr][cc] = 1;
							dumpGrid2(cr,cc,rows,cols,a,"");
							cout<<"EnQueued "<<intPairToString(pDown)<<endl;
							}
					  if (canGoLeft(cr,cc,rows,cols,a))
							{
							Triple<int> pLeft(cr,cc-1,dist+1);
							q.enQ(pLeft);
							a[cr][cc] = 1;						
							dumpGrid2(cr,cc,rows,cols,a,"");
							cout<<"EnQueued "<<intPairToString(pLeft)<<endl;
							}						
					}
				   }
				 if (isEqual(pFinal,pp))
					cout<<"We can move from "<<intPairToString(pStart)<<" to point "<<intPairToString(pFinal)<<" with total distance "<<dist<<endl;
				 else cout<<"We cannot move from "<<intPairToString(pStart)<<" to point "<<intPairToString(pFinal)<<endl;
			 }
			}
		/** Final Part.
		 * Run paint program.
		 */
		 cout<<endl;
		 cout<<"To run Paint program,  ";
			string filename,output;
			char ch;
			cout<<" Enter input file name: ";
			cin>>filename;
			
			CImg<unsigned char> workimage(filename.c_str());	// create CImg variable "workimage".
			int height,width;
			height = workimage.height();			// refers to number of rows.
			width = workimage.width();				// refers to number of columns.
			
			// Create 2D array of zeros with size of image(total number of pixels) to help in marking visited spots.
			int **arr = new int*[height];
			for (int i=0;i<height;i++)
				{
					arr[i] = new int[width];
					for (int j=0;j<width;j++)
					   arr[i][j] = 0;
				}

		    int distc = 0,crc,ccc;								// variable for distance;
		    Triple <int> ppc,pSt;
		    Queue<Triple<int> > qc;						// Create a queue of Triple (Pairs with distances.)

			string clrs[10];
			char **cgrid = makeColors(clrs);				// create colors.
			
			
			CImgDisplay mainwindow(workimage,"Working Image");				
			while (!mainwindow.is_closed())
			{
				mainwindow.wait();
				if (mainwindow.button()&1)							//left button click.
				{
					dumpColors(cgrid,"");							// dump string of colors.
					int sx,sy,choice;
					int r,red,g,green,b,blue;
					sx = mainwindow.mouse_x();
					sy = mainwindow.mouse_y();
					r = (int)workimage(sx,sy,0,0);					// get color channels of pixel being clicked on.
					b = (int)workimage(sx,sy,0,1);					//			""
					g = (int)workimage(sx,sy,0,2);					//			""
					pSt.setFirst(sx); pSt.setSecond(sy);
					qc.enQ(pSt);
					
					cout<<"Enter number for color:(e.g. 1 = Blue, 2 = Green etc... : ";
					cin>>choice;
					assignColors(choice,red,blue,green);					// get color channels of new color.
					workimage(sx,sy,0,0) = red;workimage(sx,sy,0,1) = green;workimage(sx,sy,0,2) = blue;	//color point clicked on.
					while (!qc.isEmpty())
					{
					  qc.deQ(ppc);
					  crc = ppc.getFirst(); ccc = ppc.getSecond(); distc = ppc.getDistance();
					  if (canGoU(crc,ccc,height,width,r,g,b,workimage,arr))
							{
							Triple<int> pU(crc-1,ccc,distc+1);
							qc.enQ(pU);
							arr[crc][ccc] = 1;				// mark the visited pixel.
							workimage(crc-1,ccc,0,0) = red;workimage(crc-1,ccc,0,1) = green;workimage(crc-1,ccc,0,2) = blue;										
							}
					  if (canGoR(crc,ccc,height,width,r,g,b,workimage,arr))
							{
							Triple<int> pR(crc,ccc+1,distc+1);
							qc.enQ(pR);
							arr[crc][ccc] = 1;				// mark the visited pixel.
							workimage(crc,ccc+1,0,0) = red;workimage(crc,ccc+1,0,1) = green;workimage(crc,ccc+1,0,2) = blue;
							}
					  if (canGoD(crc,ccc,height,width,r,g,b,workimage,arr))
							{
							Triple<int> pD(crc+1,ccc,distc+1);
							qc.enQ(pD);
							arr[crc][ccc] = 1;				// mark the visited pixel.
							workimage(crc+1,ccc,0,0) = red;workimage(crc+1,ccc,0,1) = green;workimage(crc+1,ccc,0,2) = blue;
							}
					  if (canGoL(crc,ccc,height,width,r,g,b,workimage,arr))
							{
							Triple<int> pL(crc,ccc-1,distc+1);
							qc.enQ(pL);
							arr[crc][ccc] = 1;				// mark the visited pixel.
							workimage(crc,ccc-1,0,0) = red;workimage(crc,ccc-1,0,1) = green;workimage(crc,ccc-1,0,2) = blue;				
							}					
					}
					cout<<"Done painting! Click on image to continue or close image to Terminate."<<endl;
				}
			}			
								
			cout<<endl;
			cout<<" Do you want to save your output (Y/N)?:  ";
			cin>>ch;
			if (ch == 'Y' || ch == 'y' )
				{
				cout<<"output file name :";
				cin>>output;
				workimage.save(output.c_str());			// save output file.
				}
			else {};	
				
   }			// end the program.

