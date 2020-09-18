#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include <iostream>
using namespace std;

class MusicLib{
	public:
	
	MusicLib();
	~MusicLib();
		
	FILE *FileMusicLib;
	struct song_duration
	{
		int minute, second;
	};
	
	struct music_record
	{
		song_duration record_duration;
		char record_name[30], album_name[20], artist[20], genre[15];
		int release_year;
	} M, *m;
	
	public:
	int el_size(FILE* f);
	void table();
	void show1(music_record M);
	int main_menu();
	int add_new_record(int q);
	int show_all();
	void search_menu();
	void sorting_menu();
	int search_year();
	int search_genre();
	int search_artist();
	int search_name();
	int sort_name();
	int sort_artist();
	int sort_genre();
	int sort_year();
	int sort_duration_long();
	int sort_duration_short();
};
#endif
