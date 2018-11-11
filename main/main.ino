#include <Servo.h>
#include <AFMotor.h>

#define MOTOR_1_PORT 1
#define MOTOR_2_PORT 2
#define MOTOR_3_PORT 3
#define MOTOR_4_PORT 4

#define MOTOR_SPEED 255

#define MAX_MOTION_DELAY 200
#define INC_MOTION_DELAY 100

#define MAX_TURN_DELAY 70
#define INC_TURN_DELAY 35

#define MAX_ANGLE_SERVO_1 160
#define MIN_ANGLE_SERVO_1 0
#define INC_ANGLE_DELTA_SERVO_1 20

int servo_1_angle = 0;
int serial_input = 0;

AF_DCMotor motor_3 = AF_DCMotor(MOTOR_3_PORT);
AF_DCMotor motor_4 = AF_DCMotor(MOTOR_4_PORT);

Servo servo_1;

void setup()
{
  Serial.begin(9600);

  servo_1.attach(10);

  motor_3.setSpeed(200);
  motor_3.run(RELEASE);

  motor_4.setSpeed(200);
  motor_4.run(RELEASE);

  motor_3.setSpeed(MOTOR_SPEED);
  motor_4.setSpeed(MOTOR_SPEED);
}

void loop()
{
  serial_input = Serial.read();
  Serial.println(serial_input);

  if (serial_input == 119)
  { // 'w' forward
    move_forward(MAX_MOTION_DELAY);
  }
  else if (serial_input == 97)
  { // 'a' left
    turn_left(MAX_TURN_DELAY);
  }
  else if (serial_input == 115)
  { // 's' back
    move_backward(MAX_MOTION_DELAY);
  }
  else if (serial_input == 100)
  { // 'd' right
    turn_right(MAX_TURN_DELAY);
  }
  else if (serial_input == 119)
  { // 't' forward
    move_forward(INC_MOTION_DELAY);
  }
  else if (serial_input == 102)
  { // 'f' left
    turn_left(INC_TURN_DELAY);
  }
  else if (serial_input == 103)
  { // 'g' back
    move_backward(INC_MOTION_DELAY);
  }
  else if (serial_input == 104)
  { // 'h' right
    turn_right(INC_TURN_DELAY);
  }

  if (serial_input == 104)
  { // 'h' fully open servo 1 arm
    open_servo_1(MAX_ANGLE_SERVO_1);
  }
  else if (serial_input == 106)
  { // 'j' fully close servo 1 arm
    close_servo_1(MAX_ANGLE_SERVO_1);
  }
  else if (serial_input == 107)
  { // 'k' incrementally open servo 1 arm
    open_servo_1(INC_ANGLE_DELTA_SERVO_1);
  }
  else if (serial_input == 108)
  { // 'l' incrementally close servo 1 arm
    close_servo_1(INC_ANGLE_DELTA_SERVO_1);
  }

  delay(10);
}

void open_servo_1(int angle_delta)
{
  servo_1_angle = servo_1_angle + angle_delta;
  if (servo_1_angle > 160)
  {
    servo_1_angle = 160;
  }

  servo_1.write(servo_1_angle);
}

void close_servo_1(int angle_delta)
{
  servo_1_angle = servo_1_angle - angle_delta;
  if (servo_1_angle < 0)
  {
    servo_1_angle = 0;
  }

  servo_1.write(servo_1_angle);
}

void move_forward(int delay_magnitude)
{
  motor_3.run(BACKWARD);
  motor_4.run(BACKWARD);

  delay(delay_magnitude);

  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
}

void move_backward(int delay_magnitude)
{
  motor_3.run(FORWARD);
  motor_4.run(FORWARD);

  delay(delay_magnitude);

  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
}

void turn_right(int delay_magnitude)
{
  motor_3.run(FORWARD);
  motor_4.run(BACKWARD);

  delay(delay_magnitude);

  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
}

void turn_left(int delay_magnitude)
{
  motor_3.run(BACKWARD);
  motor_4.run(FORWARD);

  delay(delay_magnitude);

  motor_3.run(RELEASE);
  motor_4.run(RELEASE);
}
