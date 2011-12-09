// MarketModel.cpp
// Implements the MarketModel Class

#include "MarketModel.h"
#include "InputXML.h"
#include "CycException.h"
#include "Timer.h"

#include "Logger.h"
#include <string>

using namespace std;

MarketModel::MarketModel() {
  setModelType("Market");

  TI->registerResolveListener(this);
  MarketModel::markets.push_back(this);
};

MarketModel* marketForCommod(std::string commod) {
  MarketModel* market = NULL;
  for (int i = 0; i < MarketModel::markets.size(); i++) {
    if (MarketModel::markets.at(i).commodity() == commod) {
      market = MarketModel::markets.at(i);
      break;
    }
  }

  if (market == NULL) {
    std::string err_msg = "No market found for commodity '";
    err_msg += commod + "'.";
    throw CycNullException(err_msg);
  }
  return market;
}
  
void MarketModel::init(xmlNodePtr cur)
{
  Model::init(cur);
  
  /** 
   *  Specific initialization for MarketModels
   */

  /// all markets require commodities
  string commodity_ = XMLinput->get_xpath_content(cur,"mktcommodity");
}

void MarketModel::copy(MarketModel* src) {
  Model::copy(src);
  Communicator::copy(src);

   /** 
   *  Specific initialization for MarketModels
   */

  commodity_ = src->commodity();
}

void MarketModel::print() { 
  Model::print(); 

  LOG(LEV_DEBUG2) << "    trades commodity " << commodity_;

};

