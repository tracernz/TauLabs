/**
 ******************************************************************************
 *
 * @file       stloadergadget.h
 * @author     Tau Labs Team, http://www.taulabs.org Copyright (C) 2015.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @{
 * @brief Gadget for loading STM32 devices
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef STLOADERGADGET_H
#define STLOADERGADGET_H

#include <coreplugin/iuavgadget.h>
#include "stloadergadgetwidget.h"

class IUAVGadget;
class QWidget;
class QString;
class StLoaderGadgetWidget;

using namespace Core;

class StLoaderGadget : public Core::IUAVGadget
{
    Q_OBJECT
public:
    StLoaderGadget(QString classId, StLoaderGadgetWidget *widget, QWidget *parent = 0);
    ~StLoaderGadget();

    QWidget *widget() { return m_widget; }
    void loadConfiguration(IUAVGadgetConfiguration* config);

private:
    StLoaderGadgetWidget *m_widget;
};

#endif
