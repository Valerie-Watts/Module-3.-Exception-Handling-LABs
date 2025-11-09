# README: 3.4.13 LAB Exceptions. using in program

Este documento detalla el funcionamiento del programa C++ `3.4.13 LAB Exceptions. using in program`, que implementa una versión jugable de las Torres de Hanoi, utilizando un conjunto de excepciones personalizadas para gestionar la lógica del juego y los errores del usuario.

## Captura de pantalla del código

```cpp
#include <iostream>
#include <vector>
#include <exception>

// Excepción 1: Torres fuera de rango
class InvalidTowerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid tower number. Must be between 1 and 3.";
    }
};

// Excepción 2: Disco más grande sobre uno pequeño
class InvalidMoveException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid move. Cannot place a larger disk on a smaller one.";
    }
};

// Excepción 3: Torre vacía
class EmptyTowerException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Source tower is empty.";
    }
};

class Node {
private:
    int dato;
    Node* next;

public:
    Node(int block) : dato(block), next(nullptr) {}
    
    Node(int block, Node* nextNode) : dato(block), next(nextNode) {}

    int getDato() { return dato; }
    void setDato(int value) { dato = value; }
    
    Node* getNext() { return next; }
    void setNext(Node* node) { next = node; }
};

class Pile {
private:
    Node* top;

public:
    Pile() : top(nullptr) {}

    ~Pile() {
        while (!Empty()) {
            Pop();
        }
    }

    void Push(int block) {
        Node* newNode = new Node(block, top);
        top = newNode;
    }

    int Pop() {
        if (top == nullptr) {
            throw EmptyTowerException();
        }
        int block = top->getDato();
        Node* temp = top;
        top = top->getNext();
        delete temp;
        return block;
    }

    int Peek() {
        if (top == nullptr) {
            throw EmptyTowerException();
        }
        return top->getDato();
    }

    bool Empty() {
        return top == nullptr;
    }

    std::vector<int> GetBlocks() {
        std::vector<int> blocks;
        Node* current = top;
        while (current != nullptr) {
            blocks.push_back(current->getDato());
            current = current->getNext();
        }
        return blocks;
    }
};

class Tower {
public:
    Pile blocks;

    void AddBlocks(int block) {
        blocks.Push(block);
    }

    bool Move(Tower& targetTower) {
        if (blocks.Empty()) {
            throw EmptyTowerException();
        }

        int diskToMove = blocks.Peek();

        if (!targetTower.blocks.Empty() && diskToMove > targetTower.blocks.Peek()) {
            throw InvalidMoveException();
        }

        targetTower.blocks.Push(blocks.Pop());
        return true;
    }
};

// Función global para imprimir torres
void PrintTowers(Tower towers[], int numTowers) {
    int maxHeight = 0;
    for (int i = 0; i < numTowers; i++) {
        std::vector<int> currentBlocks = towers[i].blocks.GetBlocks();
        if (currentBlocks.size() > maxHeight) {
            maxHeight = currentBlocks.size();
        }
    }

    std::vector<std::vector<int>> allBlocks;
    for (int i = 0; i < numTowers; i++) {
        allBlocks.push_back(towers[i].blocks.GetBlocks());
    }

    for (int level = 0; level < maxHeight; level++) {
        for (int t = 0; t < numTowers; t++) {
            if (level < allBlocks[t].size()) {
                int blockSize = allBlocks[t][level];
                int spaces = (13 - blockSize) / 2;
                for (int s = 0; s < spaces; s++) std::cout << " ";
                for (int s = 0; s < blockSize; s++) std::cout << "*";
                for (int s = 0; s < spaces; s++) std::cout << " ";
            } else {
                for (int s = 0; s < 6; s++) std::cout << " ";
                std::cout << "|";
                for (int s = 0; s < 6; s++) std::cout << " ";
            }
            std::cout << "   ";
        }
        std::cout << "\n";
    }

    for (int t = 0; t < numTowers; t++) {
        std::cout << "=============   ";
    }
    std::cout << "\n";

    for (int t = 0; t < numTowers; t++) {
        std::cout << "   Tower " << (t + 1) << "     ";
    }
    std::cout << "\n\n";
}

int main() {
    // Corregido: array directo sin copias innecesarias
    Tower towers[3];
    int blocks = 0;

    std::cout << "Insert the number of disks from 1-7: ";
    std::cin >> blocks;

    if (blocks < 1 || blocks > 7) {
        std::cout << "Invalid number! Please enter a value between 1 and 7.\n";
        return 0;
    }

    // Orden decreciente de bloques
    for (int i = blocks; i >= 1; i--) {
        towers[0].AddBlocks(i * 2 - 1);
    }

    PrintTowers(towers, 3);

    while (true) {
        try {
            std::cout << "\nMove a disk from one tower to another.\n";
            std::cout << "Enter from what tower you want to move the disk (1, 2, or 3): ";
            int fromTowerIndex;
            std::cin >> fromTowerIndex;
            fromTowerIndex--;

            std::cout << "Enter the tower you want to move it to (1, 2, or 3): ";
            int toTowerIndex;
            std::cin >> toTowerIndex;
            toTowerIndex--;

            if (fromTowerIndex < 0 || fromTowerIndex > 2 || toTowerIndex < 0 || toTowerIndex > 2) {
                throw InvalidTowerException();
            }

            towers[fromTowerIndex].Move(towers[toTowerIndex]);
            std::cout << "Moved a disk from tower " << (fromTowerIndex + 1) << " to tower " << (toTowerIndex + 1) << "\n";
            PrintTowers(towers, 3);

            if (towers[2].blocks.GetBlocks().size() == blocks) {
                std::cout << "\nCongratulations! You've solved the Tower of Hanoi!\n";
                break;
            }

        } catch (std::exception& e) {
            std::cout << e.what() << " Try again.\n";
        }
    }

    return 0;
}
````

## Captura de pantalla de la ejecución

*(Simulación con 3 discos)*

**Ejecución 1 (Inicio y movimiento válido):**

```
Insert the number of disks from 1-7: 3
      * |            |   
     *** |            |   
    ***** |            |   
=============   =============   =============   
   Tower 1         Tower 2         Tower 3     


Move a disk from one tower to another.
Enter from what tower you want to move the disk (1, 2, or 3): 1
Enter the tower you want to move it to (1, 2, or 3): 3
Moved a disk from tower 1 to tower 3
     *** |            * ***** |            |   
=============   =============   =============   
   Tower 1         Tower 2         Tower 3     
```

**Ejecución 2 (Movimiento inválido - grande sobre pequeño):**

```
Move a disk from one tower to another.
Enter from what tower you want to move the disk (1, 2, or 3): 1
Enter the tower you want to move it to (1, 2, or 3): 3
Invalid move. Cannot place a larger disk on a smaller one. Try again.
```

**Ejecución 3 (Movimiento inválido - torre de origen vacía):**

```
Move a disk from one tower to another.
Enter from what tower you want to move the disk (1, 2, or 3): 2
Enter the tower you want to move it to (1, 2, or 3): 1
Source tower is empty. Try again.
```

**Ejecución 4 (Entrada inválida - número de torre incorrecto):**

```
Move a disk from one tower to another.
Enter from what tower you want to move the disk (1, 2, or 3): 1
Enter the tower you want to move it to (1, 2, or 3): 5
Invalid tower number. Must be between 1 and 3. Try again.
```

## Explicación del ejercicio

Este es un ejemplo completo que utiliza excepciones para gestionar la lógica de un juego interactivo (Torres de Hanoi). El programa define tres clases de excepción personalizadas (`InvalidTowerException`, `InvalidMoveException`, `EmptyTowerException`), todas heredando de `std::exception`.

El manejo de excepciones se implementa en múltiples capas:

1.  **Capa de Datos (`Pile`):** La pila (`Pile`) lanza una `EmptyTowerException` desde `Pop()` o `Peek()` si se intenta acceder a una pila vacía.
2.  **Capa de Lógica (`Tower`):** El método `Move` de la torre propaga la `EmptyTowerException` si su pila interna la lanza. Más importante aún, aplica la regla del juego: comprueba si el disco a mover (`diskToMove`) es más grande que el disco superior de la torre destino (`targetTower.blocks.Peek()`). Si lo es, lanza una `InvalidMoveException`.
3.  **Capa de Interfaz (`main`):** El bucle principal del juego (`while (true)`) está completamente envuelto en un bloque `try`. Este bloque gestiona la entrada del usuario. Lanza su propia excepción, `InvalidTowerException`, si el usuario introduce un número de torre fuera del rango (ej. 5). Luego, llama a `towers[fromTowerIndex].Move(...)`, que puede lanzar `InvalidMoveException` o `EmptyTowerException`.

Lo más destacable es el bloque `catch (std::exception& e)`. Gracias al polimorfismo, este *único* bloque `catch` puede capturar las *tres* excepciones personalizadas (ya que todas heredan de `std::exception`). Imprime el mensaje de error específico (`e.what()`) para informar al usuario *exactamente* qué salió mal, y luego el bucle continúa ("Try again."). Esto evita que el programa se bloquee y permite al usuario corregir su error y seguir jugando.
