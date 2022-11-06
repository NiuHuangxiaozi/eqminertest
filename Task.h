#pragma once
#include<vector>
#include<string>
#include<iostream>
#include<dirent.h>
#include<cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include "JudgeControl.h"
#include <thread>

class Judge {


private:
	std::vector<JudgeControl*> factories;
	std::vector<std::string> fordernames;
    std::vector<std::thread*> thds;
	std::string tempprefix;
	std::string answerfix;
    std::string sourcefix;
	bool finished;

public:
	Judge(std::string sourcepath, int index);
    ~Judge();

	bool is_finished() {
		return finished = true;
	}
	void create_environment();

	void start_factories();

	void save_results();





};
