#pragma once

#include <gmpxx.h>
#include <iostream>
#include <time.h>

#include <benchmark/benchmark.h>

using namespace std;

typedef std::vector<mpz_class> Vector;
typedef std::vector< std::vector<mpz_class> > Matrix;


//随机数生成
mpz_class randbits(int bits)//base=2
{
    gmp_randclass a(gmp_randinit_default);
    std::srand(time(nullptr));
    // a.seed(std::time(nullptr));
    a.seed(rand());//该方法不行
    mpz_class l(bits);
    return a.get_z_bits(l);
}
mpz_class RandomNum(int bits) {// bits 整数二进制位数
    gmp_randclass randz(gmp_randinit_default);
    randz.seed(rand());
    mpz_class gz_bits = bits;
    return randz.get_z_bits(gz_bits);
}
//随机素数的生成
inline mpz_class randprime(int bits)
{
    mpz_class a=randbits(bits);
    mpz_class ret;
    mpz_nextprime(ret.get_mpz_t(),a.get_mpz_t());
    return ret;
}

Vector gen_vector(int size, int bits){
    Vector vec(size);
    for (auto &&v : vec)
    {
        // v = randbits(bits);

        v = RandomNum(bits);
    }
    return vec;
}

Matrix gen_marix(int rows, int cols, int bits){
    Matrix mat(rows);
    for (auto &&v : mat)
    {
        v = gen_vector(cols, bits);
    }
    return mat;
}

/**
 * mat^(n \times l) = mat1^(n \times m) * mat2^(m times l)
 * 注意：本函数值检查矩阵mat1中第一行的列向量与mat2行向量个数。
*/
Matrix matrixMul(Matrix mat1, Matrix mat2){
    if (mat1.empty() || mat2.empty() || mat1[0].empty() || mat2[0].empty())
    {
        std::cerr<< "矩阵不能为空" << std::endl;
    }
    else if (mat1[0].size() != mat2.size()) //mat1
    {
        std::cerr<< "列向量与行向量大小不匹配" << std::endl;
    }
    //初始化结果矩阵
    Matrix res(mat1.size());
    for (auto &&v : res)
    {
        v.resize(mat2[0].size());
        for (auto &&i : v)
        {
            i = 0;
        }
    }

    // 矩阵乘法
    for (size_t i = 0; i < mat1.size(); i++)
    {
        for (size_t j = 0; j < mat2[0].size(); j++)
        {
            for (size_t k = 0; k < mat2.size(); k++)
            {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return res;
}

mpz_class dotProduct(Vector vec1, Vector vec2){
    if (vec1.empty() || vec2.empty())
    {
        std::cerr<< "向量不能为空" << std::endl;
    }
    else if (vec1.size() != vec2.size()) //mat1
    {
        std::cerr<< "向量大小不匹配" << std::endl;
    }
    mpz_class res = 0;
    //点积计算
    for (size_t i = 0; i < vec1.size(); i++)
    {
        res += vec1[i] * vec2[i];
    }
    return res;
}

void printVec(Vector v){
    std::cout << "[";
    for (size_t i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << ", ";
    }
    std::cout << "]" << std::endl;
}

void printMatrix(Matrix m){
    for (size_t i = 0; i < m.size(); i++)
    {
        printVec(m[i]);
    }
}

// int main(int argc, char const *argv[])
// {
//     mpz_class a,b,c;
//     a = randbits(4);
//     b = randbits(4);
//     c = a*b;
//     std::cout <<"a*b = " << c << std::endl;
//     return 0;
// }

/***************** vector benchmark ***********************/
static void bench_dotProduct_8(benchmark::State& state){
    Vector v1,v2;
    mpz_class res;
    v1 = gen_vector(8,8);
    v2 = gen_vector(8,8);
    for (auto _: state){
        res = dotProduct(v1,v2);
    }
}

BENCHMARK(bench_dotProduct_8);

static void bench_dotProduct_16(benchmark::State& state){
    Vector v1,v2;
    mpz_class res;
    v1 = gen_vector(16,8);
    v2 = gen_vector(16,8);
    for (auto _: state){
        res = dotProduct(v1,v2);
    }
}

BENCHMARK(bench_dotProduct_16);
static void bench_dotProduct_32(benchmark::State& state){
    Vector v1,v2;
    mpz_class res;
    v1 = gen_vector(32,8);
    v2 = gen_vector(32,8);
    for (auto _: state){
        res = dotProduct(v1,v2);
    }
}

// BENCHMARK(bench_dotProduct_32);

static void bench_dotProduct_64(benchmark::State& state){
    Vector v1,v2;
    mpz_class res;
    v1 = gen_vector(64,8);
    v2 = gen_vector(64,8);
    for (auto _: state){
        res = dotProduct(v1,v2);
    }
}

// BENCHMARK(bench_dotProduct_64);

/***************** matrix benchmark ***********************/

static void bench_matrixMul_8_8(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(8,8,8);
    m2 = gen_marix(8,8,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_8_8);

static void bench_matrixMul_16_16(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(16,16,8);
    m2 = gen_marix(16,16,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_16_16);

static void bench_matrixMul_32_32(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(32,32,8);
    m2 = gen_marix(32,32,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_32_32);

static void bench_matrixMul_64_64(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(64,64,8);
    m2 = gen_marix(64,64,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_64_64);

static void bench_matrixMul_128_128(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(128,128,8);
    m2 = gen_marix(128,128,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_128_128);

static void bench_matrixMul_256_256(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(256,256,8);
    m2 = gen_marix(256,256,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_256_256);
 

static void bench_matrixMul_512_512(benchmark::State& state){
    Matrix m1,m2,res;
    m1 = gen_marix(512,512,8);
    m2 = gen_marix(512,512,8);
    for (auto _: state){
        res = matrixMul(m1,m2);
    }
}

BENCHMARK(bench_matrixMul_512_512);

BENCHMARK_MAIN();