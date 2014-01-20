/* This file is part of the KDE libraries
   Copyright (C) 2001,2002 Joseph Wenninger <jowenn@kde.org>
   Copyright (C) 2001 Christoph Cullmann <cullmann@kde.org>
   Copyright (C) 1999 Jochen Wilhelmy <digisnap@cs.tu-berlin.de>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef __KATE_SYNTAXMANAGER_H__
#define __KATE_SYNTAXMANAGER_H__

#include "katetextline.h"
#include "kateextendedattribute.h"

#include <ktexteditor/highlightinterface.h>

#include <KConfig>
#include <KActionMenu>

#include <QVector>
#include <QList>
#include <QHash>
#include <QMap>

#include <QObject>
#include <QStringList>
#include <QPointer>
#include <QDate>
#include <QLinkedList>

class KateSyntaxDocument;
class KateHighlighting;

class KateHlManager : public QObject
{
    Q_OBJECT

public:
    KateHlManager();
    ~KateHlManager();

    static KateHlManager *self();

    KateSyntaxDocument *syntaxDocument()
    {
        return syntax;
    }

    inline KConfig *getKConfig()
    {
        return &m_config;
    }

    KateHighlighting *getHl(int n);
    int nameFind(const QString &name);

    QString identifierForName(const QString &);
    /**
     * Returns the mode name for a given identifier, as e.g.
     * returned by KateHighlighting::hlKeyForAttrib().
     */
    QString nameForIdentifier(const QString &);

    // methodes to get the default style count + names
    static uint defaultStyles();
    static QString defaultStyleName(int n, bool translateNames = false);

    void getDefaults(const QString &schema, KateAttributeList &, KConfig *cfg = 0);
    void setDefaults(const QString &schema, KateAttributeList &, KConfig *cfg = 0);

    int highlights();
    QString hlName(int n);
    QString hlNameTranslated(int n);
    QString hlSection(int n);
    bool hlHidden(int n);

    void incDynamicCtxs()
    {
        ++dynamicCtxsCount;
    }
    int countDynamicCtxs()
    {
        return dynamicCtxsCount;
    }
    void setForceNoDCReset(bool b)
    {
        forceNoDCReset = b;
    }

    // be carefull: all documents hl should be invalidated after having successfully called this method!
    bool resetDynamicCtxs();

Q_SIGNALS:
    void changed();

private:
    friend class KateHighlighting;

    // This list owns objects it holds, thus they should be deleted when the object is removed
    QList<KateHighlighting *> hlList;
    // This hash does not own the objects it holds, thus they should not be deleted
    QHash<QString, KateHighlighting *> hlDict;

    KConfig m_config;
    QStringList commonSuffixes;

    KateSyntaxDocument *syntax;

    int dynamicCtxsCount;
    QTime lastCtxsReset;
    bool forceNoDCReset;
};

#endif

