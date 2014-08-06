///////////////////////////////////////////////////////////////////////////////
//Source for talker node to send basic commands to i90				     					 //
//v1.0									     																								 //
//First creation							    																					 //
//Huseyin Emre Erdem																										     //
//04.08.2014																														     //
///////////////////////////////////////////////////////////////////////////////

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

#include <sstream>
#include "std_msgs/Duration.h"

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  /*Variables*/
  char data[5];
  char *dataP = &data[0];

	/*Objects*/
  ros::init(argc, argv, "talker"); //Create node called talker
  ros::NodeHandle n;//Create nodehandle to alter node parameters
  ros::Duration d = ros::Duration(1,0);//Duration object to pause node

	while(ros::ok){
		int port = open("/dev/rfcomm1", O_RDWR | O_NOCTTY | O_NDELAY);

		/*Opening port*/
		if(port == -1){
			ROS_INFO("Error opening the port");//Inform user on the terminal
		}
		else{
			ROS_INFO("Serial port is open");//Inform user on the terminal
		}

		/*Send request byte and read incoming data*/
		while(read(port,dataP,1) == 1){//Empty buffer
		}
		write(port,"s",1);
		ROS_INFO("Data request sent");//Inform user on the terminal

		d.sleep(); //Wait for 2 seconds to be published

		read(port,dataP,5);

		/*Show user the data read*/
		for(int i=0;i<5;i++){
		  printf("%c", data[i]);
		}
		printf("\n\r");

		/*Close port and exit*/
		close(port);

		ros::spinOnce();
	}

  //while(1){
  //}

  return 0;
}
