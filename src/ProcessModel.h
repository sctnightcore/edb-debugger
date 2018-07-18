/*
Copyright (C) 2014 - 2015 Evan Teran
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

#ifndef PROCESS_MODEL_H_
#define PROCESS_MODEL_H_

#include "OSTypes.h"

#include <QAbstractItemModel>
#include <QString>
#include <QVector>

#include <memory>

class IProcess;

class ProcessModel : public QAbstractItemModel {
	Q_OBJECT

public:
	struct Item {
		edb::pid_t pid;
		edb::uid_t uid;
		QString    user;
		QString    name;
	};

public:
    explicit ProcessModel(QObject *parent = nullptr);
    ~ProcessModel() override = default;

public:
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual QModelIndex parent(const QModelIndex &index) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

public:
	void addProcess(const std::shared_ptr<IProcess> &process);
	void clear();

private:
	QVector<Item> items_;
};

#endif
