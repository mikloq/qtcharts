/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qhpiemodelmapper.h"

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QHPieModelMapper
    \mainclass

    Model mappers allow you to use QAbstractItemModel derived models as a data source for a chart series.
    Horizontal model mapper is used to create a connection between QPieSeries and QAbstractItemModel derived model object that keeps the consecutive pie slices data in rows.
    It is possible to use both QAbstractItemModel and QPieSeries model API. QHPieModelMapper makes sure that Pie and the model are kept in sync.
    NOTE: used model has to support adding/removing rows/columns and modifying the data of the cells.
*/
/*!
    \qmlclass HPieModelMapper QHPieModelMapper

    HPieModelMapper allows you to use your own QAbstractItemModel derived model with data in rows as a data source
    for a pie series. It is possible to use both QAbstractItemModel and PieSeries data API to manipulate data.
    HPieModelMapper keeps the Pie and the model in sync.

    The following QML example would create a pie series with four slices (assuming the model has
    at least five columns). Each slice would contain a label from row 1 and a value from row 2.
    \code
        HPieModelMapper {
            series: pieSeries
            model: customModel
            labelsRow: 1
            valuesRow: 2
            firstColumn: 1
            columnCount: 4
        }
    \endcode
*/

/*!
    \property QHPieModelMapper::series
    \brief Defines the QPieSeries object that is used by the mapper.

    All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data)
*/
/*!
    \qmlproperty PieSeries HPieModelMapper::series
    Defines the PieSeries object that is used by the mapper. If you define the mapper element as a child for a
    PieSeries, leave this property undefined. All the data in the series is discarded when it is set to the mapper.
    When new series is specified the old series is disconnected (it preserves its data).
*/

/*!
    \property QHPieModelMapper::model
    \brief Defines the model that is used by the mapper.
*/
/*!
    \qmlproperty SomeModel HPieModelMapper::model
    The QAbstractItemModel based model that is used by the mapper. You need to implement the model and expose it to
    QML as shown in \l {QML Custom Model} demo application. NOTE: the model has to support adding/removing rows/columns
    and modifying the data of the cells.
*/

/*!
    \property QHPieModelMapper::valuesRow
    \brief Defines which row of the model is kept in sync with the values of the pie's slices
    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int HPieModelMapper::valuesRow
    Defines which row of the model is kept in sync with the values of the pie's slices. Default value is: -1 (invalid
    mapping).
*/

/*!
    \property QHPieModelMapper::labelsRow
    \brief Defines which row of the model is kept in sync with the labels of the pie's slices
    Default value is: -1 (invalid mapping)
*/
/*!
    \qmlproperty int HPieModelMapper::labelsRow
    Defines which row of the model is kept in sync with the labels of the pie's slices
    Default value is: -1 (invalid mapping)
*/

/*!
    \property QHPieModelMapper::firstColumn
    \brief Defines which column of the model contains the first slice value.
    Minimal and default value is: 0
*/
/*!
    \qmlproperty int HPieModelMapper::firstColumn
    Defines which column of the model contains the first slice value.
    The default value is 0.
*/

/*!
    \property QHPieModelMapper::columnCount
    \brief Defines the number of columns of the model that are mapped as the data for QPieSeries
    Minimal and default value is: -1 (count limited by the number of columns in the model)
*/
/*!
    \qmlproperty int HPieModelMapper::columnCount
    Defines the number of columns of the model that are mapped as the data for QPieSeries. The default value is
    -1 (count limited by the number of columns in the model)
*/

/*!
    \fn void QHPieModelMapper::seriesReplaced()
    Emitted when the series to which mapper is connected to has changed.
*/

/*!
    \fn void QHPieModelMapper::modelReplaced()
    Emitted when the model to which mapper is connected to has changed.
*/

/*!
    \fn void QHPieModelMapper::valuesRowChanged()
    Emitted when the valuesRow has changed.
*/

/*!
    \fn void QHPieModelMapper::labelsRowChanged()
    Emitted when the labelsRow has changed.
*/

/*!
    \fn void QHPieModelMapper::firstColumnChanged()
    Emitted when the firstColumn has changed.
*/

/*!
    \fn void QHPieModelMapper::columnCountChanged()
    Emitted when the columnCount has changed.
*/

/*!
    Constructs a mapper object which is a child of \a parent.
*/
QHPieModelMapper::QHPieModelMapper(QObject *parent) :
    QPieModelMapper(parent)
{
    setOrientation(Qt::Horizontal);
}

QAbstractItemModel* QHPieModelMapper::model() const
{
    return QPieModelMapper::model();
}

void QHPieModelMapper::setModel(QAbstractItemModel *model)
{
    if (model != QPieModelMapper::model()) {
        QPieModelMapper::setModel(model);
        emit modelReplaced();
    }
}

QPieSeries* QHPieModelMapper::series() const
{
    return QPieModelMapper::series();
}

void QHPieModelMapper::setSeries(QPieSeries *series)
{
    if (series != QPieModelMapper::series()) {
        QPieModelMapper::setSeries(series);
        emit seriesReplaced();
    }
}

/*!
    Returns which row of the model is kept in sync with the values of the pie's slices
*/
int QHPieModelMapper::valuesRow() const
{
    return valuesSection();
}

/*!
    Sets the model row that is kept in sync with the pie slices values.
    Parameter \a valuesRow specifies the row of the model.
*/
void QHPieModelMapper::setValuesRow(int valuesRow)
{
    if (valuesRow != valuesSection()) {
        setValuesSection(valuesRow);
        emit valuesRowChanged();
    }
}

/*!
    Returns which row of the model is kept in sync with the labels of the pie's slices
*/
int QHPieModelMapper::labelsRow() const
{
    return labelsSection();
}

/*!
    Sets the model row that is kept in sync with the pie's slices labels.
    Parameter \a labelsRow specifies the row of the model.
*/
void QHPieModelMapper::setLabelsRow(int labelsRow)
{
    if (labelsRow != labelsSection()) {
        setLabelsSection(labelsRow);
        emit labelsRowChanged();
    }
}

int QHPieModelMapper::firstColumn() const
{
    return first();
}

void QHPieModelMapper::setFirstColumn(int firstColumn)
{
    if (firstColumn != first()) {
        setFirst(firstColumn);
        emit firstColumnChanged();
    }
}

int QHPieModelMapper::columnCount() const
{
    return count();
}

void QHPieModelMapper::setColumnCount(int columnCount)
{
    if (columnCount != count()) {
        setCount(columnCount);
        emit columnCountChanged();
    }
}

#include "moc_qhpiemodelmapper.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
