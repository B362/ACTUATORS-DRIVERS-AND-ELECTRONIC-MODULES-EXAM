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
	// Do variance
	// Print statistics

	delay(1000);	// Arbitrary wait of 1 second
					// between experiments
}