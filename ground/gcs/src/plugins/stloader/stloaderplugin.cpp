
/**
 ******************************************************************************
 *
 * @file       stloaderplugin.cpp
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

#include "stloaderplugin.h"
#include "stloadergadgetfactory.h"
#include <QtPlugin>
#include <QStringList>
#include <extensionsystem/pluginmanager.h>

StLoaderPlugin::StLoaderPlugin()
{
	mf = NULL;
}

StLoaderPlugin::~StLoaderPlugin()
{
}

bool StLoaderPlugin::initialize(const QStringList &args, QString *errMsg)
{
   Q_UNUSED(args);
   Q_UNUSED(errMsg);

   mf = new StLoaderGadgetFactory(this);
   addAutoReleasedObject(mf);

   return true;
}

void StLoaderPlugin::extensionsInitialized()
{
}

void StLoaderPlugin::shutdown()
{
}
