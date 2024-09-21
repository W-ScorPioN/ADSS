#pragma once

#include <gmpxx.h>
#include <iostream>
#include <time.h>

// #include <benchmark/benchmark.h>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::chrono::nanoseconds;

//读取txt文本中的float数据（按行读取）
void read_txt_input(std::string path,std::vector<double> &pydata){
    std::ifstream infile;
    infile.open(path);
    double value;
    if(!infile){
        std::cout<<"file not found!->"<<path<<endl;
        exit(1);
    }
    //默认只有一行
    std::string line,str;
    std::getline(infile, line);
    std::stringstream ss(line);
    while(getline(ss,str,','))
    {
        std::stringstream sv(str);
        sv>>value;
        pydata.push_back(value);
    }
    infile.close();
}


std::vector<double> fl(std::vector<std::vector<double> > data, int length){
    // float *result = new float[vec[0].length];
    std::vector<double> result;
    for(int j=0;j<data[0].size();j++){
       result.push_back(0);
    }
    for(int i =0; i<length;i++)
    {
        for(int j=0;j<data[i].size();j++){
            result[j] += data[i][j];
        }
    }

    for(int j=0;j<data[0].size();j++){
        result[j] /= length;
    }
    return result;
}

void benchFL()
{
    std::vector<std::vector<double> > result;
    int fearures = 8;//8个特征
    int lenght =10;
    for(int index = 0; index < fearures; index++){
        std::vector<std::vector<double> > fl_data;
        // cout<<"f="<<f<<endl;
        for(int i = 0; i<lenght; i++)
        {
            std::vector<double> data;
            std::string path_fl_data = "./第0轮/第"+std::to_string(index)+"个特征/"+std::to_string(i)+".txt";
            // cout<<path_fl_data<<endl;
            read_txt_input(path_fl_data,data);
            fl_data.push_back(data);
        }
        result.push_back(fl(fl_data,lenght));
    }
}

int main(int argc, char const *argv[])
{
    int Iterations = 10;
     auto t1 = high_resolution_clock::now();
    for(int iter; iter<Iterations; iter++)
    {
        benchFL();   
    }
    auto t2 = high_resolution_clock::now();
    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ns_double = (t2 - t1);
    ns_double /= Iterations;

    std::cout << ns_double.count() << "ms\n";
}

