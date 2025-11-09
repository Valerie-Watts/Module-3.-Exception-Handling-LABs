# README: 3.1.9 LAB Exceptions. catch block

Este documento detalla el funcionamiento del programa C++ `3.1.9 LAB Exceptions. catch block`, que ilustra cómo un único bloque `try-catch` puede gestionar excepciones lanzadas desde múltiples funciones.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <stdexcept>

class Exeption : public std::runtime_error
{
	public:
		Exeption(const char* message) : runtime_error(message) {}
};

float square_area(float side)
{
	if (side < 0) 
	{
		throw Exeption("Your input is not valid. The area can't be negative.");
	}
	return side * side;
}

float rectangle_area(float side1, float side2) 
{
	if (side1 < 0 || side2 < 0) 
	{
		throw Exeption("Your input is not valid.The area can't be negative.");
	}
	return side1 * side2;
}


int main()
{
	float a, b, r;
	std::cin >> a;
	std::cin >> b;
	try
	{
		float rsquare = square_area(a);
		float rrectangle = rectangle_area(a, b);
		std::cout << rsquare << "\n" << rrectangle << "\n";
	}
	catch (Exeption msg)
	{
		std::cout << msg.what() << "\n";
	}
	return 0;
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Entrada válida):**

Entrada:

```
5
10
```

Salida:

```
25
50
```

**Ejecución 2 (Entrada inválida - Lado 'a' negativo):**

Entrada:

```
-5
10
```

Salida:

```
Your input is not valid. The area can't be negative.
```

**Ejecución 3 (Entrada inválida - Lado 'a' positivo, Lado 'b' negativo):**

Entrada:

```
5
-10
```

Salida:

```
Your input is not valid.The area can't be negative.
```

## Explicación del ejercicio

Este ejercicio demuestra cómo un único bloque `try-catch` puede actuar como un guardián para una secuencia de operaciones que pueden fallar. Se define una clase de excepción personalizada `Exeption` (que hereda de `std::runtime_error`) para estandarizar los mensajes de error. Dos funciones, `square_area` y `rectangle_area`, calculan áreas pero primero validan sus entradas. Si algún lado es negativo, lanzan (`throw`) una instancia de `Exeption` con un mensaje apropiado.

En `main`, las llamadas a `square_area(a)` y `rectangle_area(a, b)` se colocan *dentro* del mismo bloque `try`. Esto es crucial: el programa "intenta" ejecutar ambas. Si la primera llamada, `square_area(a)`, falla (porque `a` es negativo), lanza una excepción. La ejecución del bloque `try` se detiene *inmediatamente* en ese punto (la función `rectangle_area` ni siquiera se llama), y el control salta al bloque `catch (Exeption msg)`. Si la primera llamada tiene éxito pero la segunda (`rectangle_area`) falla, ocurre lo mismo: el `try` se detiene y el `catch` se activa. Solo si *ambas* funciones se completan sin lanzar excepciones, se ejecutan las sentencias `std::cout`. El bloque `catch` imprime el mensaje de error específico (`msg.what()`) proporcionado por la función que falló, permitiendo un manejo de errores limpio y centralizado.
