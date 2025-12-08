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
    //Usamos un numero enorme para usar solo numeros positivos
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
	    //Cuenta cuántos múltiplos de 100 hay en (old, new]
            zeros += (pos / 100) - (old_pos / 100);
        } 
        else if (dir == 'L')
       	{
            pos -= pasos;
	    //Cuenta multiplos entre variables
	    //Restamos 1 para evitar que haga cuentas extra en el total
	    //si partimos del 0 y lo incluimos en el nuevo por si vuelve
	    //a pararse en 0.
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
