/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+
   */
#include "CPointsConfig.h"
#include "ui_CPointsConfig.h"
#include "TypeOfConfig.h"

CPointsConfig::CPointsConfig(mrpt::maps::CSimplePointsMap::TMapDefinition* mapDefination)
	: CBaseConfig(), m_ui(std::make_unique<Ui::CPointsConfig>())
{
	m_ui->setupUi(this);

	generateLayoutForWidget(mapDefination->genericMapParams, m_ui->generic);
	generateLayoutForWidget(mapDefination->insertionOpts, m_ui->insert);
	generateLayoutForWidget(mapDefination->likelihoodOpts, m_ui->likelihood);
}

CPointsConfig::~CPointsConfig() {}
const QString CPointsConfig::getName()
{
	return QString::fromStdString(typeToName(TypeOfConfig::PointsMap));
}

void CPointsConfig::updateConfiguration(
	mrpt::maps::TMetricMapInitializer* options)
{
	mrpt::maps::CSimplePointsMap::TMapDefinition* mapDefination =
		dynamic_cast<mrpt::maps::CSimplePointsMap::TMapDefinition*>(options);
	assert(mapDefination);

	getData(mapDefination->genericMapParams);
	getData(mapDefination->insertionOpts);
	getData(mapDefination->likelihoodOpts);
}

TypeOfConfig CPointsConfig::type() const { return TypeOfConfig::PointsMap; }
