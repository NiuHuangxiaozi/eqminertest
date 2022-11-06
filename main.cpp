#include<iostream>

#include "Task.h"
int main()
{

	Judge a("/home/quier/inputfile", 0);
	a.start_factories();
	a.save_results();
	return 0;
}