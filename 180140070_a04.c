/*
 -------------------------------------
 File:    180140070_a04.c
 Project: cp386_a04
 file description
 -------------------------------------
 Author:  Ziying Ren
 ID:      180140070
 Email:   renx0070@mylaurier.ca
 Version  2020-08-01
 -------------------------------------
 */
/*
 -------------------------------------
 File:    180140070_a04.c
 Project: a04
 file description
 -------------------------------------
 Author:   Ziying Ren
 ID:       180140070
 GitHub login ID:         Ziying-Ren
 Github repository URL:
 Email:   renx0070@mylaurier.ca
 Version  2020-07-20
 -------------------------------------
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4
#define TRUE 1
#define FALSE 0
int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int requests[]);
void release_resources(int customer_num, int release[]);

// Handle the allocation task
// If Request_i < Need_i, output unsafe
int request_resources(int customer_num, int request[]) {
	int SAFE_FLAG = TRUE;
	int WAIT_FLAG = FALSE;
	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		if (request[i] > need[customer_num[i]]) {
			SAFE_FLAG = FALSE;
			break;
		} else
			continue;
	}
	if (SAFE_FLAG == FALSE) {
		return -1;
	}

	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		if (request[i] > available[i]) {
			WAIT_FLAG = TRUE;
			break;
		} else
			continue;
	}
	if (WAIT_FLAG == TRUE) {
		return -1;
	}

	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		available[i] -= request[i];
		allocation[customer_num][i] += request[i];
		need[customer_num][i] -= request[i];
	}
	if (!safe_state(available)) {
		// Roll back the result
		for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
			available[i] += request[i];
			allocation[customer_num][i] -= request[i];
			need[customer_num][i] += request[i];
		}
		return -1;
	} else {
		return 0;
	}

}
void release_resources(int customer_num, int release[]) {
	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		//Try to release all resources
		available[i] += release[i];
		allocation[customer_num][i] -= release[i];
		need[customer_num][i] += release[i];
		if (allocation[customer_num][i] < 0) //If don't have so much resources.
				{
			fprintf(stderr, "This release request is invaild! denied.\n");
			for (int j = 0; j < i; j++) {
				available[i] -= release[i];
				allocation[customer_num][i] += release[i];
				need[customer_num][i] -= release[i];
			}
			return;
		}
	}
}

int main() {
	char buf[100];
	char c;
	int i = 0;
	while ((c = getchar()) != (int) '\n')
		buf[i++] = c;
	if (buf[0] == 'R' && buf[1] == 'Q') {
		int customer_index;
		int require[NUMBER_OF_RESOURCES];
		char type[2];
		char *pointer = (buf + 3);
		sscanf(pointer, "%d", &customer_index); //Read the index first
		pointer += 2;
		for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
			sscanf(pointer, "%d", &require[i]);
			pointer += 2;
		}
		if (request_resources(customer_index, require) == 0) {
			printf("This situation is safe, accepted.\n");
			continue;
		} else {
			fprintf(stderr, "This request is unsafe, denied.\n");
			continue;
		}

	}
}

