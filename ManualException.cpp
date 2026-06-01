#include <iostream>
using namespace std;

int main()
{
    //membuat isi dari try untuk pengujian error
    try
    {
        cout << "Selamat belajar di prodi TI UMY" << endl;
        //throw 0.5; //melemparkan sebuah integer maka
        cout << "Pernyataan tidak akan dtampilkan" << endl;
    }
    //kondisi jika throw yang bertipe data integer
    catch (int e)
    {
        cout << "Pengecualian akan dieksekusi"<< endl;
    }
    //kondisi jika throw yang bertipe data selain integer
    catch (...)
    {
        cout << "default Pengecualian dieksekusi" << endl;
    }
    return 0;
}