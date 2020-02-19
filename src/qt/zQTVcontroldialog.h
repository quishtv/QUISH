// Copyright (c) 2017-2019 The PIVX developers
// Copyright (c) 2020 The QUISH developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZQTVCONTROLDIALOG_H
#define ZQTVCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zQTV/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZQTVControlDialog;
}

class CZQTVControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZQTVControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZQTVControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZQTVControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZQTVControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZQTVControlDialog(QWidget *parent);
    ~ZQTVControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZQTVControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZQTVControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZQTVCONTROLDIALOG_H
