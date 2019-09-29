#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int ARRAY = 10;

void test(double[], string[]);

int main (){

  string foodName[ARRAY];
  double foodPrice[ARRAY];
  fstream inputStream;

  inputStream.open("proj1_items.txt");

  for(int i = 0; i < 10; i++){
      getline(inputStream, foodName[i] , ',');
      inputStream >> foodPrice[i];
      if(inputStream.peek() == '\n')
	inputStream.ignore();
  }

  test(foodPrice, foodName);

  inputStream.close();

  return 0;
}

void test(double foodPrice[ARRAY], string foodName[ARRAY]){

  for(int i = 0; i < 10; i++){
    cout << setw(20) << foodName[i];
    cout <<setw(20) << foodPrice[i] << endl;
  }
}
