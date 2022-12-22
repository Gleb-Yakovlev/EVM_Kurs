#include "Proc_sys.h"

void Proc_sys::commutator()
{
	setlocale(LC_ALL, "Russian");
	int access;
	int delay = 1;
	cout << "Commutator" << endl;
	for (int i = 0; i < K; i++)
	{
		for (int id = 0; id < N; id++)
		{
			if (data[id][i])
			{
				cout << "Запрос на передачу данных" << "\t" << data[id][i] << "\tПроцессор " << id + 1 << endl;
				while (1)
				{
					access = memory(REQUEST, data[id][i]);

					if (access == ACCESSED)
					{
						cout << "Доступ к памяти" << "\t\t\t" << data[id][i] << "\tПроцессор " << id + 1 << endl;
						lead_time[1][id] += M;
						break;
					}
					else
					{
						cout << "Ожидание памяти" << "\t\t\t" << data[id][i] << "\tПроцессор " << id + 1 << endl;
						lead_time[1][id] += 1 * delay;
						delay++;
						memory(FREE, data[id][i]);
					}
				}
			}
			else
			{
				lead_time[1][id] += 1;
				cout << "Без запроса памяти" << "\t\t-" << "\tПроцессор " << id + 1 << endl;
			}
		}

		for (int i = 0; i < N; i++) memory_access[i] = ALLOWED;
		delay = 1;
	}
}