// CODE FOR ROB3 ARDUINO EXAMINATION - BASED ON REACT TIME CODE

#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define ST 2
#define BG 3
#define BR 4
#define redled 7
#define yelled 8
#define grled 9

struct userdata {
	// This structure stores data and statistics for
	// 7 users (size of our project group)
	int id;
	unsigned long results[7][10];
	char status[7][10];				// 'p' if passed, 'f' if failed
	float average[7];
	float variance[7];
	//float allaverage;
	//float allvariance;
};

//-------------------------------------------SETUP----------------------------------------//

void setup()
{
	pinMode(ST, INPUT);
	pinMode(BG, INPUT);
	pinMode(BR, INPUT);
	pinMode(redled, OUTPUT);
	pinMode(yelled, OUTPUT);
	pinMode(grled, OUTPUT);

	Serial.begin(9600);
	delay(2);
	Serial.println("Booted up");

}

//------------------------------------------LOOP------------------------------------//

void loop()
{
	// Select user
	struct userdata user;
	//user.id = SelectUser();
	user.id = 0; //Placeholder

	// Wait for start button

	for (int i; i < 10; i++) {
		int led = random(7, 9);
		pinMode(led, 1);
		// Detects button
		int button = 0;	//Placeholder
		// Detects time taken
		unsigned long reacttime = 0; //Placeholder

		switch (led)	//  <-------------------- Switch-Case structure here
		{
		default:
			break;
		case redled:
			if (button == BR) {
				user.results[user.id][i] = reacttime;
				user.status[user.id][i] = 'p';
			}
			else {
				user.results[user.id][i] = 0;
				user.status[user.id][i] = 'f';
			}
			break;

		case grled:
			if (button == BG) {
				user.results[user.id][i] = reacttime;
				user.status[user.id][i] = 'p';
			}
			else {
				user.results[user.id][i] = 0;
				user.status[user.id][i] = 'f';
			}
			break;

		case yelled:
			if (button == 0) {
				user.results[user.id][i] = 0;
				user.status[user.id][i] = 'p';
			}
			else {
				user.results[user.id][i] = 0;
				user.status[user.id][i] = 'f';
			}
			break;
		}

		delay(random(500, 3000));	// Delay a random amount of time
									// Between 0.5 and 3 seconds
	}

	// Do average
	average(results[user.id][10]);

	// Do variance
	
	variance(results[user.id][10]);
	
	printStatistics(user.id);

	delay(1000);	// Arbitrary wait of 1 second
					// between experiments
}


//---------------------------------------------------FUNCTIONS---------------------------------------//


float average(float time_arr[][10]){   // Declare a function that returns a float in the form of an average

  float sum = 0;  // Declare a float to hold the sum of all the time from the array
  
  for(unsigned int i=0, i<10, i++){      // A for loop that sums the array

    sum = sum + time_arr[i];    // Add all entries from the array of timings.
  }

  float average = sum/10; // Calculate average of the sum

  return average;  // Return the average of the data type float
}


float variance( float time_arr[][10]){ // Declare a function that returns a float in the form of variance

    float sum1 = 0;
    float variance = 0;
    
    for(unsigned int i=0, i<10, i++){

      sum1 = sum1 + pow(time_arr[i], 2);
    }

    variance = sqrt((sum1/10));
    
    return variance;  
}



void printStatistics(int id) {
	struct userdata user;
	Serial.print("Displaying results for user ");
	Serial.println(id);
	Serial.print("\n");
	for (int i = 0; i < 10; i++) {
		Serial.print("Trial #");
		Serial.print(i);
		if (user.status[id][i] == 'p') {
			Serial.print(":	Passed - ");
			Serial.println(user.results[id][i]);
		}
		else Serial.println(":	Failed");
	}
	Serial.print("Average:	");
	Serial.println(user.average[id]);
	Serial.print("Variance:	");
	Serial.println(user.variance[id]);
	Serial.println("\n");
	return;
}

//Select User & Detects Button

// This constant won't change:
const int buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  if (Serial.available() > 0) {
    int number = Serial.read();
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
    
switch (number) {
case 1: //selecting user
  Serial.println("User 1"); //prints User 1
    {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;
  
case 2://selecting user
  Serial.println("User 2");
    {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;

case 3://selecting user
  Serial.println("User 3");
  {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;
  case 4://selecting user
  Serial.println("User 4"); 
  {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;
  case 5: //selecting user
  Serial.println("User 5");
  {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;
  case 6: //selecting user
  Serial.println("User 6");
  {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;
  case 7: //selecting user
  Serial.println("User 7"); 
  {
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes:  ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
     // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;
  // turns on the LED every 3 button pushes by
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of
  // the division of two numbers:
  if (buttonPushCounter % 3 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
    }
   }
  }
  break;
  default:
  Serial.println("User Invalid"); //selecting invalid user e.g.'8'
  break;
}
delay(1);
}
}
