#ifndef CHARTINFLATOR_H
#define CHARTINFLATOR_H

#include <QObject>
#include <QPoint>

//-----------------------------------------------------

static const QVector<QPoint> input_points
    {
    {   7, 13 },
    {  31, 10 },
    {  61, 9  },
    {  99, 10 },
    { 129, 12 },
    { 178, 20 },
    { 209, 26 }
              };

//-----------------------------------------------------

class ChartInflator : public QObject
{
    Q_OBJECT
private:
    QVector<QPoint> pointers_;
    QVector<QPoint> LSMpointers_; //got by Linear Squares Method array

    void setPointers(const QVector<QPoint>&);

    const QPoint getMin() const;
    const QPoint getMax() const;

    void setLSMpointers();

public:
    explicit ChartInflator(QObject *parent = nullptr);

    Q_INVOKABLE int getPointersSize() const;
    Q_INVOKABLE int getLSMPointersSize() const;

    Q_INVOKABLE const int getX(const int)const;
    Q_INVOKABLE const int getY(const int)const;

    Q_INVOKABLE const int getLSMX(const int)const;
    Q_INVOKABLE const int getLSMY(const int)const;

    Q_INVOKABLE const int getMinX()const;
    Q_INVOKABLE const int getMinY()const;

    Q_INVOKABLE const int getMaxX()const;
    Q_INVOKABLE const int getMaxY()const;



signals:

};

//-----------------------------------------------------

#endif // CHARTINFLATOR_H
