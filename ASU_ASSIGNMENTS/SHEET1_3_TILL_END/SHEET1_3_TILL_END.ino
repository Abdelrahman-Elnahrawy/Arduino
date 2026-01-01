/**************************************************************
 * Introduction to Embedded Systems — ASU COURSE
 * ======================= SHEET 1 ============================
 *
 * To compile or test any part:
 * 👉 Uncomment ONLY the required section
 *
 * THANK YOU <3
 *************************************************************/


/**************************************************************
 * SHEET_1_1 — IDIOT_PWM
 *************************************************************/
/*
int x = 2000 * 25 / 100;

void setup() {
    pinMode(7, OUTPUT);
}

void loop() {
    digitalWrite(7, HIGH);
    delay(500);
    digitalWrite(7, LOW);
    delay(1500);
}
*/


/**************************************************************
 * SHEET_1_2 — BOUNCING_LEDS
 *************************************************************/
/*
int LEDs[4] = {4, 5, 6, 7};

void setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
}

void loop() {
    for (int i = 0; i < 4; i++) {
        digitalWrite(LEDs[i], HIGH);
        delay(500);
        digitalWrite(LEDs[i], LOW);
    }

    digitalWrite(7, HIGH);

    for (int i = 3; i > 0; i--) {
        digitalWrite(LEDs[i], HIGH);
        delay(500);
        digitalWrite(LEDs[i], LOW);
    }
}
*/


/**************************************************************
 * SHEET_1_3 — PRIME_NUMBERS
 *************************************************************/
/*
int number = 0;
int x = 2;   // prime counter

void setup() {
    Serial.begin(9600);
    Serial.println("The prime number is: 2");
    Serial.println("The prime number is: 3");
}

void loop() {
    if (x < 1000) {                  // max prime count
        number++;

        for (int i = 2; i < (number / 2); i++) {
            if (number % i == 0) {
                break;
            }

            if (i == (number / 2) - 1) {
                Serial.print("The prime number is: ");
                Serial.println(number, DEC);
                x++;
            }
        }
    }
}
*/


/**************************************************************
 * SHEET_1_4 — PWM_SERIAL_INACCURATE
 *************************************************************/
/*
unsigned long D, N, X;
int incomingByte = 0;

void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(9600);
}

void loop() {

    if (Serial.available() > 0) {
        incomingByte = Serial.read();
        X = 0;

        if (incomingByte == 'D') {
            D = 0;
            Serial.println("Enter delay value then press ENTER");

            while (1) {
                if (Serial.available() > 0) {
                    incomingByte = Serial.read();

                    if (incomingByte == 13) {
                        Serial.println("Delay saved");
                        break;
                    }

                    if (incomingByte >= '0' && incomingByte <= '9') {
                        D = D * pow(10, X) + (incomingByte - '0');
                        X++;
                        if (X > 1) X = 1;

                        Serial.print("D = ");
                        Serial.println(D);
                    }
                }
            }
        }

        if (incomingByte == 'N') {
            N = 0;
            Serial.println("Enter number of pulses then press ENTER");

            while (1) {
                if (Serial.available() > 0) {
                    incomingByte = Serial.read();

                    if (incomingByte == 13) {
                        Serial.println("Number saved");
                        break;
                    }

                    if (incomingByte >= '0' && incomingByte <= '9') {
                        N = N * pow(10, X) + (incomingByte - '0');
                        X++;
                        if (X > 1) X = 1;

                        Serial.print("N = ");
                        Serial.println(N);
                    }
                }
            }
        }

        if (incomingByte == 'S') {
            Serial.println("LOOP started");

            for (int i = 0; i < N; i++) {
                digitalWrite(13, HIGH);
                delay(D / 2);
                digitalWrite(13, LOW);
                delay(D / 2);
            }

            Serial.println("DONE");
        }

        Serial.println("Press D to change delay");
        Serial.println("Press N to change pulses");
        Serial.println("Press S to start");
    }
}
*/


/**************************************************************
 * SHEET_1_6 — SQUARE_ROOT_SERIAL
 *************************************************************/
/*
float x, s;
int income;
int y = 0;
int z = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Welcome to Dumb Root");
    Serial.println("Enter number then press ENTER");
}

void loop() {
    if (Serial.available() > 0) {
        income = Serial.read();

        if (income >= '0' && income <= '9') {
            x = x * pow(10, y) + (income - '0');
            y++;
            if (y > 1) y = 1;
            Serial.println(x, 0);
        }

        else if (income == '.') {
            while (1) {
                if (Serial.available() > 0) {
                    income = Serial.read();

                    if (income == 13) {
                        s = sqrt(x);
                        Serial.print("Answer: ");
                        Serial.println(s, 8);
                        x = y = z = 0;
                        break;
                    }

                    if (income >= '0' && income <= '9') {
                        z--;
                        x += (income - '0') * pow(10, z);
                        Serial.println(x, 4);
                    }
                }
            }
        }

        else if (income == 13) {
            s = sqrt(x);
            Serial.print("Answer: ");
            Serial.println(s, 8);
            x = y = z = 0;
        }
    }
}
*/


/**************************************************************
 * SHEET_1_7 — SERIAL_CALCULATOR
 *************************************************************/
/*
#define SUM     0
#define MUL     1
#define AVERAGE 2

int state;
float x, s;
int income, y = 0, z = 0, n = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("Welcome to Dumb Calculator");
}

void loop() {
    if (Serial.available() > 0) {
        income = Serial.read();

        if (income == 's') state = SUM;
        if (income == 'm') { state = MUL; s = 1; }
        if (income == 'a') state = AVERAGE;
    }
}
*/


/**************************************************************
 * THANK YOU <3 <3 <3
 *************************************************************/
