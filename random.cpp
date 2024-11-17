// random.cpp - 乱数ルーチン
#include "random.h"
#include <random>

// 乱数の種
int vsk_seed = 0;
// 乱数生成器
std::mt19937 vsk_random_generator;
// 一つ前の乱数
float vsk_prev_rand = 0.0f;

// 基本的には次の乱数を取得する。必要ならば乱数生成を初期化したり、前の値を取得することもある
float vsk_rand_get_next(int func)
{
    if (func < 0) // funcがゼロ未満なら初期化
    {
        vsk_rand_init(vsk_seed);
        func = 1; // あとは正の場合と同じ
    }

    if (func > 0) // funcが正の場合、次の乱数を生成する
    {
        std::uniform_real_distribution<float> distribution(0, 1);
        do
        {
            vsk_prev_rand = distribution(vsk_random_generator);
        } while (vsk_prev_rand == 1.0); // ちょうど1.0の場合はやり直し
    }

    return vsk_prev_rand;
}

// 乱数生成を初期化
void vsk_rand_init(int seed)
{
    vsk_seed = seed;
    vsk_random_generator = std::mt19937(seed);
    vsk_prev_rand = vsk_rand_get_next(1);
}
