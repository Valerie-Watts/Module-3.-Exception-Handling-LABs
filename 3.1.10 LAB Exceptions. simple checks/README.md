# README: 3.1.10 LAB Exceptions. simple checks

Este documento detalla el funcionamiento del programa C++ `3.1.10 LAB Exceptions. simple checks`, que implementa una clase de Matriz y maneja excepciones personalizadas para operaciones no válidas.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>

class MatricesSizeException :public std::runtime_error
{
public:
	MatricesSizeException(const char* message) : std::runtime_error(message) {}
};

class Matrix
{
private: 
	int rows, columns; 
	std::vector<std::vector<float>> Vmatrix;

public:

	Matrix(int r, int c) : rows(r), columns(c), Vmatrix(r, std::vector<float>(c, 0)){}
	
	void addValue(int value)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Vmatrix[i][j] += value;
			}
		}
	}

	void addMatrix(Matrix& Omatrix)
	{
		if (Omatrix.rows != rows || Omatrix.columns != columns) {
			throw MatricesSizeException("Matrices sizes do not match for addition.");
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				Vmatrix[i][j] += Omatrix.Vmatrix[i][j];
			}
		}
	}

	void print()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++) 
			{
				std::cout << Vmatrix[i][j] << " ";
			}

			std::cout << "\n";
		}
	}
};

void tryA(Matrix& m1, Matrix& m2) 
{
	try
	{
		m1.addMatrix(m2);
		m1.print();
	}
	catch (MatricesSizeException& ex)
	{
		std::cout << ex.what() << "\n";
	}
}


int main()
{
	int m1r, m1c, m2r, m2c, m3r, m3c;

	std::cin >> m1r >> m1c;
	std::cin >> m2r >> m2c;
	std::cin >> m3r >> m3c;

	Matrix m1(m1r, m1c);
	Matrix m2(m2r, m2c);	
	Matrix m3(m3r, m3c);	

	tryA(m1, m2);
	tryA(m1, m3);
	tryA(m2, m3);

	return 0; 
}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Una adición válida y dos inválidas):**

Entrada (m1 y m2 tienen el mismo tamaño, m3 es diferente):

```
2 2
2 2
3 3
```

Salida (La primera suma se realiza, las otras dos lanzan excepción):

```
0 0 
0 0 
Matrices sizes do not match for addition.
Matrices sizes do not match for addition.
```

**Ejecución 2 (Todas las adiciones son inválidas):**

Entrada (m1, m2 y m3 tienen tamaños diferentes):

```
2 2
3 3
2 3
```

Salida (Las tres operaciones lanzan excepción):

```
Matrices sizes do not match for addition.
Matrices sizes do not match for addition.
Matrices sizes do not match for addition.
```

## Explicación del ejercicio

Este ejercicio demuestra un manejo de excepciones más robusto y orientado a objetos. El objetivo es simular una operación de suma de matrices, validando que sus dimensiones sean compatibles. Para manejar errores de forma elegante, se define una clase de excepción personalizada `MatricesSizeException`, que hereda de `std::runtime_error`. Esto permite que nuestra excepción se integre con la jerarquía de excepciones estándar de C++ y pueda transportar un mensaje de error específico.

La clase `Matrix` encapsula la lógica y los datos de una matriz. El método clave es `addMatrix(Matrix& Omatrix)`. Antes de intentar sumar los elementos, este método realiza una validación: comprueba si las filas (`rows`) y columnas (`columns`) de la matriz actual y la `Omatrix` (la otra matriz) son idénticas. Si no lo son, la operación es inválida, y el método "lanza" (`throw`) una instancia de `MatricesSizeException` con un mensaje descriptivo.

En la función `main`, se crean tres matrices con tamaños definidos por el usuario. La lógica de `try-catch` se ha movido a una función auxiliar `tryA(Matrix& m1, Matrix& m2)`. Esta función "intenta" (`try`) ejecutar `m1.addMatrix(m2)`. Si la operación tiene éxito (los tamaños coinciden), se imprime la matriz resultante. Si `addMatrix` lanza la excepción `MatricesSizeException` (porque los tamaños no coinciden), el bloque `catch` toma el control, previene que el programa se detenga abruptamente y, en su lugar, imprime el mensaje de error obtenido de la excepción (`ex.what()`). El programa principal llama a `tryA` tres veces para probar todas las combinaciones, demostrando cómo manejar selectivamente operaciones que pueden fallar sin detener la ejecución total del programa.
