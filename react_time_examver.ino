// CODE FOR ROB3 ARDUINO EXAMINATION - BASED ON REACT TIME CODE

#include <math.h>
#include <stdlib.h>

// REMEMBER TO ADJUST THE I/O PINS USED BELLOW

#define ST 2  // Start button
#define BG 3  // Button for green led
#define BR 4  // Button for red led
#define redled 7  // Self explanatory
#define yelled 8
#define grled 9

struct userdata {
	// This structure stores data and statistics for
	// up to 7 users (size of our project group)
	int id;
	unsigned long results[7][10];
	char status[7][10];				// 'p' if passed, 'f' if failed
	float average[7];
	float variance[7];
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
	struct userdata user;
	user.id = selectUser();

	// Wait for start button
	Serial.println("Press start");
	while (!digitalRead(ST)) delay(2);
	Serial.println("Starting...");

	for (int i; i < 10; i++) {		// Do experiment 10 times
		delay(random(500, 3000));	// Delay a random amount of time
									// Between 0.5 and 3 seconds
		int led = random(7, 10);	// When converted to type int, will give
                              // a number between 7 and 9
		digitalWrite(led, 1);
		int button = 0;
		unsigned long reacttime = 0;
		Serial.print(i); Serial.print("	"); Serial.println(led);	// Debug
		waitForButton(&button, &reacttime);		//  <--------- Use of pointers here
		// In the case of the function above, since we wanted it
		// to return 2 values, we used pointers, so the function
		// can "return" these values directly to the variable's address
		digitalWrite(led, 0);
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
	}

	// Do Statistics
	user.average[user.id] = average(user.results, user.id);
	user.variance[user.id] = variance(user.results, user.id);
	printStatistics(user.id);

	delay(1000);
}


//---------------------------------------------------FUNCTIONS---------------------------------------//


float average(unsigned long time_arr[][10], int id) {   // Declare a function that returns an average

	unsigned long sum = 0;  // Declare a float to hold the sum of all the time from the array
	int counter = 0;
	for (int i = 0; i < 10; i++) {      // A for loop that sums the array
		if (time_arr[id][i] != 0) {
			sum = sum + time_arr[id][i];    // Add all VALID entries from the array of timings.
			counter++;
		}
	}
	return sum / counter; // Calculate average of the sum and return the average of the data
}

float variance(unsigned long time_arr[][10], int id){ // Declare a function that returns a variance

	float sum1 = 0;
	int counter1 = 0;
	for (int i = 0; i < 10; i++){
		if (time_arr[id][i] != 0) {
			sum1 = sum1 + (time_arr[id][i] * time_arr[id][i]);	// Normally we would
													// use a pow() function, but it only
													// accepts arguments of type "double",
													// so we figured it would be simpler this way.
		counter1++;
		}
	}
	return sqrt(sum1 / counter1);
}

void printStatistics(int id) {
	struct userdata user;
	Serial.print("Displaying results for user ");
	Serial.println(id+1);
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

int selectUser(void) {
  int sread = 0;
  Serial.println("Choose user:  ");
	while (1) {
		if (Serial.available() > 0) {
			sread =  Serial.read();
      break;
		}
   delay(2);
	}
  sread -= 48;  // ASCII conversion
	Serial.print("Selected user ");
	Serial.println(sread);
	return sread-1;
}

void waitForButton(int *button, unsigned long *time) {
	unsigned long temp = millis();	// Remember starting time
	while (1) {		// Start infinite loop and return if condition are met
					// (button press or timeout)
		if (millis() - temp > 3000) {
			*button = 0;	// Timeout
			*time = 0;
			return;
		}
		if (digitalRead(BR)) {
			*button = BR;
			*time = millis() - temp;
			return;
		}
		if (digitalRead(BG)) {
			*button = BG;
			*time = millis() - temp;
			return;
		}
		delay(2);	// Arbitrary
	}
}
