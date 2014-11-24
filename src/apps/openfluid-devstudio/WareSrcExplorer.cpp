/*

 This file is part of OpenFLUID software
 Copyright(c) 2007, INRA - Montpellier SupAgro


 == GNU General Public License Usage ==

 OpenFLUID is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenFLUID is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

 Other Usage means a use of OpenFLUID that is inconsistent with the GPL
 license, and requires a written agreement between You and INRA.
 Licensees for Other Usage of OpenFLUID may use this file in accordance
 with the terms contained in the written agreement between You and INRA.

 */

/**
 \file WareSrcExplorer.cpp
 \brief Implements ...

 \author Aline LIBRES <aline.libres@gmail.com>
 */

#include "WareSrcExplorer.hpp"

#include <QFileSystemModel>

#include "DevStudioFileIconProvider.hpp"

WareSrcExplorer::WareSrcExplorer(QWidget* Parent) :
    QTreeView(Parent)
{
  mp_Model = new QFileSystemModel();
  setModel(mp_Model);
  hideColumn(1);
  hideColumn(2);
  hideColumn(3);
}


// =====================================================================
// =====================================================================


WareSrcExplorer::~WareSrcExplorer()
{

}


// =====================================================================
// =====================================================================


void WareSrcExplorer::setType(openfluid::waresdev::Tools::SrcType Type)
{
  QString Path = openfluid::waresdev::Tools::getCurrentSrcDir(Type);

  mp_Model->setRootPath(Path);
  setRootIndex(mp_Model->index(Path));
  mp_Model->setIconProvider(new DevStudioFileIconProvider(Path));
}


// =====================================================================
// =====================================================================


