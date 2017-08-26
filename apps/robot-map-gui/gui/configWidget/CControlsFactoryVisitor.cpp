/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2017, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+
   */
#include "CControlsFactoryVisitor.h"


void ControlsFactoryVisitor::operator()(const mrpt::utils::CLoadableOptions::PropertyPage &propery)
{

}

void ControlsFactoryVisitor::operator()(const Property::SReflectionOpts<int> &propery)
{
	auto& value = propery.value;
	if (propery.type == Type::SpinBox)
	{
		auto spinBox = new QSpinBox(m_parent);
		spinBox->setRange(propery.min, propery.max);
		spinBox->setSingleStep(propery.step);
		spinBox->setValue(value);
		m_parent->addFunction([spinBox, &value, this]() {
			value = spinBox->value();
		});
		m_res = spinBox;
	}
	else
	{
		auto combobox = new QComboBox(m_parent);
		int i = 0;
		for (auto& item : propery.data)
			combobox->insertItem(i++, QString::fromStdString(item));
		combobox->setCurrentIndex(value);
		m_parent->addFunction([combobox, &value, this]() {
			value = combobox->currentIndex();
		});
		m_res = combobox;
	}
}

void ControlsFactoryVisitor::operator()(const Property::SReflectionOpts<uint32_t> &propery)
{
	auto& value = propery.value;
	auto spinBox = new QSpinBox(m_parent);
	spinBox->setRange(propery.min, propery.max);
	spinBox->setSingleStep(propery.step);
	spinBox->setValue(value);
	m_parent->addFunction([spinBox, &value, this]() {
		value = spinBox->value();
	});
	m_res = spinBox;
}

void ControlsFactoryVisitor::operator()(const Property::SReflectionOpts<bool> &propery)
{
	auto button = new QRadioButton(m_parent);
	button->setAutoExclusive(false);
	button->setChecked(propery.value);
	auto& value = propery.value;
	m_parent->addFunction([button, &value, this]() {
		value = button->isChecked();
	});
	m_res = button;
}

void ControlsFactoryVisitor::operator()(const Property::SReflectionOpts<float> &propery)
{
	auto spinBox = new QDoubleSpinBox(m_parent);
	spinBox->setRange(propery.min, propery.max);
	spinBox->setSingleStep(propery.step);
	spinBox->setValue(propery.value);
	auto& value = propery.value;
	m_parent->addFunction([spinBox, &value, this]() {
		value = spinBox->value();
	});
	m_res = spinBox;
}

void ControlsFactoryVisitor::operator()(const Property::SReflectionOpts<double> &propery)
{
	auto spinBox = new QDoubleSpinBox(m_parent);
	spinBox->setRange(propery.min, propery.max);
	spinBox->setSingleStep(propery.step);
	spinBox->setValue(propery.value);
	auto& value = propery.value;
	m_parent->addFunction([spinBox, &value, this]() {
		value = spinBox->value();
	});
	m_res = spinBox;
}
