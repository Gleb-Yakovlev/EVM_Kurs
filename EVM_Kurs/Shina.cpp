#include "Proc_sys.h"

void Proc_sys::shina()
{
	setlocale(LC_ALL, "Russian");
	int access;
	int delay = 1;
	cout << "Shina" << endl;
	for (int i = 0; i < K; i++)
	{
		for (int id = 0; id < N; id++)
		{
			if (data[id][i])
			{
				cout << "������ �� �������� ������" << "\t" << data[id][i] << "\t��������� " << id + 1 << endl;
				while (true)
				{
					access = memory(REQUEST);

					if (access == ACCESSED)
					{
						cout << "������ � ������" << "\t\t\t" << data[id][i] << "\t��������� " << id + 1 << endl;
						lead_time[0][id] += M;
						break;
					}
					else
					{
						cout << "�������� ������" << "\t\t\t" << data[id][i] << "\t��������� " << id + 1 << endl;
						lead_time[0][id] += 1 * delay;
						delay++;
						memory(FREE);
					}
				}
			}
			else
			{
				lead_time[0][id] += 1;
				cout << "��� ������� ������" << "\t\t-" << "\t��������� " << id + 1 << endl;
			}
		}
		delay = 1;
	}
}