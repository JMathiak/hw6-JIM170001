/*
 * Filename:            cdkexample.cc
 * Date:                11/08/2020
 * Author:              Stephen Perkins
 * Email:               stephen.perkins@utdallas.edu
 * Version:             1.0
 * Copyright:           2020, All Rights Reserved
 *
 * Description:
 *
 *      Build and display a small text based GUI matrix using curses
 *      and the CDK.
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <cstring>
#include <cstdint>
#include <string>
#include <sstream>
#include <iomanip>
#include <bits/stdc++.h>
/*
 * For grins and giggles, we will define values using the C
 * Preprocessor instead of C or C++ data types.  These symbols (and
 * their values) get inserted into the Preprocessor's symbol table.
 * The names are replaced by their values when seen later in the code.
 */

#define MATRIX_ROWS 5
#define MATRIX_COLS 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"
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

  // CDK uses offset 1 and C/C++ use offset 0.  Therefore, we create one more 
  // slot than necessary and ignore the value at location 0.
  const char 		*rowTitles[MATRIX_ROWS+1] = {"IGNORE", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_COLS+1] = {"IGNORE", "a", "b", "c"};
  int		colWidths[MATRIX_COLS+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_COLS+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
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
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
