# ⚔️ C++ Polymorphic RPG Engine

A turn-based terminal RPG built with **C++** that demonstrates high-level **Object-Oriented Programming (OOP)** principles. Face off against various monsters, manage your stats, and try to survive a rare encounter with the legendary boss, **Defne** (my gf).

---

## 🚀 Features

* **Polymorphic Combat System:** Uses a base `Entity` class with virtual functions to allow unique behaviors across different monster types.
* **Dynamic Monster Factory:** Monsters are spawned with weighted probabilities, ensuring a different experience each run.
* **Input Validation:** A robust loop that handles invalid entries and prevents terminal crashes from non-integer inputs.

### 👾 Monster Compendium

| Enemy | Special Ability |
| :--- | :--- |
| **Slime** | **Split:** Becomes a "Little Slime" with fresh stats when defeated. |
| **Goblin** | **Frenzy:** 20% chance to perform a double attack in a single turn. |
| **Undead** | **Rage:** At <20 HP, damage doubles while defense is halved. |
| **Defne** | **Rare Boss:** Stats scale exponentially every hit. Features an insta-kill threshold. |

---

## 🛠️ Technical Implementation

This project was built to practice and demonstrate core C++ engineering concepts:

* **Inheritance & Overriding:** Specialized logic for unique monster types inheriting from a shared interface.
* **Virtual Destructors:** Ensures safe memory cleanup and prevents leaks when deleting derived objects via base pointers.
* **Dynamic Memory:** Utilizes heap allocation (`new`/`delete`) for the player and enemy life-cycles.
* **Encapsulation:** Internal stats are protected, exposed only through validated combat methods.

---

## 📥 Installation & Running

Since this is a standard C++ project, you can compile it using `g++` on any Linux distribution (developed and tested on **Arch Linux**).

```bash
# 1. Clone the repository
git clone [https://github.com/your-username/rpg-engine.git](https://github.com/your-username/rpg-engine.git)
cd rpg-engine

# 2. Compile the source with optimizations
g++ -O3 main.cpp -o rpg_game

# 3. Run the binary
./rpg_game