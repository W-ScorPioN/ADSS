#!/bin/bash
# 自动化编译 c/c++

dir=`pwd` ; echo "欢迎使用自动化汇编程序，当前路径为： $dir"


touchCMake(){

sudo touch CMakeLists.txt ; sudo chmod 777 CMakeLists.txt ;

echo "
project(FSDS)
#项目名
cmake_minimum_required(VERSION 3.10)
# 编译要求：cmake 要大于最低版本 3.1 
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
# 设置编译器， 如果没有配置环境变量，可以改为gcc具体文件路径

include_directories(a)
include_directories(a)
include_directories(a)
# 添加 头文件搜索路径 (mysql.h 搜索路径)

#add_executable("xx" xx.c )
# add_executable("test" main.c )
#add_executable("xx" xx.cpp )
add_executable("test" main.cpp )
# 生成可执行文件： 将 test.cpp 编译成 test.exe 可执行文件

# rm -rf ./build ; cmake ./ -Bbuild -G "Unix Makefiles" ; cmake --build build
# rm -rf ./build ; cmake ./ -Bbuild ; cmake --build build
# 编译到当前目录下的 build 文件夹
# 也可以不用指定 -G
" > CMakeLists.txt 

# 如果 echo 字符串中有 变量，需要加反斜线转义

}


autoINCPath(){
    incList[0]="include_directories($dir/include/inc/)"
    incList[1]="include_directories($dir/include/src/)"
    incList[2]="include_directories($dir/include/)"
    # 路径为绝对路径，相对路径会报错.  此数组个数与 CMakeLists.txt 中的  include_directories 个数对应

    file="CMakeLists.txt"
    incNumber=`cat -n $file | grep -w include_directories | wc -l`     # wc -l 计算个数

    if [ "${#incList[*]}" != "$incNumber" ]
    then 
        echo "$file 文件 include_directories 定义个数 ${#incList[*]} 与 $incNumber 目标修改个数不相等，无法对应修改。"
        echo "请在 touchCMake 和 autoINCPath 函数， 增加或者 删除 include_directories 关键字个数，以达到与目标修改个数一致。然后重新执行脚本"
        exit
    else

        incI=0;
        while :
        do
            incNumberList=(`cat -n $file | grep -w include_directories  | grep -v okset| awk -F" " '{print $1}' `) 
            Number=${#incNumberList[*]}
            NR=${incNumberList[0]}

            if [ "$Number" -lt "1" ]
            then 
                echo "[ok] 当前绝对路径已经全部修正, 正在执行 CMakeLists.txt 自动化编译。 "
                break
            fi

            echo "[runing] 当前游标：$incI 当前修改行：$NR  当前剩余总修改次数: $Number 文件：$file 所有行：${incNumberList[*]} 目标内容：${incList[$incI]} "

            sed -i "$NR a ${incList[$incI]}   # [eisc.cn_okset]" $file
            sed -i "$NR d " $file
            # 始终修改第一个元素，然后由于循环再去查找行号
            # 错误方式，删除一行后，其他内容行号会变，因此每次删除，需要重新扫描行号
            #  [okset]  修改了的地方做标记

            let "incI++"
            # 先获取 0 后，再自动增加。而不是 先增加： 0+1 第一次为 1 
            sleep 0.3
        done

        sleep 2
    fi

}

touchCMake ; autoINCPath
rm -rf ./build ; cmake ./ -Bbuild ; cmake --build build 

./build/test

#运行该脚本：sudo sh test.sh