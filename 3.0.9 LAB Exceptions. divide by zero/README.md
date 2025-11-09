# README: 3.0.9 LAB Exceptions. divide by zero

Este documento detalla el funcionamiento del programa C++ `3.0.9 LAB Exceptions. divide by zero`, que demuestra la creación y uso de una clase de excepción personalizada.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>

class DivideByZeroException 
{
public:
    const char* what() const throw() 
    {
        return "Your input is not valid, you can't divide by zero.";
    }
};

int main(void)
{
    int numerator, denominator;
    std::cout << "Enter numerator: ";
    std::cin >> numerator;
    std::cout << "Enter denominator: ";
    std::cin >> denominator;

    try {
        if (denominator == 0) {
            throw DivideByZeroException();
        }

        int result = numerator / denominator; 
        std::cout << "Result: " << result << "\n";

        return 0;
    }
    catch (DivideByZeroException& e)
    {
        std::cout << e.what() << std::endl;
    }

}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Entrada válida):**

```
Enter numerator: 10
Enter denominator: 2
Result: 5
```

**Ejecución 2 (Entrada inválida - División por cero):**

```
Enter numerator: 10
Enter denominator: 0
Your input is not valid, you can't divide by zero.
```

## Explicación del ejercicio

Este ejercicio avanza en el manejo de excepciones al definir una clase personalizada, `DivideByZeroException`. Esta clase encapsula el error específico de la división por cero y proporciona un método `what()` que devuelve un mensaje de error descriptivo, una práctica común en las clases de excepción de C++. El programa solicita al usuario un numerador y un denominador. La operación de división se sitúa dentro de un bloque `try`. Antes de realizar la división, una sentencia `if` comprueba si el `denominator` es cero. Si lo es, en lugar de lanzar un tipo primitivo como `bool`, el programa instancia y "lanza" (`throw`) un objeto de nuestra clase `DivideByZeroException`. Si el denominador no es cero, la división se completa y se muestra el resultado. El bloque `catch (DivideByZeroException& e)` está diseñado para "atrapar" específicamente objetos de este tipo de excepción. Cuando se captura, el programa accede al mensaje de error a través del método `e.what()` y lo imprime en la consola, proporcionando una retroalimentación clara y específica del error. Este enfoque es superior a lanzar tipos primitivos porque permite un manejo de errores más estructurado, escalable y orientado a objetos, permitiendo que el programa maneje el error de forma controlada sin terminar abruptamente.
