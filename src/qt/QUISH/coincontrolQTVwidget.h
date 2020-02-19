// Copyright (c) 2019 The PIVX developers
// Copyright (c) 2020 The QUISH developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLQTVWIDGET_H
#define COINCONTROLQTVWIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlQTVWidget;
}

class CoinControlQTVWidget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlQTVWidget(QWidget *parent = nullptr);
    ~CoinControlQTVWidget();

private:
    Ui::CoinControlQTVWidget *ui;
};

#endif // COINCONTROLQTVWIDGET_H
