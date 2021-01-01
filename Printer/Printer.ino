/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
   http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo vertical; 
Servo horizontal;
Servo pen;


const int CHAR_HT = 10;
const int CHAR_WID = 10;
const int CHAR_ROW_COUNT = 3;
const int CANVAS_WIDTH = CHAR_ROW_COUNT * CHAR_WID;

char someString[] = "aaaaaa";

const float startHorizontalPos = 20;
const float endingHorizontalPos = 100;
const float jumpsInHorizontalPos = (endingHorizontalPos - startHorizontalPos) / (CHAR_WID * CHAR_ROW_COUNT);

const int LETTER_TO_MATRIX_MAP_LEN = 255;
char** letter_to_matrix_map = new char*[LETTER_TO_MATRIX_MAP_LEN];

char a[CHAR_HT * CHAR_WID] =  {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};

int maxBluePen = 10;

int HORIZONTAL_POS = startHorizontalPos;



void setup() {
  
  Serial.begin(9600);
  Serial.println("STARTED");
  delay(40);
  
  vertical.attach(8);
  vertical.write(38); 
  pen.attach(9);
  pen.write(90);
  horizontal.attach(7);
  horizontal.write(20);


  // initialize the letter-to-matrix-map
  for (unsigned char letter = 0; letter < LETTER_TO_MATRIX_MAP_LEN; ++letter) {
    // by default, set to empty matrix
    letter_to_matrix_map[letter] = 0;
    if ( (letter >= 'a') and (letter <= 'z') ) {
      letter_to_matrix_map[letter] = 0;
    }
    if ( (letter >= '0') and (letter <= '9') ) {
      letter_to_matrix_map[letter] = 0;
    }    
    /////////////////////////////////////
    letter_to_matrix_map['a'] = a;       
    ////////////////////////////////////          
  }
}

// this returns a SINGLE row to be printed as a MATRIX
char* give_canvas(char* letter_list, int letter_count=CHAR_ROW_COUNT) {
  // confirm the number of letters being printed on this row

  int actual_letter_count = (letter_count < CHAR_ROW_COUNT) ? letter_count : CHAR_ROW_COUNT;

  Serial.println(String("In da function1 ") + String(letter_list));
  //Serial.println(String(canvas));
  //Serial.println(String(letter_list));
  delay(500);


  Serial.println(String("In da function2 ") + String(letter_list));
  //Serial.println(String(canvas));
  //Serial.println(String(letter_list));
  delay(500);


  // create, initialize canvas
  char* canvas = new char[CHAR_HT * CANVAS_WIDTH];
  for (int count = 0; count < (CHAR_HT * CANVAS_WIDTH); ++count) {
    canvas[count] = 0;
  }


  

  // push letters on the canvas
  // letter-by-letter in every row as we iterate through each row  
  int col_offset = 0;
  for (int letter = 0; letter < actual_letter_count; ++letter) {
     for (int row = 0; row < CHAR_HT; ++row) {
        // calculate the position of the cursor before 
        // starting to write a new letter
        col_offset = (letter * CHAR_WID);      
        for (int col = 0; col < CHAR_WID; ++col) {
          // copy the letter's matrix if possible, if not leave the area empty
          canvas[row * (CANVAS_WIDTH) + (col_offset + col)] = ((letter_to_matrix_map[letter_list[letter]] == 0) ?  0 : letter_to_matrix_map[letter_list[letter]][row * CHAR_WID + col]);   
        }
     }
  }

  // return the canvas array containing the complete row of letters
  return canvas;
}

// this returns a LIST of rows to be printed as a MATRIX
int give_row_count(int list_len) {
   int canvas_count = (list_len / CHAR_ROW_COUNT) + ((list_len % CHAR_ROW_COUNT) != 0);
   return canvas_count; 
}
char** give_rows(char* letter_list, int list_len) {
  // calculate number of rows required to print the content
  int canvas_count = (list_len / CHAR_ROW_COUNT) + ((list_len % CHAR_ROW_COUNT) != 0);
  char** canvas_list = new char*[canvas_count];

  Serial.println(String(canvas_count));
  delay(500);
  
  // convert each row of letters to a matrix to be printed
  int letters_in_current_row = 0;
  for (int canvas_index = 0; canvas_index < canvas_count; canvas_index += 1) {
    letters_in_current_row = (canvas_index == (canvas_count-1)) ? (list_len % CHAR_ROW_COUNT) : CHAR_ROW_COUNT;


    Serial.println(String("In da loop ") + String(canvas_index));
    Serial.println(String(letters_in_current_row));
    Serial.println(String(letter_list));
    delay(500);
    
    canvas_list[canvas_index] = give_canvas(letter_list + (canvas_index * CHAR_ROW_COUNT), letters_in_current_row);
  }

 // return a list of matrices
  return canvas_list;
}


void pen_write_dot() {
      pen.attach(9);
      for (int penPos = 105; penPos >= maxBluePen; penPos -= 2) { 
        pen.write(penPos);              
        delay(2);                       
      }
      delay(60);
      for (int penPos = maxBluePen; penPos <= 105; penPos += 2) { 
        pen.write(penPos);              
        delay(2);                      
      }
      delay(10);
      pen.detach();
}

void set_horizontal_pos(float horizontalPos) {
      horizontal.attach(7);
      for (float currHorizontalPos = HORIZONTAL_POS; currHorizontalPos < horizontalPos; ++currHorizontalPos) {
        horizontal.write(currHorizontalPos);              // tell servo to go to position in variable 'pos'        
        delay(45);
      }
      HORIZONTAL_POS = horizontalPos;
      horizontal.detach();  
}

void loop() {
 int stringLen = strlen(someString);
 Serial.println(someString);
 Serial.println(stringLen);
 delay(200);

 
 char** output_rows = give_rows(someString, stringLen);


 
 int output_row_count = give_row_count(stringLen);



 float horizonalPos = 0;
 for (int output_row_index = 0; output_row_index < output_row_count; ++output_row_index) {
  for (int output_pixel_row_index = 0; output_pixel_row_index < CHAR_HT; ++output_pixel_row_index) {
     for (int col_index = 0; col_index < CANVAS_WIDTH; ++col_index) {
        horizonalPos = startHorizontalPos + (col_index * jumpsInHorizontalPos);
   
        //Serial.print(output_rows[output_row_index][output_pixel_row_index * CANVAS_WIDTH + col_index]);        
        if (output_rows[output_row_index][output_pixel_row_index * CANVAS_WIDTH + col_index]) {
          set_horizontal_pos(horizonalPos);
          pen_write_dot();
          Serial.print(String("1"));

          // set a delay to keep power load reasonable
          delay(2);
        }
        else {
          Serial.print(String("0"));
        }
     }

     /*
     for (horizonalPos = startHorizontalPos; horizonalPos <= endingHorizontalPos; horizonalPos += jumpsInHorizontalPos ) { // goes from 0 degrees to 180 degrees in steps of 1 degree
          set_horizontal_pos(horizonalPos);
          pen_write_dot();
    
          // set a delay to keep power load reasonable
          delay(2);
     }
     */     
     
    
      horizontal.attach(7);
      for (; horizonalPos >= startHorizontalPos - 10; horizonalPos -= 2) { // goes from 180 degrees to 0 degrees
        horizontal.write(horizonalPos);              // tell servo to go to position in variable 'pos'
        delay(15);                       // waits 15ms for the servo to reach the position
      }
      HORIZONTAL_POS = horizonalPos;
      delay(50);
      horizontal.detach();

      /////////////////////////////////
      Serial.print(String("\n"));
      /////////////////////////////////
      
      // Move down
      vertical.attach(8);
      vertical.write(90);
      delay(125);
      vertical.write(38);              // tell servo to go to position in variable 'pos'                       // waits 15ms for the servo to reach the position
      vertical.detach();
      delay(50);
  }
 }
}
