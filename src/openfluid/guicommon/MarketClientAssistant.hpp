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
  \file MarketClientAssistant.hpp
  \brief Header of ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#ifndef __MARKETCLIENTASSISTANT_HPP__
#define __MARKETCLIENTASSISTANT_HPP__

#include <gtkmm/assistant.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/combobox.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treestore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/alignment.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/textview.h>
#include <gtkmm/notebook.h>
#include <gtkmm/paned.h>

#include <openfluid/dllexport.hpp>
#include <openfluid/market/MarketClient.hpp>


namespace openfluid { namespace guicommon {

class MarketPackWidget;


class DLLEXPORT MarketClientAssistant : public Gtk::Assistant
{

  private:

    // ===== Package selection =====//
    Gtk::VBox m_SelectionPageBox;

    Gtk::HBox m_URLBox;
    Gtk::Label m_URLLabel;
    Gtk::ComboBox m_URLCombo;
    Glib::RefPtr<Gtk::ListStore> m_RefURLComboBoxModel;

    class URLComboColumns : public Gtk::TreeModel::ColumnRecord
    {
      public:

        Gtk::TreeModelColumn<Glib::ustring> m_Name;
        Gtk::TreeModelColumn<Glib::ustring> m_URL;

        URLComboColumns() { add(m_Name); add(m_URL); }
    };

    URLComboColumns m_URLColumns;


    Gtk::Notebook m_TypesTabs;

    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::VBox*> mp_TabBox;

    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::VBox*> mp_AvailTypesPacksBox;
    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::ScrolledWindow*> mp_AvailTypesPacksSWindow;

    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::HBox*> mp_ActionButtonsBox;
    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::Button*> mp_SelectAllButton;
    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::Button*> mp_SelectNoneButton;
    std::map<openfluid::market::PackageInfo::TypePackage,Gtk::Button*> mp_CommonBuildConfigButton;

    std::map<openfluid::market::PackageInfo::TypePackage,std::list<MarketPackWidget*> > mp_AvailPacksWidgets;

    void onURLComboChanged();

    void onPackageInstallModified();

    void onSelectAllClicked();

    void onSelectNoneClicked();

    void onCommonBuildConfigClicked();


    // ===== Licenses =====//
    Gtk::VBox m_LicensesPageBox;

    Gtk::Label m_LicensesLabel;

    Gtk::HPaned m_LicensesReviewPaned;
    Gtk::TreeView m_LicensesTreeView;

    Glib::RefPtr<Gtk::TreeStore> m_RefLicenseTreeViewModel;


    class LicensesTreeViewColumns : public Gtk::TreeModel::ColumnRecord
    {
      public:

        Gtk::TreeModelColumn<Glib::ustring> m_ID;

        LicensesTreeViewColumns() { add(m_ID); }
    };

    LicensesTreeViewColumns m_LicensesColumns;

    Glib::RefPtr<Gtk::TreeSelection> m_RefLicensesTreeSelection;

    Gtk::TextView m_LicensesTextView;

    Glib::RefPtr<Gtk::TextBuffer> m_RefLicenseTextBuffer;


    Gtk::ScrolledWindow m_LicensesListSWindow;
    Gtk::ScrolledWindow m_LicensesReviewSWindow;

    Gtk::RadioButton m_LicensesAcceptRadio;
    Gtk::RadioButton m_LicensesDoNotRadio;


    void onLicensesTreeviewChanged();

    void onLicenseRadioClicked();

    // ===== Download and install =====//
    Gtk::VBox m_InstallPageBox;

    Gtk::TreeView m_InstallTreeView;
    Glib::RefPtr<Gtk::TreeView> m_RefInstallTreeView;

    Glib::RefPtr<Gtk::ListStore> m_RefInstallTreeViewModel;

    class InstallTreeViewColumns : public Gtk::TreeModel::ColumnRecord
    {
      public:

        Gtk::TreeModelColumn<Glib::ustring> m_ID;
        Gtk::TreeModelColumn<Glib::ustring> m_Format;
        Gtk::TreeModelColumn<Glib::ustring> m_Status;

        InstallTreeViewColumns() { add(m_ID); add(m_Format); add(m_Status);}
    };

    InstallTreeViewColumns m_InstallColumns;


    Gtk::ScrolledWindow m_InstallSWindow;
    Gtk::ProgressBar m_InstallProgressBar;
    Gtk::Button m_ViewLogButton;
    Gtk::Alignment m_LogButtonAlign;

    void onInstallTimeoutOnce();

    void onViewLogClicked();


    void setupSelectionPage();
    void setupConfirmationPage();
    void setupLicensesPage();
    void setupDownloadPage();


    void onApply();
    void onCancel();
    void onClose();
    void onPrepare(Gtk::Widget* Widget);

    void updateAvailPacksTreeview();

    void updateInstallTreeview();

    void initializeLicencesTreeView();

    openfluid::market::MarketClient m_MarketClient;

    int m_InstallationTimeout;

  public:
    MarketClientAssistant();

    virtual ~MarketClientAssistant();


};

} } //namespaces


#endif /* __MARKETCLIENTASSISTANT_HPP__ */
