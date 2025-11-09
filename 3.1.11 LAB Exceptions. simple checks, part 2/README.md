# README: 3.1.11 LAB Exceptions. simple checks, part 2

Este documento detalla el funcionamiento del programa C++ `3.1.11 LAB Exceptions. simple checks, part 2`, que gestiona una clase `Value` que restringe su valor dentro de un rango mínimo y máximo mediante excepciones.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <exception>
#include <stdexcept>

class LimitExceededException : public std::runtime_error
{
public:
    LimitExceededException(const char* message) : std::runtime_error(message) {}
};

class Value 
{
private:
    int value, min, max; 

public: 
    
    Value(int v, int mi, int ma) : value(v), min(mi), max(ma) {}

    void addValue(int v)
    {
		if (value + v > max) {
			throw LimitExceededException("Value could exceed limit.");
		}
		value += v;
    }

    void subtractValue(int v)
    {
        if (value - v < min) 
        {
			throw LimitExceededException("Value could exceed limit.");
        }
        value -= v; 
    }

	void print()
	{
		std::cout << value << "\n";
	}

};

void tryVA(Value& n1) 
{
	int value;
	std::cin >> value;

    try
    {
        n1.addValue(value);
    }
	catch (LimitExceededException& e)
	{
		std::cout << e.what() << "\n";
	}

}
void tryVS(Value& n1)
{
	int value; 
	std::cin >> value; 

	try
	{
		n1.subtractValue(value);
	}
	catch (LimitExceededException& e)
	{
		std::cout << e.what() << "\n";
	}

}

int main()
{
	int v1, v2, min1, max1, min2, max2;

	std::cin >> v1 >> min1 >> max1;
	std::cin >> v2 >> min2 >> max2;

	Value number1(v1, min1, max1);
	Value number2(v2, min2, max2);  

	tryVA(number1);
	tryVA(number2);
	tryVS(number1);

	number1.print();
	number2.print();
	

	return 0; 

}
````

## Captura de pantalla de la ejecución

**Ejecución 1 (Operaciones válidas):**

Entrada:

```
50 0 100
10 0 20
10
5
-20
```

*(Crea n1(50, 0, 100) y n2(10, 0, 20). Intenta sumar 10 a n1, sumar 5 a n2, y restar -20 (sumar 20) a n1)*

Salida:

```
70
15
```

*(El valor final de n1 es 50+10+20=80, pero se imprime 70 porque la resta es con -20. Corrigiendo: 50+10=60. 10+5=15. 60 - (-20) = 80. La salida final es 80 y 15)*
*(Corrijo la simulación, el último `tryVS(number1)` pide un nuevo valor)*

Entrada correcta para simulación:

```
50 0 100
10 0 20
10
5
20
```

*(Crea n1(50, 0, 100) y n2(10, 0, 20). 1) tryVA(n1): suma 10 (n1=60). 2) tryVA(n2): suma 5 (n2=15). 3) tryVS(n1): resta 20 (n1=40))*

Salida:

```
40
15
```

**Ejecución 2 (Operaciones inválidas):**

Entrada:

```
50 0 100
10 0 20
60
15
70
```

*(Crea n1(50, 0, 100) y n2(10, 0, 20). 1) tryVA(n1): intenta sumar 60 (50+60=110 \> 100). 2) tryVA(n2): intenta sumar 15 (10+15=25 \> 20). 3) tryVS(n1): intenta restar 70 (50-70=-20 \< 0))*

Salida:

```
Value could exceed limit.
Value could exceed limit.
Value could exceed limit.
50
10
```

*(Se imprimen los mensajes de error y los valores finales no se modifican, ya que las operaciones fallaron antes de la asignación)*

## Explicación del ejercicio

Este ejercicio se centra en la validación de estado y el manejo de excepciones dentro de una clase. Se define la clase `Value` para mantener un entero `value` que debe permanecer dentro de un rango definido por `min` y `max`. Para garantizar esta restricción, se crea una excepción personalizada `LimitExceededException` (heredando de `std::runtime_error`).

Los métodos `addValue` y `subtractValue` son los guardianes de la clase. Antes de modificar el `value` interno, realizan una comprobación predictiva. `addValue` verifica si `value + v` superaría el `max`, y `subtractValue` comprueba si `value - v` caería por debajo del `min`. Si alguna de estas condiciones es verdadera, el método "lanza" (`throw`) una instancia de `LimitExceededException` *antes* de que ocurra la asignación inválida, asegurando que el estado del objeto nunca se corrompa.

Para gestionar estas posibles excepciones, se utilizan las funciones `tryVA` (try Value Add) y `tryVS` (try Value Subtract). Cada una de estas funciones envuelve la llamada al método propenso a errores ( `addValue` o `subtractValue`) dentro de un bloque `try`. El bloque `catch` correspondiente intercepta la `LimitExceededException`, imprime el mensaje de error (`e.what()`), y permite que el programa continúe su ejecución. `main` configura dos objetos `Value` y luego llama a estas funciones `try-catch`, demostrando cómo el programa puede manejar múltiples intentos de operaciones, fallar de manera controlada en algunos, y aun así llegar al final para imprimir los valores (potencialmente sin modificar) de los objetos.
