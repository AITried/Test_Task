// Test_Zad.cpp: определяет точку входа для приложения.

#include "Test_Zad.h"
#include <iostream>
#include <atomic>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <boost/random.hpp>

using namespace std;

const int NUM_PHILOSOPHERS = 5;

enum PhilosopherState { THINKING, HUNGRY, EATING };
atomic<bool> stop_flag(true);

boost::mutex forks[NUM_PHILOSOPHERS];
boost::mutex coutMutex;

int getRandomTime(int min, int max) //рандомное время действий философа
{
    return min + rand() % (max - min);
}

void think()//философ думает
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(getRandomTime(1000, 3000)));
}

void eat()//философ ест
{
    boost::this_thread::sleep_for(boost::chrono::milliseconds(getRandomTime(1000, 3000)));
}

void philosopher(int i)
{
    int leftFork = i;//индекс левой вилки
    int rightFork = (i + 1) % NUM_PHILOSOPHERS;//индекс правой вилки

    while (stop_flag)
    {

        {
            boost::lock_guard<boost::mutex> coutLock(coutMutex);//получаем доступ к консоли
            cout << "Философ " << i << " думает." << endl;
        }
        think();

        {
            boost::lock_guard<boost::mutex> coutLock(coutMutex);//получаем доступ к консоли
            cout << "Философ " << i << " проголодался." << endl;
        }

        boost::unique_lock<boost::mutex> leftLock(forks[leftFork], boost::defer_lock);//попытка получить доступ к левой вилке, так чтобы мьютекс не блокировался

        boost::unique_lock<boost::mutex> rightLock(forks[rightFork], boost::defer_lock);//попытка получить доступ правой вилке, так чтобы мьютекс не блокировался

        lock(leftLock, rightLock);//попытка захватить оба мьютекса так, что их захват возможен только в случае,когда они оба свободны

        {
            boost::lock_guard<boost::mutex> coutLock(coutMutex);//получаем доступ к консоли
            cout << "Философ " << i << " ест." << endl;
        }

        eat();
    }
}

void main() {
    setlocale(LC_ALL, "Rus");
    boost::thread philosophers[NUM_PHILOSOPHERS];// создаем массив потоков
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i] = boost::thread(philosopher, i);// создаём потоки
    }
    boost::this_thread::sleep_for(boost::chrono::milliseconds(10000));
    stop_flag = false;
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i)
    {
        philosophers[i].join();// ждём завершения потоков
    }


}
