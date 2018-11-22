/********************************************************************************
** Form generated from reading UI file 'GLPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLPLAYER_H
#define UI_GLPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GLPlayerClass
{
public:

    void setupUi(QWidget *GLPlayerClass)
    {
        if (GLPlayerClass->objectName().isEmpty())
            GLPlayerClass->setObjectName(QStringLiteral("GLPlayerClass"));
        GLPlayerClass->resize(600, 400);

        retranslateUi(GLPlayerClass);

        QMetaObject::connectSlotsByName(GLPlayerClass);
    } // setupUi

    void retranslateUi(QWidget *GLPlayerClass)
    {
        GLPlayerClass->setWindowTitle(QApplication::translate("GLPlayerClass", "GLPlayer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GLPlayerClass: public Ui_GLPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLPLAYER_H
