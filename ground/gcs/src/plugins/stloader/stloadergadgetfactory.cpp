/**
 ******************************************************************************
 *
 * @file       stloadergadgetfactory.cpp
 * @author     Tau Labs Team, http://www.taulabs.org Copyright (C) 2015.
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @{
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

#include "stloadergadgetfactory.h"
#include "stloadergadgetwidget.h"
#include "stloadergadget.h"
#include "stloadergadgetconfiguration.h"
#include <coreplugin/iuavgadget.h>

StLoaderGadgetFactory::StLoaderGadgetFactory(QObject *parent) :
                IUAVGadgetFactory(QString("STLoader"), tr("STLoader"), parent)
{
}

StLoaderGadgetFactory::~StLoaderGadgetFactory()
{
}

Core::IUAVGadget* StLoaderGadgetFactory::createGadget(QWidget *parent)
{
        StLoaderGadgetWidget *gadgetWidget = new StLoaderGadgetWidget(parent);
        return new StLoaderGadget(QString("STLoader"), gadgetWidget, parent);
}
