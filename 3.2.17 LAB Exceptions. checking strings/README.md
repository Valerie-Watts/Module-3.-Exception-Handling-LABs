# README: 3.2.17 LAB Exceptions. checking strings

Este documento detalla el funcionamiento del programa C++ `3.2.17 LAB Exceptions. checking strings`, que valida una dirección IP y un rango de subred, utilizando excepciones para manejar entradas incorrectas.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

class ipAddress
{
private:
    std::string address; 

    bool check(const std::string& addr) {

        int number = 0;
        int counter = 0;
        bool hasDigit = false;

        for (char n : addr)
        {
            if (n != '.') {

                if (n < '0' || n > '9') {
                    return false;
                }

                int digit = n - '0';

                number = (number * 10 + digit);

                if (number > 255)
                {
                    return false;
                }
                hasDigit = true;
            }
            else
            {
                if (!hasDigit) {
                    return false;
                }

                counter++;
                number = 0;
                hasDigit = false;

            }
        }
        return hasDigit && number <= 255 && counter == 3;

    }

public:

	ipAddress(const std::string& addr) : address(addr) 
    {
		if (!check(addr)) { throw std::runtime_error("Exception - invalid IP number."); }
    }

	void printRange(int number) 
	{
        if (!(number > 0 && (number & (number - 1)) == 0)) {
			throw std::runtime_error("Exception - invalid range.");
		}

        int a, b, c, d;
        char dot;
        std::istringstream ss(address);
        ss >> a >> dot >> b >> dot >> c >> dot >> d;

        for (int i = 1; i <= number; i++) {
            // Nota: Esto no maneja correctamente el desbordamiento (ej. 192.168.1.255 + 2)
            // pero sigue la lógica del laboratorio.
            std::cout << a << "." << b << "." << c << "." << (d + i) << "\n";
        }
        std::cout << "\n";
	}

};

int main()
{
	std::string ip ; 
    int subnet;

	std::cin >> ip >> subnet;

    try
    {
		ipAddress ipAddr(ip);
		ipAddr.printRange(subnet);
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
    }
	
    return 0; 
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Entrada válida):**

Entrada:

```
192.168.1.1
4
```

Salida:

```
192.168.1.2
192.168.1.3
192.168.1.4
192.168.1.5

```

**Ejecución 2 (Entrada inválida - IP incorrecta):**

Entrada:

```
192.168.1.256
4
```

Salida:

```
Exception - invalid IP number.
```

**Ejecución 3 (Entrada inválida - Rango incorrecto, no es potencia de 2):**

Entrada:

```
192.168.1.1
5
```

Salida:

```
Exception - invalid range.
```

## Explicación del ejercicio

Este ejercicio demuestra el uso de excepciones para la validación de entradas complejas en diferentes etapas. La clase `ipAddress` realiza dos validaciones críticas que pueden lanzar excepciones.

Primero, la validación de la IP ocurre *dentro del constructor*. El constructor llama al método privado `check`, que analiza meticulosamente el string para asegurar que contenga solo dígitos y tres puntos, y que cada número esté entre 0 y 255. Si `check` devuelve `false`, el constructor "lanza" (`throw`) una `std::runtime_error` ("invalid IP number"). Esto previene que un objeto `ipAddress` pueda ser creado en un estado inválido.

Segundo, el método `printRange` valida *su propio* argumento `number`. Utiliza una comprobación bitwise (`(number & (number - 1)) == 0`) para asegurar que el rango sea una potencia de 2. Si no lo es, "lanza" una `std::runtime_error` diferente ("invalid range.").

En `main`, el bloque `try` envuelve *ambas* operaciones: la creación del objeto `ipAddress ipAddr(ip)` (que puede fallar) y la llamada al método `ipAddr.printRange(subnet)` (que también puede fallar). El único bloque `catch (std::runtime_error& e)` es capaz de capturar *cualquiera* de las dos excepciones. Si la creación del objeto falla, el `catch` se activa inmediatamente. Si la creación tiene éxito pero `printRange` falla, el `catch` se activa de igual manera, demostrando un manejo de errores robusto y unificado.
