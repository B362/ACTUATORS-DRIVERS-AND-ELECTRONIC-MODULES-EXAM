// CODE FOR ROB3 ARDUINO EXAMINATION - BASED ON REACT TIME CODE

#include <math.h>
#include <stdlib.h>

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
		pinMode(led, 0);
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

	// Do Statistics
	user.average[user.id] = average(user.results, user.id);
	user.variance[user.id] = variance(user.results, user.id);
	printStatistics(user.id);

	delay(1000);	// Arbitrary wait of 1 second
					// between experiments
}


//---------------------------------------------------FUNCTIONS---------------------------------------//


float average(unsigned long time_arr[][10], int id) {   // Declare a function that returns a float in the form of an average

	unsigned long sum = 0;  // Declare a float to hold the sum of all the time from the array
	int counter = 0;
	for (int i = 0; i < 10; i++) {      // A for loop that sums the array
		if (time_arr[id][i] != 0) {
			sum = sum + time_arr[id][i];    // Add all entries from the array of timings.
			counter++;
		}
	}
	return sum / counter; // Calculate average of the sum and eturn the average of the data type float
}

float variance(unsigned long time_arr[][10], int id){ // Declare a function that returns a float in the form of variance

	float sum1 = 0;
	int counter1 = 0;
	for (int i = 0; i < 10; i++){
		if (time_arr[id][i] != 0) {
			sum1 = sum1 + (time_arr[id][i] * time_arr[id][i]);
		counter1++;
		}
	}
	return sqrt(sum1 / counter1);
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