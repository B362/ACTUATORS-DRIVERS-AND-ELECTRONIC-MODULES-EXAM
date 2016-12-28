// CODE FOR ROB3 ARDUINO EXAMINATION - BASED ON REACT TIME CODE

#include <math.h>
#include <stdlib.h>

// REMEMBER TO ADJUST THE I/O PINS USED BELOW

#define ST 2                                                                        // Start button
#define BR 3                                                                        // Button for red led
#define BB 4                                                                        // Button for blue led
#define redled 7                                                                    // Self explanatory
#define yelled 8
#define blooled 9
int Test =0;

struct userdata {
  int id;                                                                           // This structure stores data and statistics for
  unsigned long results[7][10];                                                     // up to 7 users (size of our project group)
  int check;                                                                        // 1 if passed, 0 if failed
  float average[7];
  float variance[7];
  //int check = 0;
};
typedef struct userdata Userdata;

//-------------------------------------------SETUP----------------------------------------//

void setup()
{
  pinMode(ST, INPUT);
  pinMode(BB, INPUT);
  pinMode(BR, INPUT);
  pinMode(redled, OUTPUT);
  pinMode(yelled, OUTPUT);
  pinMode(blooled, OUTPUT);

  Serial.begin(9600);
  delay(2);
  Serial.println("Booted up");

}

//------------------------------------------LOOP------------------------------------//

void loop()
{
  Userdata user;                                                             // Creates a userdata struct with value 'user' //rephrase properly
  user.id = selectUser();                                                           // sets the id of the set struct instance

  Serial.println("Press start");                                                    // Wait for start button
  while (!digitalRead(ST)) delay(2);                                                // While no input(no digitalRead) keep system on endless wait.
  Serial.println("Starting...");

  for (int i = 0; i < 10; i++) {                                                        // Do experiment 10 times
    delay(random(250, 1000));                                                       // Delay a random amount of time
                                                                                    // Between //whatever// seconds
    int led = random(7, 10);                                                        // When converted to type int, will give
                                                                                    // 7, 8 or 9
    digitalWrite(led, HIGH);
    int button = 0;
    unsigned long reacttime = 0;
    Serial.print("Attempt :"); Serial.print(i); Serial.print(", LED :"); Serial.print(led-6); Serial.print(", Button pressed :");// Debug
    waitForButton(&button, &reacttime);                                             //  <--------- Use of pointers here
    //Serial.print(button);
    Serial.println(button);// button); //Serial.println(button);                                // In the case of the function above, since we wanted it
    Serial.print("Reaction time :");
    Serial.println(reacttime);                                                                                // to return 2 values, we used pointers, so the function
                                                                                    // can "return" these values directly to the variable's address
    digitalWrite(led, LOW);
    switch (led)                                                                    //  <-------------------- Switch-Case structure here
    {
      
    case 7://%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%case1
    //Serial.print("button 1");
      if (button == 1) {
        user.results[user.id][i] = reacttime;
        user.check = 5;
        Serial.println("yay");
        //digitalWrite(7, LOW);
        Test = 5;
      }
      else {
        user.results[user.id][i] = 0;
        user.check = 6;
        Serial.println("nay");
        //Serial.println();
        Test = 6;
      }
      break;
      
    case 8://%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%case2
    //Serial.print("button 2");
      if (button == 2) {
        user.results[user.id][i] = reacttime;
        user.check = 5;
        Serial.println("yay");
        //digitalWrite(8, LOW);
        Test = 5;
      }
      else {
        user.results[user.id][i] = 0;
        user.check = 6;
        Serial.println("nay");
        //Serial.println();
        Test = 6;
      }
      break;
      
    case 9://%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%case3
    //Serial.print("button 3");
      if (button == 3) {
        user.results[user.id][i] = 0;
        //user.check = 5;
        user.check = 5;
        Serial.println("yay");
        //digitalWrite(9, LOW);
        Test = 5;
      }
      else {
        user.results[user.id][i] = 0;
        user.check = 6;
        Serial.println("nay");
        //Serial.println();
        Test = 6;
      }
      break;  
      
    default:
      Serial.println("Shit's fucked");
      break;
    }
  }

  user.average[user.id] = average(user.results, user.id);                           // Do Statistics
  user.variance[user.id] = variance(user.results, user.id);
  printStatistics(user.id);

  delay(1000);
}


//---------------------------------------------------FUNCTIONS---------------------------------------//


float average(unsigned long time_arr[][10], int id) {                               // Declare a function that returns an average

  unsigned long sum = 0;                                                            // Declare a float to hold the sum of all the time from the array
  int counter = 0;
  for (int i = 0; i < 10; i++) {                                                    // A for loop that sums the array
    if (time_arr[id][i] != 0) {
      sum = sum + time_arr[id][i];                                                  // Add all VALID entries from the array of timings.
      counter++;
    }
  }
  return sum / counter;                                                             // Calculate average of the sum and return the average of the data
}

float variance(unsigned long time_arr[][10], int id){                               // Declare a function that returns a variance

  float sum1 = 0;
  int counter1 = 0;
  for (int i = 0; i < 10; i++){
    if (time_arr[id][i] != 0) {
      sum1 = sum1 + (time_arr[id][i] * time_arr[id][i]);                            // Normally we would
                                                                                    // use a pow() function, but it only
                                                                                    // accepts arguments of type "double",
                                                                                    // so we figured it would be simpler this way.
    counter1++;
    }
  }
  return sqrt(sum1 / counter1);
}

void printStatistics(int id) {
  Userdata user;
  Serial.print("Displaying results for user ");
  Serial.println(id);
  Serial.print("\n");
  for (int i = 0; i < 10; i++) {
    Serial.print("Trial #");
    Serial.print(i);
    Serial.print(": ");
    if (Test == 5){
    //if (user.check == 5) {                                                       //GET RESULTS IF USER CHECK IS INSTEAD JUST INT AND NOT PART OF STRUCT
      Serial.print("Passed ");
      Serial.println(user.results[user.id][i]);
    }
    else if (Test == 6){
    //else if (user.check == 6){
      Serial.println("Failed");
    }
    else Serial.println("no reading");
    }
  Serial.print("Average:  ");
  Serial.println(user.average[id]);
  Serial.print("Variance: ");
  Serial.println(user.variance[id]);
  Serial.println("\n");
  return;
}

int selectUser(void) {                                                              //Creates the 'selectUser' function
  int sread = 0;                                                                    //Creates the int used as the value of SelectUser
  Serial.println("Choose user:  ");                                                 //Prints prompt for user #
  while (1) {                                                                       //While loop that continues untill it gets serial input
    if (Serial.available() > 0) { //failed attempt at fixing group below 8: && Serial.available() < 8
      sread = Serial.parseInt();                                                    //Assigns serial input to 'sread' int
      break;
    }
   delay(2);
  }
  //sread -= 48;  // ASCII conversion //Irrelevant when using parseint
  Serial.print("Selected user ");                                                   //Prints which user is selected
  Serial.println(sread);
  return sread;                                                                   //sets the value to be
}

void waitForButton(int *button, unsigned long *tome) {                              //tome instead of time just to test -zz
  unsigned long temp = millis();                                                    // Remember starting time
  while (1) {                                                                       // Start infinite loop and return if condition are met
                                                                                    // (button press or timeout)
    if (millis() - temp > 3000) {
      *button = 0;                                                                  //This if statement checks whether the LED has been on for 3 or more seconds
      *tome = 0;
      //Serial.println("no button clicked");
      return;
    }
    else if (digitalRead(2)) {                                                     //This if statement checks whether button 1 is pressed
      *button = 1;
      *tome = millis() - temp;
      //Serial.println("button 1 clicked");
      return;
    }
    else if (digitalRead(3)) {                                                     //This if statement checks whether button 2 is pressed
      *button = 2;
      *tome = millis() - temp;
      //Serial.println("button 2 clicked");
      return;
    }
    else if (digitalRead(4)) {                                                     //This if statement checks whether button 3 is pressed
      *button = 3;
      *tome = millis() - temp;
      //Serial.println("button 3 clicked");
      return;
    }
    delay(2);                                                                       // Arbitrary
  }
}
