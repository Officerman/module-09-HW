#include <iostream>
#include <memory>
#include <string>
#include <iomanip>

// Интерфейс для напитка
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual std::string Description() const = 0;
    virtual double Cost() const = 0;
};

// Класс Эспрессо
class Espresso : public Beverage {
public:
    std::string Description() const override {
        return "Espresso";
    }

    double Cost() const override {
        return 2.0;
    }
};

// Класс Чай
class Tea : public Beverage {
public:
    std::string Description() const override {
        return "Tea";
    }

    double Cost() const override {
        return 1.5;
    }
};

// Абстрактный декоратор для добавок
class BeverageDecorator : public Beverage {
protected:
    std::unique_ptr<Beverage> beverage;

public:
    explicit BeverageDecorator(std::unique_ptr<Beverage> b) : beverage(std::move(b)) {}
};

// Декоратор Молоко
class Milk : public BeverageDecorator {
public:
    explicit Milk(std::unique_ptr<Beverage> b) : BeverageDecorator(std::move(b)) {}

    std::string Description() const override {
        return beverage->Description() + ", Milk";
    }

    double Cost() const override {
        return beverage->Cost() + 0.5;
    }
};

// Декоратор Сахар
class Sugar : public BeverageDecorator {
public:
    explicit Sugar(std::unique_ptr<Beverage> b) : BeverageDecorator(std::move(b)) {}

    std::string Description() const override {
        return beverage->Description() + ", Sugar";
    }

    double Cost() const override {
        return beverage->Cost() + 0.2;
    }
};

// Декоратор Взбитые сливки
class WhippedCream : public BeverageDecorator {
public:
    explicit WhippedCream(std::unique_ptr<Beverage> b) : BeverageDecorator(std::move(b)) {}

    std::string Description() const override {
        return beverage->Description() + ", Whipped Cream";
    }

    double Cost() const override {
        return beverage->Cost() + 0.7;
    }
};

// Клиентский код для создания напитка с добавками
int main() {
    std::unique_ptr<Beverage> beverage = std::make_unique<Espresso>();
    beverage = std::make_unique<Milk>(std::move(beverage));
    beverage = std::make_unique<Sugar>(std::move(beverage));
    beverage = std::make_unique<WhippedCream>(std::move(beverage));

    std::cout << "Drink: " << beverage->Description() << std::endl;
    std::cout << "Total Cost: $" << std::fixed << std::setprecision(2) << beverage->Cost() << std::endl;

    return 0;
}

/*

//Паттерн адаптер
#include <iostream>
#include <memory>
#include <string>

// Интерфейс для процессора оплаты
class IPaymentProcessor {
public:
    virtual ~IPaymentProcessor() = default;
    virtual void ProcessPayment(double amount) const = 0;
};

// Класс для оплаты через PayPal
class PayPalPaymentProcessor : public IPaymentProcessor {
public:
    void ProcessPayment(double amount) const override {
        std::cout << "Processing PayPal payment of $" << amount << std::endl;
    }
};

// Сторонняя система оплаты через Stripe
class StripePaymentService {
public:
    void MakeTransaction(double totalAmount) {
        std::cout << "Processing Stripe transaction of $" << totalAmount << std::endl;
    }
};

// Адаптер для StripePaymentService
class StripePaymentAdapter : public IPaymentProcessor {
private:
    StripePaymentService stripeService;

public:
    void ProcessPayment(double amount) const override {
        stripeService.MakeTransaction(amount);
    }
};

// Клиентский код для работы с различными процессорами оплаты
int main() {
    std::unique_ptr<IPaymentProcessor> paypalProcessor = std::make_unique<PayPalPaymentProcessor>();
    std::unique_ptr<IPaymentProcessor> stripeProcessor = std::make_unique<StripePaymentAdapter>();

    std::cout << "Using PayPal:" << std::endl;
    paypalProcessor->ProcessPayment(50.0);

    std::cout << "\nUsing Stripe:" << std::endl;
    stripeProcessor->ProcessPayment(75.0);

    return 0;
}
*/