#include <cmath>
#include <iostream>
#include <string>
#include <ctime>
#define GFNAME "<3 Defne <3"
using namespace std;

class Entity
{
protected:
    string name;
    double cur_hp, max_hp, dmg, def, heal;
    bool isDef;

public:
    Entity(string a = "", double b = 100.0, double c = 10.0, double d = 10.0, double e = 10.0) : name(a), cur_hp(b), max_hp(b), dmg(c), def(d), heal(e), isDef(false) {}
    virtual ~Entity() {}

    bool isAlive() { return cur_hp > 0; }

    void resetDef() { isDef = false; }

    string getName() { return name; }
    double getCurHP() { return cur_hp; }
    double getMaxHP() { return max_hp; }
    void setHP(double a) { cur_hp = a; }

    double rollDice()
    {
        cout << "Rolling the dice..." << endl;
        int random = (rand() % 6) + 1;
        cout << "You rolled a " << random << " on the dice!" << endl;
        return double(random);
    }

    virtual double attack() { return rollDice() * 0.4 * dmg; }

    void defend()
    {
        isDef = true;
        cout << name << " is defending itself!" << endl;
    }

    virtual bool takeDamage(double a, Entity* attacker = nullptr)
    {
        double finalDmg = a;
        if (isDef)
        {
            finalDmg = a * (1.0 - (def / 100.0));
        }
        cur_hp -= finalDmg;
        if (cur_hp < 0)
            cur_hp = 0;
        cout << name << " took " << finalDmg << " damage!" << endl;
        return (cur_hp <= 0);
    }

    void healSelf()
    {
        cur_hp += heal;
        if (cur_hp > max_hp)
        {
            cur_hp = max_hp;
        }
        cout << name << " healed for " << heal << " HP!" << endl;
    }

    virtual void print()
    {
        cout << "Name: " << name << " | Current Health: " << cur_hp << " | Attack Power: " << dmg << " | Defense: " << def << " | Regeneration: " << heal << endl;
    }
};

class Slime : public Entity
{
private:
    bool bigSlime;

public:
    Slime(bool a = true) : Entity(a ? "Big Slime" : "Little Slime", a ? 30 : 10, a ? 8 : 3, a ? 10 : 5, a ? 20 : 5) {}

    bool takeDamage(double a, Entity* attacker = nullptr) override
    {
        Entity::takeDamage(a);

        if (cur_hp <= 0 && bigSlime)
        {
            cout << "The slime became a smaller slime!" << endl;
            bigSlime = false;
            name = "Little Slime";
            max_hp = 15;
            cur_hp = 15;
            dmg = 5;
            def = 5;
            return false;
        }

        return (cur_hp <= 0);
    }

    void print() override
    {
        Entity::print();
        cout << "(This enemy should be easy, right?)" << endl;
    }
};

class Goblin : public Entity
{
public:
    Goblin() : Entity("Goblin", 50, 20, 0, 5) {}

    double attack() override
    {
        if ((rand() % 100) + 1 <= 20)
        {
            cout << "The Goblin goes into a frenzy! Double Attack!" << endl;
            return Entity::attack() + Entity::attack();
        }
        return Entity::attack();
    }

    void print() override
    {
        Entity::print();
        cout << "(Watch your back, may attack 2 times)" << endl;
    }
};

class Undead : public Entity
{
private:
    bool isRage;

public:
    Undead() : Entity("Undead", 80, 15, 30, 10), isRage(false) {}

    bool takeDamage(double a, Entity* attacker = nullptr) override
    {
        bool dead = Entity::takeDamage(a);
        if (cur_hp > 0 && cur_hp <= 20 && !isRage)
        {
            dmg *= 2;
            def /= 2;
            isRage = true;
            cout << "The Undead is now enraged! Damage doubled, defense halved!" << endl;
        }
        return dead;
    }

    void print() override
    {
        Entity::print();
        cout << "(Looks a bit angry and scary...)" << endl;
    }
};

class Boss : public Entity
{
private:
    double init_dmg;

public:
    Boss(string gfName) : Entity(gfName, 400, 25, 20, 15) { init_dmg = dmg; }

    bool takeDamage(double a, Entity* attacker = nullptr) override
    {
        Entity::takeDamage(a);

        if (cur_hp > 0)
        {
            cout << GFNAME << " is angry at you. Her attack power and defense doubles!" << endl;
            dmg *= 2;
            def *= 1.5;

            if (dmg >= init_dmg * 4)
            {
                if (dmg >= init_dmg * 8)
                {
                    cout << GFNAME << " lures you into the sea and insta-kills you!" << endl;
                    if (attacker != nullptr)
                    {
                        attacker->takeDamage(INFINITY);
                    }
                }
                else
                {
                    cout << GFNAME << " is about to lure you..." << endl;
                }
            }
        }

        return (cur_hp <= 0);
    }

    void print() override
    {
        Entity::print();
        cout << "WARNING: RARE BOSS APPEARS!!!" << endl;
    }
};

class Player : public Entity
{
public:
    Player(string a = "Bob", int b = 100, int c = 15, int d = 15, int e = 10) : Entity(a, b, c, d, e) {}
};

void printVictory(Entity* a, Player* b)
{
    cout << "\n===============================" << endl;
    cout << "       🏆 VICTORY! 🏆" << endl;
    cout << "===============================" << endl;
    cout << "The " << a->getName() << " collapses in defeat!" << endl;
    cout << "Your remaining HP: " << b->getCurHP() << "/" << b->getMaxHP() << endl;
}

void printLose(Entity* a, Player* b)
{
    cout << "\n===============================" << endl;
    cout << "       💀 GAME OVER 💀" << endl;
    cout << "===============================" << endl;
    cout << "You have been slain by the " << a->getName() << "..." << endl;
    cout << "The monster had " << a->getCurHP() << " HP remaining." << endl;

    if (a->getCurHP() < 10)
    {
        cout << "So close! Just one more hit would have done it!" << endl;
    }
}

int main()
{
    srand(time(0));
    cout << "--- Welcome to C++ RPG Game! ---" << endl;

    string a;

    Player* player = nullptr;
    while (player == nullptr)
    {
        cout << "Do you want to use the default values or input them yourself? (d/i): ";
        char player_input;
        cin >> player_input;
        if (player_input != 'd' && player_input != 'i')
        {
            cout << "Wrong input! Try again..." << endl;
            continue;
        }
        else if (player_input == 'd')
        {
            player = new Player();
            cout << "Using default player values...";
            break;
        }
        else if (player_input == 'i')
        {
            cout << "Enter your name: ";
            string name;
            cin.ignore();
            getline(cin, name);
            cout << "Enter your maximum health: ";
            double max_health;
            cin >> max_health;
            cout << "Enter your attack power: ";
            double attack_power;
            cin >> attack_power;
            cout << "Enter your defense: ";
            double defense;
            cin >> defense;
            cout << "Enter your heal amount: ";
            double heal_amount;
            cin >> heal_amount;
            player = new Player(name, max_health, attack_power, defense, heal_amount);
        }
    }

    int spawnRoll = (rand() % 100) + 1;
    Entity* enemy = nullptr;

    if (spawnRoll <= 20)
    {
        enemy = new Boss(GFNAME);
    }
    else
    {
        int regularMonster = rand() % 100;
        if (regularMonster < 25)
            enemy = new Slime(true);
        else if (regularMonster < 50)
            enemy = new Slime(false);
        else if (regularMonster < 75)
            enemy = new Goblin();
        else if (regularMonster < 100)
            enemy = new Undead();
    }
    cout << "Your enemy is: " << enemy->getName() << " !" << endl;
    while (player->isAlive() && enemy->isAlive())
    {
        player->resetDef();
        enemy->resetDef();

        cout << "\n--- YOUR TURN ---" << endl;
        player->print();
        enemy->print();
        cout << "1. Attack | 2. Defend | 3. Heal: ";
        int action;
        cin >> action;
        if (action == 1)
            enemy->takeDamage(player->attack(), player);
        else if (action == 2)
            player->defend();
        else if (action == 3)
            player->healSelf();
        else if (enemy->getName() == GFNAME && action == 4)
        {
            cout << "You gave " << GFNAME << " a compliment and she liked it. She spares you!" << endl;
            printVictory(enemy, player);
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Wrong action! Try again..." << endl;
            continue;
        }

        if (enemy->isAlive())
        {
            cout << "\n--- ENEMY TURN ---" << endl;
            int ai = rand() % 100;
            if (ai < 70)
                player->takeDamage(enemy->attack(), enemy);
            else if (ai < 85)
                enemy->defend();
            else if ((ai < 100) && (enemy->getCurHP() <= (enemy->getMaxHP() * 0.5)) && (enemy->getName() != "Goblin"))
                enemy->healSelf();
            else
            {
                player->takeDamage(enemy->attack(), enemy);
            }
        }

        if (player->isAlive() && !enemy->isAlive())
        {
            printVictory(enemy, player);
            break;
        }
        else if (!player->isAlive() && enemy->isAlive())
        {
            printLose(enemy, player);
            break;
        }
    }

    delete player;
    delete enemy;

    cout << "Thanks for playing! Press Enter to exit..." << endl;
    cin.ignore();
    cin.get();
    return 0;
}