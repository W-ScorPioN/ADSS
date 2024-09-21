// #pragma once
// // #include <gmpxx.h>
// // #include <iostream>
// // #include <time.h>
// // #include <fstream>
// #include <iostream>
// #include <vector>
// #include <string>
// #include <sstream>
// #include <fstream>

// // #include <benchmark/benchmark.h>

// using namespace std;

// //读取txt文本中的float数据（按行读取）
// void read_txt_input(std::string path,std::vector<double> &pydata){
//     std::ifstream infile;
//     infile.open(path);
//     double value;
//     if(!infile){
//         std::cout<<"file not found"<<endl;
//         exit(1);
//     }
//     //   while(infile>>value){
//     //     pydata.push_back(value);
//     //   }
//     //默认只有一行
//     std::string line,str;
//     std::getline(infile, line);
//     std::stringstream ss(line);
//     while(getline(ss,str,','))
//     {
//         std::stringstream sv(str);
//         sv>>value;
//         pydata.push_back(value);
//     }
//     infile.close();
// }



// int main(int argc, char const *argv[])
// {
//     //std::unique_prt<venus::Tensor> pqmf_x =pqmf_net->get_input_by_name(n1);获取tensor
//     std::vector<double> py_data;
//     std::string path_py_data = "./第0轮/第"+std::to_string(0)+"个特征/0.txt";
//     read_txt_input(path_py_data,py_data);
//     //copy(py_data.data(),py_tensor,shape_size);

//     for (size_t i = 0; i < py_data.size(); i++)
//     {
//         cout<<fixed<<py_data[i]<<setprecision(9)<<" ";
//     }
    

//     // std::map<int, std::pair<std::string,std::string>> txtMap;                                                                                                                                                   
//     // readline_model_txt(std::string(net_param_path),txtMap);
//     return 0;
// }
