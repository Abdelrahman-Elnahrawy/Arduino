int red    = 4;
int yellow = 5;
int green  = 6;
int blue   = 7;
int orange = 8;
void setup() {
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  //all low init
  digitalWrite(red   , LOW);
  digitalWrite(green , LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue  , LOW);
  digitalWrite(orange, LOW);

  // red on blue on all off
  digitalWrite(red , HIGH);  
  digitalWrite(blue, HIGH); 
  delay(15000); 
  // red off blue off orange on yellow on                     
  digitalWrite(red,  LOW); 
  digitalWrite(blue, LOW);
  digitalWrite(orange, HIGH);     
  digitalWrite(yellow, HIGH);
  delay(3000); 
  digitalWrite(yellow, LOW);    
  digitalWrite(green  , HIGH);           
  delay(60000);
  digitalWrite(green, LOW);    
  digitalWrite(yellow, HIGH);
  delay(3000);
             
}
