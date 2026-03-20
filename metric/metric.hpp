#pragma once
#include "Graph.hpp"

/**
 * Базовый интерфейс для всех метрик.
 * Наследуйся от него и реализуй compute() + нужный getter.
 */
class IMetric {
public:
    virtual ~IMetric() {}
    
    // Вычислить метрику на графе
    virtual void compute(const Graph& g) = 0;
    
    // Геттеры для разных типов результатов
    virtual int getIntResult() const { return 0; }
    virtual double getDoubleResult() const { return 0.0; }
    virtual bool getBoolResult() const { return false; }
};
