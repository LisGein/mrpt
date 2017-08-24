/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+
   */
#include "CBaseConfig.h"

CBaseConfig::CBaseConfig() : QWidget() {}
using namespace mrpt::utils;
void CBaseConfig::generateLayoutForWidget(
	const CLoadableOptions::Options& opts, QWidget* parent)
{
	bool setLay = false;
	auto layout = dynamic_cast<QVBoxLayout*>(parent->layout());
	if (layout == nullptr)
	{
		setLay = true;
		layout = new QVBoxLayout();
	}
	for (auto& param : opts)
	{
		QString name = QString::fromStdString(param.name);
		auto lay = new QHBoxLayout();
		switch (param.type)
		{
			case CLoadableOptions::SReflectionOpts::RadioButton:
			{
				auto button = new QRadioButton(parent);
				button->setAutoExclusive(false);
				button->setChecked(param.defaultValue);
				m_widgets.emplace(name, button);
				lay->addWidget(button);
				break;
			}
			case CLoadableOptions::SReflectionOpts::SpinBox:
			{
				auto spinBox = new QSpinBox(parent);
				spinBox->setRange(param.min, param.max);
				spinBox->setSingleStep(param.step);
				spinBox->setValue(param.defaultValue);
				m_widgets.emplace(name, spinBox);
				lay->addWidget(spinBox);
				break;
			}
			case CLoadableOptions::SReflectionOpts::DoubleSpinBox:
			{
				auto spinBox = new QDoubleSpinBox(parent);
				spinBox->setRange(param.min, param.max);
				spinBox->setSingleStep(param.step);
				spinBox->setValue(param.defaultValue);
				m_widgets.emplace(name, spinBox);
				lay->addWidget(spinBox);
				break;
			}
			case CLoadableOptions::SReflectionOpts::Combobox:
			{
				auto combobox = new QComboBox(parent);
				int i = 0;
				for (auto& item : param.data)
					combobox->insertItem(i++, QString::fromStdString(item));
				combobox->setCurrentIndex(param.defaultValue);
				m_widgets.emplace(name, combobox);
				lay->addWidget(combobox);
				break;
			}
			default:
				break;
		}

		auto label = new QLabel(name);
		lay->addWidget(label);
		lay->addStretch();

		layout->addLayout(lay);
	}
	layout->addStretch();
	if (setLay) parent->setLayout(layout);
}
