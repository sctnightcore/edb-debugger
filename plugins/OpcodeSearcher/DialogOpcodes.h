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

#ifndef DIALOGOPCODES_20061101_H_
#define DIALOGOPCODES_20061101_H_

#include "Types.h"
#include "Instruction.h"

#include <QDialog>
#include <QList>
#include <vector>

class QSortFilterProxyModel;
class QListWidgetItem;

namespace OpcodeSearcherPlugin {

namespace Ui { class DialogOpcodes; }

class DialogOpcodes : public QDialog {
	Q_OBJECT

public:
    explicit DialogOpcodes(QWidget *parent = nullptr);
    ~DialogOpcodes() override;

public Q_SLOTS:
	void on_btnFind_clicked();
	void on_listWidget_itemDoubleClicked(QListWidgetItem *);

private:
	using InstructionList = std::vector<edb::Instruction *>;

private:
	// we currently only support opcodes sequences up to 8 bytes big
	union OpcodeData {
		quint32 dword;
		quint64 qword;
		quint8  data[sizeof(quint64)];
	};

	void test_esp_add_0(const OpcodeData &data, edb::address_t start_address);
	void test_esp_add_regx1(const OpcodeData &data, edb::address_t start_address);
	void test_esp_add_regx2(const OpcodeData &data, edb::address_t start_address);
	void test_esp_sub_regx1(const OpcodeData &data, edb::address_t start_address);
	void do_find();
	void add_result(const InstructionList &instructions, edb::address_t rva);
	void run_tests(int classtype, const OpcodeData &opcode, edb::address_t address);

	template <int REG>
	void test_reg_to_ip(const OpcodeData &data, edb::address_t start_address);

	template <int REG>
	void test_deref_reg_to_ip(const OpcodeData &data, edb::address_t start_address);

private:
    virtual void showEvent(QShowEvent *event) override;

private:
	Ui::DialogOpcodes *const ui;
	QSortFilterProxyModel *  filter_model_;
};

}

#endif
