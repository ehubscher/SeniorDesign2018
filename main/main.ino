#include <Servo.h>
#include <AFMotor.h>

#define MOTOR_SPEED 255

int servo_1_angle = 0; 
int motor_num_1 = 1;
int motor_num_2 = 2;
int motor_num_3 = 3;
int motor_num_4 = 4;

AF_DCMotor M3 = AF_DCMotor(motor_num_3);
AF_DCMotor M4 = AF_DCMotor(motor_num_4);

Servo servo_1;

int serialData = 0;

void setup() {
 Serial.begin(9600);

 servo_1.attach(10);

 M3.setSpeed(200);
 M3.run(RELEASE);

 M4.setSpeed(200);
 M4.run(RELEASE);

 M3.setSpeed(MOTOR_SPEED);
 M4.setSpeed(MOTOR_SPEED);
}

void loop() {
  serialData = Serial.read(); //; - '0';
  Serial.println(serialData);
  if (serialData == 97) { // a left
    turn_left();
  }
 
  if (serialData == 119) { //w forward
    move_forward();
  }
 
  if (serialData == 100) { //d right
    turn_right();
  }
 
  if (serialData == 115) { //s back
    move_backward();
  }

  if (serialData == 104) { //h open servo 1 arm
    open_servo_1();
  }

  if (serialData == 106) { //j close servo 1 arm
    close_servo_1();
  }

  if (serialData == 107) { //k incrementally open servo 1 arm
    inc_open_servo_1();
  }

  if (serialData == 108) { //l incrementally close servo 1 arm
    inc_close_servo_1();
  }

 delay(10);

}

void open_servo_1() {
  servo_1.write(0);
  //delay(1000);
}

void close_servo_1() {
  servo_1.write(160);
  //delay(1000);
}

void inc_open_servo_1() {
  servo_1_angle = servo_1_angle + 20;
  if(servo_1_angle > 180) {
    servo_1_angle = 180;
  }
  
  servo_1.write(servo_1_angle);
  //delay(1000);
}

void inc_close_servo_1() {
  servo_1_angle = servo_1_angle - 20;
  if(servo_1_angle < 0) {
    servo_1_angle = 0;
  }
  
  servo_1.write(servo_1_angle);
  //delay(1000);
}

void move_forward() {
  M3.run(BACKWARD);
  M4.run(BACKWARD);

  delay(100);

  M3.run(RELEASE);
  M4.run(RELEASE);
}

void move_backward() {
  M3.run(FORWARD);
  M4.run(FORWARD);

  delay(100);

  M3.run(RELEASE);
  M4.run(RELEASE);
}

void turn_right() {
  M3.run(FORWARD);
  M4.run(BACKWARD);

  delay(100);

  M3.run(RELEASE);
  M4.run(RELEASE);
}

void turn_left() {
  M3.run(BACKWARD);
  M4.run(FORWARD);

  delay(100);

  M3.run(RELEASE);
  M4.run(RELEASE);
}
