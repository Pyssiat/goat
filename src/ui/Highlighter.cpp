#include "Highlighter.h"

#include <QDebug>
#include <QSettings>
#include <QResource>
#include <QXmlStreamReader>

Highlighter::Highlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    QSettings settings(":/syntax/sql.ini", QSettings::IniFormat, this);

    QStringList keys;
    keys.append("1");
    keys.append("2");
    keys.append("3");
    keys.append("4");
    keys.append("5");
    keys.append("6");
    keys.append("7");
    keys.append("8");

    foreach (QString key, keys)
    {
        settings.beginGroup(key);

        QString type = settings.value("TYPE").toString();
        QStringList items = settings.value("ITEMS").toStringList();
        QString color = settings.value("COLOR").toString();
        QString regexp = settings.value("REGEXP").toString();
        QStringList modifiers = settings.value("MODIFIERS").toStringList();

        settings.endGroup();

        QTextCharFormat format;
        format.setForeground(QColor(color));
        rule.format = format;

        QString string_expression;
        if (items.isEmpty()) string_expression = regexp;
        else string_expression = regexp.replace("___ITEMLIST___", items.join("|"), Qt::CaseInsensitive);

        QRegularExpression expression;
        expression.setPattern(string_expression);

        foreach (QString modifier, modifiers)
        {
            if (modifier == "i") expression.setPatternOptions(expression.patternOptions() | QRegularExpression::CaseInsensitiveOption);
            if (modifier == "m") expression.setPatternOptions(expression.patternOptions() | QRegularExpression::MultilineOption);
            if (modifier == "s") expression.setPatternOptions(expression.patternOptions() | QRegularExpression::DotMatchesEverythingOption);
        }

        rule.format=format;
        rule.pattern = expression;

        highlightingRules_new.append(rule);
    }
}


void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules_new) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}
