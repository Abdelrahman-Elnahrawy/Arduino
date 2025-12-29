// -------------------- Global Variables --------------------

// Error flag (1 = error detected)
int ERROR = 0;

// -------- Oxygen Flow Variables --------
float CurrentReadingO;
float SumO = 0;
float AverageO;
int MeasuresNO = 10;   // Number of samples for Oxygen
float OF;              // Oxygen Flow result

// -------- Air Flow Variables --------
float CurrentReadingA;
float SumA = 0;
float AverageA;
int MeasuresNA = 10;   // Number of samples for Air
float AF;              // Air Flow result

// -------- Patient Flow Variables --------
float CurrentReadingP;
float SumP = 0;
float AverageP;
int MeasuresNP = 10;   // Number of samples for Patient
float IF;              // Patient Flow result

// -------- Flow Summation over 3 seconds --------
float OFSUM = 0;       // Oxygen flow sum
float AFSUM = 0;       // Air flow sum
float IFSUM = 0;       // Patient flow sum

// Timing variable
unsigned long previousMillis1 = 0;

// ----------------------------------------------------------

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentMillis1 = millis();

  // -------- Oxygen sensor averaging (A5) --------
  for (int i = 0; i < MeasuresNO; i++)
  {
    CurrentReadingO = analogRead(A5);
    SumO += CurrentReadingO;
    delay(1);
  }
  AverageO = SumO / MeasuresNO;
  SumO = 0;

  // -------- Air sensor averaging (A6) --------
  for (int i = 0; i < MeasuresNA; i++)
  {
    CurrentReadingA = analogRead(A6);
    SumA += CurrentReadingA;
    delay(1);
  }
  AverageA = SumA / MeasuresNA;
  SumA = 0;

  // -------- Patient sensor averaging (A7) --------
  for (int i = 0; i < MeasuresNP; i++)
  {
    CurrentReadingP = analogRead(A7);
    SumP += CurrentReadingP;
    delay(1);
  }
  AverageP = SumP / MeasuresNP;
  SumP = 0;

  // -------- Accumulate averages for 3 seconds --------
  OFSUM += AverageO;
  AFSUM += AverageA;
  IFSUM += AverageP;

  // -------- Check every 3 seconds --------
  if (currentMillis1 - previousMillis1 >= 3000)
  {
    previousMillis1 = currentMillis1;

    // Check if patient flow matches air + oxygen flow
    if (IFSUM < (AFSUM + OFSUM) * 0.95 ||
        IFSUM > (AFSUM + OFSUM) * 1.05)
    {
      ERROR = 1;   // Flow mismatch detected
    }
    else
    {
      ERROR = 0;
    }

    // Reset sums for next 3 seconds window
    OFSUM = 0;
    AFSUM = 0;
    IFSUM = 0;
  }

  /* -------------------- Flow Calculation --------------------
     ⚠ WARNING ⚠
     This linear equation is NOT validated.
     Etnafis team is NOT responsible for any damage.
     Used only for testing with available fan.
  ------------------------------------------------------------*/

  OF = (AverageO - 68) * 0.265 + 2.7;
  AF = (AverageA - 68) * 0.265 + 2.7;
  IF = (AverageP - 68) * 0.265 + 2.7;
}
