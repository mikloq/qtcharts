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

#include "qarealegendmarker.h"
#include "qarealegendmarker_p.h"
#include "qareaseries_p.h"
#include <QAreaSeries>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

/*!
    \class QAreaLegendMarker
    \brief QAreaLegendMarker object
    \mainclass

    QAreaLegendMarker is related to QAreaSeries. One QAreaSeries results in one marker.

    \sa QLegend QAreaSeries
*/

/*!
  \fn virtual LegendMarkerType QAreaLegendMarker::type()
  Returns QLegendMarker::LegendMarkerTypeArea
*/

/*!
  Constructor
*/
QAreaLegendMarker::QAreaLegendMarker(QAreaSeries *series, QLegend *legend, QObject *parent) :
    QLegendMarker(*new QAreaLegendMarkerPrivate(this,series,legend), parent)
{
}

/*!
  Destructor
*/
QAreaLegendMarker::~QAreaLegendMarker()
{
}

/*!
    \internal
*/
QAreaLegendMarker::QAreaLegendMarker(QAreaLegendMarkerPrivate &d, QObject *parent) :
    QLegendMarker(d, parent)
{
}

/*!
  Returns related series of marker
*/
QAreaSeries* QAreaLegendMarker::series()
{
    Q_D(QAreaLegendMarker);
    return d->m_series;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

QAreaLegendMarkerPrivate::QAreaLegendMarkerPrivate(QAreaLegendMarker *q, QAreaSeries *series, QLegend *legend) :
    QLegendMarkerPrivate(q,legend),
    m_series(series)
{
    QObject::connect(m_series->d_func(),SIGNAL(updated()), this, SLOT(updated()));
    QObject::connect(m_series, SIGNAL(nameChanged()), this, SLOT(updated()));
    updated();
}

QAreaLegendMarkerPrivate::~QAreaLegendMarkerPrivate()
{
}

QAreaSeries* QAreaLegendMarkerPrivate::series()
{
    return m_series;
}

QObject* QAreaLegendMarkerPrivate::relatedObject()
{
    return m_series;
}

void QAreaLegendMarkerPrivate::updated()
{
    bool labelChanged = false;
    bool brushChanged = false;

    if (m_item->brush() != m_series->brush()) {
        m_item->setBrush(m_series->brush());
        brushChanged = true;
    }
    if (m_item->label() != m_series->name()) {
        m_item->setLabel(m_series->name());
        labelChanged = true;
    }
    invalidateLegend();

    if (labelChanged)
        emit q_ptr->labelChanged();
    if (brushChanged)
        emit q_ptr->brushChanged();
}

#include "moc_qarealegendmarker.cpp"
#include "moc_qarealegendmarker_p.cpp"

QTCOMMERCIALCHART_END_NAMESPACE
