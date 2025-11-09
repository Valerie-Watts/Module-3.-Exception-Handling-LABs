# README: 3.1.8 LAB Exceptions. input validation

Este documento detalla el funcionamiento del programa C++ `3.1.8 LAB Exceptions. input validation`, que aísla la lógica de división y el lanzamiento de excepciones en una función separada.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <stdexcept>

const bool DivideByZero = true;

float internaldiv(float arg1, float arg2)
{
	if (0 == arg2)
		throw DivideByZero;
	return arg1 / arg2;
}


int main()
{
	float r, a, b;
	while (std::cin >> a) {
		std::cin >> b;
		try
		{
			r = internaldiv(a, b); 
			std::cout << r << "\n";
			return 0;

		}
		catch (bool exe)
		{
			std::cout << "Are you kidding me?" << "\n";
			std::cout << "Your input is not valid, you can't divide by zero."; 

			return 0;
		}

		
	}
	
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Entrada válida):**

Entrada:

```
10 5
```

Salida:

```
2
```

**Ejecución 2 (Entrada inválida - División por cero):**

Entrada:

```
10 0
```

Salida:

```
Are you kidding me?
Your input is not valid, you can't divide by zero.
```

## Explicación del ejercicio

El objetivo de este ejercicio es demostrar cómo una excepción "lanzada" (`throw`) desde una función anidada puede ser "atrapada" (`catch`) por un bloque en la función que la llamó. La lógica de la división se encapsula en la función `internaldiv(float arg1, float arg2)`. Esta función realiza la validación: si el `arg2` (divisor) es cero, lanza (`throw`) la constante booleana `DivideByZero`.

En la función `main`, se solicita al usuario dos números, `a` y `b`, dentro de un bucle `while`. La llamada a `internaldiv(a, b)` se coloca dentro de un bloque `try`. Si la función se ejecuta sin problemas (el divisor no es cero), se imprime el resultado `r` y el programa termina con `return 0`. Sin embargo, si `internaldiv` lanza la excepción `bool`, la ejecución normal del `try` se interrumpe y el control pasa al bloque `catch (bool exe)`. Este bloque imprime dos mensajes de error personalizados y luego también termina el programa con `return 0`. Esto ilustra cómo `try-catch` puede gestionar errores que ocurren en funciones más profundas, permitiendo al programa principal manejar el error de forma controlada en lugar de fallar. Nótese que, debido al `return 0` tanto en el `try` como en el `catch`, el `while` loop solo se ejecutará una vez.
