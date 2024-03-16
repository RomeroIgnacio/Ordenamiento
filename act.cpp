#include <iostream>

using namespace std;

const int TAM = 5;

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

class Cola
{
    public:
        Cola() : ult(-1), alumnos{} {}

        bool vacia() const
        {
            return ult == -1;
        }

        void encolar(const Alumno& alumno)
        {
            if (ult == TAM - 1)
            {
                cout << endl << "Cola llena. No se puede agregar el alumno." << endl;
                return;
            }
            else
            {
                ult++;
                alumnos[ult] = alumno;
                cout << endl << "Alumno agregado correctamente" << endl;
            }
        }

        void desencolar()
        {
            if (vacia())
            {
                cout << endl << "No hay constancias por hacer..." << endl;
            }
            else
            {
                cout << endl << "Alumno que recibe constancia: " << endl;
                alumnos[0].mostrar();

                for (int i = 1; i <= ult; i++)
                {
                    alumnos[i - 1] = alumnos[i];
                }

                ult--;
                cout << endl << "Constancia entregada correctamente" << endl;
            }
        }

		int buscar(string nombre)
		{
            for (int i = 0; i <= ult; i++)
            {
                if (alumnos[i].obtenerNombre() == nombre)
                {
                    return i;
                }
            }
            return -1;
        }

        void quicksort(int ult)
        {
            if (vacia())
            {
                cout << endl << "No hay Alumnos en la cola" << endl;
            }
            else
            {
                for (int i = 0; i < ult; i++)
                {
                    for (int j = 0; j < ult - i; j++) {
                        if (alumnos[j].obtenerPromedio() > alumnos[j + 1].obtenerPromedio())
                        {
                            Alumno temp = alumnos[j];
                            alumnos[j] = alumnos[j + 1];
                            alumnos[j + 1] = temp;
                        }
                    }
                }

                for (int i = 0; i <= ult; i++)
                {
                    alumnos[i].mostrar();
                }
            }
        }

        int obtenerUltimo()
        {
            return ult;
        }

	private:
		Alumno alumnos[TAM];
		int ult;
};

int menu(int op)
{
	cout << endl <<
    "Menu" << endl << 
    " 1) Dar de alta solicitud de Alumno" << endl << 
    " 2) Elaborar constancia" << endl << 
	" 3) Ordenar alumnos de menor a mayor calificación" << endl << 
    " 4) Buscar solicitud" << endl << 
    " 5) Salir" << endl << 
    "Ingresa una opción: ";
	cin >> op;

	return op;
}

int main()
{
	int op;
    Cola cola;

	do
	{
		switch(menu(op))
		{
			case 1:
            {
                Alumno alumno;
                cin >> alumno;
				cola.encolar(alumno);
                break;
            }

			case 2:
			{
                cola.desencolar();
                break;
			}

            case 3:
            {
                cola.quicksort(cola.obtenerUltimo());
                break;
            }

            case 4:
            {
                string nombre;
                cout << endl << "Ingrese el nombre del alumno a buscar: ";
                cin >> nombre;
                int posicion = cola.buscar(nombre);
                
                if (posicion != -1)
                {
                    int constanciasAntes = posicion;
                    cout << endl << "Número de constancias a elaborar antes de la solicitud del alumno: " << constanciasAntes << endl;
                }
                else
                {
                    cout << endl << "No se encontró ninguna solicitud con ese nombre." << endl << "Debe dar de alta una solicitud." << endl;
                }
                break;
            }

			case 5:
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