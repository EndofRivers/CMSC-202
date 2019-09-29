#ifndef TQUEUE_H
#define TQUEUE_H

#include <iostream>
#include <cstdlib>
#include <stdexcept>
using namespace std;

template <class T, int N>
class Tqueue {
public:
  //Name: Tqueue - Default Constructor
  //Precondition: None (Must be templated)
  //Postcondition: Creates a queue using dynamic array
  Tqueue();
  //Name: Copy Constructor
  //Precondition: Existing Tqueue
  //Postcondition: Copies an existing Tqueue
  Tqueue( const Tqueue<T,N>& x );
  //Name: Destructor
  //Precondition: Existing Tqueue
  //Postcondition: Destructs existing Tqueue
  ~Tqueue();
  //Name: enqueue
  //Precondition: Existing Tqueue
  //Postcondition: Adds item to back of queue
  void enqueue(T data);
  //Name: dequeue
  //Precondition: Existing Tqueue
  //Postcondition: Removes item from queue (from front)
  void dequeue(T&); 
  //Name: queueFront
  //Precondition: Existing Tqueue
  //Postcondition: Retrieve front (does not remove it)
  void queueFront(T&);
  //Name: isEmpty
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is empty else 0
  int isEmpty();
  //Name: isFull
  //Precondition: Existing Tqueue
  //Postcondition: Returns 1 if queue is full else 0
  int isFull();
  //Name: size
  //Precondition: Existing Tqueue
  //Postcondition: Returns size of queue
  int size();
  //Name: Overloaded assignment operator
  //Precondition: Existing Tqueue
  //Postcondition: Sets one Tqueue to same as a second Tqueue using =
  Tqueue<T,N>& operator=( Tqueue<T,N> y);
  //Name: Overloaded [] operator
  //Precondition: Existing Tqueue
  //Postcondition: Returns object from Tqueue using []
  T& operator[] (int x);
private:
  T* m_data; //Data of the queue (Must be dynamically allocated array)
  int m_front; //Front of the queue
  int m_back; //Back of the queue
};

// Default Constructor
template <class T, int N>
Tqueue<T, N>::Tqueue() {
  m_data = new T[N];
  m_front = 0;
  m_back = -1;
}
// Copy Constructor
template <class T, int N>
Tqueue<T, N>::Tqueue( const Tqueue<T,N>& x ) {
  m_data = new T[N];
  for(int i = 0; i < x.m_count; i++){
    m_data[i] = x.m_data[i];
  }
  m_front = x.m_front;
  m_back = x.m_back;
}
// Destructor
template <class T, int N>
Tqueue<T, N>::~Tqueue() {
  delete [] m_data;
  m_data = NULL;
}
// Adds item to queue (to back)
template <class T, int N>
void Tqueue<T, N>::enqueue(T data) {
  m_back = (m_back + 1) % N;
  m_data[m_back] = data;
}
// Removes item from queue (from front)
template <class T, int N>
void Tqueue<T, N>::dequeue(T& data) {
  if(isEmpty() == 1)
    throw out_of_range("Queue<>::dequeue(): empty queue");
  m_front = (m_front + 1) % N;
}
// Retrieve front (does not remove it)
template <class T, int N>
void Tqueue<T, N>::queueFront(T& data) {
  if(isEmpty() == 1)
    throw out_of_range("Queue<>::queueFront(): empty queue");
  cout << m_data[m_front];
}
// Returns 1 if queue is empty, else 0
template <class T, int N>
int Tqueue<T, N>::isEmpty() {
  if(size() == 0)
    return 1;
  else
    return 0;
}
// Returns 1 if queue is full, else 0
template <class T, int N>
int Tqueue<T, N>::isFull() {
  if(size() == N)
    return 1;
  else
    return 0;
}
// Returns size of queue
template <class T, int N>
int Tqueue<T, N>::size() {
  return (m_back - m_front);
}
// Overloaded assignment operator for queue
template <class T, int N>
Tqueue<T,N>& Tqueue<T, N>::operator=( Tqueue<T,N> y) {
  for(int i = 0; i < y.m_count; i++){
    m_data[i] = y.m_data[i];
  }
  m_front = y.m_front;
  m_back = y.m_back;
  return *this;
}
// Overloaded [] operator to pull data from queue
template <class T, int N>
T& Tqueue<T, N>::operator[] (int x) {
  return m_data[x];
}
/*
int main() {
  Tqueue<int, 10> q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);

  Tqueue<int, 10> copy(q);
  copy.dequeue();
  q.enqueue(4);
  copy.dequeue();
  q.enqueue(5);

  for(int i = 0; i < q.size(); i++){
    cout << "Original: " <<  q[i] << " ";
  }
  cout << endl;
  for(int i = 0; i < copy.size(); i++){
    cout << "Copy: " << copy[i] << " ";
  }
  cout << endl;
  return 0;
}
*/
#endif
