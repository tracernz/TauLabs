/**
 ******************************************************************************
 *
 * @file       stloadergadgetfactory.h
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

#ifndef STLOADERGADGETFACTORY_H
#define STLOADERGADGETFACTORY_H

#include <coreplugin/iuavgadgetfactory.h>

namespace Core {
	class IUAVGadget;
	class IUAVGadgetFactory;
}

using namespace Core;

class StLoaderGadgetFactory : public Core::IUAVGadgetFactory
{
    Q_OBJECT

public:
    StLoaderGadgetFactory(QObject *parent = 0);
    ~StLoaderGadgetFactory();

    Core::IUAVGadget * createGadget(QWidget *parent);
};

#endif
