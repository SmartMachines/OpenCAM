/**
 * Copyright (c) 2011-2017 by Andrew Mustun. All rights reserved.
 * Copyright (c) 2015 by Robert S. (Modification to draw arc with specified height).
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

include("../Arc.js");

/**
 * \class Arc2PH
 * \brief Arc from two points and height.
 * \ingroup ecma_draw_arc
 */
function Arc2PH(guiAction) {
    Arc.call(this, guiAction);

    this.point1 = undefined;
    this.point2 = undefined;
    this.center = undefined;
    this.height = undefined;
    this.radius = undefined;
    this.reversed = false;

    this.setUiOptions("Arc2PH.ui");
}

Arc2PH.prototype = new Arc();

Arc2PH.State = {
    SettingPoint1 : 0,
    SettingPoint2 : 1
};

Arc2PH.prototype.beginEvent = function() {
    Arc.prototype.beginEvent.call(this);

    this.setState(Arc2PH.State.SettingPoint1);
};

Arc2PH.prototype.setState = function(state) {
    Arc.prototype.setState.call(this, state);

    this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case Arc2PH.State.SettingPoint1:
        this.point1 = undefined;
        this.point2 = undefined;
        this.center = undefined;
        var trStartPoint = qsTr("Start point");
        this.setCommandPrompt(trStartPoint);
        this.setLeftMouseTip(trStartPoint);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case Arc2PH.State.SettingPoint2:
        this.point2 = undefined;
        this.center = undefined;
        var trEndPoint = qsTr("End point");
        this.setCommandPrompt(trEndPoint);
        this.setLeftMouseTip(trEndPoint);
        this.setRightMouseTip(EAction.trBack);
        break;
    }

    EAction.showSnapTools();
};

Arc2PH.prototype.escapeEvent = function() {
    switch (this.state) {
    case Arc2PH.State.SettingPoint1:
        EAction.prototype.escapeEvent.call(this);
        break;

    case Arc2PH.State.SettingPoint2:
        this.setState(Arc2PH.State.SettingPoint1);
        break;
    }
};

Arc2PH.prototype.pickCoordinate = function(event, preview) {
    this.error = "";
    var di = this.getDocumentInterface();

    switch (this.state) {
    case Arc2PH.State.SettingPoint1:
        this.point1 = event.getModelPosition();
        if (!preview) {
            di.setRelativeZero(this.point1);
            this.setState(Arc2PH.State.SettingPoint2);
        }
        break;

    case Arc2PH.State.SettingPoint2:
        this.point2 = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.point2);
                this.setState(Arc2PH.State.SettingPoint1);
            }
        }
        break;
    }

    if (!preview && this.error.length!==0) {
        EAction.handleUserWarning(this.error);
    }
};

Arc2PH.prototype.getOperation = function(preview) {
    var shape = this.getArc2PH(preview);

    if (isNull(shape)) {
        return undefined;
    }

    var doc = this.getDocument();

    var entity = new RArcEntity(doc, new RArcData(shape));

    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

Arc2PH.prototype.getArc2PH = function(preview) {
    if (isNull(this.point1) || isNull(this.point2) || !isNumber(this.height)) {
        return undefined;
    }

    if (this.height <= 0.0 || this.height > 1.0e6) {
        if (!preview) {
            this.error = qsTr("Invalid height");
        }
        return undefined;
    }

    if (this.point1.equalsFuzzy(this.point2)) {
        if (!preview) {
            this.error = qsTr("The two points are identical");
        }
        return undefined;
    }

    var chordlen = this.point1.getDistanceTo(this.point2);
    var archeight = this.height;

    this.radius = (archeight / 2) + ((chordlen * chordlen) / (8 * archeight));

    var circle1 = new RCircle(this.point1, this.radius);
    var circle2 = new RCircle(this.point2, this.radius);

    var ips = circle1.getIntersectionPoints(circle2, false);
    if (ips.length===2) {
        var ipRight, ipLeft;
        var line = new RLine(this.point1, this.point2);
        if (line.getSideOfPoint(ips[0]) === RS.RightHand) {
            ipRight = ips[0];
            ipLeft = ips[1];
        }
        else {
            ipLeft = ips[0];
            ipRight = ips[1];
        }
        if (this.reversed === false) {
            if (this.height > (chordlen / 2)) {
                this.center = ipRight;
            } else {
                this.center = ipLeft;
            }
        } else {
            if (this.height > (chordlen / 2)) {
                this.center = ipLeft;
            } else {
                this.center = ipRight;
            }
        }
    } else {
        // center in the middle:
        var v = new RVector();
        v.setPolar(this.radius, this.point1.getAngleTo(this.point2));
        this.center = this.point1.operator_add(v);
        this.point2 = this.point1.operator_add(v.operator_multiply(2.0));
    }

    var angle1 = this.center.getAngleTo(this.point1);
    var angle2 = this.center.getAngleTo(this.point2);

    return new RArc(this.center, this.radius, angle1, angle2, this.reversed);
};

Arc2PH.prototype.slotHeightChanged = function(value) {
    this.height = value;
    this.updatePreview(true);
};

Arc2PH.prototype.slotDirectionChanged = function(button) {
    if (!isQObject(button) || button.checked!=true) {
        return;
    }

    if (button.objectName==="Clockwise") {
        this.reversed = true;
    }
    else {
        this.reversed = false;
    }

    this.updatePreview(true);
};

Arc2PH.prototype.getAuxPreview = function() {
    if (isNull(this.center) || isNull(this.point1) || isNull(this.point2)) {
        return undefined;
    }

    var ret = [];

    if (this.state==Arc2PH.State.SettingPoint2) {
        ret.push(new RLine(this.center, this.point1));
        ret.push(new RLine(this.center, this.point2));
    }

    return ret;
};
