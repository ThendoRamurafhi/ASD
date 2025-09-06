#include <iostream>
#include <string>
#include <variant>
#include <vector>

// Pear class
class Pear {
    int weight;
public:
    Pear(int weight) : weight(weight) {}
    int juice() const { return weight / 2; }
    void takeJuice(int amount) { weight -= (amount * 2); }
};

// Grapes class
class Grapes {
    int count;
public:
    Grapes(int count) : count(count) {}
    int wine() const { return count * 2; }
    void takeWine(int amount) { count -= (amount / 2); }

    int getCount() const { return count; } // added getter
};

// Variant type
using Fruit = std::variant<Pear, Grapes>;

// Print visitor
class Print {
public:
    void operator()(const Pear& p) const {
        std::cout << "Hmm juicy pear " << p.juice() << "\n";
    }
    void operator()(const Grapes& g) const {
        std::cout << g.getCount() << " grapes hold " << g.wine() << " wine\n";
    }
};

// Squeeze visitor
class Squeeze {
    int amount;
public:
    Squeeze(int amount) : amount(amount) {}
    void operator()(Pear& p) const { p.takeJuice(amount); }
    void operator()(Grapes& g) const { g.takeWine(amount); }
};

// Apply visitors
void PrintAll(const std::vector<Fruit>& fruits) {
    for (auto& f : fruits) {
        std::visit(Print(), f);
    }
}

void SqueezeAll(std::vector<Fruit>& fruits, int amount) {
    for (auto& f : fruits) {
        std::visit(Squeeze(amount), f);
    }
}

int main() {
    std::vector<Fruit> fruits;
    fruits.push_back(Pear{10});
    fruits.push_back(Grapes{20});
    fruits.push_back(Grapes{30});

    PrintAll(fruits);
    SqueezeAll(fruits, 1);
    PrintAll(fruits);

    return 0;
}
