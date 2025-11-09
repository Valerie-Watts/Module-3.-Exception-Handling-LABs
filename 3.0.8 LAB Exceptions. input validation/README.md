# README: 3.0.8 LAB Exceptions. Input Validation

Este documento detalla el funcionamiento del programa C++ `3.0.8 LAB Exceptions. input validation.cpp`, enfocado en el manejo de excepciones para validar la entrada del usuario.

## Captura de pantalla del código

```cpp
#include <iostream>

const bool divZero = true;

int main()
{
	int a = 8, b = 0, c = 0;
	std::cout << "Enter a divisor: \n";
	std::cin >> b;

	try {
		
		if (b == 0) {
			throw divZero;
		}
		c = a / b;
	}
	catch (bool isZero)	
	{
		std::cout << "Your input is not valid, you can't divide by zero. \n";

	}

	std::cout << c << "\n";

	return 0;	
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Entrada válida):**

```
Enter a divisor: 
4
2
```

**Ejecución 2 (Entrada válida - División por cero):**

```
Enter a divisor: 
0
Your input is not valid, you can't divide by zero. 
0
```

## Explicación del ejercicio

El objetivo de este ejercicio es demostrar el manejo básico de excepciones en C++ para prevenir un error crítico en tiempo de ejecución: la división por cero. El programa inicializa dos enteros, `a` (numerador) y `b` (divisor), y una variable `c` para el resultado. Solicita al usuario que ingrese un valor para el divisor `b`. La lógica central se encuentra dentro de un bloque `try`, que monitorea el código propenso a errores. Dentro de este bloque, una instrucción `if` evalúa si el divisor `b` ingresado por el usuario es igual a cero. Si lo es, el programa "lanza" (`throw`) una excepción, en este caso, el valor booleano `divZero` (que es `true`). Si `b` no es cero, la división se realiza de forma segura. Inmediatamente después del bloque `try`, un bloque `catch (bool isZero)` está diseñado para "atrapar" específicamente una excepción de tipo `bool`. Si la excepción fue lanzada (porque `b` era cero), este bloque se ejecuta, imprimiendo un mensaje de error claro al usuario. Crucialmente, el programa no se detiene abruptamente. Note que si se captura la excepción, la variable `c` nunca se actualiza y conserva su valor inicial de 0, que se imprime al final. Esto demuestra cómo `try-catch` permite al programa manejar un error grave (división por cero) de manera controlada, informar al usuario y continuar su ejecución hasta el final.
