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
	
 	int total_jual[100];
	for (int i = 0; i < count_pegawai - 1; i++){
		total_jual[i] = 0;
		for (int j = 0; j < count_log - 1; j++){
			if (data_log[j].kasir == data_pegawai[i].id){
				total_jual[i] += (data_log[j].harga - data_log[j].diskon) * data_log[j].kuantiti;
			}
		}
	}
 
 	for (int i = 0; i < count_pegawai - 1; i++){
		cout << data_pegawai[i].id << '\t' << data_pegawai[i].nama << "\t" << total_jual[i] << endl;
 	}
	
	// tulis data item ke file binary
	ofstream out_item("itemdata.bin", ios::binary);
	for (int i = 0; i < count_item - 1; i++){
		out_item.write((char*)&(data_item[i].id_item), sizeof(data_item[i].id_item));
		auto texto_nama = data_item[i].nama.c_str();
		out_item.write(texto_nama, data_item[i].nama.length());
		auto texto_sku = data_item[i].sku.c_str();
		out_item.write(texto_sku, data_item[i].sku.length());
		out_item.write((char*)&(data_item[i].diskon_nominal), sizeof(data_item[i].diskon_nominal));
		out_item.write((char*)&(data_item[i].diskon_persen), sizeof(data_item[i].diskon_persen));
	}

	ofstream out_log("logdata.bin", ios::binary);
	for (int i = 0; i < count_log - 1; i++){
	   auto texto_time = data_log[i].time.c_str();
	   out_log.write(texto_time, data_log[i].time.length());
	   out_log.write((char*)&(data_log[i].kasir), sizeof(data_log[i].kasir));
	   out_log.write((char*)&(data_log[i].konsumen), sizeof(data_log[i].konsumen));
	   out_log.write((char*)&(data_log[i].id_item), sizeof(data_log[i].id_item));
	   out_log.write((char*)&(data_log[i].harga), sizeof(data_log[i].harga));
	   out_log.write((char*)&(data_log[i].diskon), sizeof(data_log[i].diskon));
	   out_log.write((char*)&(data_log[i].kuantiti), sizeof(data_log[i].kuantiti));
   }
	
	ofstream out_pegawai("pegawaidata.bin", ios::binary);
	for (int i = 0; i < count_pegawai - 1; i++){
		out_pegawai.write((char*)&(data_pegawai[i].id), sizeof(data_pegawai[i].id));
		auto texto_nmpgw = data_pegawai[i].nama.c_str();
		out_pegawai.write(texto_nmpgw, data_pegawai[i].nama.length());
	}
	
	// tulis data total penjualan ke file binary
	ofstream out_penjualan("penjualandata.bin", ios::binary);
 	for (int i = 0; i < count_pegawai - 1; i++){
		out_penjualan.write((char*)&(data_pegawai[i].id), sizeof(data_pegawai[i].id));
		auto texto_nmpgw = data_pegawai[i].nama.c_str();
		out_penjualan.write(texto_nmpgw, data_pegawai[i].nama.length());
		out_penjualan.write((char*)&(total_jual[i]), sizeof(total_jual[i]));
	 }
 
	return 0;
}
