#include "plugincurvemenusection.hpp"
#include "plugincurvesection.hpp"

const QString PluginCurveMenuSection::DELETE = "Delete";

PluginCurveMenuSection::PluginCurveMenuSection(PluginCurveSection *section, QWidget *parent):
    QMenu(parent)
{
    Q_UNUSED(section);
    addAction(DELETE);
    addSeparator();
}
