import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.15
import QtQuick.Controls 2.15
import ru.gb.ChartInflator 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property int beautyMargin: 10

    ChartInflator{
        id: chartInflator
    }

    ValueAxis{
        id: valueAxisX
        titleText: qsTr("X")
        min: chartInflator.getMinX() - beautyMargin
        max: chartInflator.getMaxX() + beautyMargin
    }
    ValueAxis{
        id: valueAxisY
        titleText: qsTr("Y")
        min: chartInflator.getMinY() - beautyMargin
        max: chartInflator.getMaxY() + beautyMargin
    }

    ChartView{
        id: chartView
        title: qsTr("test")
        anchors.fill: parent

        ScatterSeries{
            id: scatterSeries
            axisX: valueAxisX
            axisY: valueAxisY

            Component.onCompleted: {
                for(var i = 0; i < chartInflator.getPointersSize(); i++)
                    scatterSeries.append(chartInflator.getX(i), chartInflator.getY(i))
            }
        }
        LineSeries{
            id: lineSeries
            axisX: valueAxisX
            axisY: valueAxisY

            Component.onCompleted: {
                for(var i = 0; i < chartInflator.getLSMPointersSize(); i++)
                    lineSeries.append(chartInflator.getLSMX(i), chartInflator.getLSMY(i))
            }
        }

    }

}
