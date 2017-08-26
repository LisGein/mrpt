/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+
   */
#include "COccupancyConfig.h"
#include "ui_COccupancyConfig.h"
#include "TypeOfConfig.h"

#include <mrpt/utils/CFileOutputStream.h>

using namespace mrpt;
using namespace maps;

COccupancyConfig::COccupancyConfig(mrpt::maps::COccupancyGridMap2D::TMapDefinition* def)
	: CBaseConfig(), m_ui(std::make_unique<Ui::COccupancyConfig>())
{
	m_ui->setupUi(this);
	generateLayoutForWidget(def->genericMapParams, m_ui->generic);
	generateLayoutForWidget(def->insertionOpts, m_ui->insert);
	generateLayoutForWidget(def->likelihoodOpts, m_ui->likelihood);

	setCreationOpt(
		def->min_x, def->max_x, def->min_y, def->max_y, def->resolution);
}

const QString COccupancyConfig::getName()
{
	return QString::fromStdString(typeToName(TypeOfConfig::Occupancy));
}

void COccupancyConfig::updateConfiguration(TMetricMapInitializer* options)
{
	COccupancyGridMap2D::TMapDefinition* mapDefination =
		dynamic_cast<COccupancyGridMap2D::TMapDefinition*>(options);
	assert(mapDefination);

	mapDefination->min_x = m_ui->min_x->value();
	mapDefination->max_x = m_ui->max_x->value();
	mapDefination->min_y = m_ui->min_y->value();
	mapDefination->max_y = m_ui->max_y->value();
	mapDefination->resolution = m_ui->resolution->value();

	getData(mapDefination->genericMapParams);
	getData(mapDefination->insertionOpts);
	getData(mapDefination->likelihoodOpts);
}

TypeOfConfig COccupancyConfig::type() const { return TypeOfConfig::Occupancy; }
void COccupancyConfig::setCreationOpt(
	float min_x, float max_x, float min_y, float max_y, float resolution)
{
	m_ui->min_x->setValue(min_x);
	m_ui->max_x->setValue(max_x);
	m_ui->min_y->setValue(min_y);
	m_ui->max_y->setValue(max_y);
	m_ui->resolution->setValue(resolution);
}

