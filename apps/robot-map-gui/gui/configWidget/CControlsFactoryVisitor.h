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
#include <mrpt/utils/CLoadableOptions.h>

#include "CBaseConfig.h"

#include <QWidget>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>


using Property = mrpt::utils::CLoadableOptions;
using Type = mrpt::utils::CLoadableOptions::TypeOfOptions;

class ControlsFactoryVisitor
{
public:

	ControlsFactoryVisitor(CBaseConfig* parent) : m_parent(parent){}
	QWidget* get() { return m_res; }

	void operator()(const Property::PropertyPage& propery) ;
	void operator()(const Property::SReflectionOpts<int>& propery) ;
	void operator()(const Property::SReflectionOpts<uint32_t>& propery) ;
	void operator()(const Property::SReflectionOpts<bool>& propery);
	void operator()(const Property::SReflectionOpts<float>& propery);
	void operator()(const Property::SReflectionOpts<double>& propery);

private:

	CBaseConfig* m_parent;
	QWidget* m_res;
	std::function<void()> m_updateFunc;
};
