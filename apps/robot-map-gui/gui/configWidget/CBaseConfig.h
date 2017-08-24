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

   protected:
	void generateLayoutForWidget(
		const mrpt::utils::CLoadableOptions::Options& opts, QWidget* parent);

	template <class T>
	T getData(const QString& str);

	template <class T>
	void setData(const QString& str, const T& data);

	std::map<QString, QWidget*> m_widgets;
};

template <class T>
T CBaseConfig::getData(const QString& str)
{
	auto iter = m_widgets.find(str);
	assert(iter != m_widgets.end() && iter->second != nullptr);

	auto radioButton = dynamic_cast<QRadioButton*>(iter->second);
	if (radioButton) return radioButton->isChecked();

	auto spinBox = dynamic_cast<QSpinBox*>(iter->second);
	if (spinBox) return spinBox->value();

	auto doubleSpinBox = dynamic_cast<QDoubleSpinBox*>(iter->second);
	if (doubleSpinBox) return doubleSpinBox->value();

	auto combobox = dynamic_cast<QComboBox*>(iter->second);
	if (combobox) return combobox->currentIndex();

	throw "Didn't find this type!";
	return T(0);
}

template <class T>
void CBaseConfig::setData(const QString& str, const T& data)
{
	auto iter = m_widgets.find(str);
	assert(iter != m_widgets.end() && iter->second != nullptr);

	auto radioButton = dynamic_cast<QRadioButton*>(iter->second);
	if (radioButton)
	{
		radioButton->setChecked(data);
		return;
	}

	auto spinBox = dynamic_cast<QSpinBox*>(iter->second);
	if (spinBox)
	{
		spinBox->setValue(data);
		return;
	}

	auto doubleSpinBox = dynamic_cast<QDoubleSpinBox*>(iter->second);
	if (doubleSpinBox)
	{
		doubleSpinBox->setValue(data);
		return;
	}

	auto combobox = dynamic_cast<QComboBox*>(iter->second);
	if (combobox)
	{
		combobox->setCurrentIndex(data);
		return;
	}

	throw "Didn't find this type!";
	return;
}
