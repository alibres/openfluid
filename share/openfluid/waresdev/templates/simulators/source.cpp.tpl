/**
  @file %%ROOTCPPFILENAME%%
*/


/*
<sim2doc>

</sim2doc>
*/


#include <openfluid/ware/PluggableSimulator.hpp>


// =====================================================================
// =====================================================================


BEGIN_SIMULATOR_SIGNATURE("%%WAREID%%")

%%SIGNATUREINFOS%%
%%SIMSIGNATUREDATA%%
END_SIMULATOR_SIGNATURE


// =====================================================================
// =====================================================================


/**

*/
class %%CLASSNAME%% : public openfluid::ware::PluggableSimulator
{
  private:

  
  public:

  
    %%CLASSNAME%%(): PluggableSimulator()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    ~%%CLASSNAME%%()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    void initParams(const openfluid::ware::WareParams_t& /*Params*/)
    {


    }


    // =====================================================================
    // =====================================================================
  
  
    void prepareData()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    void checkConsistency()
    {
  
  
    }
  
  
    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest initializeRun()
    {  
%%SIMINITCODE%%      
      return %%SIMSCHEDRETURN%%;
    }


    // =====================================================================
    // =====================================================================
  
  
    openfluid::base::SchedulingRequest runStep()
    {
%%SIMRUNCODE%%
      return %%SIMSCHEDRETURN%%;
    }


    // =====================================================================
    // =====================================================================
  
  
    void finalizeRun()
    {
  
  
    }

};


// =====================================================================
// =====================================================================


DEFINE_SIMULATOR_CLASS(%%CLASSNAME%%);


// =====================================================================
// =====================================================================


#ifdef OPENFLUID_PARAMSUI_ENABLED

%%PARAMSUICOMMENT%%#include "%%PARAMSUIROOTHPPFILENAME%%"

%%PARAMSUICOMMENT%%DEFINE_PARAMETERIZATIONWIDGET_CLASS(%%PARAMSUICLASSNAME%%)

#endif


