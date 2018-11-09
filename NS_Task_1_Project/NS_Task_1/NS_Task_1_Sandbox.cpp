#include "NS_Task_1_Sandbox.h"

/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
{
	printf("Node = %c\n", node);
	for (int count = node - '0'; count > 0; count--)
	{
		int left = ADC_Conversion(1);
		int right = ADC_Conversion(3);
		printf("Left = %d ### Right = %d\n", left, right);
		while ((left < 101) && (right < 101))
		{
			forward();
			_delay_ms(200);
			left = ADC_Conversion(1);
			right = ADC_Conversion(3);
		}
	}
	stop();
}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{

}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{

}

/*
*
* Function Name: Square
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a square path on the arena
* Example Call: Square();
*/
void Square(void)
{
	/*forward();
	_delay_ms(500);
	left();
	_delay_ms(500);
	forward();
	_delay_ms(500);
	left();
	_delay_ms(500);
	forward();
	_delay_ms(500);
	left();
	_delay_ms(500);
	forward();
	_delay_ms(500);
	left();
	_delay_ms(500);
	stop();*/
	for (int i = 0; i < 4; i++)
	{
		forward();
		_delay_ms(3000);
		right();
		_delay_ms(467);
	}
	
	
	stop();    //Stop after you have made a square
	_delay_ms(3000); //This delay is for you to observe the output before resetting the simulator.
}


/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
	initSensors();

	/*forward();
	_delay_ms(500);
	stop();*/
	//_delay_ms(2000);
	//printf("\nLeft = %c\n", ADC_Conversion(0)/*==NULL?'n':'s'*/);
	//_delay_ms(2000);
	//int m = (int)ADC_Conversion(2);
	//printf("Middle = %d\n", m /*== NULL ? 'n' : 's'*/);

	//Follow black line till turn encounters (lines 120 - 131)
	//forward();
	//_delay_ms(200);
	//int k = 0;
	//for (k = ADC_Conversion(2); k > 101; k = ADC_Conversion(2))
	//{
	//	forward();
	//	_delay_ms(200);
	//	printf("Sensor = %d\n", k /*== NULL ? 'n' : 's'*/);
	//}
	//printf("Exit sensor = %d\n", k /*== NULL ? 'n' : 's'*/);
	//stop();
	//_delay_ms(1000);

	//wls working
	forward_wls('3');

	/*printf("Right = %c\n", ADC_Conversion(2));
	_delay_ms(2000);*/
	//forward_wls(1);
	//_delay_ms(1000);
}

/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{

}
