/******************************************************************************

PROYECTO MIGUEL RAFAEL FONSECA SANDOVAL 32211118
CONTROL DE ESTACIONAMIENTO

*******************************************************************************/

// LIBRERIAS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>

// using namespace std;

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fixed;
using std::fstream;
using std::ios;
using std::left;
using std::ofstream;
using std::right;
using std::setprecision;
using std::setw;
using std::showpoint;
using std::string;

class ESTACIONAMIENTO
{
  // ATRIBUTOS
private:
  string codAuto;
  double precioPorHora;

  // CONSTRUCTOR
public:
  ESTACIONAMIENTO(string newCodAuto, double newPrecioPorHora)
  {
    setCodAuto(newCodAuto);
    setPrecioPorHora(newPrecioPorHora);
  }

  // METODOS SETTERS

  void setCodAuto(string newCodAuto)
  {
    codAuto = newCodAuto;
  }

  void setPrecioPorHora(double newPrecioPorHora)
  {
    precioPorHora = newPrecioPorHora;
  }

  // METODOS GETTERS

  string getCodAuto()
  {
    return codAuto;
  }

  double getPrecioPorHora()
  {
    return precioPorHora;
  }

}; // FIN DE LA CLASE ESTACIONAMIENTO

class REGISTRO : public ESTACIONAMIENTO
{ // CLASE REGISTRO HEREDADA DE CLASE ESTACIONAMIENTO
  // ATRIBUTOS
private:
  string fecha;
  int horaDeEntrada;
  int minutosEntrada;
  int horaDeSalida;
  int minutosSalida;
  double precioTotal;

  // METODOS SETTERS
public:
  void setFecha(string newFecha)
  {
    fecha = newFecha;
  }

  void setHoraDeEntrada(int newHoraDeEntrada)
  {
    horaDeEntrada = newHoraDeEntrada;
  }
  void setMinutosDeEntrada(int newMinutosDeEntrada)
  {
    minutosEntrada = newMinutosDeEntrada;
  }

  void setHoraDeSalida(int newHoraDeSalida)
  {
    horaDeSalida = newHoraDeSalida;
  }
  void setMinutosDeSalida(int newMinutosDeSalida)
  {
    minutosSalida = newMinutosDeSalida;
  }

  // METODOS GETTERS
  string getFecha()
  {
    return fecha;
  }

  int getHoraDeEntrada()
  {
    return horaDeEntrada;
  }
  int getMinutosDeEntrada()
  {
    return minutosEntrada;
  }

  int getHoraDeSalida()
  {
    return horaDeSalida;
  }
  int getMinutosDeSalida()
  {
    return minutosSalida;
  }
  // CONSTRUCTOR

  REGISTRO(string newCodAuto, double newPrecioPorHora, string newFecha, int newHoraDeEntrada, int newminutosEntrada, int newHoraDeSalida, int newMinutosDeSalida) : ESTACIONAMIENTO(newCodAuto, newPrecioPorHora)
  {
    setFecha(newFecha);
    setHoraDeEntrada(newHoraDeEntrada);
    setMinutosDeEntrada(newminutosEntrada);
    setHoraDeSalida(newHoraDeSalida);
    setMinutosDeSalida(newMinutosDeSalida);
  }

  // FUNCION QUE CALCULA EL PRECIO DEL COSTO POR EL ESATCIONAMIENTO BASADO EN LAS HORAS PASADAS
  void calcularPrecio()
  {
    double entrada, salida;
    entrada = ((getHoraDeEntrada() * 60) + getMinutosDeEntrada());
    salida = (((getHoraDeSalida() * 60)) + getMinutosDeSalida());

    precioTotal = getPrecioPorHora() * ((salida - entrada) / 60);
  }

  // FUNCION PARA RECUPERAR LOS DATOS
  void getDatos()
  {
    calcularPrecio();

    cout << left << setw(10) << getFecha()
         << setw(6) << getCodAuto()
         << setw(6) << fixed << setprecision(2) << getPrecioPorHora()
         << right << setw(5) << horaDeEntrada << ":" << setw(2) << minutosEntrada
         << setw(5) << horaDeSalida << ":" << setw(2) << minutosSalida
         << setw(7) << setprecision(2) << precioTotal << endl;
  }

}; // FIN DE LA CLASE REGISTRO

void descripColumnas()
{
  cout << setw(10) << left << "Fecha" << setw(6) << left << "Cod" << setw(6) << left << "Prec" << setw(9) << right << "HoraEn" << setw(8) << right << "HoraSa" << setw(6) << right << "Total" << setw(6) << endl;
}

int main()
{

  double precio;
  int hhEntrada, minEntrada, hhSalida, minSalida, opcion;
  char res = 'S';
  string codBuscar, codigo, fecha;
  REGISTRO ingreso("", 0.0, "", 0, 0, 0, 0);

  fstream archivo("Estacionamiento.dat", ios::in | ios::out | ios::binary);

  if (!archivo)
  {
    cerr << "No se puede abrir el archivo!";
    return 1;
  }

  while ((res == 'S') || (res == 's'))
  {
    cout << " \n";
    cout << " ** MENU DE OPCIONES ** \n";
    cout << " 1. Ingresar nuevo Auto \n";
    cout << " 2. Leer archivos de Registros de Autos \n";
    cout << " 3. Consulta de Registro de autos \n";
    cout << " 4. Actualizacion de Registro de autos \n";
    cout << " 5. Borrado de Registro de autos \n";
    cout << " Ingrese su opcion: ";
    cin >> opcion;

    // string codigo, fecha;

    switch (opcion)
    {
    case 1:

      cout << "**Ingresar Nuevo Registro**" << endl;

      cout << "Ingrese el codigo del Auto: " << endl;
      cin >> codigo;

       archivo.clear();
  archivo.seekg(0, ios::beg);
  while (archivo.read(reinterpret_cast<char *>(&ingreso), sizeof(REGISTRO)))
  {
    if (ingreso.getCodAuto() == codigo)
    {
     cout<< "El codigo ingresado ya existe por favor escriba otro codigo\n";
      break;
    }else{

      cout << "Ingrese la Fecha con formato (dd/mm/aa): " << endl;
      cin >> fecha;
      cout << "Ingrese el precio del estacionamiento: " << endl;
      cin >> precio;
      cout << "Ingrese la hora de entrada del auto con formato (HH MM) EJEMPLO(14 25):" << endl;
      cin >> hhEntrada >> minEntrada;
      cout << "Ingrese la hora de salida del auto con formato (HH MM) EJEMPLO(18 00): " << endl;
      cin >> hhSalida >> minSalida;

      ingreso = REGISTRO(codigo, precio, fecha, hhEntrada, minEntrada, hhSalida, minSalida);

      cout << "Cada registro de cite Medira: " << sizeof(REGISTRO) << endl;

      archivo.clear();

      archivo.seekp(0, ios::end);

      archivo.write(reinterpret_cast<const char *>(&ingreso), sizeof(REGISTRO));

    }
  }

      
      break;

    case 2:

      cout << " Leer Archivo" << endl;

      descripColumnas();

      archivo.clear();
      archivo.seekg(0, ios::beg);

      while (archivo.read(reinterpret_cast<char *>(&ingreso), sizeof(REGISTRO)))
      {

        if (ingreso.getCodAuto() != "") // Verifica si el código de auto no es una cadena vacía
        {
          ingreso.getDatos(); // Imprimir los datos leídos
        }
      }

      break;

    case 3:
      cout << "Buscar Registro Por Codigo" << endl;
      cout << "Ingrese el codigo a buscar" << endl;
      cin >> codBuscar;

      archivo.clear();
      archivo.seekg(0, ios::beg);

      while (archivo.read(reinterpret_cast<char *>(&ingreso), sizeof(REGISTRO)))
      {
        if (ingreso.getCodAuto() == codBuscar)
        {
          cout << "Se encontro el codigo buscado" << endl;
          descripColumnas();
          ingreso.getDatos();
        }else{
          cout << "No se encontro el codigo buscado" << endl;
        }
      }

      break;

    case 4:
      cout << "Buscar Registro Por Codigo" << endl;
      cout << "Ingrese el codigo a buscar" << endl;
      cin >> codBuscar;

      archivo.clear();
      archivo.seekg(0, ios::beg);

      while (archivo.read(reinterpret_cast<char *>(&ingreso), sizeof(REGISTRO)))
      {
        if (ingreso.getCodAuto() == codBuscar)
        {
          cout << "Se encontro el codigo buscado" << endl;
          descripColumnas();
          ingreso.getDatos();

          cout << "**Actualizar Registro de Codigo de Auto: #" << ingreso.getCodAuto() << " rellenando los siguientes datos**" << endl;

          cout << "Ingrese la Fecha con formato (dd/mm/aa): " << endl;
          cin >> fecha;
          cout << "Ingrese el precio del estacionamiento: " << endl;
          cin >> precio;
          cout << "Ingrese la hora de entrada del auto con formato (HH MM) EJEMPLO(14 25):" << endl;
          cin >> hhEntrada >> minEntrada;
          cout << "Ingrese la hora de salida del auto con formato (HH MM) EJEMPLO(18 00): " << endl;
          cin >> hhSalida >> minSalida;

          ingreso.setPrecioPorHora(precio);
          ingreso.setFecha(fecha);
          ingreso.setHoraDeEntrada(hhEntrada);
          ingreso.setMinutosDeEntrada(minEntrada);
          ingreso.setHoraDeSalida(hhSalida);
          ingreso.setMinutosDeSalida(minSalida);

          // Mover el cursor al principio del registro
          archivo.seekp(-static_cast<int>(sizeof(REGISTRO)), ios::cur);

          // Escribir los datos actualizados en el archivo
          archivo.write(reinterpret_cast<const char *>(&ingreso), sizeof(REGISTRO));

          cout << "Registro actualizado exitosamente." << endl;
        }
      }

      break;

    case 5:
      cout << "Eliminar Registro Por Codigo" << endl;
      cout << "Ingrese el codigo a eliminar" << endl;
      cin >> codBuscar;

      archivo.clear();
      archivo.seekg(0, ios::beg);

      while (archivo.read(reinterpret_cast<char *>(&ingreso), sizeof(REGISTRO)))
      {
        if (ingreso.getCodAuto() == codBuscar)
        {
          cout << "Se encontro el codigo buscado" << endl;
          descripColumnas();
          ingreso.getDatos();

          // Establecer todos los valores del registro a cero o al valor predeterminado
          ingreso.setCodAuto("");
          ingreso.setPrecioPorHora(0.0);
          ingreso.setFecha("");
          ingreso.setHoraDeEntrada(0);
          ingreso.setMinutosDeEntrada(0);
          ingreso.setHoraDeSalida(0);
          ingreso.setMinutosDeSalida(0);
          ingreso.calcularPrecio(); // Recalcular el precio (opcional)

          // Mover el cursor al principio del registro
          archivo.seekp(-static_cast<int>(sizeof(REGISTRO)), ios::cur);

          // Escribir los datos actualizados en el archivo
          archivo.write(reinterpret_cast<const char *>(&ingreso), sizeof(REGISTRO));

          cout << "Registro eliminado exitosamente." << endl;
        }
      }

      break;

    default:
      cout << "Error" << endl;
      break;
    }

    if ((opcion >= 1) && (opcion <= 5))
    {
      cout << "Desea continuar (S/N) ? " << endl;
      cin >> res;
    }
  }

  archivo.close();
  std::cout << "Archivo binario creado exitosamente." << std::endl;

  system("pause"); // USADO PARA MANTENER EL PROGRAMA ABIERTO EN LA CONSOLA DE COMANDOS
  return 0;
}
