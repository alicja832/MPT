/*
	This exercise aims for practicing gained knowledge about threads, barriers and semaphores. 
	In order to finish this exercise fill fields marked as 'fill', to achieve identical output, as shown below,
	***IMPORTANT***
	--Marked spaces can be filled with ONLY one line of code.
	--Remember to compile examples with barriers and semaphores you need g++ compiler in version 11.1.x or higher
*/
#include <syncstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <semaphore>
#include <barrier>
#include <thread>

int size = 10000;
using Matrix = std::vector<std::vector<double>>;
std::counting_semaphore data_speed(0);
std::counting_semaphore data_init(0);
std::barrier proccesed{3};


void saveData(Matrix& data, std::string filename){
	std::osyncstream(std::cout) << "Printing " + filename << std::endl;
	std::ofstream file;
	file.open(filename);
	for(auto & row : data){
			file << row[0] << " ";
		file << "\n";
	}
	file.close();
}
void InitField(Matrix& field){
	for(int i = 0; i < size; i++)
			for(int j = 0; j < size; j++)
				field[i][j] = std::pow(1 - i / double(size), 2) + 100 * std::pow(j / double(size) - (i / double(size)) * (i / double(size)), 2); 
	std::osyncstream(std::cout) << "Data initialized.\n";
	
	data_init.release();
	proccesed.arrive_and_wait();
	
	saveData(field,"location.txt");

}
void CalculateSpeed(Matrix& field, Matrix& speed){
	std::osyncstream(std::cout) << "Waiting for data, blocking...\n";
	data_init.acquire();
	std::osyncstream(std::cout) << "Calculation of speed starts.\n";
	for(int i = 0; i < size - 1; i++)
			for(int j = 0; j < size; j++)
				speed[i][j] = (field[i][j] - field[i+1][j]) / (1. / size); 
	std::osyncstream(std::cout) << "Speed calculated.\n";
	
	
	data_speed.release();
	proccesed.arrive_and_wait();
	saveData(field,"speed.txt");
	
	
}
void CalculateAcceleration(Matrix& speed, Matrix& acceleration){
	std::osyncstream(std::cout) << "Waiting for data, blocking...\n";
	data_speed.acquire();
	std::osyncstream(std::cout) << "Calculation of acceleration starts.\n";
	for(int i = 0; i < size - 2; i++)
			for(int j = 0; j < size; j++)
				acceleration[i][j] = (speed[i][j] - speed[i+1][j]) / (1. / size); 
	std::osyncstream(std::cout) << "Acceleration calculated.\n";
	
	
	
	proccesed.arrive_and_wait();
	saveData(acceleration,"acceleration.txt");
	
}
int main(){
	Matrix plainField(size, std::vector<double>(size));
	Matrix speed(size, std::vector<double>(size));
	Matrix acceleration(size, std::vector<double>(size));
	std::jthread phase1{InitField, std::ref(plainField)};
	std::jthread phase2{CalculateSpeed, std::ref(plainField), std::ref(speed)};
	std::jthread phase3{CalculateAcceleration, std::ref(speed), std::ref(acceleration)};
	std::osyncstream(std::cout) << "finishing main... waiting for other threads\n";
}

/*OUTPUT
-------------------------------------------
finishing main... waiting for other threads
Waiting for data, blocking...
Waiting for data, blocking...
Data initialized.
Calculation of speed starts.
Speed calculated.
Calculation of acceleration starts.
Acceleration calculated.
Printing acceleration.txt
Printing location.txt
Printing speed.txt
-------------------------------------------
*/