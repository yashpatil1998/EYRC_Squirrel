#include "NS_Task_1_Predef.h"
extern unsigned int color_sensor_pulse_count;
extern unsigned int obstacle;
#include <vector>
#define MAX 23			//Number of vertices of graph
#define INFINITY 9999   //defining infinity
#define PICKUP 23
#define DEPOSIT 24
using namespace std;
//A vector of vectors having all paths from given source node(fixed) to all other nodes
extern std::vector<vector<int>> paths;

/*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the nodes specified
* Example Call: forward_wls(2) //Goes forward by two nodes
*
*/
void forward_wls(int node);

void left_turn_wls(void);

void right_turn_wls(void);

void Square(void);

void Task_1_1(void);

void Task_1_2(void);

void line_follow(void);

void forward_delay(int);

char colour_detect(void);

void dijkstra(int G[MAX][MAX], int n, int startnode, int endnode);

void direction(char);

void line_follow_delay(int delay);

int obstacle_detect(void);