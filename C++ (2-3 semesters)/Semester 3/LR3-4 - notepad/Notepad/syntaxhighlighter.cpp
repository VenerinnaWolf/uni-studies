#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent, const QString& extention) : QSyntaxHighlighter(parent)
{
    parse_xml(extention);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    if (commentStartExpression != QRegularExpression("")) {
        int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = text.indexOf(commentStartExpression);
        while (startIndex >= 0) {
            QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
            int endIndex = match.capturedStart();
            int commentLength = 0;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex
                                + match.capturedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
        }
    }
}

void SyntaxHighlighter::parse_xml(const QString& fileExtention) {
    QFile file(settingsFileName);
    QDomDocument doc;
    if (file.open(QIODevice::ReadOnly)){
        if (doc.setContent(&file)){
            QDomElement element = doc.documentElement();
            QDomElement subElement;
            QDomNode node;

            while (element.tagName() != "syntax") {
                node = element.firstChild();
                element = node.toElement();
            }

            bool extention_found = false;

            while (!node.isNull()) {
                QString ext_list = element.attribute("ext_list");
                if (ext_list.split(" ").contains(fileExtention)) {
                    extention_found = true;
                    break;
                }
                node = node.nextSibling();
                element = node.toElement();
            }

            if (!extention_found) return;

            HighlightingRule rule;

            node = node.firstChild();
            element = node.toElement();

            if (element.tagName() == "keywords") {
                QString key_words = element.attribute("words_list");
                QList<QString> key_words_list = key_words.split(" ");
                keywordFormat.setForeground(QBrush(QColor(element.attribute("foreground"))));
                int a = element.attribute("font_weight").toInt();
                if (a == 75) keywordFormat.setFontWeight(QFont::Bold);
                for (const QString &word : key_words_list) {
                    rule.pattern = QRegularExpression("\\b"+word+"\\b");
                    rule.format = keywordFormat;
                    highlightingRules.append(rule);
                }

                node = node.nextSibling();
                element = node.toElement();
            }

            if (element.tagName() == "multicomment") {
                subElement = element.firstChild().toElement();
                commentStartExpression = QRegularExpression(subElement.attribute("value"));
                subElement = subElement.nextSibling().toElement();
                commentEndExpression = QRegularExpression(subElement.attribute("value"));
                subElement = subElement.nextSibling().toElement();
                multiLineCommentFormat.setForeground(QBrush(QColor(subElement.attribute("foreground"))));
                int a = subElement.attribute("font_weight").toInt();
                if (a == 75) multiLineCommentFormat.setFontWeight(QFont::Bold);

                node = node.nextSibling();
                element = node.toElement();
            }

            while (!node.isNull()) {
                if (element.tagName() == "rule") {
                    HighlightingRule rule;
                    QTextCharFormat format;
                    subElement = element.firstChild().toElement();
                    rule.pattern = QRegularExpression(subElement.attribute("value"));
                    subElement = subElement.nextSibling().toElement();
                    format.setForeground(QBrush(QColor(subElement.attribute("foreground"))));
                    int a = subElement.attribute("font_weight").toInt();
                    if (a == 75) format.setFontWeight(QFont::Bold);
                    rule.format = format;
                    highlightingRules.append(rule);
                }

                node = node.nextSibling();
                element = node.toElement();
            }

        }
        file.close();
    }
}
