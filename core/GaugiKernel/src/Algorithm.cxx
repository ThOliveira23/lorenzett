
#include "GaugiKernel/Algorithm.h"

using namespace Gaugi;


Algorithm::Algorithm(): 
  IMsgService(),
  PropertyService()
{;}

void Algorithm::setStoreGateSvc( SG::StoreGate *store )
{
  m_store = store;
}

SG::StoreGate* Algorithm::getStoreGateSvc() const
{
  return m_store;
}

const std::string& Algorithm::name() const
{
  return getLogName();
}



