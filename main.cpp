// Author : Sung-ju Kim
// Email  : goddoe2@gmail.com
// github : https://github.com/goddoe
// The MIT License (MIT)
// Copyright (c) 2016 Sung-ju Kim

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

        for(int i = 0 ; i < m_input.size() ; ++i)
        {
            printf("in : %f %f\n", m_input[i][0], m_input[i][1]);
            printf("out: %f\n", m_target[i][0]);
        }
    }
};

void MLP(int argc, char* argv[])
{
    /****************************/

    Trainer trainer;
    trainer.parseData("./sample.txt");

    Net *net = new Net();

    //Net *net_2;
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


    printf("feedforward start!\n");

    printf("size =  %d\n", trainer.m_input.size());
    int count =0;
    for(int i = 0 ; i < trainer.m_input.size(); ++i)
    {
        net->feedforward(trainer.m_input[i]);
        net->backprob(trainer.m_target[i]);
        ++count;
        if(count%5000 == 0)
            printf("count: %d\n", count);
    }
    printf("learing done!\n");

    net->save("first_net_20150814_2.txt");

    /*try
    {
    net_2 = new Net();
    net_2->load("first_net.txt");
    net_2->save("second_net.txt");
    }
    catch(exception e)
    {
        printf("%s\n",e.what());
    }*/

    //net->load("first_net_20150812.txt");

    while(true)
    {
        float input[2];

        printf("input : ");
        scanf("%f %f", &input[0], &input[1]);

        if(input[0] == 100.0)
            break;

        net->feedforward(input);
        //system("clear");

        printf("result : %f\n\n", (float)(net->m_layersActivation.back()[0]));
    }
     delete net;
    //delete net_2;
}

int main(int argc, char* argv[])
{
   printf("\n\n");
   MLP(argc, argv);
}
