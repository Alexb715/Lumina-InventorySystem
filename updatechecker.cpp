#include "updatechecker.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUrl>

#ifndef APP_VERSION
#define APP_VERSION "0.0.0"
#endif

static const char *RELEASES_URL =
    "https://api.github.com/repos/AlexB715/Lumina-InventorySystem/releases/latest";

UpdateChecker::UpdateChecker(QObject *parent)
    : QObject(parent) {
    connect(&m_manager, &QNetworkAccessManager::finished,
            this, &UpdateChecker::onReplyFinished);
}

void UpdateChecker::checkForUpdates() {
    QNetworkRequest request{QUrl(RELEASES_URL)};
    request.setHeader(QNetworkRequest::UserAgentHeader, "LuminaInventorySystem");
    m_manager.get(request);
}

void UpdateChecker::onReplyFinished(QNetworkReply *reply) {
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Update check failed:" << reply->errorString();
        return;
    }

    auto doc = QJsonDocument::fromJson(reply->readAll());
    if (!doc.isObject()) return;

    QString tag = doc.object().value("tag_name").toString();
    QString url = doc.object().value("html_url").toString();

    // Strip leading 'v' from tag
    QString latestVersion = tag.startsWith('v') ? tag.mid(1) : tag;
    QString currentVersion = QString(APP_VERSION);

    if (latestVersion.isEmpty() || currentVersion == "0.0.0") return;

    // Simple version comparison: split on '.', compare each segment
    auto current = currentVersion.split('.');
    auto latest = latestVersion.split('.');

    for (int i = 0; i < qMax(current.size(), latest.size()); ++i) {
        int c = (i < current.size()) ? current[i].toInt() : 0;
        int l = (i < latest.size()) ? latest[i].toInt() : 0;
        if (l > c) {
            emit updateAvailable(latestVersion, url);
            return;
        }
        if (c > l) return;
    }
}
