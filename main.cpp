#include <iostream>
// BUAT BIKIN FILE TXT
#include <fstream>
// BUAT BIKIN ARRAY
#include <vector>
// BUAT DAPETIN WAKTU-TANGGAL
#include <ctime>
#include <string>

using namespace std;

// MEMBUAT CLASS GOR AGAR DATA GOR MUDAH DIUBAH
class Gor
{
public:
    int id_gor = 1;
    float rating = 4;
    string nama = "Gor SukmaJaya", no_telp = "089614721891";
};

// MEMBUAT CLASS LAPANGAN YANG MEWARISI GOR AGAR DAPAT MEMBUAT DATA LAPANGAN DENGAN MUDAH
class Lapangan : Gor
{
public:
    int Id, harga;
    string nama, desc;
    Lapangan(int a, string b, int c, string d)
    {
        Id = a;
        nama = b;
        harga = c;
        desc = d;
    }
};

// MEMBUAT CLASS TOOL AGAR MUDAH MEMBUAT DATA PERLENGKAPAN
class Tool
{
public:
    int Id;
    int harga;
    int min;
    int qty;
    string nama;
    Tool(int a, int b, int c, int d, string e)
    {
        Id = a;
        harga = b;
        min = c;
        qty = d;
        nama = e;
    }
};

// MAU BIKIN CURRENCY FORMAT
string currencyFormatter(int price)
{
    string strHarga = to_string(price);
    if (strHarga.length() == 5)
    {
        strHarga.insert(2, ".");
    }
    else if (strHarga.length() == 6)
    {
        strHarga.insert(3, ".");
    }
    else if (strHarga.length() == 7)
    {
        strHarga.insert(1, ".");
        strHarga.insert(5, ".");
    }

    return strHarga;
}

// MENDISPLAY LIST LAPANGAN YANG TERDAPAT DI CLASS LAPANGAN
void ListLapangan(vector<Lapangan *> Lapangans)
{
    cout << "================= DAFTAR LAPANGAN =================" << endl;

    // time_t ttime = time(0);
    // tm *local_time = localtime(&ttime);
    // cout << local_time->tm_mday << "-" << 1 + local_time->tm_mon << "-" << 1900 + local_time->tm_year << endl;

    for (int i = 0; i < int(Lapangans.size()); i++)
    {
        cout << i + 1 << ". " << Lapangans[i]->nama << "\nRp. " << currencyFormatter(Lapangans[i]->harga) << "/Jam" << endl;
    }
    cout << "===================================================" << endl;
}

// MEMBUAT LIST PERLENGKAPAN DARI CLASS TOOLS
void ListTool(int &tool, vector<Tool *> Tools)
{
    cout << "================= DAFTAR PERLENGKAPAN =================" << endl;
    for (int i = 0; i < int(Tools.size()); i++)
    {
        cout << i + 1 << ". " << Tools[i]->nama << "\nRp. " << currencyFormatter(Tools[i]->harga) << "/ " << Tools[i]->min << "pcs" << endl;
    }
    cout << "=======================================================" << endl;
    cout << "Pilih menu atau 0 untuk tidak meminjam perlengkapan" << endl;
    cin >> tool;
}

// MENGAMBIL INPUTAN LAPANGAN YANG USER MAU
void getLap(int lap, int &dur, vector<Lapangan *> Lapangans)
{
    for (int i = 0; i < int(Lapangans.size()); i++)
    {
        if (Lapangans[i]->Id == lap)
        {
            system("CLS");
            cout << "================== DETIL LAPANGAN =================" << endl;
            cout << Lapangans[i]->nama << endl;
            cout << "Rp. " << currencyFormatter(Lapangans[i]->harga) << "/Jam\n\n";
            cout << "INFO :" << endl;
            cout << "Belum termasuk perlengkapan " << endl;
            cout << "===================================================" << endl;
            do
            {
                cout << "Maksimal bermain 24 Jam " << endl;
                cout << "Durasi bermain (jam): ";
                cin >> dur;
            } while (dur <= 0 || dur >= 24);
            break;
        }
    }
}

// PRINT TRANSAKSI SETELAH MEMILIH LAPANGAN PERLENGKAPAN DAN WAKTUN BERMAIN
void PrintTransaction(int lap, int tool, vector<Tool *> Tools, int dur, vector<Lapangan *> Lapangans, int totalTools, int totalAll)
{
    for (int i = 0; i < int(Lapangans.size()); i++)
    {
        if (Lapangans[i]->Id == lap)
        {
            ofstream myfile;
            myfile.open("transaction.txt");
            myfile << "================== DETIL TRANSAKSI =================" << endl;
            myfile << Lapangans[i]->nama << endl;
            myfile << "Rp. " << currencyFormatter(Lapangans[i]->harga) << "/Jam\n";
            myfile << Lapangans[i]->desc << "\n\n";
            myfile << "INFO :" << endl;
            myfile << "Belum termasuk perlengkapan " << endl;
            myfile << "Durasi bermain\t: " << dur << " Jam" << endl;
            myfile << "Perlengkapan\t: " << endl;
            for (int j = 0; j < int(Tools.size()); j++)
            {
                int num = 1;
                if (Tools[j]->Id == tool)
                {
                    myfile << num << ". " << Tools[j]->nama << " - " << currencyFormatter(Tools[j]->harga) << endl;
                    num++;
                }
            }
            myfile << endl;
            myfile << "========================TOTAL=======================" << endl;
            myfile << "Lapangan\t\t: "
                   << "Rp. " << currencyFormatter(Lapangans[i]->harga) << " x " << dur << " Jam" << endl;
            myfile << "Perlengkapan\t: "
                   << "Rp. " << currencyFormatter(totalTools) << endl;
            myfile << "Total harga\t\t: "
                   << "Rp. " << currencyFormatter(totalAll) << endl;
            myfile << "====================================================" << endl;
            myfile.close();
        }
    }
}

// MENDISPLAY DETIL TRANSAKSI YANG TELAH DILAKUKAN
void getDetail(int lap, int tool, vector<Tool *> Tools, int dur, vector<Lapangan *> Lapangans)
{
    int totalTools = 0, totalAll;
    for (int i = 0; i < int(Lapangans.size()); i++)
    {
        if (Lapangans[i]->Id == lap)
        {
            system("CLS");
            cout << "================== DETIL TRANSAKSI =================" << endl;
            cout << Lapangans[i]->nama << endl;
            cout << "Rp. " << currencyFormatter(Lapangans[i]->harga) << "/Jam\n";
            cout << Lapangans[i]->desc << "\n\n";
            cout << "INFO :" << endl;
            cout << "Belum termasuk perlengkapan " << endl;
            cout << "Durasi bermain\t: " << dur << " Jam" << endl;
            cout << "Perlengkapan\t: " << endl;
            for (int j = 0; j < int(Tools.size()); j++)
            {
                int num = 1;
                if (Tools[j]->Id == tool)
                {
                    totalTools += Tools[j]->harga;
                    cout << num << ". " << Tools[j]->nama << " - " << currencyFormatter(Tools[j]->harga) << endl;
                    num++;
                }
            }
            cout << endl;
            totalAll = totalTools + (Lapangans[i]->harga * dur);
            cout << "========================TOTAL=======================" << endl;
            cout << "Lapangan\t: "
                 << "Rp. " << currencyFormatter(Lapangans[i]->harga) << " x " << dur << " Jam" << endl;
            cout << "Perlengkapan\t: "
                 << "Rp. " << currencyFormatter(totalTools) << endl;
            cout << "Total harga\t: "
                 << "Rp. " << currencyFormatter(totalAll) << endl;
            cout << "====================================================" << endl;

            PrintTransaction(lap, tool, Tools, dur, Lapangans, totalTools, totalAll);
        }
    }
}

int main()
{
    int lap, tool, time;
    // MEMBUAT DATA DARI CLASS LAPANGAN
    vector<Lapangan *> Lapangans{{new Lapangan(1, "Lapangan Normal", 15000, "Lapangan normal, hanya lapangan saja."), new Lapangan(2, "Lapangan Rumput", 25000, "Lapangan dengan rumput, hanya lapangan saja.")}};
    // MEMBUAT DATA DARI CLASS TOOLS
    vector<Tool *> Tools{{new Tool(1, 5000, 1, 12, "Bole Bliter"), new Tool(2, 5000, 4, 50, "Cone"), new Tool(3, 15000, 7, 24, "Rompi")}};

    system("CLS");

    ListLapangan(Lapangans);
    cin >> lap;

    system("CLS");
    getLap(lap, time, Lapangans);

    system("CLS");
    ListTool(tool, Tools);

    system("CLS");
    getDetail(lap, tool, Tools, time, Lapangans);

    system("pause");
    return 0;
}