#include "Proc_sys.h"

void Proc_sys::set_data_to_memory()
{
	memory_access = new int[N];
	lead_time = new int* [2];
	data = new int* [N];

	lead_time[0] = new int[N];
	lead_time[1] = new int[N];
	for (int i = 0; i < N; i++)
	{
		memory_access[i] = ALLOWED;
		lead_time[0][i] = 0;
		lead_time[1][i] = 0;
		data[i] = new int[K];
	}

	for (int id = 0; id < N; id++)
	{
		srand(time(NULL) - 100 * id);
		int delta_K = K - K * Kr; //кол-во команд, требующих обращение в память
		int delta_K_to_block = delta_K * Pn; //кол-во команд, которые будут обращены в один кокнретный блок памяти
		int memory = 0;

		for (int i = 0; i < K; i++)
		{
			if (delta_K && rand() % ((K - i) / delta_K) == 0) //если дельта_к и рандом от 0 до (отношение декремента кол-ва команд на число команд, требующих обращение в память) = 0
			{
				if (delta_K - delta_K_to_block != 0 && rand() % (delta_K / (delta_K - delta_K_to_block)) == 0) 																			   //и рандом от 0 до отношения дельты_к на разность дельта_к и
					while (1)																			  
					{																						  
						memory = rand() % N + 1; 

						if (memory != id + 1) break;
					}
				else
				{
					memory = id + 1;
					delta_K_to_block--;
				}

				data[id][i] = memory;
				delta_K--;
			}
			else
			{
				data[id][i] = 0; //команда, не требующая обращения к блоку памяти
			}
		}
	}
}

int Proc_sys::memory(int req, int num) //функция доступа к памяти для коммутатора
{
	ACCESS = memory_access[num - 1]; 
	if (ACCESS == ALLOWED && req == REQUEST)
	{
		ACCESS = DENIED;
		memory_access[num - 1] = DENIED;
		return ACCESSED;
	}
	else if (ACCESS == DENIED && req == REQUEST) return DENIED;

	else if (ACCESS == DENIED && req == FREE) ACCESS = ALLOWED;


	memory_access[num - 1] = ALLOWED;
	return ACCESS;
}

int Proc_sys::memory(int req) //функция доступа к памяти для шины
{
	if (ACCESS == ALLOWED && req == REQUEST)
	{
		ACCESS = DENIED;
		return ACCESSED;
	}
	else if (ACCESS == DENIED && req == FREE) ACCESS = ALLOWED;

	return ACCESS;
}

int Proc_sys::worktime(int n)
{						 
	
	int max = 0;
	for (int i = 0; i < N; ++i)
		if (lead_time[n][i] > max)	max = lead_time[n][i];

	for (int i = 0; i < N; i++) lead_time[n][i] = 0;
	return max;
}