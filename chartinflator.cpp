#include "chartinflator.h"
#include <limits>
#include <QtMath>

//-----------------------------------------------------

ChartInflator::ChartInflator(QObject *parent)
    : QObject{ parent },
      pointers_{},
      LSMpointers_{}
{
    setPointers(input_points);
    setLSMpointers();
}

//-----------------------------------------------------

void ChartInflator::setPointers(const QVector<QPoint> &other_vec)
{
    pointers_ = other_vec;
}

//-----------------------------------------------------

void ChartInflator::setLSMpointers(){

    int n = pointers_.size();
    double x[n], y[n], a, b;

    for (int i{} ; i < n; i++)
    {
        x[i] = pointers_.at(i).x();
        y[i] = pointers_.at(i).y();
    }

    double xsum{}, x2sum{}, ysum{}, xysum{};

    for (int i{}; i < n; i++)
    {
        xsum = xsum + x[i];                        
        ysum = ysum + y[i];                       
        x2sum = x2sum + qPow(x[i], 2);           
        xysum = xysum +x[i] * y[i];             
    }

    a = (n * xysum - xsum * ysum)/(n * x2sum - xsum * xsum);            
    b = (x2sum * ysum - xsum * xysum)/(x2sum * n - xsum * xsum);       

    double new_y[n];                        

    for (int i{}; i < n; i++)
        new_y[i] = a * x[i] + b;


    for (int i{}; i < n; i++)
    {
        LSMpointers_.push_back({ pointers_.at(i).x(), new_y[i] });
    }
}

//-----------------------------------------------------

int ChartInflator::getPointersSize()const{
    return pointers_.size();
}

//-----------------------------------------------------

int ChartInflator::getLSMPointersSize()const{
    return LSMpointers_.size();
}

//-----------------------------------------------------

const int ChartInflator::getX(const int index) const
{
    return pointers_.at(index).x();
}


//-----------------------------------------------------

const int ChartInflator::getY(const int index) const
{
    return pointers_.at(index).y();
}

//-----------------------------------------------------

const int ChartInflator::getLSMX(const int index) const
{
    return LSMpointers_.at(index).x();
}


//-----------------------------------------------------

const int ChartInflator::getLSMY(const int index) const
{
    return LSMpointers_.at(index).y();
}

//-----------------------------------------------------

const QPoint ChartInflator::getMin() const
{
    QPoint ret_val {
        std::numeric_limits<int>::max(),
                std::numeric_limits<int>::max()
    };

    for (auto value : pointers_)
    {
        if (ret_val.rx() > value.rx())
            ret_val.rx() = value.rx();

        if (ret_val.ry() > value.ry())
            ret_val.ry() = value.ry();
    }

    return ret_val;
}

//-----------------------------------------------------

const QPoint ChartInflator::getMax() const
{
    QPoint ret_val {
        std::numeric_limits<int>::min(),
                std::numeric_limits<int>::min()
    };

    for (auto value : pointers_)
    {
        if (ret_val.rx() < value.rx())
            ret_val.rx() = value.rx();

        if (ret_val.ry() < value.ry())
            ret_val.ry() = value.ry();
    }

    return ret_val;

}

//-----------------------------------------------------

const int ChartInflator::getMinX()const{
    return getMin().x();
}

//-----------------------------------------------------

const int ChartInflator::getMinY()const{
    return getMin().y();
}

//-----------------------------------------------------

const int ChartInflator::getMaxX()const{
    return getMax().x();
}

//-----------------------------------------------------

const int ChartInflator::getMaxY()const{
    return getMax().y();
}

//-----------------------------------------------------

