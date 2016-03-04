// Author : Sung-ju Kim
// Email  : goddoe2@gmail.com
// github : https://github.com/goddoe
// The MIT License (MIT)
// Copyright (c) 2016 Sung-ju Kim


// This example teachs you how you can train your own neural network with AwsomeNN
// In this example you neural network trains text data which is about XOR problem
// Neural net learns about how to solve XOR problem 
// After this example, you can use AwsomeNN to apply any problem with it.

#include <stdio.h>
#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include "Net.h"

using namespace std;
using namespace sj;

class Trainer
{
public:
    vector< float*> m_input;
    vector< float*>  m_target;

    void parseData(char* _fileName)
    {
        FILE *f = fopen(_fileName, "rt");
        for(int i = 0 ; i < 100; ++i)
        {
            float *input = new float[2];
            float *target = new float[1];

            fscanf(f, "in: %f %f\n", &input[0], &input[1]  );
            fscanf(f, "out: %f\n", &target[0] );

            m_input.push_back(input);
            m_target.push_back(target);
        }

		//
        //for(int i = 0 ; i < m_input.size() ; ++i)
        //{
        //    printf("in : %f %f\n", m_input[i][0], m_input[i][1]);
        //    printf("out: %f\n", m_target[i][0]);
        //}
    }
};


void MLP(int argc, char* argv[])
{
    /****************************/

    Trainer trainer;
    trainer.parseData("./sample.txt");

    Net *net = new Net();

    try
    {
        net = new Net(2);
        net->push_back_layer(50);
        net->push_back_layer(30);
        net->push_back_layer(20);
        net->push_back_layer(1);

        net->setWeight();
    }
    catch(exception e)
    {
        printf("%s\n", e.what());
        exit(0);
    }

	printf("*************************************************\n");
	printf("MLP Learning Start!\n");
    printf("size =  %d\n", trainer.m_input.size());

	int count =0;
    for(int i = 0 ; i < trainer.m_input.size(); ++i)
    {
        net->feedforward(trainer.m_input[i]);
        net->backprob(trainer.m_target[i]);
        
        if( (count++) % 5000 == 0)
            printf("count: %d\n", count);
    }
    printf("learing done!\n");
	printf("*************************************************\n");
	
	char save_path[2048]	= "./first_net.txt";
	printf("Your neural network is saved \"%s\"\n", save_path);

	net->save("first_net.txt");

	// if you wants load your network, use code below!	
    // net->load("first_net.txt");
	printf("*************************************************\n");


	// this is for test!
    printf("Test your self!\n");
	printf("type like\n");
	printf("input: 1.0 1.0\n");
	printf("then you can get near 0, because 1.0 XOR 1.0 is 0!\n");
	printf("input: 1.0 0.0\n");
	printf("then you can get near 1, because 1.0 XOR 0.0 is 1!\n");
	printf("! means not factorial this times! :-)\n");
	printf("if you wants to quit the program type 100 0\n\n");

	while(true)
    {
        float input[2];

        printf("input : ");
        scanf("%f %f", &input[0], &input[1]);

        if(input[0] == 100.0)
            break;

        net->feedforward(input);

        printf("result : %f\n\n", (float)(net->m_layersActivation.back()[0]));
    }
     delete net;

	 printf("bye ;-)\n");
}

int main(int argc, char* argv[])
{
	system("clear");
	MLP(argc, argv);
}
