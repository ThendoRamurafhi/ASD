#include <ostream>
#include <string>

class Pear{
    int weight;
public:
    Pear(const int weight): weight(weight){}
    int juice() const { return weight / 2; }
    void takeJuice(const int amount) { weight -= (amount * 2); }
};

class Grapes{
    int count;
public:
    Grapes(const int count) : count(count){}
    int wine() const {return count * 2;}
    void takeWine(const int amount) {count -= (amount / 2); }
};

using Fruit = std::variant<Pear, Grapes>;

class Print{
public:
    void operator() (const Pear& p) const {//worker method
        std::println("Hmm juicy pear {}", p.juice());
    }
    void operator() (const Grapes& g) const {
        std::println("{} grapes hold {} wine", g.count(), g.wine()); 
    }
};

class Squeeze {
    const int amount;
public:
    Squeeze(const int amount): amount(amount){}
    void operator() (Pear& p) const { p.takeJuice(amount); }
    void operator() (Grapes& g) const { g.takeWine(amount); }
};

void PrintAll(const std::vector<Fruit>& fruits) {
    for(auto& f: fruits) {std::applyPattern(Print(), f);}
}

void SqueezeAll(const std::vector<Fruit>& fruits, const int amount) {
    for(auto& f: fruits) {std::applyPattern(Squeeze(amount), f);}
}

int main(){
    std::vector<Fruit> fruits;
    fruits.push_back(Pear{10});
    fruits.push_back(Grapes{20});
    fruits.push_back(Grapes{30});
    PrintAll(fruits);
    SqueezeAll(fruits, 1);
    PrintAll(fruits);
}