# README: 3.2.16 LAB Exceptions. file checks

Este documento detalla el funcionamiento del programa C++ `3.2.16 LAB Exceptions. file checks`, que implementa una clase Matrix capaz de manejar errores de E/S (Entrada/Salida) de archivos mediante excepciones.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>
#include <stdexcept>
#include <vector>
#include <fstream>

class Matrix
{
private:
	int rows = 2, columns = 2;
	std::vector<std::vector<float>> Vmatrix;

public:

	Matrix() : Vmatrix(2, std::vector<float>(2, 0)) {}

	void loadFromFile(std::string filename) 
	{
		std::ifstream file(filename);
		if (!file.is_open()) {
			throw std::runtime_error("File not found at: " + filename);
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				if (!(file >> Vmatrix[i][j])) {
					// Esta condición también podría lanzar un error de formato de archivo
					throw std::runtime_error("Error reading data from file: " + filename);
				}
			}
		}
		file.close();
	}

	void saveToFile(std::string filename) 
	{
		std::ofstream file(filename);
		if (!file.is_open()) {
			
			throw std::runtime_error("No rights to write to file: " + filename);
		}
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{
				file << Vmatrix[i][j] << " ";
			}
			file << "\n";
		}
		file.close();
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



int main()
{
	Matrix m; 

	try
	{
		m.loadFromFile("nonexistent.txt");
		
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

	try
	{
		// Intentar escribir en un directorio protegido (C:\Windows\ en Windows)
		// En otros SO, un path como "/test.txt" (raíz) podría fallar
		m.saveToFile("C:\\Windows\\test.txt"); 

	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

	

	return 0; 
}
````

## Captura de pantalla de la ejecución

**Ejecución (Simulada):**

La salida del programa está diseñada para mostrar los errores, asumiendo que `nonexistent.txt` no existe y que el usuario no tiene permisos de administrador para escribir en `C:\Windows`.

```
File not found at: nonexistent.txt
No rights to write to file: C:\Windows\test.txt
```

## Explicación del ejercicio

Este ejercicio demuestra cómo manejar errores de Entrada/Salida (I/O) de archivos, que son un tipo común de excepción en tiempo de ejecución (`runtime_error`). La clase `Matrix` tiene dos métodos críticos: `loadFromFile` y `saveToFile`.

En `loadFromFile`, se intenta abrir un `std::ifstream`. La validación `if (!file.is_open())` comprueba si el archivo se pudo abrir. Si falla (por ejemplo, el archivo no existe), el método "lanza" (`throw`) una `std::runtime_error` con un mensaje que incluye el nombre del archivo. Del mismo modo, `if (!(file >> ...))` verifica si la lectura del archivo falla (por ejemplo, el archivo está corrupto o tiene menos datos de los esperados).

En `saveToFile`, se intenta abrir un `std::ofstream`. La misma validación `!file.is_open()` se usa para verificar si el archivo se puede crear o sobrescribir. Si falla (por ejemplo, se intenta escribir en un directorio protegido como `C:\Windows` sin permisos), el método lanza una `std::runtime_error`.

En la función `main`, se utilizan dos bloques `try-catch` separados para probar estas condiciones de error a propósito. El primer `try` intenta cargar desde `"nonexistent.txt"`, lo cual falla y es capturado. El segundo `try` intenta guardar en `"C:\\Windows\\test.txt"`, lo que también falla y es capturado. Esto muestra un uso robusto del manejo de excepciones para gestionar problemas externos (como el sistema de archivos) que están fuera del control lógico del programa.
