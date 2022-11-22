#include <fstream>
#include <iostream>
using namespace std;

struct var_item{
	unsigned long long id_item;
	string nama, sku;
	int harga, diskon_nominal, stok;
	double diskon_persen;
};

struct var_pegawai{
	int id;
	string nama;
};

struct var_log{
	unsigned long long id_item;
	string time;
	int kasir, konsumen, harga, diskon, kuantiti;
};

struct penjualan_pegawai{
	int id, total_penjualan, total_kuantiti;
	string nama;
};

struct penjualan_barang {
	unsigned long long id;
	int total_kuantiti;
	string nama;
};

void baca_item(var_item arr[], int &count_item){
	string buffer;
	ifstream input_item("item.txt");
	
	count_item = 0;
	input_item.seekg(0);
	getline(input_item, buffer, '\n');
  
	while (!input_item.eof()){
		input_item >> arr[count_item].id_item;
		getline(input_item, buffer, '\t');
		getline(input_item, arr[count_item].nama, '\t');
		getline(input_item, arr[count_item].sku, '\t');
		input_item >> arr[count_item].harga;
		input_item >> arr[count_item].diskon_nominal;
		input_item >> arr[count_item].diskon_persen;
		input_item >> arr[count_item].stok;
		getline(input_item, buffer, '\n');
		++count_item;
	}
	input_item.close();
}

void baca_pegawai(var_pegawai arr[], int &count_pegawai){
	string buffer;
	ifstream input_pegawai("pegawai.txt");
	
	count_pegawai = 0;
	input_pegawai.seekg(0);
	getline(input_pegawai, buffer, '\n');
  
	while (!input_pegawai.eof()){
		input_pegawai >> arr[count_pegawai].id;
		getline(input_pegawai, buffer, '\t');
		getline(input_pegawai, arr[count_pegawai].nama, '\n');
		++count_pegawai;
	}
	input_pegawai.close();
}

void baca_log(var_log arr[], int &count_log){
	string buffer;
	ifstream input_log("log.txt");
	
	count_log = 0;
	input_log.seekg(0);
	getline(input_log, buffer, '\n');

	while (!input_log.eof()){
		getline(input_log, arr[count_log].time, '\t');
		input_log >> arr[count_log].kasir;
		input_log >> arr[count_log].konsumen;
		input_log >> arr[count_log].id_item;
		input_log >> arr[count_log].harga;
		input_log >> arr[count_log].diskon;
		input_log >> arr[count_log].kuantiti;
		getline(input_log, buffer, '\n');
		++count_log;
	}
	
	input_log.close();
}

void tulis_item(int count_item, var_item arr[]){
	ofstream out_item("itemdata.bin", ios::binary);
	for (int i = 0; i < count_item - 1; i++){
		out_item.write((char*)&(arr[i].id_item), sizeof(arr[i].id_item));
		auto texto_nama = arr[i].nama.c_str();
		out_item.write(texto_nama, arr[i].nama.length());
		auto texto_sku = arr[i].sku.c_str();
		out_item.write(texto_sku, arr[i].sku.length());
		out_item.write((char*)&(arr[i].diskon_nominal), sizeof(arr[i].diskon_nominal));
		out_item.write((char*)&(arr[i].diskon_persen), sizeof(arr[i].diskon_persen));
	}
}

void tulis_log(int count_log, var_log arr[]){
	ofstream out_log("logdata.bin", ios::binary);
	for (int i = 0; i < count_log - 1; i++){
		auto texto_time = arr[i].time.c_str();
		out_log.write(texto_time, arr[i].time.length());
		out_log.write((char*)&(arr[i].kasir), sizeof(arr[i].kasir));
		out_log.write((char*)&(arr[i].konsumen), sizeof(arr[i].konsumen));
		out_log.write((char*)&(arr[i].id_item), sizeof(arr[i].id_item));
		out_log.write((char*)&(arr[i].harga), sizeof(arr[i].harga));
		out_log.write((char*)&(arr[i].diskon), sizeof(arr[i].diskon));
		out_log.write((char*)&(arr[i].kuantiti), sizeof(arr[i].kuantiti));
	}
}

void tulis_pegawai(int count_pegawai, var_pegawai arr[]){
	ofstream out_pegawai("pegawaidata.bin", ios::binary);
	for (int i = 0; i < count_pegawai - 1; i++){
		out_pegawai.write((char*)&(arr[i].id), sizeof(arr[i].id));
		auto texto_namapegawai = arr[i].nama.c_str();
		out_pegawai.write(texto_namapegawai, arr[i].nama.length());
	}
}

void hitung_jual(penjualan_pegawai arr[], var_log data_log[], var_pegawai data_pegawai[], int count_pegawai, int count_log){
	for (int i = 0; i < count_pegawai - 1; i++){
		arr[i].id = data_pegawai[i].id;
		arr[i].total_penjualan = 0;
		arr[i].total_kuantiti  = 0;
		arr[i].nama = data_pegawai[i].nama;
		for (int j = 0; j < count_log - 1; j++){
			if (data_log[j].kasir == arr[i].id){
				arr[i].total_penjualan += (data_log[j].harga - data_log[j].diskon) * data_log[j].kuantiti;
				arr[i].total_kuantiti += data_log[j].kuantiti;
			}
		}
	}
}

void hitung_kuantiti (penjualan_barang arr[], var_log data_log[], var_item data_item[], int count_log, int count_item){
	for (int i = 0; i < count_item - 1; i++){
		arr[i].id = data_item[i].id_item;
		arr[i].total_kuantiti = 0;
		arr[i].nama = data_item[i].nama;
		for (int j = 0; j < count_log - 1; j++){
			if(arr[i].id == data_log[j].id_item)
				arr[i].total_kuantiti += data_log[j].kuantiti;
		}
	}
}

void _swap(int &a, int &b){
	int temp = a;
	a = b;
	b = temp;
}

void _swap(penjualan_pegawai &a, penjualan_pegawai &b){
	penjualan_pegawai temp = a;
	a = b;
	b = temp;
}

void _swap(penjualan_barang &a, penjualan_barang &b){
	penjualan_barang temp = a;
	a = b;
	b = temp;
}

void _sort(int arr[], int data_size){
	for (int i = 0; i < data_size - 1; i++){
		for (int j = 0; j < data_size - i - 1; j++){
			if(arr[j] < arr[j + 1])
				_swap(arr[j], arr[j + 1]);		
		}
	}
}

void _sort(penjualan_pegawai arr[], int data_size){
	for (int i = 0; i < data_size - 1; i++){
		for (int j = 0; j < data_size - i - 1; j++){
			if(arr[j].total_penjualan < arr[j + 1].total_penjualan)
				_swap(arr[j], arr[j + 1]);		
		}
	}
}

void _sort(penjualan_barang arr[], int data_size){
	for (int i = 0; i < data_size; i++){
		for (int j = 0; j < data_size - 1; j++){
			if(arr[j].total_kuantiti < arr[j + 1].total_kuantiti)
				_swap(arr[j], arr[j + 1]);		
		}
	}
}

int main(){

	var_item data_item[100];
	int count_item;
	baca_item (data_item, count_item);
	
	var_pegawai data_pegawai[100];
	int count_pegawai;
	baca_pegawai (data_pegawai, count_pegawai);

	var_log data_log[100];
	int count_log;
	baca_log (data_log, count_log);

	penjualan_pegawai total_jual[count_pegawai];
	hitung_jual(total_jual, data_log, data_pegawai, count_pegawai, count_log);
	_sort(total_jual, count_pegawai - 1);
	
	for (int i = 0; i < count_pegawai - 1; i++){
		cout << total_jual[i].id << '\t' << total_jual[i].nama << "\t" << total_jual[i].total_penjualan << "\t" << total_jual[i].total_kuantiti << endl;
	}

	penjualan_barang total_kuantiti[count_item];
	hitung_kuantiti(total_kuantiti, data_log, data_item, count_log, count_item);
	_sort(total_kuantiti, count_item - 1);

	for (int i = 0; i < 5; i++){
		cout << total_kuantiti[i].id << '\t' << total_kuantiti[i].nama << "\t" << total_kuantiti[i].total_kuantiti << endl;
	}

	tulis_item(count_item, data_item);
	tulis_log(count_log, data_log);
	tulis_pegawai(count_pegawai, data_pegawai);

	return 0;
}
