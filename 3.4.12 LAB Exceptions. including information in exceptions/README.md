# README: 3.4.12 LAB Exceptions. including information in exceptions

Este documento detalla el funcionamiento del programa C++ `3.4.12 LAB Exceptions. including information in exceptions`, que valida múltiples entradas en un constructor y utiliza el mensaje de la excepción para especificar qué validación falló.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>
#include <stdexcept>

class ipAddress
{
private:
    std::string address1, address2;

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

	ipAddress(const std::string& addr1, const std::string& addr2) : address1(addr1), address2(addr2)
    {
        if (!check(addr1)) { throw std::runtime_error("Invalid IP Header - Source IP Address is invalid."); }
        if (!check(addr2)) { throw std::runtime_error("Invalid IP Header - Source IP Address is invalid."); }
		std::cout << "Valid IP Header.\n";
    }

    

};

int main()
{
    std::string ip1, ip2; 

	std::cin >> ip1 >> ip2;

    try {
		ipAddress ipAddr(ip1, ip2);
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
10.0.0.1
```

Salida:

```
Valid IP Header.
```

**Ejecución 2 (Entrada inválida - Primera IP incorrecta):**

Entrada:

```
192.168.1.256
10.0.0.1
```

Salida:

```
Invalid IP Header - Source IP Address is invalid.
```

**Ejecución 3 (Entrada inválida - Segunda IP incorrecta):**

Entrada:

```
192.168.1.1
10.0.0.999
```

Salida:

```
Invalid IP Header - Source IP Address is invalid.
```

## Explicación del ejercicio

Este ejercicio se enfoca en cómo las excepciones pueden transportar información contextual específica sobre un error. La clase `ipAddress` toma dos direcciones IP (fuente y destino) en su constructor y debe validarlas ambas antes de que el objeto se cree con éxito.

El constructor utiliza el mismo método privado `check` de laboratorios anteriores. Primero, valida `addr1`. Si falla, "lanza" (`throw`) una `std::runtime_error` con un mensaje muy específico: `"Invalid IP Header - Source IP Address is invalid."`. Si la primera IP es válida, procede a chequear `addr2`. Si esta segunda validación falla, lanza otra `std::runtime_error`.

En `main`, una única llamada al constructor `ipAddress(ip1, ip2)` está envuelta en un bloque `try`. Si *cualquiera* de las validaciones dentro del constructor falla, el constructor se detiene y la excepción es capturada por el bloque `catch`. Lo importante aquí es que el bloque `catch` imprime `e.what()`, que muestra el mensaje exacto proporcionado por el `throw`. Esto le dice al usuario no solo *que* hubo un error ("Invalid IP Header"), sino *cuál* fue el error ("Source IP Address is invalid"). Si ambas validaciones pasan, la construcción se completa y se imprime "Valid IP Header."
