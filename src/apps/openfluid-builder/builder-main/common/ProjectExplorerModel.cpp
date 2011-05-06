/*
 This file is part of OpenFLUID software
 Copyright (c) 2007-2010 INRA-Montpellier SupAgro


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
 along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

 In addition, as a special exception, INRA gives You the additional right
 to dynamically link the code of OpenFLUID with code not covered
 under the GNU General Public License ("Non-GPL Code") and to distribute
 linked combinations including the two, subject to the limitations in this
 paragraph. Non-GPL Code permitted under this exception must only link to
 the code of OpenFLUID dynamically through the OpenFLUID libraries
 interfaces, and only for building OpenFLUID plugins. The files of
 Non-GPL Code may be link to the OpenFLUID libraries without causing the
 resulting work to be covered by the GNU General Public License. You must
 obey the GNU General Public License in all respects for all of the
 OpenFLUID code and other code used in conjunction with OpenFLUID
 except the Non-GPL Code covered by this exception. If you modify
 this OpenFLUID, you may extend this exception to your version of the file,
 but you are not obligated to do so. If you do not wish to provide this
 exception without modification, you must delete this exception statement
 from your version and license this OpenFLUID solely under the GPL without
 exception.


 == Other Usage ==

 Other Usage means a use of OpenFLUID that is inconsistent with the GPL
 license, and requires a written agreement between You and INRA.
 Licensees for Other Usage of OpenFLUID may use this file in accordance
 with the terms contained in the written agreement between You and INRA.
 */

/**
 \file ProjectExplorerModel.cpp
 \brief Implements ...

 \author Aline LIBRES <libres@supagro.inra.fr>
 */

#include "ProjectExplorerModel.hpp"

#include <boost/foreach.hpp>

// =====================================================================
// =====================================================================


ProjectExplorerModelImpl::ProjectExplorerModelImpl() :
  mp_ModelInstance(0), mp_SimBlob(0), m_ActivatedElementsPair(std::make_pair(
      ProjectExplorerCategories::EXPLORER_NONE, ""))
{

}

// =====================================================================
// =====================================================================


ProjectExplorerModelImpl::~ProjectExplorerModelImpl()
{
  // TODO Auto-generated destructor stub
}

// =====================================================================
// =====================================================================


sigc::signal<void> ProjectExplorerModelImpl::signal_Initialized()
{
  return m_signal_Initialized;
}

// =====================================================================
// =====================================================================


sigc::signal<void> ProjectExplorerModelImpl::signal_ActivationChanged()
{
  return m_signal_ActivationChanged;
}

// =====================================================================
// =====================================================================


sigc::signal<void> ProjectExplorerModelImpl::signal_UpdateModelAsked()
{
  return m_signal_UpdateModelAsked;
}

// =====================================================================
// =====================================================================


sigc::signal<void> ProjectExplorerModelImpl::signal_UpdateDomainAsked()
{
  return m_signal_UpdateDomainAsked;
}

// =====================================================================
// =====================================================================


sigc::signal<void> ProjectExplorerModelImpl::signal_UpdateSimulationAsked()
{
  return m_signal_UpdateSimulationAsked;
}

// =====================================================================
// =====================================================================


sigc::signal<void> ProjectExplorerModelImpl::signal_UpdateResultsAsked()
{
  return m_signal_UpdateResultsAsked;
}

// =====================================================================
// =====================================================================


void ProjectExplorerModelImpl::setEngineRequirements(
    openfluid::machine::ModelInstance& ModelInstance,
    openfluid::machine::SimulationBlob& SimBlob)
{
  mp_ModelInstance = &ModelInstance;
  mp_SimBlob = &SimBlob;

  m_signal_Initialized.emit();
}

// =====================================================================
// =====================================================================


void ProjectExplorerModelImpl::updateModelAsked()
{
  m_signal_UpdateModelAsked.emit();
}

// =====================================================================
// =====================================================================


void ProjectExplorerModelImpl::updateDomainAsked()
{
  m_signal_UpdateDomainAsked.emit();
}

// =====================================================================
// =====================================================================


void ProjectExplorerModelImpl::updateSimulationAsked()
{
  m_signal_UpdateSimulationAsked.emit();
}

// =====================================================================
// =====================================================================


void ProjectExplorerModelImpl::updateResultsAsked()
{
  m_signal_UpdateResultsAsked.emit();
}

// =====================================================================
// =====================================================================


openfluid::machine::ModelInstance* ProjectExplorerModelImpl::getModelInstance()
{
  return mp_ModelInstance;
}

// =====================================================================
// =====================================================================


openfluid::machine::SimulationBlob* ProjectExplorerModelImpl::getSimulationBlob()
{
  return mp_SimBlob;
}

// =====================================================================
// =====================================================================


void ProjectExplorerModelImpl::setActivatedElements(
    std::pair<ProjectExplorerCategories::ProjectExplorerCategory, std::string> ElementsPair)
{
  m_ActivatedElementsPair = ElementsPair;
  m_signal_ActivationChanged.emit();
}

// =====================================================================
// =====================================================================


std::pair<ProjectExplorerCategories::ProjectExplorerCategory, std::string> ProjectExplorerModelImpl::getActivatedElement()
{
  return m_ActivatedElementsPair;
}

//
//void ProjectExplorerModelImpl::extractFunctionNames()
//{
//  BOOST_FOREACH(openfluid::machine::ModelItemInstance* Fct,mp_ModelInstance->getItems())
// {
//    Gtk::TreeRow Row = *(m_refTreeModel->append(ModelRow->children()));
//    Row[m_Columns.m_Val] = Fct->Signature->ID;
//  }
//}
//
//// =====================================================================
//// =====================================================================
//
//
//void ProjectExplorerModelImpl::extratcClassNamesAndInfo()
//{
//
//}
//
//// =====================================================================
//// =====================================================================
//
//
//void ProjectExplorerModelImpl::extractRunInfo()
//{
//
//}
//
//// =====================================================================
//// =====================================================================
//
//
//void ProjectExplorerModelImpl::extractSetNamesAndInfo()
//{
//
//}