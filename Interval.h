//
// Created by 94164 on 2023/10/6.
// 管理具有最小值和最大值的实值区间类
//

#ifndef RAYTRACING_INTERVAL_H
#define RAYTRACING_INTERVAL_H

#include <cmath>
#include <limits>

#include "Utils.h"

class Interval {
public:
    Interval() : m_Min(Infinity), m_Max(-Infinity) {}
    Interval(double min, double max) : m_Min(min), m_Max(max) {}

    double Min() const { return m_Min; }
    double Max() const { return m_Max; }

    bool Contains(double value) const {
        return value >= m_Min && value <= m_Max;
    }
    bool Surrounds(double value) const {
        return m_Min < value && value < m_Max;
    }

private:
    double m_Min;
    double m_Max;
};

const static Interval Empty = Interval(Infinity, -Infinity);
const static Interval Universe = Interval(-Infinity, Infinity);

#endif //RAYTRACING_INTERVAL_H
