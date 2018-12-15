#include "NS_Task_1_Sandbox.h"
#include "string.h"
using namespace std;
std::vector<vector<int>> paths;
unsigned int obstacle;
#define nut1 11
#define nut2 12

int graph[MAX][MAX] = {
	{0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//0
	{2,0,6,3,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0},//1
	{0,6,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,2},//2
	{0,3,0,0,3,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0},//3
	{0,0,0,3,0,1,0,0,0,0,0,0,0,0,6,0,0,0,0,0,0,0,0},//4
	{0,0,0,0,1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//5
	{0,0,0,0,0,3,0,3,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//6
	{0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//7
	{0,0,0,0,0,0,5,0,0,3,5,0,0,0,0,0,0,0,0,0,0,0,0},//8
	{0,0,0,5,0,0,0,0,3,0,0,4,0,0,0,0,0,0,0,0,0,0,0},//9
	{0,0,0,0,0,0,0,0,5,0,0,2,0,0,0,0,0,0,0,0,0,0,0},//10
	{0,0,0,0,0,0,0,0,0,4,2,0,2,0,0,0,0,0,0,0,0,0,0},//11
	{0,0,2,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0},//12
	{0,3,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,5,0,0,0},//13
	{0,0,0,0,6,0,0,0,0,0,0,0,0,3,0,1,0,0,0,0,0,0,0},//14
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,3,0,0,0,0,0,0},//15
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,5,0,0,0,0},//16
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0},//17
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,3,5,0,0},//18
	{0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,3,0,0,4,0},//19
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,3,0},//20
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,3,0,2},//21
	{0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0}//22
};

/*static int out_nodes[23][4] = { { 1,0,0,0 },{ 2, 3, 13, 0 },{ 1, 12, 22, INFINITY },{ 1, 4, 9, INFINITY },		// 0,1,2,3
{ 3, 5, 14, INFINITY },{ 4, 6, INFINITY, INFINITY },{ 7, 5, 8, INFINITY },{6, INFINITY, INFINITY, INFINITY},	// 4,5,6,7
{ 6, 9, 10, INFINITY },{ 8, 3, 11, INFINITY },{ 8, 11, INFINITY, INFINITY },{10, 9, 12, INFINITY},				// 8,9,10,11
{11, 2, INFINITY, INFINITY},{1, 19, 14, INFINITY},{ 4, 15, 13, INFINITY },{ 14, 16, INFINITY, INFINITY},		// 12,13,14,15
{15, 17, 18, INFINITY},{ 16, INFINITY, INFINITY, INFINITY},{16, 19, 20, INFINITY},{ 18, 13, 21, INFINITY},		// 16,17,18,19
{18, 21, INFINITY, INFINITY},{19, 20, 22, INFINITY},{ 2, 21, INFINITY, INFINITY}								// 20,21,22
};*/

static int out_nodes[23][4] = { { 1,0,0,0 },{ 2, 3, 13, 0 },{ 1, 12, 22, INFINITY },{ 1, 4, 9, INFINITY },		// 0,1,2,3
{ 3, 5, 14, INFINITY },{ 4, 6, DEPOSIT, INFINITY }, { 7, 5, 8, INFINITY }, { 6, DEPOSIT, INFINITY, INFINITY },	// 4,5,6,7
{ 6, 9, 10, INFINITY },{ 8, 3, 11, INFINITY },{ 8, 11, PICKUP, INFINITY },{10, 9, 12, PICKUP},				// 8,9,10,11
{11, 2, PICKUP, INFINITY},{1, 19, 14, INFINITY},{ 4, 15, 13, INFINITY },{ 14, 16, DEPOSIT, INFINITY},			// 12,13,14,15
{15, 17, 18, INFINITY},{ 16, DEPOSIT, INFINITY, INFINITY},{16, 19, 20, INFINITY},{ 18, 13, 21, INFINITY},		// 16,17,18,19
{18, 21, PICKUP, INFINITY},{19, 20, 22, PICKUP},{ 2, 21, PICKUP, INFINITY}									// 20,21,22
};

static char out_dir[23][16] = { {'f',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ' },	// 0
{ 'b', 'r', 'l', 'f', 'l', 'b', 'f', 'r', 'r', 'f', 'b', 'l', 'f', 'l', 'r', 'b' },									// 1
{ 'b', 'l', 'r', ' ', 'r', 'b', 'f', ' ', 'l', 'f', 'b', ' ', ' ', ' ', ' ', ' ' },									// 2
{ 'b', 'f', 'r', ' ', 'f', 'b', 'l', ' ', 'l', 'r', 'b', ' ', ' ', ' ', ' ', ' ' },									// 3
{ 'b', 'r', 'f', ' ', 'l', 'b', 'r', ' ', 'f', 'l', 'b', ' ', ' ', ' ', ' ', ' ' },									// 4
{ 'b', 'f', '1', ' ', 'f', 'b', '3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },									// 5
{ 'b', 'r', 'f', ' ', 'l', 'b', 'r', ' ', 'f', 'l', 'b', ' ', ' ', ' ', ' ', ' ' },									// 6
{ 'b', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },									// 7
{ 'b', 'r', 'f', ' ', 'l', 'b', 'r', ' ', 'f', 'l', 'b', ' ', ' ', ' ', ' ', ' ' },									// 8
{ 'b', 'r', 'l', ' ', 'l', 'b', 'f', ' ', 'r', 'f', 'b', ' ', ' ', ' ', ' ', ' ' },									// 9
{ 'b', 'r', ' ', ' ', 'l', 'b', '3', ' ', 'l', 'r', ' ', ' ', ' ', ' ', ' ', ' ' },									// 10
{ 'b', 'r', 'f', '1', 'l', 'b', 'r', ' ', 'f', 'l', 'b', '3', 'l', '4', 'r', ' ' },									// 11
{ 'b', 'f', '1', ' ', 'f', 'b', '3', ' ', 'l', 'r', ' ', ' ', ' ', ' ', ' ', ' ' },									// 12
{ 'b', 'l', 'f', ' ', 'r', 'b', 'l', ' ', 'f', 'r', 'b', ' ', ' ', ' ', ' ', ' ' },									// 13
{ 'b', 'r', 'f', ' ', 'l', 'b', 'r', ' ', 'f', 'l', 'b', ' ', ' ', ' ', ' ', ' ' },									// 14
{ 'b', 'f', '3', ' ', 'f', 'b', '1', ' ', 'r', 'l', ' ', ' ', ' ', ' ', ' ', ' ' },									// 15
{ 'b', 'r', 'l', ' ', 'l', 'b', 'f', ' ', 'r', 'f', 'b', ' ', ' ', ' ', ' ', ' ' },									// 16
{ 'b', ' ', ' ', ' ', 'r', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },									// 17
{ 'b', 'l', 'f', ' ', 'r', 'b', 'l', ' ', 'f', 'r', 'b', ' ', ' ', ' ', ' ', ' ' },									// 18
{ 'b', 'l', 'r', ' ', 'r', 'r', 'f', ' ', 'l', 'f', 'b', ' ', ' ', ' ', ' ', ' ' },									// 19
{ 'b', 'l', ' ', ' ', 'r', 'b', '1', ' ', 'r', 'l', ' ', ' ', ' ', ' ', ' ', ' ' },									// 20
{ 'b', 'r', 'l', ' ', 'l', 'b', 'f', '3', 'r', 'f', 'b', '1', '4', 'r', 'l', ' ' },									// 21
{ 'b', 'f', '1', ' ', 'f', 'b', '3', ' ', 'l', 'r', ' ', ' ', ' ', ' ', ' ', ' ' }									// 22
};

/*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*/
void forward_wls(int node)
{
	int i;
	for (i = 0; i < node + 1; i++)
	{
		line_follow();
		if(i!=node)
			forward_delay(100);
	}
}

/*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)
{
	left();
	_delay_ms(200);
	while (ADC_Conversion(2) <= 200 && ADC_Conversion(3) <= 200)
	{
		left();
		velocity(127, 127);
	}
	stop();
	_delay_ms(150);
}

/*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
	right();
	_delay_ms(200);
	while (ADC_Conversion(2) <= 200 && ADC_Conversion(1) <= 200)
	{
		right();
		velocity(127, 127);
	}
	stop();
	_delay_ms(150);
}

/*
* Function Name: Square
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a square path on the arena
* Example Call: Square();
*/
void Square(void)
{

}

/*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
	/*
	   1 = left turn until path found
	   2 = forward till next node
	   3 = right turn until path found
	   */
	int dir[] = { 2,3,2,1,2,1,2,1,2,3,2,2,2,3,2,1,2,1,2,1,2,3,2 };
	initSensors();
	forward();
	_delay_ms(100);

	for (int i = 0; i < 23; i++)
	{
		switch (dir[i])
		{
		case 1:
			left_turn_wls();
			stop();
			_delay_ms(500);
			break;
		case 2:
			if (i == 2 || i == 20)
			{
				forward_wls(1);
			}
			else
			{
				forward_wls(0);
			}
			stop();
			_delay_ms(500);
			break;
		case 3:
			right_turn_wls();
			stop();
			_delay_ms(500);
		default:
			break;
		}
	}
	_delay_ms(2000);
	stop();
}

/*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
	direction('f');
	int index1,index2,index3;
	dijkstra(graph, MAX, 0, nut1);
	int length = 0;
	int path[10];
	for (int i = 1; i < 7; i++)
		path[i] = -999;
	int count = 0;
	path[count] = PICKUP;
	for (int i : paths[nut1]) {
		path[count+1] = i;
		count++;
	}
	//path[count + 1] = PICKUP;
	count = 0;
	for (int i = 0; i < 10; i++) {
		if (path[i] >= 0)
			length++;
	}
	printf("\n ****** length = %d\n", length);
	int *p = (int*) malloc(sizeof(int) * (length + 2));
	for (int i = 1; i <= length; i++) {
		*(p - i + length - 1) = path[i];
		printf(" %d ", path[i]);
	}
	printf("\n\nPrinting path $$$$$$$$$$$$$$$\n");
	for (int i = 1; i <= length; i++) {
		printf(" %d -> ", *(p + i));
	}
	//*(p + 0) = PICKUP;
	//*(p + length + 1) = DEPOSIT;
	for (int i = 1; i < length-3; i++)
	{
		int previous_node = 0;
		int current_node = *(p + i);
		if(current_node != 0)
			previous_node = *(p + i - 1);

		int next_node = *(p + i + 1);
		for (int j = 0; j < 4; j++)
		{
			//index1 = 0;
			if (out_nodes[current_node][j] == next_node)
				index2 = j;
			if (out_nodes[current_node][j] == previous_node)
				if (current_node ==0 && previous_node == 0)
					index1 = 0;
				else
					index1 = j;
		}
		char dir = out_dir[current_node][4 * index1 + index2];
		printf("%c\n", dir);
		direction(dir);
	}

	printf("\n\n Result of MAlloc %%%%%%%%%%%%%\n");
	for (int i = 0; i < length + 2; i++) {
		printf("%d -> ", *(p + i));
	}
	//pick();
	/*forward_wls(2);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	right();
	_delay_ms(50);
	stop();
	colour_detect();
	pick();
	_delay_ms(2000);
	//////////////////////////////////////////////////
	//char putred1[] = { 'r','r','f','r','f','l','f' };
	right_turn_wls();
	right_turn_wls();
	forward_wls(0);
	_delay_ms(500);
	forward_delay(1000);
	_delay_ms(500);
	left_turn_wls();
	forward_wls(0);
	left_turn_wls();
	forward_wls(0);
	left_turn_wls();
	forward_wls(1);
	//path1(putred1);
	place();
	_delay_ms(1000);
	///////////////////////////////////////////////////
	right_turn_wls();
	forward_wls(0);
	right_turn_wls();
	//right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(0);
	forward_wls(0);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();*/
}

/*
* Function Name: line_follow
* Input: void
* Output: void
* Logic: Use this function to follow a black line. The function exits after encountering a node.
* Example Call: line_follow();
*/
void line_follow(void)
{
	unsigned char left_sensor, centre_sensor, right_sensor;
	forward();
	velocity(150, 150);
	while (1)
	{
		obstacle = obstacle_detect();
		left_sensor = ADC_Conversion(1);
		centre_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		printf("\n %d %d %d\n ", left_sensor, centre_sensor, right_sensor);
		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor <= 100)//FORWARD
		{
			velocity(150, 150);
		}
		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor >= 100)//RIGHT
		{

			velocity(250, 20);

		}
		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor >= 100)//RIGHT
		{

			velocity(150, 100);;
		}
		if (left_sensor >= 100 && centre_sensor <= 100 && right_sensor <= 100)//LEFT
		{

			velocity(20, 250);
			//_delay_ms(50);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor <= 100)//LEFT
		{

			velocity(100, 150);;
		}
		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor <= 100)//SEARCH FOR BLACK LINE
		{
			velocity(150, 150);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor >= 100)//STOP
		{
			stop();
			forward_delay(150);
			break;
		}
		/*if (obstacle)
		{
			stop();
			right_turn_wls();
			line_follow();
			break;
		}*/
	}
}

/*
* Function Name: forward_delay
* Input: integer
* Output: void
* Logic: Use this function to go forward for a time given in parameters
* Example Call: forward_delay(50);
*/
void forward_delay(int delay)
{
	forward();
	_delay_ms(delay);
	stop();
}

/*
* Function Name: colour_detect
* Input: void
* Output: character
* Logic: Use this function to detect the colour of the object present in front of the bot
* Example Call: colour_detect();
*/
char colour_detect(void)
{
	unsigned int red_pulse_count, green_pulse_count, blue_pulse_count, clear_pulse_count, object_distance;
	for (int i = 0; i < 20; i++)
	{
		filter_red();
		red_pulse_count = color_sensor_pulse_count;
		filter_green();
		green_pulse_count = color_sensor_pulse_count;
		filter_blue();
		blue_pulse_count = color_sensor_pulse_count;
		filter_clear();
		clear_pulse_count = color_sensor_pulse_count;
		//printf("%d \t %d \t %d \t %d \t", red_pulse_count, green_pulse_count, blue_pulse_count, clear_pulse_count);
		object_distance = ADC_Conversion(4);
		//printf("%d\n", object_distance);
		_delay_ms(10);
	}
	if (red_pulse_count > (green_pulse_count + 1000))
		return 'r';
	else if (green_pulse_count > (red_pulse_count + 1000))
		return 'g';
}

void dijkstra(int G[MAX][MAX], int n, int startnode, int endnode) //n is number of nodes which is equal to MAX = 23
{
	int z = 0;
	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes seen so far
	//create the cost matrix from heuristic matrix (graph)
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];

	//initialize pred[],distance[] and visited[]
	for (i = 0; i < n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0; // visited = 0 means not yet visited
	}

	distance[startnode] = 0;
	visited[startnode] = 1; // visited = 1 means counted and visited
	count = 1;
	while (count < n - 1)
	{

		mindistance = INFINITY;
		//nextnode gives the node at minimum distance
		for (i = 0; i < n; i++)
		{
			if (distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}
		}

		//check if a better path exists through nextnode            
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}


	//Store all paths in global vector
	for (i = 0; i < n; i++)
	{
		//A vector containing the shortest path from source node to "i"-th node
		std::vector<int> path;
		if (i != startnode)
		{
			path.push_back(i);
			j = i;
			do
			{
				j = pred[j];
				path.push_back(j);
			} while (j != startnode);
		}
		paths.push_back(path);
	}
	int distCount = 0;
	////printf("\n\n %%%%%%%%%%%%%%%%%%%%%%% \n\n Number of paths %d\n", paths.size());
	////Display all paths
	//for (vector<int> i : paths)
	//{
	//	/*std::reverse(i.begin(), i.end());
	//	paths.erase(paths.begin() + distCount);
	//	paths.push_back(i);*/
	//	if (distCount != startnode)
	//	{
	//		/*printf("\nDistance between %d and %d is : %d\n", startnode, distCount, distance[distCount]);
	//		printf("\nPath is :\n");*/
	//		for (int p : i)
	//		{
	//			//path_node[z] = p;
	//			//printf("%d -> ", p);
	//			//z++;
	//		}
	//		printf("\n");
	//	}
	//	distCount++;
	//}
	////paths.clear();
	////return path_node;
}

void direction(char direction)
{
	switch (direction)
	{
	case 'l': //Left + Line Follow
		left_turn_wls();
		line_follow();
		stop();
		_delay_ms(500);
		break;
	case 'f': //Front Line Follow
		forward_wls(0);
		stop();
		_delay_ms(500);
		break;
	case 'r': // Right + Line Follow
		right_turn_wls();
		line_follow();
		stop();
		_delay_ms(500);
		break;
	case '1': // Left
		left_turn_wls();
		line_follow_delay(200);
		stop();
		_delay_ms(500);
		break;
	case '3': // Right
		right_turn_wls();
		line_follow_delay(200);
		stop();
		_delay_ms(500);
		break;
	case '4': // Double Right
		right_turn_wls();
		right_turn_wls();
		line_follow();
		stop();
		_delay_ms(500);
		break;
	case '5': // Double Left
		left_turn_wls();
		left_turn_wls();
		stop();
		_delay_ms(500);
		break;
	default:
		break;
	}
}

void line_follow_delay(int delay)
{
	unsigned char left_sensor, centre_sensor, right_sensor;
	int count = 0;
	forward();
	velocity(150, 150);
	while (count < delay)
	{
		left_sensor = ADC_Conversion(1);
		centre_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		//printf("\n %d %d %d\n ", left_sensor, centre_sensor, right_sensor);
		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor <= 100)//FORWARD
		{
			velocity(150, 150);
		}
		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor >= 100)//RIGHT
		{

			velocity(250, 20);

		}
		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor >= 100)//RIGHT
		{

			velocity(150, 100);;
		}
		if (left_sensor >= 100 && centre_sensor <= 100 && right_sensor <= 100)//LEFT
		{

			velocity(20, 250);
			//_delay_ms(50);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor <= 100)//LEFT
		{

			velocity(100, 150);;
		}
		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor <= 100)//STOP
		{
			velocity(150, 150);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor >= 100)
		{
			stop();
			forward_delay(150);
			break;
		}
		_delay_ms(1);
		count++;
	}
}

int obstacle_detect(void)
{
	if (ADC_Conversion(FRONT_IR_ADC_CHANNEL) < 10)
		return 1;
	else
		return 0;
}