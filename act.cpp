#include <iostream>

using namespace std;

const int TAM = 5;

enum
{
    AGREGAR = 1,
    BUSCAR,
    ELIMINAR,
    INSERTAR,
    MOSTRAR,
    ORDENAR,
    SALIR,
};

class Alumno
{
    public:
        Alumno() : nombre(""), carrera(""), nombrePreparatoria(""), promedio(0.0) {}
        Alumno(string nombre, string carrera, string nombrePreparatoria, float promedio) : nombre(nombre), carrera(carrera), nombrePreparatoria(nombrePreparatoria), promedio(promedio) {}

        friend istream& operator >> (istream& in, Alumno& i)
        {
            cout << endl << "Ingrese el nombre del Alumno: ";
            in.ignore();
            getline(in, i.nombre);

            cout << "Ingrese el nombre de la carrera del Alumno: ";
            getline(in, i.carrera);

            cout << "Ingrese el nombre le la preparatoria procedente del Alumno: ";
            getline(in, i.nombrePreparatoria);

            cout << "Ingrese el promedio general del Alumno: ";
            in >> i.promedio;

            return in;
        }

        friend ostream& operator << (ostream& out, const Alumno& o)
        {
            out << endl << 
            "Nombre del Alumno: " << o.nombre << endl << 
            "Carrera del Alumno: " << o.carrera << endl << 
            "Preparatoria procedente: " << o.nombrePreparatoria << endl << 
            "Promedio del Alumno: " << o.promedio << endl;

            return out;
        }

        Alumno& operator=(const Alumno& a)
        {
            nombre = a.nombre;
            carrera = a.carrera;
            nombrePreparatoria = a.nombrePreparatoria;
            promedio = a.promedio;

            return *this;
        }

		bool operator==(const Alumno& a)
        {
            return promedio == a.promedio;
        }

        void mostrar() const
        {
            cout << endl << 
            "Nombre de Alumno: " << nombre << endl << 
            "Carrera del Alumno: " << carrera << endl << 
            "Preparatoria procedente: " << nombrePreparatoria << endl << 
            "Promedio del Alumno: " << promedio << endl;
        }

        string obtenerNombre() const
        {
            return nombre;
        }

        float obtenerPromedio() const
        {
            return promedio;
        }

    private:
        string nombre;
        string carrera;
        string nombrePreparatoria;
        float promedio;
};

class Lista
{
    public:
        Lista() : ult(-1), alumnos{} {}

        bool vacia() const
        {
            return ult == -1;
        }

        bool llena() const
        {
            return ult == TAM - 1;
        }

        void agregarAlumno(const Alumno& alumno)
        {
            if (llena()) {
                cout << endl << "Error: la lista de alumnos está llena." << endl;
            }
            else
            {
                ult++;
                alumnos[ult] = alumno;
                cout << endl << "Alumno agregado correctamente." << endl;
            }
        }

        void mostrarAlumnos() const
        {
            if (vacia())
            {
                cout << endl << "No hay alumnos para mostrar." << endl;
            }
            else
            {
                cout << endl << "Lista de Alumnos:" << endl;
                for (int i = 0; i <= ult; ++i)
                {
                    alumnos[i].mostrar();
                }
            }
        }

        void buscarAlumnos(string nombre) const
        {
            bool encontrado = false;
            for (int i = 0; i <= ult; ++i)
            {
                if (alumnos[i].obtenerNombre() == nombre)
                {
                    cout << endl << "Alumno encontrado:" << endl;
                    cout << alumnos[i];

                    encontrado = true;
                    break;
                }
            }
            if (!encontrado)
            {
                cout << endl << "Alumno no encontrado." << endl;
            }
        }

        void eliminarAlumno(string nombre)
        {
            bool encontrado = false;
            for (int i = 0; i <= ult; ++i)
            {
                if (alumnos[i].obtenerNombre() == nombre)
                {
                    for (int j = i; j < ult; ++j)
                    {
                        alumnos[j] = alumnos[j + 1];
                    }
                    ult--;
                    encontrado = true;
                    cout << endl << "Alumno eliminado correctamente." << endl;
                    break;
                }
            }
            if (!encontrado)
            {
                cout << endl << "Alumno no encontrado." << endl;
            }
        }

        void insertarAlumno(const Alumno& alumno, int pos)
        {
            if (llena())
            {
                cout << endl << "Error: la lista de Alumnos está llena." << endl;
            }
            else if (pos < 0 || pos > ult + 1)
            {
                cout << endl << "No se puede insertar en la posición especificada." << endl;
            }
            else
            {
                if (pos == ult + 1)
                {
                    alumnos[pos] = alumno;
                    ult++;
                    cout << endl << "Alumno insertado correctamente." << endl;
                }
                else
                {
                    for (int i = ult + 1; i > pos; --i)
                    {
                        alumnos[i] = alumnos[i - 1];
                    }
                    alumnos[pos] = alumno;
                    ult++;
                    cout << endl << "Empleado insertado correctamente." << endl;
                }
            }
        }

        void quicksort(int primero, int ultimo)
        {
            if (primero < ultimo)
            {
                int izquierda = primero;
                int derecha = ultimo;
                Alumno pivote = alumnos[(izquierda + derecha) / 2];

                do
                {
                    while (alumnos[izquierda].obtenerPromedio() > pivote.obtenerPromedio()) // Cambio aquí
                        izquierda++;
                    while (alumnos[derecha].obtenerPromedio() < pivote.obtenerPromedio()) // Cambio aquí
                        derecha--;

                    if (izquierda <= derecha)
                    {
                        Alumno temp = alumnos[izquierda];
                        alumnos[izquierda] = alumnos[derecha];
                        alumnos[derecha] = temp;
                        izquierda++;
                        derecha--;
                    }
                } while (izquierda <= derecha);

                quicksort(primero, derecha);
                quicksort(izquierda, ultimo);
            }
        }

        void ordenarAlumnos()
        {
            quicksort(0, ult);
        }


    private:
		Alumno alumnos[TAM];
		int ult;
};

int menu(int op)
{
	cout << endl << "Menu:" << endl << " " << 
    AGREGAR << ") Agregar Alumno" << endl << " " << 
    BUSCAR << ") Buscar Alumno" << endl << " " << 
    ELIMINAR << ") Eliminar Alumno" << endl << " " << 
    INSERTAR << ") Insertar Alumno" << endl << " " << 
    MOSTRAR << ") Mostrar Alumno" << endl << " " << 
    ORDENAR << ") Ordenar Alumnos" << endl << " " <<
    SALIR << ") Salir" << endl << 
    "Ingresa una opción: ";
    cin >> op;

	return op;
}

int main()
{
	int op;
    Lista lista;

	do
	{
		switch(menu(op))
		{
			case AGREGAR:
            {
                Alumno alumno;
                cin >> alumno;
				lista.agregarAlumno(alumno);
                break;
            }

			case BUSCAR:
			{
                string nombre;
                cout << endl << "Ingrese el nombre del Alumno a buscar: ";
                cin >> nombre;
                lista.buscarAlumnos(nombre);
                break;
			}

            case ELIMINAR:
            {
                string nombre;
                cout << endl << "Ingrese la clave del empleado a eliminar: ";
                cin >> nombre;
                lista.eliminarAlumno(nombre);
                break;
            }

            case INSERTAR:
            {
                int pos;
                cout << endl << "Ingrese la posición donde desea insertar el empleado: ";
                cin >> pos;
                Alumno alumno;
                cin >> alumno;
                lista.insertarAlumno(alumno, pos);
                break;
            }

            case MOSTRAR:
                lista.mostrarAlumnos();
                break;

            case ORDENAR:
            {
                Alumno alumno;
                lista.ordenarAlumnos();
                cout << endl << "Alumnos ordenados de mayor calificación a menor" << endl;
                lista.mostrarAlumnos();
                break;
            }

			case SALIR:
            {
				cout << endl << "Saliendo del programa..." << endl;
				return 0;
                break;
            }

			default:
            {
				cout << endl << "Orden no encontrada. Ingrese una orden correcta." << endl;
            }
		}
	} while (true);

    return 0;
}