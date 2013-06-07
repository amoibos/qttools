/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#ifndef ATWRAPPER_H
#define ATWRAPPER_H

#include <QHash>
#include <QString>
#include <QUrlInfo>
#include <QList>
#include <QImage>

class uiLoader : public QObject
{
    Q_OBJECT

    public:
        uiLoader(const QString &pathToProgram);

        enum TestResult { TestRunDone, TestConfigError, TestNoConfig };
        TestResult runAutoTests(QString *errorMessage);

    private:
        bool loadConfig(const QString &, QString *errorMessage);
        void initTests();

        void setupFTP();
        void setupLocal();
        void clearDirectory(const QString&);

        void ftpMkDir( QString );
        void ftpGetFiles(QList<QString>&, const QString&,  const QString&);
        void ftpList(const QString&);
        void ftpClearDirectory(const QString&);
        bool ftpUploadFile(const QString&, const QString&);
        void executeTests();

        void createBaseline();
        void downloadBaseline();

        bool compare();

        void diff(const QString&, const QString&, const QString&);
        int imgDiff(const QString fileA, const QString fileB, const QString output);
        QStringList uiFiles() const;
    
        QHash<QString, QString> enginesToTest;

        QString framework;
        QString suite;
        QString output;
        QString ftpUser;
        QString ftpPass;
        QString ftpHost;
        QString ftpBaseDir;
        QString threshold;

        QString errorMsg;

        QList<QString> lsDirList;
        QList<QString> lsNeedBaseline;

        QString configPath;
        
        QString pathToProgram;

    private slots:
        //void ftpAddLsDone( bool );
        void ftpAddLsEntry( const QUrlInfo &urlInfo );
};

#endif
