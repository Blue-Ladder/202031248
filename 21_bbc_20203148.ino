#include <Servo.h>

// Arduino pin assignment
#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10
#define _INTERVAL_DIST    50 // interval (unit: ms)
#define _INTERVAL_SERVO    50 // servo interval (unit: ms)
#define _INTERVAL_SERIAL    100 // serial interval (unit: ms) 
int a, b; // unit: mm
float raw_dist, dist_cali;

unsigned long last_sampling_time_dist, last_sampling_time_servo, last_sampling_time_serial; // unit: ms
bool event_dist, event_servo, event_serial;
Servo myservo;
void setup() {
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(1500);
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
// initialize serial port
  Serial.begin(57600);
  a = 90;
  b = 285;

// initialize event variables
  last_sampling_time_dist = last_sampling_time_servo = last_sampling_time_serial = 0;
  event_dist = event_servo = event_serial = false;
}
float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}
void loop() {
// wait until next sampling time. 
// millis() returns the number of milliseconds since the program started. Will overflow after 50 days.
  unsigned long time_curr = millis();
  if(time_curr >= last_sampling_time_dist + _INTERVAL_DIST) {
        last_sampling_time_dist += _INTERVAL_DIST;
        event_dist = true;
  }
  if(time_curr >= last_sampling_time_servo + _INTERVAL_SERVO) {
        last_sampling_time_servo += _INTERVAL_SERVO;
        event_servo = true;
  }
  if(time_curr >= last_sampling_time_serial + _INTERVAL_SERIAL) {
        last_sampling_time_serial += _INTERVAL_SERIAL;
        event_serial = true;
  }
  if(event_dist) {
    event_dist = false;
    raw_dist = ir_distance();
    dist_cali = 100 + 155.0 / (b - a) * (raw_dist - a);
  }
  if(event_servo) {
    event_servo = false;
// adjust servo position according to the USS read value
    if(dist_cali > 255){
      myservo.writeMicroseconds(770);
    }else{
      myservo.writeMicroseconds(1080);
    }
  }
  
  if(event_serial) {
    event_serial = false;
// output the read value to the serial port
    Serial.print("min:0,max:500,dist:");
    Serial.print(raw_dist); 
    Serial.print(",dist_cali:");
    Serial.println(dist_cali);
  }
   

}
