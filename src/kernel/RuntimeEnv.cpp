/***copyright>=========================================================

  OpenFLUID - Software environment for modelling Fluxes In Landscapes

  This file is a part of OpenFLUID software
  http://www.umr-lisah.fr/openfluid
  Copyright (c) INRA
  See the file "copyright" for the full license governing this code.

=========================================================<copyright***/


/**
  \file
  \brief implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/

#include "RuntimeEnv.h"
#include "config.h"

#include <wx/stdpaths.h>
#include <iostream>
#include <boost/filesystem/operations.hpp>


RuntimeEnvironment::RuntimeEnvironment()
{

  m_UserDataDir = _S(wxStandardPaths::Get().GetUserDataDir()) + _S(wxFILE_SEP_PATH) + "engine";

  m_OutputDir = m_UserDataDir + _S(wxFILE_SEP_PATH) + OPENFLUID_DEFAULT_OUTDIR;
  m_InputDir = m_UserDataDir + _S(wxFILE_SEP_PATH) + OPENFLUID_DEFAULT_INDIR;


  m_ClearOutputDir = false;
  m_QuietRun = false;
  m_VerboseRun = false;
  m_WriteResults = true;
  m_WriteSimReport = true;
  m_CheckVarNames = true;

  m_ProgressiveOutput = false;

  mp_FuncEnv = new openfluid::base::FunctionEnvironment();

  mp_FuncEnv->setValue("dir.input",m_InputDir);
  mp_FuncEnv->setValue("dir.output",m_OutputDir);

  mp_FuncEnv->setValue("mode.cleanoutput",m_ClearOutputDir);
  mp_FuncEnv->setValue("mode.quiet",m_QuietRun);
  mp_FuncEnv->setValue("mode.verbose",m_VerboseRun);
  mp_FuncEnv->setValue("mode.saveresults",m_WriteResults);
  mp_FuncEnv->setValue("mode.writereport",m_WriteSimReport);
  mp_FuncEnv->setValue("mode.checkvarnames",m_CheckVarNames);



  // when development mode (__DEVEL__),
  // use the plugins built on the same development cycle (located in mainappdir/functions)
  #ifdef __LINUX__
  #ifdef __DEVEL__
    m_PlugsDirs.Add(m_AppDir + wxFILE_SEP_PATH + OPENFLUID_PLUGINS_SUBDIR);
  #endif
  #endif

  // plugins search order: user directory then system directory
  m_PlugsDirs.push_back(m_UserDataDir + _S(wxFILE_SEP_PATH) + OPENFLUID_PLUGINS_SUBDIR);

  #ifdef __LINUX__
  #ifndef __DEVEL__
  m_PlugsDirs.push_back(OPENFLUID_PLUGINS_STDSYSDIR);
  #endif
  #endif

  #ifdef __WXMSW__
  m_PlugsDirs.push_back(_S(wxStandardPaths::Get().GetPluginsDir()) + _S(wxFILE_SEP_PATH) + OPENFLUID_PLUGINS_SUBDIR);
  #endif

  // set ignition date time
  m_IgnitionDateTime = boost::posix_time::microsec_clock::local_time();


  // build simulation ID
  std::string BaseStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  m_SimulationID = boost::gregorian::to_iso_string(m_IgnitionDateTime.date()) + "-";

  srand(time(NULL));

  for (int i=0;i<6;i++)
  {
    m_SimulationID = m_SimulationID + BaseStr[rand() % 26];
  }


  m_EffectiveSimulationDuration = boost::posix_time::time_duration();


}

// =====================================================================
// =====================================================================

RuntimeEnvironment::~RuntimeEnvironment()
{

}



// =====================================================================
// =====================================================================


void RuntimeEnvironment::setDateTimeOutputDir()
{
  m_OutputDir = boost::filesystem::path(m_UserDataDir + "/" + "OPENFLUID." + boost::posix_time::to_iso_string(m_IgnitionDateTime) + ".OUT").string();
}


// =====================================================================
// =====================================================================

void RuntimeEnvironment::addExtraPluginsPaths(std::string ColonSeparatedPaths)
{
  std::vector<std::string> ExtraPaths;

  ExtraPaths = SplitString(ColonSeparatedPaths,":");

  for (int i = ExtraPaths.size()-1 ; i>=0 ; i--) m_PlugsDirs.insert(m_PlugsDirs.begin(),1,RemoveTrailingSlashes(ExtraPaths[i]));
}


// =====================================================================
// =====================================================================


std::string RuntimeEnvironment::getPluginFullPath(std::string Filename)
{
  std::string PlugFullPath = "";
  boost::filesystem::path TmpPath;

  unsigned int i = 0;

  while ((PlugFullPath.length() == 0) && (i<m_PlugsDirs.size()))
  {

    TmpPath = boost::filesystem::path(m_PlugsDirs[i] + "/" + Filename);

    if (boost::filesystem::exists(TmpPath)) PlugFullPath = TmpPath.string();

    i++;
  }

  return PlugFullPath;
}


// =====================================================================
// =====================================================================


