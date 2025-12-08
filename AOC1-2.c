#include <iostream>
#include <fstream>
#include <string>

void solve()
{
    std::ifstream file("datosAOC1.txt");
    if (!file.is_open())
    {
        std::cerr << "No se pudo abrir 'datosAOC1.txt'.\n";
        return;
    }

    long long pos = 1000000000000LL + 50; 
    long long zeros = 0;
    char dir;
    long long pasos;

    while (file >> dir >> pasos)
    {
        long long old_pos = pos;

        if (dir == 'R') 
	{
            pos += pasos;
            zeros += (pos / 100) - (old_pos / 100);
        } 
        else if (dir == 'L')
       	{
            pos -= pasos;
            zeros += ((old_pos - 1) / 100) - ((pos - 1) / 100);
        }
    }

    std::cout << "Password: " << zeros << std::endl;
}

int main() 
{
    solve();
    return 0;
}
