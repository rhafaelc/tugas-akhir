#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct buku {
  string title;
	string authors;
	string isbn;
	string publication_date;
	string publisher;
};

struct pinjam{
    string nama;
    string NIM;
    string isbn;
    string title;
    int tanggal, bulan, tahun;
    int tanggal1, bulan1, tahun1;
    bool is_pinjam = false;
};

//Global Variables
bool found = false;
int denda;
int lewat;
int total;
	
//Deklarasi Array of Struct 
buku data_buku[] = {{"Harry Potter Collection #1-6            ",	"J.K. Rowling   ", "0439827604", "     9/12/2005", "Scholastic           "},
                  {"Hitchhiker's Guide to the Galaxy  #1-5  ", "Douglas Adams  ", "0517149257", "     1/17/1996", "Wings Books          "},
	              {"The Lord of the Rings  #1-3             ", "Alan  Lee      ", "0618260587", "     10/1/2002", "Houghton Mifflin H.  "},
                  {"Hatchet (Brian's Saga  #1)              ", "Gary Paulsen   ", "0689840926", "     4/1/2000" , "Richard Jackson Books"},
	              {"The Art of the Fellowship of the Ring   ", "Gary Russell   ", "0618212906", "     6/12/2002", "Houghton Mifflin H.  "},
	              {"New Hope for the Dead #2                ", "James Lee Burke", "0400032490", "     8/10/2004", "Black Lizard         "},
	              {"The New York Trilogy Paul Auster/Art    ", "Luc Sante      ", "0143039830", "     3/28/2006", "Penguin Classics     "},
	              {"The Kingdom of God Is Within You        ", "Leo Tolstoy    ", "0486451380", "     9/8/2006" , "Dover Publications   "},
	              {"Why We Love (or Hate) Everyday Things   ", "Donald Norman  ", "0475270785", "     5/11/2005", "Basic Books          "},
	              {"The Dark Side of the All-American Meal  ", "Eric Schlosser ", "0460838582", "     7/5/2005" , "Harper Perennial     "},
                  {"Notes from a Small Island               ", "Bill Bryson    ", "0380727501", "     5/28/1997" , "Morrow Paperbacks    "}};

//Untuk Menghitung Jumlah Elemen dalam Array
int datasize = sizeof(data_buku)/sizeof(data_buku[0]);

//Fungsi Sort (Selection Sort)
void _sort(buku data_buku[], int n){
    int i, min;
    buku temp;

    for(int i = 0; i<n; i++) {
    min = i;
        for(int j=1+i; j<n; j++){
            if(data_buku[j].title < data_buku[min].title){
                min = j;
            }
        }
        temp = data_buku[i];
        data_buku[i] = data_buku[min];
        data_buku[min] = temp;
    }
}

//Fungsi Untuk Menulis Data Peminjam Di Text File
void tulis_pinjam(pinjam arr){
	ofstream out_pinjam("data_pinjam.txt", ofstream::app);
    out_pinjam << arr.nama << "\t" << arr.NIM << "\t" << arr.title << "\t" << arr.tanggal 
	<< "/" << arr.bulan << "/" << arr.tahun << "\t" << arr.tanggal1 << "/" << arr.bulan1 
	<< "/" << arr.tahun1 << "\t" << arr.is_pinjam << endl;
}

//Fungsi Opsi Pilihan 1 (Mendata Peminjam)
void pilihan1(){
    pinjam data_pinjam;
    cout << "Nama Peminjam : ";
	cin.ignore();
	getline (cin, data_pinjam.nama);
	
	cout << "Nomor Induk Mahasiswa : ";
	cin >> data_pinjam.NIM;
	cout << endl;
	
	cout << "Daftar Peminjaman Buku" << endl;
	cout << "Masukkan ISBN buku yang akan dipinjam : ";
	cin >> data_pinjam.isbn;
	cout << endl;

  /*Sequential Searching untuk Mencari ISBN tertentu di Array Buku, lalu mengambil Judul Buku di Index itu dan dimasukkan ke variabel di Struct Pinjam*/
    int i;
    for(i = 0; i < datasize; i++){
        if(data_pinjam.isbn == data_buku[i].isbn){
            data_pinjam.title = data_buku[i].title;
        }
    }
	//Sequential untuk Mencari ISBN Tertentu
	for (int j = 0; j < datasize; j++){
		if (data_buku[j].isbn == data_pinjam.isbn){
			found = true;
            data_pinjam.is_pinjam = true;
			
			cout << "==========================================================================================================================================" << endl;
			cout << "|" << setw(25) << "Judul Buku" << setw(20) << "|" << setw(15)
			<< "Penulis Buku" << setw(5)  << "|" << setw(10) << "ISBN" 
			<< setw(10) << "|" << setw(17) << "Tanggal Terbit" << setw(5)  << "|" 
			<< setw(20) << "Penerbit" << setw(10) << "|" << endl; 
			cout << "==========================================================================================================================================" << endl;
	
			cout << "|" << data_buku[j].title << setw(5) << right << "|" <<
        	data_buku[j].authors << setw(5) << "|" << setw(15) << 
        	data_buku[j].isbn << setw(5) << "|" << setw(15) << 
        	data_buku[j].publication_date << setw(7) << "|" << setw(10) << 
        	data_buku[j].publisher << setw(10) << "| " << endl;
        	
        	cout << "==========================================================================================================================================" << endl;
			cout << endl;
			
			cout << "Tanggal Peminjaman (dd/mm/yyyy) : "; 
			cin >> data_pinjam.tanggal >> data_pinjam.bulan >> data_pinjam.tahun;

      //Percabangan untuk Menentukan Tanggal Jatuh Tempo
			data_pinjam.tanggal1 = data_pinjam.tanggal + 7;
	        if (data_pinjam.bulan == 1 || data_pinjam.bulan == 3 || data_pinjam.bulan == 5 
				|| data_pinjam.bulan == 7 || data_pinjam.bulan == 8 ||
                data_pinjam.bulan == 10 || data_pinjam.bulan == 12){
                if(data_pinjam.tanggal1 > 31){
                    data_pinjam.tanggal1 = data_pinjam.tanggal1 - 31;
                    if(data_pinjam.bulan == 12){
                        data_pinjam.tahun1 = data_pinjam.tahun + 1;
                        data_pinjam.bulan1 = 1;
                    }
                    else{
                        data_pinjam.bulan1 = data_pinjam.bulan + 1;
                        data_pinjam.tahun1 = data_pinjam.tahun;
                    }
                }
                else{
                    data_pinjam.bulan1 = data_pinjam.bulan;
                    data_pinjam.tahun1 = data_pinjam.tahun;
                }
            }
            else if(data_pinjam.bulan == 2){
                if(data_pinjam.tanggal1 > 28){
                    data_pinjam.tanggal1 = data_pinjam.tanggal1 - 28;
                    data_pinjam.bulan1 = data_pinjam.bulan + 1;
                    data_pinjam.tahun1 = data_pinjam.tahun;
                }
                else{
                    data_pinjam.bulan1 = data_pinjam.bulan;
                    data_pinjam.tahun1 = data_pinjam.tahun;
                }
            }
            else{
                if(data_pinjam.tanggal1 > 30){
                    data_pinjam.tanggal1 = data_pinjam.tanggal1 - 30;
                    data_pinjam.bulan1 = data_pinjam.bulan + 1;
                    data_pinjam.tahun1 = data_pinjam.tahun;
                }
                else{
                    data_pinjam.bulan1 = data_pinjam.bulan;
                    data_pinjam.tahun1 = data_pinjam.tahun;
                }
            }
			
			cout << "Tanggal Jatuh Tempo Pengembalian (dd/mm/yyyy) : " << data_pinjam.tanggal1 
			<< " " << data_pinjam.bulan1 << " " << data_pinjam.tahun1 << endl;
		}
	}
	cout << endl;
	
	if (!found){
		cout << "Buku tidak ditemukan" << endl;
	}

    tulis_pinjam(data_pinjam);
}

// Menghitung berapa banyak baris dalam file (nantinya yang dipakai tidak lebih dari ((banyak row) - 1) karena dalam file terdapat (banyak row) baris di mana baris ke (banyak row - 1) kosong)
int count_row(int &count_pinjam){
    count_pinjam = 0;
    string buffer;

    ifstream baca_baris("data_pinjam.txt");
    baca_baris.seekg(0);
    while (!baca_baris.eof()){
        getline(baca_baris, buffer, '\n');
        count_pinjam++;
    }
    return count_pinjam;
}

//Fungsi Untuk Membaca Text File Yang Menyimpan Data Peminjam dan Memindahkannya ke Array
void read_file(int cnt, pinjam baca_pinjam[]){
    string buffer;

    ifstream out_pinjam("data_pinjam.txt");
    out_pinjam.seekg(0);
    baca_pinjam[cnt];

    int i = 0;
    while (!out_pinjam.eof() && i < cnt){
		getline(out_pinjam, baca_pinjam[i].nama, '\t');
		getline(out_pinjam, baca_pinjam[i].NIM, '\t');
		getline(out_pinjam, baca_pinjam[i].title, '\t');
        out_pinjam >> baca_pinjam[i].tanggal;
        getline(out_pinjam, buffer, '/');
        out_pinjam >> baca_pinjam[i].bulan;
        getline(out_pinjam, buffer, '/');
        out_pinjam >> baca_pinjam[i].tahun;
        getline(out_pinjam, buffer, '\t');
        out_pinjam >> baca_pinjam[i].tanggal1;
        getline(out_pinjam, buffer, '/');
        out_pinjam >> baca_pinjam[i].bulan1;
        getline(out_pinjam, buffer, '/');
        out_pinjam >> baca_pinjam[i].tahun1; 
        getline(out_pinjam, buffer, '\t');
        out_pinjam >> baca_pinjam[i].is_pinjam; 
        getline(out_pinjam, buffer, '\n');
        i++;
    }
    out_pinjam.close();
}

//Fungi Opsi Pilihan 2 (Pengembalian Buku dan Perhitungan Denda)
// pengubahan kolom is_pinjam menjadi false ketika data dapat ditemukan
void pilihan2(){
    int cnt;
    string key;
    count_row(cnt);
    
    pinjam baca_pinjam[cnt];
    read_file(cnt, baca_pinjam);

    cout << "Masukkan NIM Peminjam : ";
    cin.ignore();
    getline(cin, key);
    cout << endl;

    found = false;
    int i, index;
    int datasize_peminjam = sizeof(baca_pinjam)/sizeof(baca_pinjam[0]);

  //Sequential Searching untuk Mencari NIM terentu di dalam Array of Struct
    for(i = 0; i < datasize_peminjam; i++){
        if(baca_pinjam[i].NIM == key){
            found = true;
            index = i;
            
            cout << "Daftar Peminjaman : " << endl;
            cout << "===========================================================================================================================================" << endl;
            cout << "|" << setw(20) << "Nama Peminjam" << setw(10) << "|" << setw(8)
            << "NIM" << setw(7)  << "|" << setw(25) << "Judul Buku" 
            << setw(20) << "|" << setw(15) << "Tanggal Pinjam" << setw(5)  << "|" << setw(23) 
			<< "Tanggal Jatuh Tempo" << setw(5) << "|" << endl; 
            cout << "===========================================================================================================================================" << endl;
                cout << "|" << setw(18) << left << baca_pinjam[i].nama << setw(12) << right << "|" << setw(10) 
				<< baca_pinjam[i].NIM << setw(5) << "|" << baca_pinjam[i].title 
                << setw(5) << right << "|" << setw(7) << baca_pinjam[i].tanggal << "/" << setw(2) 
				<< setfill('0') << baca_pinjam[i].bulan << setw(0) << setfill(' ') << "/" << baca_pinjam[i].tahun
                << setw(5)  << "|" << setw(10) << baca_pinjam[i].tanggal1 << "/" << setw(2) 
				<< setfill('0') << baca_pinjam[i].bulan1 << setw(0) << setfill(' ') << "/" 
				<< baca_pinjam[i].tahun1 << setw(10) << "|" << endl;
            cout << "===========================================================================================================================================" << "\n\n"; 
        }
    }

	if (!found){
		cout << "Data peminjam tidak ditemukan" << "\n\n";
	}
  //Kode untuk menghitung Perbedaan Hari lalu Menghitung denda berdasarkan itu
    else{
        int haribulan[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        int tanggal2, bulan2, tahun2;

        cout << "Tanggal Pengembalian (dd/mm/yyyy) : ";
        cin >> tanggal2 >> bulan2 >> tahun2;

        long int diff1 = baca_pinjam[index].tahun1 * 365 + baca_pinjam[index].tanggal1;
        for (int i = 0; i < baca_pinjam[index].bulan1 - 1; i++) 
            diff1 += haribulan[i];
        
        long int diff2 = tahun2 * 365 + tanggal2;
        for (int i = 0; i < bulan2 - 1; i++)
            diff2 += haribulan[i];

        denda = 1000;
        lewat = diff2 - diff1;
        total = lewat * denda;

        if (total <= 0){
            cout << baca_pinjam[index].nama << " tidak memiliki denda" << "\n\n";
        }
        else{
            cout << baca_pinjam[index].nama << " memiliki denda sebesar : Rp" << total << endl;
            cout << endl;
        }
        baca_pinjam[index].is_pinjam = false;  

        ofstream ganti_pinjam("data_pinjam.txt");
        for (int i = 0; i < datasize_peminjam - 1; i++){
            ganti_pinjam << baca_pinjam[i].nama << "\t" << baca_pinjam[i].NIM << "\t" << baca_pinjam[i].title << "\t" << baca_pinjam[i].tanggal 
	        << "/" << baca_pinjam[i].bulan << "/" << baca_pinjam[i].tahun << "\t" << baca_pinjam[i].tanggal1 << "/" << baca_pinjam[i].bulan1 
	        << "/" << baca_pinjam[i].tahun1 << "\t" << baca_pinjam[i].is_pinjam << endl;
        }
    }
}

//Fungsi Opsi Pilihan 3
//Ganti "Telah Dikembalikan"
void pilihan3(){
    cout << "=======================================================================================================================================================================" << endl;
	cout << "|" << setw(20) << "Nama Peminjam" << setw(10) << "|" << setw(8) << "NIM" << setw(7)  
	<< "|" << setw(25) << "Judul Buku" << setw(20) << "|" << setw(15) << "Tanggal Pinjam" 
	<< setw(5)  << "|" << setw(23) << "Tanggal Jatuh Tempo" << setw(5) << "|" << setw(23) << "Status Pengembalian" << setw(5) << "|" << endl; 
	cout << "=======================================================================================================================================================================" << endl;
    int cnt;
    count_row(cnt);
    
    pinjam baca_pinjam[cnt];
    read_file(cnt, baca_pinjam);

    for (int i = 0; i < cnt - 1; i++){
        cout << "|" << setw(18) << left << baca_pinjam[i].nama << setw(12) << right << "|" 
		<< setw(10) << baca_pinjam[i].NIM << setw(5) << "|" << baca_pinjam[i].title 
        << setw(5) << right << "|" << setw(7) << baca_pinjam[i].tanggal << "/" << setw(2) 
		<< setfill('0') << baca_pinjam[i].bulan << setw(0) << setfill(' ') << "/" << baca_pinjam[i].tahun
        << setw(5)  << "|" << setw(10) << baca_pinjam[i].tanggal1 << "/" << setw(2) << setfill('0') 
		<< baca_pinjam[i].bulan1 << setw(0) << setfill(' ') << "/" << baca_pinjam[i].tahun1 << setw(10) 
		<< "|" << setw(23);
        
        if(!baca_pinjam[i].is_pinjam)
            cout << "Telah Dikembalikan";
        else
            cout << "Belum Dikembalikan";
        
        cout << setw(5) << "|" << endl;
	}
    cout << "=======================================================================================================================================================================" << endl;
    cout << endl;
}

int main(){
//Sorting Judul Buku Berdasarkan Alfabet
  _sort(data_buku, datasize);

	cout << "==========================================================================================================================================" << endl;
	cout << "                                                      DAFTAR BUKU PERPUSTAKAAN" << endl;
	cout << "                                                              MIPA UGM" << endl;
	cout << "==========================================================================================================================================" << endl;

	cout << "|" << setw(25) << "Judul Buku" << setw(20) << "|" << setw(15)
	<< "Penulis Buku" << setw(5)  << "|" << setw(12) << "ISBN" 
	<< setw(8) << "|" << setw(17) << "Tanggal Terbit" << setw(5)  << "|" << setw(18) 
	<< "Penerbit" << setw(12) << "|" << endl; 
	cout << "==========================================================================================================================================" << endl;
	
	for (int i = 0; i < 10; i++){
		cout << "|" << data_buku[i].title << setw(5) << right << "|" <<
        data_buku[i].authors << setw(5) << "|" << setw(15) << 
        data_buku[i].isbn << setw(5) << "|" << setw(15) << 
        data_buku[i].publication_date << setw(7) << "|" << setw(10) << 
        data_buku[i].publisher << setw(10) << "| " << endl;
	}
	cout << "==========================================================================================================================================" << endl;
	cout << endl;

int pilihan;
    while(true){
    cout << "=== PROGRAM PERPUSTAKAN MIPA UGM ===" << endl; 
    cout << endl;
    cout << "1 : Peminjaman Buku" << endl;
    cout << "2 : Pengembalian Buku" << endl;
    cout << "3 : Data Peminjam Buku" << endl;
    cout << "4 : Keluar Program" << endl;
    cout << endl;
    cout << "Masukkan Pilihan : ";
    cin >> pilihan;
    cout << endl;

        //Percabangan yang membagi pilihan input untuk user
        switch(pilihan){
          case 1:
          pilihan1();
          continue;
          case 2:
          pilihan2();
          continue;
          case 3:
          pilihan3();
          continue;
          case 4:
          	cout << "========== Program Selesai =========" << endl;
          break;
        }
        break;
    }
    cout << endl;
  
    system("pause");
  
}