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

CPointsConfig::CPointsConfig()
	: CBaseConfig(), m_ui(std::make_unique<Ui::CPointsConfig>())
{
	m_ui->setupUi(this);

	auto* mapDefination = new mrpt::maps::CSimplePointsMap::TMapDefinition();

	generateLayoutForWidget(
		mapDefination->genericMapParams.dataForVisualize(), m_ui->generic);
	generateLayoutForWidget(
		mapDefination->insertionOpts.dataForVisualize(), m_ui->insert);
	generateLayoutForWidget(
		mapDefination->likelihoodOpts.dataForVisualize(), m_ui->likelihood);
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

	mapDefination->genericMapParams.enableSaveAs3DObject =
		getData<bool>("enableSaveAs3DObject");
	mapDefination->genericMapParams.enableObservationLikelihood =
		getData<bool>("enableObservationLikelihood");
	mapDefination->genericMapParams.enableObservationInsertion =
		getData<bool>("enableObservationInsertion");
	mapDefination->insertionOpts.minDistBetweenLaserPoints =
		CBaseConfig::getData<double>(QString("minDistBetweenLaserPoints"));
	mapDefination->insertionOpts.addToExistingPointsMap =
		getData<bool>("addToExistingPointsMap");
	mapDefination->insertionOpts.also_interpolate =
		getData<bool>("also_interpolate");
	mapDefination->insertionOpts.disableDeletion =
		getData<bool>("disableDeletion");
	mapDefination->insertionOpts.fuseWithExisting =
		getData<bool>("fuseWithExisting");
	mapDefination->insertionOpts.isPlanarMap = getData<bool>("isPlanarMap");
	mapDefination->insertionOpts.horizontalTolerance =
		getData<double>("horizontalTolerance");
	mapDefination->insertionOpts.maxDistForInterpolatePoints =
		getData<double>("maxDistForInterpolatePoints");
	mapDefination->insertionOpts.insertInvalidPoints =
		getData<bool>("insertInvalidPoints");
}

TypeOfConfig CPointsConfig::type() const { return TypeOfConfig::PointsMap; }
void CPointsConfig::setInsertOpt(
	const mrpt::maps::CPointsMap::TInsertionOptions& insertOpt)
{
	setData("minDistBetweenLaserPoints", insertOpt.minDistBetweenLaserPoints);
	setData("addToExistingPointsMap", insertOpt.addToExistingPointsMap);
	setData("also_interpolate", insertOpt.also_interpolate);
	setData("disableDeletion", insertOpt.disableDeletion);
	setData("fuseWithExisting", insertOpt.fuseWithExisting);
	setData("isPlanarMap", insertOpt.isPlanarMap);
	setData("horizontalTolerance", insertOpt.horizontalTolerance);
	setData(
		"maxDistForInterpolatePoints", insertOpt.maxDistForInterpolatePoints);
	setData("insertInvalidPoints", insertOpt.insertInvalidPoints);
}

void CPointsConfig::setLikelihoodOpt(
	const mrpt::maps::CPointsMap::TLikelihoodOptions& likelihoodOpt)
{
	setData("sigma_dist", likelihoodOpt.sigma_dist);
	setData("max_corr_distance", likelihoodOpt.max_corr_distance);
	setData("decimation", likelihoodOpt.decimation);
}
