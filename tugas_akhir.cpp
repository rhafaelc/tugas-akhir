#include <iostream>
#include <fstream>
#include <vector>
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;
using namespace std;

struct buku{
    int id, num_pages;
    string title, authors, isbn, language_code, publication_date, publisher;
    float average_rating;
    unsigned long long isbn13, ratings_count;
} temp;

int main(){
    string buffer;
    ifstream input_library("tes.txt");
    
    bool found = false;
    string key;

    // buku data_buku[9000];

    vector <buku> data_buku;

    int count_buku = 0;
    input_library.seekg(0);
    getline(input_library, buffer, '\n');
    
    while (!input_library.eof()){
        input_library >> temp.id;
        getline(input_library, buffer, '\t');
        getline(input_library, temp.title, '\t');
        getline(input_library, temp.authors, '\t');
        input_library >> temp.average_rating;
        getline(input_library, buffer, '\t');
        getline(input_library, temp.isbn, '\t');
        input_library >> temp.isbn13;
        getline(input_library, buffer, '\t');
        getline(input_library, temp.language_code, '\t');
        input_library >> temp.num_pages;
        getline(input_library, buffer, '\t');
        input_library >> temp.ratings_count;
        getline(input_library, buffer, '\t');
        getline(input_library, temp.publication_date, '\t');
        getline(input_library, temp.publisher, '\n');
        data_buku.push_back(temp);
    }

    input_library.close();
    
    cout << data_buku.size() << endl;
    for (int i = 0; i < 10; ++i){
		cout << data_buku[i].id << '\t' << 
        data_buku[i].title << '\t' << 
        data_buku[i].authors << '\t' << 
        data_buku[i].average_rating << '\t' << 
        data_buku[i].isbn << '\t' << 
        data_buku[i].isbn13 << '\t' << 
        data_buku[i].language_code << '\t' << 
        data_buku[i].num_pages << '\t' << 
        data_buku[i].ratings_count << '\t' << 
        data_buku[i].publication_date << '\t' << 
        data_buku[i].publisher << endl;
	}
	cout << endl;
	
	//sorting 
	//ini sorting nya ko ngga keliatan ke sorting ya
	cout << "Sorting ascending" << endl;
	cout << endl;
	
	for (int i = 0; i < 10; i++)
	{
		int j = i;
		if (j > 0 && data_buku[j].num_pages < data_buku[j-1].num_pages)
		{
			swap (data_buku[j], data_buku[j-1]);
			j--;
		}
	}
	
	for(int i = 0; i < 7; i++)
	{
		cout << data_buku[i].id << '\t' << 
        data_buku[i].title << '\t' << 
        data_buku[i].authors << '\t' << 
        data_buku[i].average_rating << '\t' << 
        data_buku[i].isbn << '\t' << 
        data_buku[i].isbn13 << '\t' << 
        data_buku[i].language_code << '\t' << 
        data_buku[i].num_pages << '\t' << 
        data_buku[i].ratings_count << '\t' << 
        data_buku[i].publication_date << '\t' << 
        data_buku[i].publisher << endl;
	}
	cout << endl;
	
	cout << "Tes sorting descending" << endl;
	
	for(int i = 0; i < 10; i++){
        int max = i;
        for(int j = i + 1; j < 10; j++){
            if(data_buku[j].id > data_buku[max].id)
            {
                max = j;
            }
        }
        swap(data_buku[i], data_buku[max]);
    }
    
    for(int i = 0; i < 7; i++)
	{
		cout << data_buku[i].id << '\t' << 
        data_buku[i].title << '\t' << 
        data_buku[i].authors << '\t' << 
        data_buku[i].average_rating << '\t' << 
        data_buku[i].isbn << '\t' << 
        data_buku[i].isbn13 << '\t' << 
        data_buku[i].language_code << '\t' << 
        data_buku[i].num_pages << '\t' << 
        data_buku[i].ratings_count << '\t' << 
        data_buku[i].publication_date << '\t' << 
        data_buku[i].publisher << endl;
	}
	cout << endl;
	

	//searching ISBN
	cout << "Masukkan ISBN buku yang akan dicari : ";
	cin >> key ;
	cout << endl;
	
	for (int i = 0; i < 11126; i++)
	{
		if (data_buku[i].isbn == key)
		{
			found = true;
			cout << data_buku[i].id << '\t' << 
        	data_buku[i].title << '\t' << 
        	data_buku[i].authors << '\t' << 
        	data_buku[i].average_rating << '\t' << 
        	data_buku[i].isbn << '\t' << 
        	data_buku[i].isbn13 << '\t' << 
        	data_buku[i].language_code << '\t' << 
        	data_buku[i].num_pages << '\t' << 
        	data_buku[i].ratings_count << '\t' << 
        	data_buku[i].publication_date << '\t' << 
        	data_buku[i].publisher << endl;
		}
	}
	
	if (!found)
	{
		cout << "Buku tidak ditemukan" << endl;
	}

}
