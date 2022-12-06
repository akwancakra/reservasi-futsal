#include <iostream>
// BUAT BIKIN FILE TXT
#include <fstream>
// BUAT BIKIN ARRAY
#include <vector>
// BUAT DAPETIN WAKTU-TANGGAL
#include <ctime>
#include <string>
// FOR CHECK SPACING
#include <cctype>
#include <algorithm>
#include <regex>

using namespace std;
// INITIALIZE DECLARATION
bool isLogin = false;
int idAccount;

// MAU BIKIN CURRENCY FORMAT
string currencyFormatter(int price) // 10000
{
    string strHarga = to_string(price);
    if (strHarga.length() == 4)
    {
        strHarga.insert(1, ".");
    }
    else if (strHarga.length() == 5)
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
    else if (strHarga.length() == 8)
    {
        strHarga.insert(2, ".");
        strHarga.insert(5, ".");
    }

    return strHarga;
}

// MENDISPLAY LIST LAPANGAN YANG TERDAPAT DI CLASS LAPANGAN
vector<vector<string>> Account = {{"1", "akwan", "akwan@mail.com", "akwan"}, {"2", "cakra", "cakra@mail.com", "cakra"}}, Lapangans = {{"1", "Lapangan Hitam", "20000"}, {"2", "Lapangan Normal", "25000"}, {"3", "Lapangan Medium", "30000"}}, Tools = {{"1", "Cone", "10000", "5", "100"}, {"2", "Rompi", "10000", "5", "100"}, {"3", "Bola", "4000", "1", "12"}}, Transactions;

// CHECK IF LAPANGAN EXIST
bool GetLapangan(int lap)
{
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == lap)
        {
            return true;
        }
    }
    return false;
}

// CHECK IF TOOL EXIST
bool GetTool(int tool)
{
    for (int i = 0; i < Tools.size(); i++)
    {
        if (stoi(Tools[i][0]) == tool)
        {
            return true;
        }
    }
    return false;
}

// CHECK IF TOOL EXIST
string GetUsername()
{
    for (int i = 0; i < Account.size(); i++)
    {
        if (stoi(Account[i][0]) == idAccount)
        {
            return Account[i][1];
        }
    }
}

// CHECK IF TOOL EXIST
bool GetEmail(string email)
{
    for (int i = 0; i < Account.size(); i++)
    {
        if (Account[i][2] == email)
        {
            return true;
        }
    }
}

bool isNumber(string number)
{
    regex regex_number("((\\b[0-9]+)?\\.)?[0-9]+\\b");
    bool isNumber = regex_match(number, regex_number);

    if (isNumber)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Login();
void Register();

// MENDISPLAY LIST LAPANGAN YANG TERDAPAT DI CLASS LAPANGAN
void ListLapangan(int &lap)
{
    cout << "================= DAFTAR LAPANGAN =================" << endl;

    for (int i = 0; i < Lapangans.size(); i++)
    {
        cout << i + 1 << ". " << Lapangans[i][1] << " - ID: " << Lapangans[i][0]
             << "\nRp. " << currencyFormatter(stoi(Lapangans[i][2])) << "/Jam" << endl;
    }
    do
    {
        cout << "===================================================" << endl;
        cout << "Pilih ID lapangan" << endl;
        cin >> lap;
        if (!isNumber(to_string(lap)))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (!GetLapangan(lap))
        {
            cout << "Data lapangan tidak tersedia untuk ID tersebut!" << endl;
        }
    } while (isNumber(to_string(lap)) != true || GetLapangan(lap) != true);
}

// MEMBUAT LIST PERLENGKAPAN DARI CLASS TOOLS
void ListTool(int &tool, int &jmlTool)
{
    cout << "================= DAFTAR PERLENGKAPAN =================" << endl;
    for (int i = 0; i < Tools.size(); i++)
    {
        cout << i + 1 << ". " << Tools[i][1] << " - ID: " << Tools[i][0] << "\nRp. "
             << currencyFormatter(stoi(Tools[i][2])) << "/ " << Tools[i][3] << "pcs" << endl;
    }
    do
    {
        cout << "=======================================================" << endl;
        cout << "Pilih ID perlengkapan atau 0 untuk tidak meminjam perlengkapan" << endl;
        cout << "ID\t: ";
        cin >> tool;
    } while (GetTool(tool) != true);

    if (tool != 0)
    {
        do
        {
            cout << "=======================================================" << endl;
            cout << "Masukan jumlah yang ingin disewa\t: ";
            cin >> jmlTool;
            if (isNumber(to_string(jmlTool)) && jmlTool > stoi(Tools[tool - 1][4]))
            {
                cout << "Jumlah barang yang disewa melebihi stok kami" << endl;
            }
            else if (jmlTool < 1)
            {
                cout << "Inputan tidak sesuai!" << endl;
            }
            else if (!isNumber(to_string(jmlTool)))
            {
                cout << "Hanya menerima angka!" << endl;
            }
        } while (isNumber(to_string(jmlTool)) != true || jmlTool < 1 || jmlTool > stoi(Tools[tool - 1][4]));
    }
}

// MENGAMBIL INPUTAN LAPANGAN YANG USER MAU
void getLap(int lap, int &dur)
{
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == lap)
        {
            system("CLS");
            cout << "================== DETIL LAPANGAN =================" << endl;
            cout << Lapangans[i][1] << endl;
            cout << "Rp. " << currencyFormatter(stoi(Lapangans[i][2])) << "/Jam\n\n";
            cout << "INFO :" << endl;
            cout << "Belum termasuk perlengkapan " << endl;
            cout << "===================================================" << endl;
            do
            {
                cout << "Maksimal bermain 24 Jam " << endl;
                cout << "Durasi bermain (jam): ";
                cin >> dur;
                if (!isNumber(to_string(dur)))
                {
                    cout << "Hanya menerima angka!" << endl;
                }
                else if (dur <= 0 || dur >= 24)
                {
                    cout << "Inputan tidak sesuai, kurang dari 0 jam atau lebih dari 24 jam!" << endl;
                }
            } while (isNumber(to_string(dur)) != true || dur <= 0 || dur >= 24);
            break;
        }
    }
}

// MENDISPLAY DETIL TRANSAKSI YANG TELAH DILAKUKAN
void getDetail(int lap, int tool, int jmlTool, int dur)
{
    int totalTools = 0, totalAll, pay;
    for (int i = 0; i < Lapangans.size(); i++)
    {
        if (stoi(Lapangans[i][0]) == lap)
        {
            system("CLS");
            cout << "================== DETIL TRANSAKSI =================" << endl;
            cout << Lapangans[i][1] << endl;
            cout << "Rp. " << currencyFormatter(stoi(Lapangans[i][2])) << "/Jam\n";
            // cout << Lapangans[i]->desc << "\n\n";
            cout << "INFO :" << endl;
            cout << "Belum termasuk perlengkapan " << endl;
            cout << "Durasi bermain\t: " << dur << " Jam" << endl;
            cout << "Perlengkapan\t: " << endl;
            for (int j = 0; j < Tools.size(); j++)
            {
                int num = 1;
                if (stoi(Tools[j][0]) == tool)
                {
                    totalTools += stoi(Tools[i][2]) * jmlTool;
                    cout << num << ". " << Tools[j][1] << " - " << currencyFormatter(stoi(Tools[i][2])) << " x " << jmlTool << endl;
                    num++;
                }
            }
            cout << endl;
            totalAll = totalTools + (stoi(Lapangans[i][2]) * dur);
            cout << "========================TOTAL=======================" << endl;
            cout << "Lapangan\t: "
                 << "Rp. " << currencyFormatter(stoi(Lapangans[i][2])) << " x " << dur << " Jam" << endl;
            cout << "Perlengkapan\t: "
                 << "Rp. " << currencyFormatter(totalTools) << endl;
            cout << "Total harga\t: "
                 << "Rp. " << currencyFormatter(totalAll) << endl;
            cout << "====================================================" << endl;
            cout << "Ketik 1 untuk membayar!" << endl;
            do
            {
                cin >> pay;
                if (!isNumber(to_string(pay)))
                {
                    cout << "Hanya menerima angka!" << endl;
                }
                else if (pay != 1)
                {
                    cout << "Inputan tidak sesuai!" << endl;
                }
            } while (isNumber(to_string(pay)) != true || pay != 1);

            Transactions.push_back({to_string(Transactions.size() + 1), to_string(idAccount), to_string(lap), to_string(tool), to_string(jmlTool), to_string(dur), "Berhasil"});
            cout << "====================== HASIL ======================" << endl;
            cout << "Pembayaran berhasil dilakukan!" << endl;
            system("pause");
            // PrintTransaction(lap, tool, Tools, dur, Lapangans, totalTools, totalAll);
        }
    }
}

void GetListTransaction(int lap, int tool, int jmlTool, int dur)
{
    int tr = 0, totalLap, totalTool;
    system("CLS");
    cout << "====================== DAFTAR TRANSAKSI ======================" << endl;
    for (int j = 0; j < Account.size(); j++)
    {
        if (stoi(Account[j][0]) == idAccount)
        {
            for (int i = 0; i < Transactions.size(); i++)
            {
                if (stoi(Transactions[i][1]) == idAccount)
                {
                    tr++;
                    cout << "Transaksi\t: " << tr << endl;
                    for (int a = 0; a < Lapangans.size(); a++)
                    {
                        if (stoi(Lapangans[a][0]) == lap)
                        {
                            totalLap = stoi(Lapangans[a][2]) * dur;
                            cout << Lapangans[a][1] << " - " << currencyFormatter(stoi(Lapangans[a][2])) << endl;
                        }
                    }
                    cout << "Durasi bermain\t " << dur << " Jam" << endl;
                    cout << "Perlengkapan\t: " << endl;
                    // {"1", "Cone", "10000", "5", "100"}
                    for (int b = 0; b < Tools.size(); b++)
                    {
                        if (stoi(Tools[b][0]) == tool)
                        {
                            totalTool = stoi(Tools[b][2]) * jmlTool;
                            cout << Tools[b][1] << "x" << jmlTool << " - " << currencyFormatter(stoi(Tools[b][2]) * jmlTool) << endl;
                        }
                    }
                    cout << "====================== TOTAL ======================" << endl;
                    cout << "Lapangan\t: "
                         << "Rp. " << currencyFormatter(totalLap) << endl;
                    cout << "Perlengkapan\t: "
                         << "Rp. " << currencyFormatter(totalTool) << endl;
                    cout << "Total harga\t: "
                         << "Rp. " << currencyFormatter(totalLap + totalTool) << endl;
                    cout << "====================================================" << endl;
                }
            }
        }
        break;
    }

    if (tr == 0)
    {
        cout << "Anda belum memiliki transaksi!" << endl;
    }
}

int lap = 0, tool = 0, jmlTool = 0, timed = 0;
void CreateSewa()
{
    system("CLS");
    ListLapangan(lap);

    system("CLS");
    ListTool(tool, jmlTool);

    system("CLS");
    getLap(lap, timed);

    system("CLS");
    getDetail(lap, tool, jmlTool, timed);
}

int MainMenu()
{
    int choice;

    system("CLS");
    cout << "Halo " << GetUsername() << "! Selamat datang kembali!" << endl;
    cout << "================== PILIH MENU ==================" << endl;
    cout << "1. Sewa lapangan\n"
         << "2. Riwayat sewa\n"
         << "3. Logout\n";
    cout << "================================================" << endl;
    cout << "Pilih Menu\t: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        CreateSewa();
        system("pause");
        break;
    case 2:
        GetListTransaction(lap, tool, jmlTool, timed);
        system("pause");
        break;
    case 3:
        isLogin = false;
        idAccount = ' ';
        cout << "Anda berhasil logout!" << endl;
        system("pause");
        Login();
        break;
    default:
        cout << "Pilihan tidak ada" << endl;
        system("pause");
        break;
    }
    return MainMenu();
}

int GetAccount(string username, string password)
{
    for (int i = 0; i < Account.size(); i++)
    {
        if (username == Account[i][1] && password == Account[i][3])
        {
            idAccount = stoi(Account[i][0]);
            return 1;
        }
        else if (i + 1 == Account.size())
        {
            if (username == "" || password == "")
            {
                return 3;
            }
            else if (username != Account[i][1] || password != Account[i][3])
            {
                return 2;
            }
        }
    }
}

void Login()
{
    int ResultGA = 0, a = 5;
    string username = "", password = "";

    do
    {
        if (a > 1)
        {
            system("CLS");
            cout << "================== LOGIN RESERVASI FUTSAL ==================" << endl;
            cout << "Silahkan login terlebih dahulu" << endl;
            cout << "Username\t: ";
            // cin.ignore();
            // getline(cin, username);
            cin >> username;
            cout << "Password\t: ";
            // cin.ignore();
            // getline(cin, password);
            cin >> password;
            ResultGA = GetAccount(username, password);

            if (ResultGA == 1)
            {
                isLogin = true;
                cout << endl;
                cout << "Login sukses!" << endl;
                system("pause");
                MainMenu();
                break;
            }
            else if (ResultGA == 2)
            {
                cout << "Username atau Password anda salah!" << endl;
                cout << "Kesempatan anda tersisa " << a - 1 << " kali lagi" << endl;
                system("pause");
            }
            else if (ResultGA == 3)
            {
                cout << "Username atau Password tidak boleh kosong!" << endl;
                cout << "Kesempatan anda tersisa " << a - 1 << " kali lagi" << endl;
                system("pause");
            }
        }
        else
        {
            system("CLS");
            cout << "Anda telah 5 kali gagal, coba lain kali" << endl;
            system("pause");
        }
        a--;
    } while (a != 0);
}

void Register()
{
    string id = to_string(Account.size() + 1), username = "", email = "", password = "", confpassword = "";
    int all;

    do
    {
        system("CLS");
        cout << "================== REGISTRASI ===================" << endl;
        cout << "===================== INFO ======================" << endl;
        cout << "= 1. Username tidak boleh mengandung spasi\t=" << endl;
        cout << "= 2. E-mail tidak boleh sama\t\t\t=" << endl;
        cout << "= 3. Password minimal 8 karakter\t\t=" << endl;
        cout << "=================================================\n\n";
        cout << "Masukan username\t: ";
        cin.ignore();
        getline(cin, username);
        // DELETING WHITESPACE
        username.erase(std::remove_if(username.begin(), username.end(), ::isspace),
                       username.end());

        do
        {
            cout << "Masukan e-mail\t\t: ";
            cin >> email;
            if (GetEmail(email))
            {
                cout << "E-mail sudah digunakan!" << endl;
            }
        } while (GetEmail(email) != false);

        int confirmed = 0;
        do
        {
            confirmed = 0;
            cout << "Masukan password\t: ";
            cin >> password;
            if (password.length() < 8)
            {
                confirmed++;
                cout << "Password tidak boleh kurang dari 8 karakter!" << endl;
            }
        } while (confirmed > 0);

        do
        {
            confirmed = 0;
            cout << "Masukan konfirmasi password\t: ";
            cin >> confpassword;
            if (password != confpassword)
            {
                confirmed++;
                cout << "Password dengan konfirmasi password tidak cocok!" << endl;
            }
        } while (confirmed > 0);

    } while (all != false);
    Account.push_back({id, username, email, password});
    cout << endl;
    cout << "Anda berhasil registrasi!" << endl;
    system("pause");
    Login();
}

int main()
{
    // MEMBUAT DATA DARI CLASS TOOLS
    string lanjut;
    system("CLS");
    cout << "================== APLIKASI RESERVASI FUTSAL ==================" << endl;
    cout << "Masukan 1 untuk registrasi akun, 2 untuk login" << endl;
    do
    {
        cin >> lanjut;
        if (!isNumber(lanjut))
        {
            cout << "Hanya menerima angka!" << endl;
        }
        else if (stoi(lanjut) < 1 || stoi(lanjut) > 2)
        {
            cout << "Inputan tidak sesuai!" << endl;
        }
    } while (isNumber(lanjut) != true || stoi(lanjut) < 1 || stoi(lanjut) > 2);

    if (stoi(lanjut) == 1)
    {
        Register();
    }
    else
    {
        if (!isLogin)
        {
            Login();
        }
    }

    system("pause");
    return 0;
}