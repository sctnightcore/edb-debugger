/*
Copyright (C) 2006 - 2014 Evan Teran
                          eteran@alum.rit.edu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "DialogInputValue.h"
#include "QULongValidator.h"
#include "QLongValidator.h"
#include "edb.h"

#include <QRegExpValidator>

#include "ui_DialogInputValue.h"

//------------------------------------------------------------------------------
// Name: DialogInputValue
// Desc:
//------------------------------------------------------------------------------
DialogInputValue::DialogInputValue(QWidget *parent) : QDialog(parent), ui(new Ui::DialogInputValue) {
	ui->setupUi(this);

	const QString regex = QString("[A-Fa-f0-9]{0,%1}").arg(edb::v1::pointer_size() * 2);

	ui->hexInput->setValidator(new QRegExpValidator(QRegExp(regex), this));
	ui->signedInput->setValidator(new QLongValidator(LONG_MIN, LONG_MAX, this));
	ui->unsignedInput->setValidator(new QULongValidator(0, ULONG_MAX, this));
}

//------------------------------------------------------------------------------
// Name: ~DialogInputValue
// Desc:
//------------------------------------------------------------------------------
DialogInputValue::~DialogInputValue() {
	delete ui;
}

//------------------------------------------------------------------------------
// Name: value
// Desc:
//------------------------------------------------------------------------------
edb::reg_t DialogInputValue::value() const {
	bool ok;
	return edb::reg_t::fromHexString(ui->hexInput->text(),&ok);
}

//------------------------------------------------------------------------------
// Name: set_value
// Desc:
//------------------------------------------------------------------------------
void DialogInputValue::set_value(edb::reg_t value) {
	ui->hexInput->setText(edb::v1::format_pointer(value));
	ui->signedInput->setText(value.signedToString());
	ui->unsignedInput->setText(value.unsignedToString());
}

//------------------------------------------------------------------------------
// Name: on_hexInput_textEdited
// Desc:
//------------------------------------------------------------------------------
void DialogInputValue::on_hexInput_textEdited(const QString &s) {
	bool ok;
	edb::reg_t value = edb::reg_t::fromHexString(s,&ok);

	if(!ok) {
		value = 0;
	}

	ui->signedInput->setText(value.signedToString());
	ui->unsignedInput->setText(value.unsignedToString());

}

//------------------------------------------------------------------------------
// Name: on_signedInput_textEdited
// Desc:
//------------------------------------------------------------------------------
void DialogInputValue::on_signedInput_textEdited(const QString &s) {
	bool ok;
	edb::reg_t value = edb::reg_t::fromSignedString(s,&ok);

	if(!ok) {
		value = 0;
	}

	ui->hexInput->setText(edb::v1::format_pointer(value));
	ui->unsignedInput->setText(value.unsignedToString());
}

//------------------------------------------------------------------------------
// Name: on_unsignedInput_textEdited
// Desc:
//------------------------------------------------------------------------------
void DialogInputValue::on_unsignedInput_textEdited(const QString &s) {
	bool ok;
	edb::reg_t value = edb::reg_t::fromString(s,&ok);

	if(!ok) {
		value = 0;
	}
	ui->hexInput->setText(edb::v1::format_pointer(value));
	ui->signedInput->setText(value.signedToString());
}
