/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+
   */
#include "CBeaconConfig.h"
#include "ui_CBeaconConfig.h"

using namespace mrpt;
using namespace maps;

CBeaconConfig::CBeaconConfig(mrpt::maps::CBeaconMap::TMapDefinition* mapDefination)
	: CBaseConfig(), m_ui(std::make_unique<Ui::CBeaconConfig>())
{
	m_ui->setupUi(this);

	generateLayoutForWidget(mapDefination->genericMapParams, m_ui->generic);
	generateLayoutForWidget(mapDefination->insertionOpts, m_ui->insert);
	generateLayoutForWidget(mapDefination->likelihoodOpts, m_ui->likelihood);
}

void CBeaconConfig::updateConfiguration(
	mrpt::maps::TMetricMapInitializer* options)
{
	mrpt::maps::CBeaconMap::TMapDefinition* mapDefination =
		dynamic_cast<mrpt::maps::CBeaconMap::TMapDefinition*>(options);
	assert(mapDefination);

	getData(mapDefination->genericMapParams);
	getData(mapDefination->insertionOpts);
	getData(mapDefination->likelihoodOpts);
}

const QString CBeaconConfig::getName()
{
	return QString::fromStdString(typeToName(TypeOfConfig::Beacon));
}

TypeOfConfig CBeaconConfig::type() const { return TypeOfConfig::Beacon; }

