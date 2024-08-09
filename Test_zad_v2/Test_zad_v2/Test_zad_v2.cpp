// Test_zad_v2.cpp: определяет точку входа для приложения.
//

#include "Test_zad_v2.h"
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>

using namespace std;


const int NUM_PHILOSOPHERS = 5;

enum PhilosopherState { THINKING, HUNGRY, EATING };
atomic<bool> stop_flag(true);

mutex forks[NUM_PHILOSOPHERS]; //мьютекс для вилок
mutex coutMutex;//мьютекс для консоли

int getRandomTime(int min, int max) //рандомное время действий философа
{
    return min + rand() % (max - min);
}

void think()//философ думает
{
    this_thread::sleep_for(chrono::milliseconds(getRandomTime(1000, 3000)));
}

void eat()//философ ест
{
    this_thread::sleep_for(chrono::milliseconds(getRandomTime(1000, 3000)));
}

void philosopher(int i)
{
    int leftFork = i;//индекс левой вилки
    int rightFork = (i + 1) % NUM_PHILOSOPHERS;//индекс правой вилки

    while (stop_flag)
    {

        {
            lock_guard<mutex> coutLock(coutMutex);//получаем доступ к консоли
            cout << "Философ " << i << " думает." << endl;
        }
        think();

        {
            lock_guard<mutex> coutLock(coutMutex);//получаем доступ к консоли
            cout << "Философ " << i << " проголодался." << endl;
        }

        unique_lock<mutex> leftLock(forks[leftFork], defer_lock);//попытка получить доступ к левой вилке, так чтобы мьютекс не блокировался

        unique_lock<mutex> rightLock(forks[rightFork], defer_lock);//попытка получить доступ правой вилке, так чтобы мьютекс не блокировался

        lock(leftLock, rightLock);//попытка захватить оба мьютекса так, что их захват возможен только в случае,когда они оба свободны

        {
            lock_guard<mutex> coutLock(coutMutex);//получаем доступ к консоли
            cout << "Философ " << i << " ест." << endl;
        }

        eat();
    }
    {
        lock_guard<mutex> coutLock(coutMutex);//получаем доступ к консоли
        cout << "Философ " << i << " наелся и встал из-за стола." << endl;
    }
}

void main() {
    setlocale(LC_ALL, "Rus");
    thread philosophers[NUM_PHILOSOPHERS];// создаем массив потоков
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i] = thread(philosopher, i);// создаём потоки
    }
    this_thread::sleep_for(chrono::milliseconds(10000));
    stop_flag = false;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i].join(); // ждём завершения потоков
        cout << "Поток " << i << " завершился" << endl;
    }


}