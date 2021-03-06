#define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200); // Initialize serial port
  while (!Serial) {
    ; // wait for serial port to connect.
  }
  Serial.println("Hello World!");
  count = toggle = 1;
  digitalWrite(PIN_LED, toggle); // turn off LED.
}

void loop() {
  Serial.println(++count);
  toggle = toggle_state(toggle); // toggle LED value.
  digitalWrite(PIN_LED, toggle); // update LED status.
  delay(1000); // wait for 1,000 milliseconds
  for(int i = 1; i<=11; i++){
  toggle = toggle_state(toggle); 
  digitalWrite(PIN_LED, toggle); 
  delay(100); 
  }
  while(1){}
}
int toggle_state(int toggle) {
  if(toggle==1){
    toggle=0;
    return toggle;
}
  else{
    toggle=1;
    return toggle;
}
}
