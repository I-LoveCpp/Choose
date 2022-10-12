#include "Head.h"

using namespace std;

const int NR = 1e5;
string name[NR];
int cnt = 1, delay = 200, speed = 0;
bool can_choose = true, wait = false;

struct mm
{
	int percent, times = 0;
};

map<string, int> mp;
map<string, mm> must;
mutex mtx;

int rm()
{
	srand(time(NULL));
	return (rand() % 10000) + (rand() % 10000) * (rand() % 10000);
}

void init()
{
	// ´°¿Ú 
	SetConsoleTitle(TEXT("Choose"));
	system("mode con cols=40 lines=19");
	HindCursor();
	
	// ¶ÁÈ¡
	ifstream in1("D:\\Data\\Choose\\Run.Ceh", ios::binary);
	if (!in1)
	{
		CreateDirectory(_T("D:\\Data\\"), NULL);
		SetFileAttributes("D:\\Data\\", FILE_ATTRIBUTE_HIDDEN);
		CreateDirectory(_T("D:\\Data\\Choose\\"), NULL);
		ofstream out1("D:\\Data\\Choose\\Run.Ceh", ios::binary);
		out1 << "0";
	}
	ifstream in2("list.bin", ios::binary);
	while (in2 >> name[cnt])
	{
		cnt++;
	}
	cnt--;

	string a, b;
	ifstream in3("D:\\Data\\Choose\\Config.Ceh", ios::binary);
	if (!in3) ofstream out2("D:\\Data\\Choose\\Config.Ceh", ios::binary);
	while (in3 >> a)
	{
		if (a == "delay")
		{
			in3 >> delay;
		}
		else if (a == "all")
		{
			in3 >> speed;
		}
		else if (a == "must")
		{
			int c, d;
			in3 >> b >> c >> d;
			must[b].percent = c;
			must[b].times = d;
		}
		else
		{
			in3 >> b;
			for (int i = 0; i <= b.length() - 1; i++)
			{
				if (b[i] == '+') mp[a] += 10;
				if (b[i] == '-') mp[a] -= 10;
			}
		}
		
	}
}

void show()
{
	int pos = 1;
	float cd = 1000 / 60.0f;// Ã¿Ãë60Ö¡ 
	clock_t beginClock = clock();
	float totalCd = 0.0f;
	while (1)
	{
		if (clock() >= beginClock + (int)totalCd)
		{
			totalCd += cd;
			//
			if (can_choose == true)
			{
				pos++;
				if (pos > cnt) pos = 1;
				if (mp[name[pos]] < 0) pos++;
				if (pos > cnt) pos = 1;
				mtx.lock();
				gto(7, 18), color(7), cout << "             ";
				gto(7, 18), color(7), cout << name[pos];
				mtx.unlock();
				if (mp[name[pos]] >= 0) this_thread::sleep_for(std::chrono::milliseconds(mp[name[pos]]));
				this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
			if (can_choose == false)
			{
				mtx.lock();
				for (int i = 1; i <= cnt; i++)
				{
					if (wait == false &&  must[name[i]].times != 0 && must[name[i]].percent >= (rm() % 100)) must[name[i]].times--, pos = i;
				}
				wait = true;
				gto(7, 18), color(7), cout << "             ";
				gto(7, 18), color(7), cout << name[pos];
				mtx.unlock();
			}
			if(totalCd - clock() > 0) Sleep(totalCd - clock());
		}
	}
}

void key()
{
	while (1)
	{
		char x = getch();
		if (x == ' ')
		{
			if (wait == false) can_choose = false;
			else can_choose = true, wait = false;
			this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
void mouse()
{
	Button button1 = NewButton(10, 18, 7, "Í£Ö¹");
	Button button2 = NewButton(10, 18, 7, "¼ÌÐø");
	while (1)
	{
		
		if (wait == false)
		{
			mtx.lock();
			if (Preserve(button1))
			{
				can_choose = false;
				gto(10, 18), color(7), cout << "¼ÌÐø";
				this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
			mtx.unlock();
		}
		else
		{
			mtx.lock();
			if (Preserve(button2))
			{
				can_choose = true, wait = false;
				gto(10, 18), color(7), cout << "Í£Ö¹";
				this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
			mtx.unlock();
		}
		this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

int main()
{
	init();
	thread task01(show);
	thread task02(key);
	thread task03(mouse);
	task01.join();
	task02.join();
	task03.join();
	
	return 0;
}
