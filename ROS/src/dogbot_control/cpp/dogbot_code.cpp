#include <ros/ros.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>

/*NOTA PER L'UTILIZZO:
	1)Aprire una shell ed eseguire i seguenti comandi:
		cd new_ws
		catkin_make
		source devel/setup.bash
		roslaunch dogbot_gazebo gztest.launch
	2)Nuova shell ed eseguire:
		cd new_ws
		source devel/setup.bash
		rosrun dogbot_control dogbot_node
	FINE
*/
int main(int argc, char** argv)
{
  //Inizializzazione e avvio del nodo
	ros::init(argc, argv, "dogbot");
	ros::NodeHandle nh;
  
	//Definizione dei Publisher
	ros::Publisher pubflk = nh.advertise<std_msgs::Float64>("/dogbot/front_left_knee_position_controller/command", 0.0);
	ros::Publisher pubblk = nh.advertise<std_msgs::Float64>("/dogbot/back_left_knee_position_controller/command", 0.0);
	ros::Publisher pubfrk = nh.advertise<std_msgs::Float64>("/dogbot/front_right_knee_position_controller/command", 0.0);
	ros::Publisher pubbrk = nh.advertise<std_msgs::Float64>("/dogbot/back_right_knee_position_controller/command", 0.0);
	ros::Publisher pubflp = nh.advertise<std_msgs::Float64>("/dogbot/front_left_pitch_position_controller/command", 0.0);
	ros::Publisher pubblp = nh.advertise<std_msgs::Float64>("/dogbot/back_left_pitch_position_controller/command", 0.0);
	ros::Publisher pubfrp = nh.advertise<std_msgs::Float64>("/dogbot/front_right_pitch_position_controller/command", 0.0);
	ros::Publisher pubbrp = nh.advertise<std_msgs::Float64>("/dogbot/back_right_pitch_position_controller/command", 0.0);
	ros::Publisher pubflr = nh.advertise<std_msgs::Float64>("/dogbot/front_left_roll_position_controller/command", 0.0);
	ros::Publisher pubfrr = nh.advertise<std_msgs::Float64>("/dogbot/front_right_roll_position_controller/command", 0.0);
	ros::Publisher pubblr = nh.advertise<std_msgs::Float64>("/dogbot/back_left_roll_position_controller/command", 0.0);
	ros::Publisher pubbrr = nh.advertise<std_msgs::Float64>("/dogbot/back_right_roll_position_controller/command", 0.0);
	ros::Publisher pubj1 = nh.advertise<std_msgs::Float64>("/dogbot/joint1_position_controller/command", 0.0);
	ros::Publisher pubj2 = nh.advertise<std_msgs::Float64>("/dogbot/joint2_position_controller/command", 0.0);
	ros::Publisher pubj3 = nh.advertise<std_msgs::Float64>("/dogbot/joint3_position_controller/command", 0.0);
	ros::Publisher pubj4 = nh.advertise<std_msgs::Float64>("/dogbot/joint4_position_controller/command", 0.0);
	ros::Publisher pubj5 = nh.advertise<std_msgs::Float64>("/dogbot/joint5_position_controller/command", 0.0);
	ros::Publisher pubj6 = nh.advertise<std_msgs::Float64>("/dogbot/joint6_position_controller/command", 0.0);
	std_msgs::Float64 flk; //definisco la variabile flk come tipo std_msgs::Float64
	flk.data = 1.8; //valore inserito in flk
	std_msgs::Float64 blk;
	blk.data = 1.7;
	std_msgs::Float64 frk;
	frk.data = -1.8;
	std_msgs::Float64 brk;
	brk.data = -1.7;
	std_msgs::Float64 flp;
	flp.data = 1.0;
	std_msgs::Float64 blp;
	blp.data = 1.0;
	std_msgs::Float64 frp;
	frp.data = -1.0;
	std_msgs::Float64 brp;
	brp.data = -1.0;
	std_msgs::Float64 flk1;
	flk1.data = 0.0;
	ros::Rate rate(1); //rateo di pubblicazione 1 sec
	ros::Rate rate2(0.5); // 2 sec
  ros::Rate rate3(8);  //0.125 sec
	ros::Rate rate4(1.5); //0.7 sec

	//ALZATA
	int i = 0;
  while(i < 2)
  {	
    pubflk.publish(flk);
		pubblk.publish(blk);
		pubfrk.publish(frk);
		pubbrk.publish(brk);
		pubflp.publish(flp);
		pubblp.publish(blp);
		pubfrp.publish(frp);
		pubbrp.publish(brp); //invio del valore flk al joint  
		rate.sleep(); //scandisce il tempo di pubblicazione
		i++; 
	}
	std_msgs::Float64 j1;
	std_msgs::Float64 j2;
	std_msgs::Float64 j3;
	std_msgs::Float64 j4;
	std_msgs::Float64 j5;
	std_msgs::Float64 j6;
	std_msgs::Float64 brr;
	std_msgs::Float64 frr;
	std_msgs::Float64 blr;
	std_msgs::Float64 flr;

//CAMMINATA
//LOGICA: Dalla posizione in cui si porta dopo essersi alzato procedo in questo modo:
	while(ros::ok()){
		while(i<10 && ros::ok()){
       frk.data=-2.10; //piego il ginocchio anteriore e posteriore destro
			 brk.data=-2.10;
       pubfrk.publish(frk);
			 pubbrk.publish(brk);
       rate3.sleep(); //attesa di 0.125 sec
       frp.data=-0.40; //porto in avanti il passo frontale e posteriore destro
			 brp.data=-0.40; //e apro leggermente il "roll joint" sempre frontale e posteriore destro
			 brr.data=0.10;
			 frr.data=-0.10;
			 j1.data=0.6; //movimentazione parziale del braccio
		   j2.data=-0.2;
			 pubj1.publish(j1);
			 pubj2.publish(j2);
       pubfrp.publish(frp);
			 pubbrp.publish(brp);
			 pubbrr.publish(brr);
			 pubfrr.publish(frr);
       rate3.sleep(); //attesa di 0.125 sec
       frk.data=-1.4;//estendo il ginocchio anteriore e posteriore destro per riportarli al contatto con il terreno
			 brk.data=-1.4;
       pubfrk.publish(frk);
			 pubbrk.publish(brk);
       rate3.sleep(); //attesa di 0.125 sec
       frp.data=-0.75;//porto indietro il passo frontale e anteriore destro
			 brp.data=-0.75;
       pubfrp.publish(frp);
			 pubbrp.publish(brp);
			 rate4.sleep(); //attesa di 0.7 sec
       //Stessa logica adoperata per il fianco destro la applico al fianco sinistro
       flk.data=2.10;
			 blk.data=2.10;
       pubflk.publish(flk);
			 pubblk.publish(blk);
       rate3.sleep(); //0.125 sec
       flp.data=0.40;
			 blp.data=0.40;
			 blr.data=-0.1;
			 flr.data=0.1;
			 j3.data=-0.2;
		   j4.data=2.0;
       pubj3.publish(j3);
			 pubj4.publish(j4);
       pubflp.publish(flp);
			 pubblp.publish(blp);
			 pubblr.publish(blr);
			 pubflr.publish(flr);	
       rate3.sleep(); //0.125 sec
       flk.data=1.4;
			 blk.data=1.4;
       pubflk.publish(flk);
			 pubblk.publish(blk);
       rate3.sleep(); //0.125 sec
			 flp.data=0.75;
			 blp.data=0.75;
       pubflp.publish(flp);
			 pubblp.publish(blp);
			 rate4.sleep(); //0.7 sec
			 i++;
		}
		i=0;
		//Movimentazione parziale del braccio a robot fermo
		rate2.sleep();
    j1.data=-0.6;
		j2.data=-0.2;
		j3.data=-0.4;
		j4.data=1.0;
		pubj1.publish(j1);
		pubj2.publish(j2);
		pubj3.publish(j3);
		pubj4.publish(j4);
		rate2.sleep();
		j1.data=0.6;
		j2.data=-0.2;
		j3.data=0.0;
		j4.data=1.2;
		pubj1.publish(j1);
		pubj2.publish(j2);
		pubj3.publish(j3);
		pubj4.publish(j4);
		rate2.sleep();
	}
	
 }


/*PROBLEMA RISCONTARTO: all'ingresso del cilco while in cui avviene la camminata non vengono rispettati gli sleep, mentre dopo l'ingresso il tutto funziona bene.*/
