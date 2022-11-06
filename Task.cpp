
#include"Task.h"

//thread
static void factory(JudgeControl * a)
{
    a->start_judge();
}



//judge
Judge::Judge(std::string sourcepath, int index)
{
    //0
    sourcefix=sourcepath+"/";
    //1
	std::string task = "task" + std::to_string(index)+"/";
	tempprefix = "./temp/" + task;
	answerfix = "./answer/" + task;
	finished = false;

    //2
	DIR* pDir;   //  是头文件<dirent.h>的类型
	struct dirent* ptr;  // opendir、readdir这些都是头文件dirent.h
	if (!(pDir = opendir(sourcepath.c_str()))) return;

	while ((ptr = readdir(pDir)) != 0)
	{
		if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
		{
			std::string filename = ptr->d_name;
            fordernames.push_back(filename);
		}
	}
	closedir(pDir);

    //3
    for(int i=0;i<fordernames.size();i++)
    {
        std::string path1=tempprefix+fordernames[i];
        std::string path2=answerfix+fordernames[i];
        int isCreate1 = mkdir(path1.c_str(),S_IRWXU);
        int isCreate2 = mkdir(path2.c_str(),S_IRWXU);
        /*
        if( !isCreate1 )
            std::cout<<"create path1: "+path1<<std::endl;
        else
            std::cout<<"create path1 failed! error code :"<<isCreate1<<path1<<std::endl;
        if( !isCreate2 )
            std::cout<<"create path1: "+path2<<std::endl;
        else
            std::cout<<"create path2 failed! error code :"<<isCreate2<<path2<<std::endl;
        */
    }
}


Judge::~Judge()
{
    for(int i=0;i<factories.size();i++)
    {
        delete factories[i];
        factories[i]=nullptr;
    }
    for(int i=0;i<thds.size();i++)
    {
        thds[i]=nullptr;
    }
}


void Judge::start_factories()
{
    //1
    for(int i=0;i<fordernames.size();i++)
    {
        std::string tempfile=tempprefix+fordernames[i];
        std::string answerfile=answerfix+fordernames[i];
        std::string sourcefile=sourcefix+fordernames[i];
        JudgeControl * c=new JudgeControl(sourcefile,answerfile,tempfile);

        factories.push_back(c);
    }

    //2
    for(int i=0;i<factories.size();i++)
    {
        std::thread * t=new std::thread(factory,factories[i]);
        thds.push_back(t);
    }

    //3
    for(int j=0;j<thds.size();j++)
        thds[j]->join();
}

void Judge::create_environment()
{


}


void Judge::save_results()
{



}