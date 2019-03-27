// Copyright (c) 2011-2013 The Bitcoin developers
// Copyright (c) 2017 The CarbonZero developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_OVERVIEWPAGE_H
#define BITCOIN_QT_OVERVIEWPAGE_H

#include "amount.h"

#include <QWidget>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QUrl>

class ClientModel;
class TransactionFilterProxy;
class TxViewDelegate;
class WalletModel;
class CBlockIndex;

namespace Ui
{
class OverviewPage;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Overview ("home") page widget */
class OverviewPage : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewPage(QWidget* parent = 0);
    ~OverviewPage();

    void setClientModel(ClientModel* clientModel);
    void setWalletModel(WalletModel* walletModel);
    void showOutOfSyncWarning(bool fShow);

public Q_SLOTS:
    void updateNewsList();

public slots:
    void setBalance(const CAmount& balance, const CAmount& unconfirmedBalance, const CAmount& immatureBalance,
                    const CAmount& zerocoinBalance, const CAmount& unconfirmedZerocoinBalance, const CAmount& immatureZerocoinBalance,
                    const CAmount& watchOnlyBalance, const CAmount& watchUnconfBalance, const CAmount& watchImmatureBalance);

    void newsFinished(QNetworkReply *reply);
    void newsReadyRead();
    void newsMetaDataChanged();
    void newsError(QNetworkReply::NetworkError);
signals:
    void transactionClicked(const QModelIndex& index);

private:
    QTimer* timer;
    Ui::OverviewPage* ui;
    ClientModel* clientModel;
    WalletModel* walletModel;
    CAmount currentBalance;
    CAmount currentUnconfirmedBalance;
    CAmount currentImmatureBalance;
    CAmount currentZerocoinBalance;
    CAmount currentUnconfirmedZerocoinBalance;
    CAmount currentimmatureZerocoinBalance;
    CAmount currentWatchOnlyBalance;
    CAmount currentWatchUnconfBalance;
    CAmount currentWatchImmatureBalance;
    double currentTXNS;
    double currentkWh;
    double currentCO2;
    double currentCZT;
    double currentMCap;
    int nDisplayUnit;
    void getPercentage(CAmount nTotalBalance, CAmount nZerocoinBalance, QString& sCZEPercentage, QString& szcarbonPercentage);
    int nHeight;
    int GetHeight() const { return nHeight; }
    TxViewDelegate* txdelegate;
    TransactionFilterProxy* filter;

    void parseXml();
    void newsGet(const QUrl &url);

    QXmlStreamReader xml;

    QNetworkAccessManager manager;
    QNetworkReply *currentReply;

private slots:
    void updateDisplayUnit();
    void handleTransactionClicked(const QModelIndex& index);
    void updateAlerts(const QString& warnings);
    void updateWatchOnlyLabels(bool showWatchOnly);
    void updateCarbonStats();
};

#endif // BITCOIN_QT_OVERVIEWPAGE_H
