/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
 * 
 * This file is part of the QCAD project.
 *
 * QCAD is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QCAD is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QCAD.
 */

include("../../../EAction.js");
include("../../../WidgetFactory.js");

function ToolBarPreferences(guiAction) {
    EAction.call(this, guiAction);
}

ToolBarPreferences.prototype = new EAction();

ToolBarPreferences.getPreferencesCategory = function() {
    return [qsTr("Widgets"), qsTr("Toolbars")];
};

ToolBarPreferences.applyPreferences = function(doc) {
    var appWin = EAction.getMainWindow();
    var children = appWin.children();
    var s = RSettings.getIntValue("ToolBar/IconSize", 32);
    for (var i=0; i<children.length; i++) {
        var c = children[i];
        if (isOfType(c, QToolBar)) {
            c.iconSize = new QSize(s,s);
        }
    }

    // TODO:
    //var optionsToolBar = EAction.getOptionsToolBar();
    //optionsToolBar.setFixedHeight(h);
};

ToolBarPreferences.initPreferences = function(pageWidget, calledByPrefDialog, document) {
    var widgets = getWidgets(pageWidget);
    var prefixChar = widgets["PrefixChar"];
    var rx = new RegExp("[^ \\+\\-]");
    this.validator = new QRegExpValidator(rx, prefixChar);
    prefixChar.setValidator(this.validator);
};
