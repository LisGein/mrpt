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
#include "CControlsFactoryVisitor.h"


CBaseConfig::CBaseConfig() : QWidget() {}

void CBaseConfig::addFunction(const std::function<void ()> &f)
{
	m_functions.push_back(f);
}

using namespace mrpt::utils;
void CBaseConfig::generateLayoutForWidget(
	const CLoadableOptions& opts, QWidget* parent)
{
	bool setLay = false;
	auto layout = dynamic_cast<QVBoxLayout*>(parent->layout());
	if (layout == nullptr)
	{
		setLay = true;
		layout = new QVBoxLayout();
	}

	for (auto& nameAndProperty : opts.getProperties())
	{

		const auto& name = nameAndProperty.first;
		QString optName = QString::fromStdString(name);
		const auto& someProperty = nameAndProperty.second;

		ControlsFactoryVisitor visitor(this);
		mapbox::util::apply_visitor(visitor, someProperty);

		auto lay = new QHBoxLayout();
		auto* control =  visitor.get();
		lay->addWidget(control);/*


		mapbox::util::apply_visitor();
		const auto& optName = nameAndProperty.first;
		const CLoadableOptions::AnyProperty& someProperty = nameAndProperty.second;
		QString name = QString::fromStdString(optName);
		auto lay = new QHBoxLayout();
		switch (someProperty.type)
		{
			case CLoadableOptions::TypeOfOptions::RadioButton:
			{
				auto button = new QRadioButton(parent);
				button->setAutoExclusive(false);
				button->setChecked(someProperty.value);
				m_widgets.emplace(name, button);
				lay->addWidget(button);
				break;
			}
			case CLoadableOptions::TypeOfOptions::SpinBox:
			{
				auto spinBox = new QSpinBox(parent);
				spinBox->setRange(someProperty.min, someProperty.max);
				spinBox->setSingleStep(someProperty.step);
				spinBox->setValue(someProperty.value);
				m_widgets.emplace(name, spinBox);
				lay->addWidget(spinBox);
				break;
			}
			case CLoadableOptions::TypeOfOptions::DoubleSpinBox:
			{
				auto spinBox = new QDoubleSpinBox(parent);
				spinBox->setRange(someProperty.min, someProperty.max);
				spinBox->setSingleStep(someProperty.step);
				spinBox->setValue(someProperty.value);
				m_widgets.emplace(name, spinBox);
				lay->addWidget(spinBox);
				break;
			}
			case CLoadableOptions::TypeOfOptions::Combobox:
			{
				auto combobox = new QComboBox(parent);
				int i = 0;
				for (auto& item : someProperty.data)
					combobox->insertItem(i++, QString::fromStdString(item));
				combobox->setCurrentIndex(someProperty.value);
				m_widgets.emplace(name, combobox);
				lay->addWidget(combobox);
				break;
			}
			default:
				break;
		}*/

		auto label = new QLabel(optName);
		lay->addWidget(label);
		lay->addStretch();

		layout->addLayout(lay);
	}
	layout->addStretch();
	if (setLay) parent->setLayout(layout);
}

void CBaseConfig::setData(const CLoadableOptions &opts)
{

}

void CBaseConfig::getData(const CLoadableOptions &opts)
{

}

void CBaseConfig::updateData()
{
	for (const auto& function : m_functions)
		function();
}
