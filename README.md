# multithreaded-program-with-banker
Write a multi-threaded program that implements the banker's algorithm.

Project Title: 		CP386 Assignment 4
---

Motivation
---
Write a multithreaded program the implements the banker's algorithm for solving deadlock problems

Installation
---
Software Tools:<br>
VitualBox 6.1.6 <br>
Ubuntu machine <br>

Screenshots
---
[![Screenshot1.jpg](https://i.postimg.cc/mrykg0CY/Screenshot1.jpg)](https://postimg.cc/SXjkZ1ZR)<br>
[![Screenshot2.jpg](https://i.postimg.cc/NFSfnYvc/Screenshot2.jpg)](https://postimg.cc/K372K6Yq)

Individual contribution (Function-wise) 
---
Ziying Ren: <br>
int request_resources(int customer_num, int requests[]) <br>
void release_resources(int customer_num, int release[]) <br>
int main()

Tests
---
Test with the gcc compiler (version 5.4.0) in a Linux environment <br>

Code Examples
---
```c
int request_resources(int customer_num, int request[]) {

	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		available[i] -= request[i];
		allocation[customer_num][i] += request[i];
		need[customer_num][i] -= request[i];
	}
	if (!safe_state(available, customer_num, request[i])) {
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
```

```c
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
```
Authors
---
@Ziying Ren
Student ID: 180140070

Credits
---
Ziying Ren

License
---
MIT License

Copyright (c) [2020] [Ziying Ren]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
