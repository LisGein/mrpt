/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+
   */

#pragma once
#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>

#include <cassert>

#include "TypeOfConfig.h"
#include <mrpt/utils/CLoadableOptions.h>

namespace mrpt
{
namespace maps
{
class TMapGenericParams;
struct TMetricMapInitializer;
}
namespace utils
{
class CLoadableOptions;
}
}

class CBaseConfig : public QWidget
{
   public:
	CBaseConfig();
	virtual ~CBaseConfig() = default;

	virtual const QString getName() = 0;
	virtual void updateConfiguration(
		mrpt::maps::TMetricMapInitializer* options) = 0;
	virtual TypeOfConfig type() const = 0;

	template <class T>
	void setLikelihoodOpt(const T& likelihoodOpt);

	void addFunction(const std::function<void()>& f);
	void updateData();

   protected:
	void generateLayoutForWidget(const mrpt::utils::CLoadableOptions &opts, QWidget* parent);

	void setData(const mrpt::utils::CLoadableOptions& opts);
	void getData(const mrpt::utils::CLoadableOptions& opts);


   private:
	std::vector<std::function<void()>> m_functions;
};


template<class T>
void CBaseConfig::setLikelihoodOpt(const T &likelihoodOpt)
{
	setData(likelihoodOpt);
}
