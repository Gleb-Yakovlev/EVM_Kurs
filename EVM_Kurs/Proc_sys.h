#pragma once 

#include <iostream>
#include <time.h>

using namespace std;
//����� �������
enum
{
	DENIED, //��������
	ALLOWED,//���������
	ACCESSED//��������
};
//����� ������
enum
{
	REQUEST,//������
	FREE//�����������
};

class Proc_sys
{
public:

	int ACCESS = DENIED;
	int** data; 
	int** lead_time; 
	int* memory_access; 
	int M, K, N;
	float Pn, Kr;

	void set_data_to_memory(); 

	void commutator();
	void shina(); 

	int memory(int, int); 
	int memory(int);
	int worktime(int);
};
