/*
Copyright (C) 2006 - 2015 Evan Teran
                          evan.teran@gmail.com

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

#ifndef DIALOGINPUTVALUE_20061101_H_
#define DIALOGINPUTVALUE_20061101_H_

#include "Types.h"

#include <QDialog>

#include "ui_DialogInputValue.h"

class Register;

class DialogInputValue : public QDialog {
	Q_OBJECT

public:
    explicit DialogInputValue(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~DialogInputValue() override = default;

public Q_SLOTS:
	void on_hexInput_textEdited(const QString &);
	void on_signedInput_textEdited(const QString &);
	void on_unsignedInput_textEdited(const QString &);

public:
	edb::reg_t value() const;
	void set_value(Register &reg);

private:
	Ui::DialogInputValue ui;
	edb::reg_t mask;
	std::size_t valueLength;
};

#endif
