#include <iostream>
#include <windows.h>
#include "Functions.h"
using namespace std;

	const char* filename = "MusicLibrary.bin";
	
MusicLib::MusicLib()
{
	FileMusicLib = fopen (filename, "ab");
}

int MusicLib::el_size(FILE* f)
{
	fseek(f, 0, 2);
	int element = ftell(f)/sizeof(music_record);
	fseek(f, 0, 0);
	return element;
}

void MusicLib::table()
{
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout<<"Назва:\t\t|\tВиконавець:\t\t|\tАльбом:\t\t|\tЖанр:\t\t|\tТривалiсть:\n";
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

void MusicLib::show1(music_record M)
{
	cout<<M.record_name<<"\t|\t"<<M.artist<<"\t\t|\t"<<M.album_name<<"("<<M.release_year<<")"<<"\t\t|\t"<<M.genre<<"\t\t|\t"<<M.record_duration.minute<<":"<<M.record_duration.second<<endl;
}

int MusicLib::main_menu()
{
	int choice, new_quantity;
	while(1)
	{
		system("cls");
		cout<<"Ласкаво просимо до музичної фонотеки.\n";
		cout<<"1. Додати новий запис у музичну фонотеку.\n";
		cout<<"2. Переглянути усi музичнi твори, що записанi у фонотеку.\n";
		cout<<"3. Видалити усi записи з фонотеки.\n";
		cout<<"4. Вiдкрити меню пошуку.\n";
		cout<<"5. Вiдкрити меню сортування.\n";
		cout<<"0. Вийти з програми\n";
		cout<<"Введiть пункт меню, який Ви хочете виконати:\t";
		cin>>choice;
		system("cls");
		FileMusicLib = fopen(filename, "ab+");
		
		switch(choice)
		{
			case 1:
				cout<<"Скiльки нових записiв Ви хочете внести у музичну фонотеку?  ";
				cin>>new_quantity;			
				add_new_record(new_quantity);
			break;
			case 2:
				show_all();	
			break;				
			case 3:
			{
				fclose(FileMusicLib);
				if ((FileMusicLib = fopen(filename,"wb+")) == NULL)
 				{
					cout << "Неможливо вiдкрити файл..." << endl;
 					return -1;
				}
				cout<<"Усi записи було видалено!\n";
				fclose(FileMusicLib);
				system("pause");
			}
			break;	
			case 4:
				search_menu();
			break;
			case 5:
				sorting_menu();
			break;
			case 0:
				cout<<"Програму буде закрито.\n";
				fclose(FileMusicLib);
				system ("pause");
			return 0;
		}
	}
	system ("pause");
	fclose(FileMusicLib);
	return 0;
}

int MusicLib::add_new_record(int q)
{
	if((FileMusicLib=fopen(filename, "ab+")) == NULL)
	{
	    cout << "Виникла помилка..." << endl;
    	return 1;
	}
	fseek(FileMusicLib, 0, SEEK_END);
	for( int i = 0; i < q; i++)
	{
		cin.ignore();
		cout<<"Назва музичної композицiї:\t";
		gets(M.record_name);
		cout<<"Виконавець:\t\t\t";
		gets(M.artist);
		cout<<"Назва альбому:\t\t\t";
		gets(M.album_name);
		cout<<"Рiк випуску:\t\t\t";
		cin>>M.release_year;
		cin.ignore();
		cout<<"Музичний жанр:\t\t\t";
		gets(M.genre);
		duration:
		cout<<"Тривалiсть музичної композицiї:\n(хвилина секунда)\t\t";
		cin>>M.record_duration.minute>>M.record_duration.second;
		if (M.record_duration.minute < 0 || M.record_duration.second < 0 || M.record_duration.second > 60)
		{
			cout<<"Виникла помилка при введеннi тривалостi музичної композицiї, спробуйте, будь ласка, ще раз.\n";
			goto duration;
		}
		fwrite(&M, sizeof(M), 1, FileMusicLib);
		system("cls");
	}
	fclose(FileMusicLib);
	return 0;
}

int MusicLib::show_all()
{
	int r, n = 0;
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	fseek (FileMusicLib, 0, 0);
	table();
	while (!feof(FileMusicLib))
	{
		n++;
		r = fread(&M, sizeof(M), 1, FileMusicLib);
        if (r < 1) break;
        cout<<n<<".";
        show1(M);
	}
	fclose (FileMusicLib);
	system("pause");
	return 0;
}

void MusicLib::search_menu()
{
	while(1)
	{
		system("cls");
		int s_choice;
		cout<<"Ви у меню пошуку. Виберiть критерiй пошуку зi списку:\n";
		cout<<"1. За назвою композицiї.\n";
		cout<<"2. За виконавцем.\n";
		cout<<"3. За жанром.\n";
		cout<<"4. За роком випуску альбома.\n";
		cout<<"0. Повернутись у головне меню.\n";
		cout<<"Введiть пункт меню, який Ви хочете виконати:\t";
		cin>>s_choice;
		system("cls");
	
		switch(s_choice)
		{
			case 1:
				search_name();
			break;
			case 2:
				search_artist();
			break;
			case 3:
				search_genre();
			break;
			case 4:
				search_year();
			break;
			case 0:
				return;
			break;
			default:
				cout<<"Вибачте, було введено неiснуючий пункт меню. Спробуйте ще раз:\n";
			break;
		}
	}
	return;
}

void MusicLib::sorting_menu()
{
	while(1)
	{
		system("cls");
		int s_choice;
		cout<<"Ви у меню сортування. Виберiть критерiй сортування зi списку:\n";
		cout<<"1. За назвою композицiї.\n";
		cout<<"2. За виконавцем.\n";
		cout<<"3. За жанром.\n";
		cout<<"4. За роком випуску альбома.\n";
		cout<<"5. За тривалiстю композицiї у порядку спадання.\n";
		cout<<"6. За тривалiстю композицiї у порядку зростання.\n";
		cout<<"0. Повернутись у головне меню.\n";
		cout<<"Введiть пункт меню, який Ви хочете виконати:\t";
		cin>>s_choice;
		system("cls");
	
		switch(s_choice)
		{
			case 1:
				sort_name();
			break;
			case 2:
				sort_artist();
			break;
			case 3:
				sort_genre();
			break;
			case 4:
				sort_year();
			break;
			case 5:
				sort_duration_long();
			break;
			case 6:
				sort_duration_short();
			break;
			case 0:
				return;
			break;
			default:
				cout<<"Вибачте, було введено неiснуючий пункт меню. Спробуйте ще раз:\n";
			break;
		}
	}
	return;
}

int MusicLib::search_year()
{
	int s_year = 2020, n = 0, q = 0, r;
	cout<<"Введiть рiк випуску альбома:\t";
	cin>>s_year;
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	fseek(FileMusicLib, 0, 0);
	table();
	while (!feof(FileMusicLib))
	{
		r = fread(&M, sizeof(M), 1, FileMusicLib);
        if (r < 1) break;
        if (M.release_year == s_year) 
        {
        	++n;
        	cout<<n<<". ";
			show1(M);
		}
		++q;
	}
	fclose(FileMusicLib);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (n == 0) cout<<"Жодного альбому, що випустився "<<s_year<<" року, не знайдено.\n";
	else
	{
		cout<<endl<<"Знайдено "<<n<<" записiв у музичнiй фонотецi за заданим критерiєм.\n";
	}
	cout<<"Всього знайдено "<<q<<" записiв у музичнiй фонотецi.\n";
	system("pause");
	return 0;
}

int MusicLib::search_artist()
{
	char s_artist[20];
	int n = 0, q = 0, r;
	cin.ignore();
	cout<<"Введiть виконавця, за яким бажаєте провести пошук:\t";
	gets(s_artist);
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	fseek(FileMusicLib, 0, 0);
	table();
	while (!feof(FileMusicLib))
	{
		r = fread(&M, sizeof(M), 1, FileMusicLib);
        if (r < 1) break;
        if (strcmp(M.artist, s_artist) == 0) 
        {
        	++n;
        	cout<<n<<". ";
			show1(M);
		}
		++q;
	}
	fclose(FileMusicLib);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (n == 0) cout<<"Жодної композицiї, що належить виконавцю "<<s_artist<<", не знайдено.\n";
	else
	{
		cout<<endl<<"Знайдено "<<n<<" записiв у музичнiй фонотецi за заданим критерiєм.\n";
	}
	cout<<"Всього знайдено "<<q<<" записiв у музичнiй фонотецi.\n";
	system("pause");
	return 0;
}

int MusicLib::search_genre()
{
	char s_genre[15];
	int n = 0, q = 0, r;
	cout<<"Введiть жанр, за яким бажаєте провести пошук:\t";
	cin>>s_genre;
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	fseek(FileMusicLib, 0, 0);
	table();
	while (!feof(FileMusicLib))
	{
		r = fread(&M, sizeof(M), 1, FileMusicLib);
        if (r < 1) break;
        if (strcmp(M.genre, s_genre) == 0) 
        {
        	++n;
        	cout<<n<<". ";
			show1(M);
		}
		++q;
	}
	fclose(FileMusicLib);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (n == 0) cout<<"Жодної композицiї, що належить до жанру \""<<s_genre<<"\", не знайдено.\n";
	else
	{
		cout<<endl<<"Знайдено "<<n<<" записiв у музичнiй фонотецi за заданим критерiєм.\n";
	}
	cout<<"Всього знайдено "<<q<<" записiв у музичнiй фонотецi.\n";
	system("pause");
	return 0;
}

int MusicLib::search_name()
{
	char s_name[30];
	int n = 0, q = 0, r;
	cout<<"Введiть назву композицiї для пошуку:\t";
	cin>>s_name;
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	fseek(FileMusicLib, 0, 0);
	table();
	while (!feof(FileMusicLib))
	{
		r = fread(&M, sizeof(M), 1, FileMusicLib);
        if (r < 1) break;
        if (strcmp(M.record_name, s_name) == 0) 
        {
        	++n;
        	cout<<n<<". ";
			show1(M);
		}
		++q;
	}
	fclose(FileMusicLib);
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (n == 0) cout<<"Жодної композицiї за назвою \""<<s_name<<"\", не знайдено.\n";
	else
	{
		cout<<endl<<"Знайдено "<<n<<" записiв у музичнiй фонотецi за заданим критерiєм.\n";
	}
	cout<<"Всього знайдено "<<q<<" записiв у музичнiй фонотецi.\n";
	system("pause");
	return 0;
}

int MusicLib::sort_name()
{
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	int x = el_size (FileMusicLib);
	music_record sort;
	m = new music_record[x];
	fseek(FileMusicLib, 0, 0);
	for(int i=0; i < x; i++)
	{
		fread(&(m[i]), sizeof(music_record), 1, FileMusicLib);
	}	 
	for(int j=0; j < x; j++)
	for(int k=0; k < x; k++)
	{
		if(strcmp(m[j].record_name,m[k].record_name)<0)
		{
			sort = m[j];
			m[j] = m[k];
			m[k] = sort;
		}	
	}
	cout<<"Музичнi композицiї було посортовано за назвою.\n";
	table();
	for (int a; a < x; a++)
	{
		show1(m[a]);
	}
	system("pause");
	return 0;
}

int MusicLib::sort_artist()
{
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	int x = el_size (FileMusicLib);
	music_record sort;
	m = new music_record[x];
	fseek(FileMusicLib, 0, 0);
	for(int i=0; i < x; i++)
	{
		fread(&(m[i]), sizeof(music_record), 1, FileMusicLib);
	}	 
	for(int j=0; j < x; j++)
	for(int k=0; k < x; k++)
	{
		if(strcmp(m[j].artist,m[k].artist)<0)
		{
			sort = m[j];
			m[j] = m[k];
			m[k] = sort;
		}	
	}
	cout<<"Музичнi композицiї було посортовано за виконавцем.\n";
	table();
	for (int a; a < x; a++)
	{
		show1(m[a]);
	}
	system("pause");
	return 0;
}

int MusicLib::sort_genre()
{
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	int x = el_size (FileMusicLib);
	music_record sort;
	m = new music_record[x];
	fseek(FileMusicLib, 0, 0);
	for(int i=0; i < x; i++)
	{
		fread(&(m[i]), sizeof(music_record), 1, FileMusicLib);
	}	 
	for(int j=0; j < x; j++)
	for(int k=0; k < x; k++)
	{
		if(strcmp(m[j].genre,m[k].genre)<0)
		{
			sort = m[j];
			m[j] = m[k];
			m[k] = sort;
		}	
	}
	cout<<"Музичнi композицiї було посортовано за жанром.\n";
	table();
	for (int a; a < x; a++)
	{
		show1(m[a]);
	}
	system("pause");
	return 0;
}

int MusicLib::sort_year()
{
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	int x = el_size (FileMusicLib);
	music_record sort;
	m = new music_record[x];
	fseek(FileMusicLib, 0, 0);
	for(int i=0; i < x; i++)
	{
		fread(&(m[i]), sizeof(music_record), 1, FileMusicLib);
	}	 
	for(int j=0; j < x; j++)
	for(int k=0; k < x; k++)
	{
		if(m[j].release_year > m[k].release_year)
		{
			sort = m[j];
			m[j] = m[k];
			m[k] = sort;
		}	
	}
	cout<<"Музичнi композицiї було посортовано за роком випуску.\nСпершу вiдображено новiшi.\n";
	table();
	for (int a; a < x; a++)
	{
		cout<<a+1<<".";
		show1(m[a]);
	}
	system("pause");
	return 0;
}

int MusicLib::sort_duration_long()
{
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	int x = el_size (FileMusicLib);
	music_record sort;
	m = new music_record[x];
	fseek(FileMusicLib, 0, 0);
	for(int i=0; i < x; i++)
	{
		fread(&(m[i]), sizeof(music_record), 1, FileMusicLib);
	}	 
	for(int j=0; j < x; j++)
	for(int k=0; k < x; k++)
	{
		int d1 = m[j].record_duration.minute*60 + m[j].record_duration.second;//тривалiсть першого з порiвнюваних музичних записiв
		int d2 = m[k].record_duration.minute*60 + m[k].record_duration.second;//тривалiсть другого з порiвнюваних музичних записiв
		
		if(d1 > d2)
		{
			sort = m[j];
			m[j] = m[k];
			m[k] = sort;
		}	
	}
	cout<<"Музичнi композицiї було посортовано за тривалiстю.\n Спершу вiдображено довшi музичнi твори.\n";
	table();
	for (int a; a < x; a++)
	{
		show1(m[a]);
	}
	system("pause");
	return 0;
}

int MusicLib::sort_duration_short()
{
	if ((FileMusicLib = fopen(filename, "rb+")) == NULL)
	{
    	cout << "Виникла помилка..." << endl;
    	return 1;
	}
	int x = el_size (FileMusicLib);
	music_record sort;
	m = new music_record[x];
	fseek(FileMusicLib, 0, 0);
	for(int i=0; i < x; i++)
	{
		fread(&(m[i]), sizeof(music_record), 1, FileMusicLib);
	}	 
	for(int j=0; j < x; j++)
	for(int k=0; k < x; k++)
	{
		int d1 = m[j].record_duration.minute*60 + m[j].record_duration.second;//тривалiсть першого з порiвнюваних музичних записiв
		int d2 = m[k].record_duration.minute*60 + m[k].record_duration.second;//тривалiсть другого з порiвнюваних музичних записiв
		
		if(d1 < d2)
		{
			sort = m[j];
			m[j] = m[k];
			m[k] = sort;
		}	
	}
	cout<<"Музичнi композицiї було посортовано за тривалiстю.\n Спершу вiдображено коротшi музичнi композицi-ї.\n";
	table();
	for (int a; a < x; a++)
	{
		show1(m[a]);
	}
	system("pause");
	return 0;
}

MusicLib::~MusicLib()
{
	fclose(FileMusicLib);
}
