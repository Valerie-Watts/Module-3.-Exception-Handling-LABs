# Repositorio de Laboratorios: Manejo de Excepciones en C++

Este repositorio es una colección de laboratorios de C++ centrados en el aprendizaje y la aplicación de los mecanismos de manejo de excepciones. A través de una serie de ejercicios progresivos, se exploran las técnicas fundamentales para escribir código robusto y resistente a errores.

El proyecto comienza con el `try-catch` básico y evoluciona hasta la implementación de clases de excepción personalizadas, el manejo de errores de lógica de negocio (como en operaciones matemáticas y de clases), la validación de E/S (archivos y entrada de usuario) y la aplicación de una jerarquía de excepciones en un programa interactivo.

## Conceptos Clave Demostrados

* Uso de los bloques `try`, `throw` y `catch`.
* Lanzamiento de tipos de datos primitivos (ej. `bool`) como excepciones.
* Definición de clases de excepción personalizadas.
* Herencia de `std::exception` y `std::runtime_error` para crear excepciones estándar.
* Uso del método `what()` para obtener mensajes de error descriptivos.
* Manejo de errores de lógica (división por cero, validación de rangos).
* Validación de E/S (lectura/escritura de archivos) y manejo de `std::runtime_error`.
* Uso de excepciones en constructores de clases para prevenir la creación de objetos en estado inválido.
* Manejo polimórfico de múltiples tipos de excepciones con un solo bloque `catch`.

## Laboratorios Incluidos

1.  **`3.0.8-Exceptions-input-validation.cpp`**:
    * Introduce el `try-catch` básico para prevenir una división por cero, lanzando un `bool`.

2.  **`3.0.9-Exceptions-divide-by-zero.cpp`**:
    * Mejora el ejercicio anterior creando una clase de excepción personalizada (`DivideByZeroException`) con un método `what()`.

3.  **`3.1.8-Exceptions-input-validation-func.cpp`**:
    * Demuestra cómo una excepción lanzada desde una función (`internaldiv`) es capturada por la función que la llamó (`main`).

4.  **`3.1.9-Exceptions-catch-block.cpp`**:
    * Ilustra cómo un solo bloque `try-catch` puede gestionar excepciones de múltiples funciones (`square_area`, `rectangle_area`).

5.  **`3.1.10-Exceptions-simple-checks-matrix.cpp`**:
    * Aplica excepciones a la lógica de clases. Lanza `MatricesSizeException` si se intentan sumar matrices de tamaños incompatibles.

6.  **`3.1.11-Exceptions-simple-checks-value.cpp`**:
    * Utiliza una `LimitExceededException` en una clase `Value` para asegurar que un valor permanezca dentro de un rango `min` y `max`.

7.  **`3.2.16-Exceptions-file-checks.cpp`**:
    * Maneja errores de E/S de archivos. Lanza `std::runtime_error` si un archivo no se puede abrir para lectura (`loadFromFile`) o escritura (`saveToFile`).

8.  **`3.2.17-Exceptions-checking-strings-ip.cpp`**:
    * Usa excepciones en múltiples etapas: 1) en el constructor para validar un formato de string (dirección IP) y 2) en un método para validar un argumento (rango de subred).

9.  **`3.4.12-Exceptions-including-information.cpp`**:
    * Demuestra cómo los mensajes de excepción pueden proveer información contextual específica sobre el error (ej. si falló la IP fuente o la IP destino).

10. **`3.4.13-Exceptions-using-in-program-hanoi.cpp`**:
    * Una aplicación completa que integra todo lo aprendido. Implementa el juego de las Torres de Hanoi usando una jerarquía de excepciones (`InvalidTowerException`, `InvalidMoveException`, `EmptyTowerException`) para gestionar la lógica del juego y los errores del usuario.

## Cómo Utilizar
Cada archivo `.cpp` es un programa independiente. Pueden ser compilados y ejecutados individualmente para observar el comportamiento de cada concepto de excepción en aislamiento.
