#include <ros.h>
#include <std_msgs/UInt16.h>
#include <DynamixelWorkbench.h>
#include <geometry_msgs/Twist.h>

#define BAUDRATE            57600
#define BAUDRATE_TO_DXL     1000000
#define LEFT_ID             1
#define RIGHT_ID            2

DynamixelWorkbench dxl_wb;
ros::NodeHandle  nh;


void messageCb( const geometry_msgs::Twist& msg) {

  if (msg.angular.z > 0)
  {
    dxl_wb.goalVelocity(LEFT_ID, -100);
    dxl_wb.goalVelocity(RIGHT_ID, 100);
  }

  else if (msg.angular.z < 0)
  {
    dxl_wb.goalVelocity(LEFT_ID,  100);
    dxl_wb.goalVelocity(RIGHT_ID, -100);
  }

  else if (msg.linear.x > 0)
  {
    dxl_wb.goalVelocity(LEFT_ID, 100);
    dxl_wb.goalVelocity(RIGHT_ID, 100);
  }

  else if (msg.linear.x < 0)
  {
    dxl_wb.goalVelocity(LEFT_ID, -100);
    dxl_wb.goalVelocity(RIGHT_ID, -100);
  }

  else
  {
    dxl_wb.goalVelocity(LEFT_ID, 0);
    dxl_wb.goalVelocity(RIGHT_ID, 0);
  }

}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  //while (!Serial); // Open a Serial Monitor

  dxl_wb.begin("", BAUDRATE_TO_DXL);
  dxl_wb.ping(LEFT_ID);
  dxl_wb.ping(RIGHT_ID);

  dxl_wb.wheelMode(LEFT_ID);
  dxl_wb.wheelMode(RIGHT_ID);

  nh.initNode();
  nh.subscribe(sub);

}

void loop()
{
  nh.spinOnce();
  delay(1);
}
