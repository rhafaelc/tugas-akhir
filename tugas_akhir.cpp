#include <iostream>
#include <fstream>
#include <vector>
using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::vector;

struct buku{
    int id, num_pages;
    string title, authors, isbn, language_code, publication_date, publisher;
    float average_rating;
    unsigned long long dick, ratings_count;
} temp;

int main(){
    string buffer;
    ifstream input_library("tes.txt");

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

}