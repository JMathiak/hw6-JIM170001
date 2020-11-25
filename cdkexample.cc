/*
 * Filename:            cdkexample.cc
 * Date:                11/25/2020
 * Author:              Josh Mathiak
 * Email:               Josh.Mathiak@utdallas.edu
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *
 *      Reads a binary header and file and displays the corresponding values to a matrix. 
 *      
 */

#include <iostream>
#include "cdk.h"
#include "hw6.h"
#include <fstream>
#include <cstring>
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents- Press Any Key to Exit"
const int maxRecordStringLength = 25;
using namespace std;

class BinaryFileHeader
{
public:
  
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};
int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix
  const char 		*rowTitles[MATRIX_ROWS+1] = {"IGNORE", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_COLS+1] = {"IGNORE", "a", "b", "c"};
  int		colWidths[MATRIX_COLS+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_COLS+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

 
  window = initscr();
  cdkscreen = initCDKScreen(window);

  
  initCDKColor();

  
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_ROWS, MATRIX_COLS, MATRIX_ROWS, MATRIX_COLS,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, colWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  BinaryFileHeader *fileHeader = new BinaryFileHeader();
  BinaryFileRecord *fileRecord = new BinaryFileRecord();
  ifstream binInfile ("/scratch/perkins/cs3377.bin" , ios::in | ios::binary);
  binInfile.read((char *) fileHeader, sizeof(BinaryFileHeader));
  int mn = fileHeader->magicNumber;
  stringstream ss;
  ss << hex << mn;
  string magnum;
  ss >> magnum;
  transform(magnum.begin(), magnum.end(), magnum.begin(), ::toupper);
  string fMagNum = "Magic: 0X" + magnum;
  const char *magicn = fMagNum.c_str();
  string vN = "Version: " + to_string(fileHeader->versionNumber);
  const char *versn = vN.c_str();
  string nR = "NumRecords: " + to_string(fileHeader->numRecords);
  const char *numr = nR.c_str();
  setCDKMatrixCell(myMatrix, 1,1,magicn);
  setCDKMatrixCell(myMatrix, 1,2, versn);
  setCDKMatrixCell(myMatrix, 1,3, numr);
  int recordnum = 0;
  int row = 2;
  while( recordnum <= 4 )
    {
      binInfile.read((char *) fileRecord, sizeof(BinaryFileRecord)); 
  int column = 1;
  string strL = "String length: " + to_string(fileRecord->strLength);
  const char *sl = strL.c_str();
  const char *buff = fileRecord->stringBuffer;
  setCDKMatrixCell(myMatrix, row,column, sl);
  column++;
  setCDKMatrixCell(myMatrix, row,column, buff);
  row++;
  recordnum++;
    }

  drawCDKMatrix(myMatrix, true);    /* required  */
  
  endProg();
  binInfile.close();

 
  return 0;
}
