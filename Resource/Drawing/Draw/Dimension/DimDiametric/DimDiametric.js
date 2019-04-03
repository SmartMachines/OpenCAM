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

include("../Dimension.js");

function DimDiametric(guiAction) {
    Dimension.call(this, guiAction);

    this.data = new RDimDiametricData();
    this.setUiOptions("../Dimension.ui");
    this.entity = undefined;
    this.shape = undefined;
    this.pos = undefined;
}

DimDiametric.prototype = new Dimension();

DimDiametric.State = {
    SettingEntity : 0,
    SettingDimPos : 1
};

DimDiametric.prototype.beginEvent = function() {
    Dimension.prototype.beginEvent.call(this);

    this.setState(DimDiametric.State.SettingEntity);
};

DimDiametric.prototype.setState = function(state) {
    Dimension.prototype.setState.call(this, state);

    this.setCrosshairCursor();

    var appWin = RMainWindowQt.getMainWindow();
    switch (this.state) {
    case DimDiametric.State.SettingEntity:
        this.getDocumentInterface().setClickMode(RAction.PickEntity);
        this.entity = undefined;
        this.shape = undefined;
        this.pos = undefined;
        var trEntity = qsTr("Choose arc or circle entity");
        this.setCommandPrompt(trEntity);
        this.setLeftMouseTip(trEntity);
        this.setRightMouseTip(EAction.trCancel);
        break;

    case DimDiametric.State.SettingDimPos:
        this.getDocumentInterface().setClickMode(RAction.PickCoordinate);
        var trDimPos = qsTr("Dimension line location or angle");
        this.setCommandPrompt(trDimPos);
        this.setLeftMouseTip(trDimPos);
        this.setRightMouseTip(EAction.trBack);
        EAction.showSnapTools();
        break;
    }

};

DimDiametric.prototype.escapeEvent = function() {
    switch (this.state) {
    case DimDiametric.State.SettingEntity:
        EAction.prototype.escapeEvent.call(this);
        break;

    case DimDiametric.State.SettingDimPos:
        this.setState(DimDiametric.State.SettingEntity);
        break;
    }
};

DimDiametric.prototype.pickEntity = function(event, preview) {
    //var di = this.getDocumentInterface();
    var doc = this.getDocument();
    var entityId = this.getEntityId(event, preview);
    var entity = doc.queryEntity(entityId);
    var pos = event.getModelPosition();

    if (isNull(entity)) {
        return;
    }

    switch (this.state) {
    case DimDiametric.State.SettingEntity:
        var shape = entity.getClosestSimpleShape(pos);

        if (isArcShape(shape) ||
            isCircleShape(shape)) {

            this.entity = entity;
            this.shape = shape;
        }
        else {
            if (!preview) {
                EAction.warnNotArcCircle();
                break;
            }
        }

        if (preview) {
            this.updatePreview();
        }
        else {
            this.setState(DimDiametric.State.SettingDimPos);
        }
        break;

    }
};

DimDiametric.prototype.pickCoordinate = function(event, preview) {
    var di = this.getDocumentInterface();

    switch (this.state) {
    case DimDiametric.State.SettingDimPos:
        this.pos = event.getModelPosition();
        if (preview) {
            this.updatePreview();
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(event.getModelPosition());
                this.setState(DimDiametric.State.SettingEntity);
            }
        }
        break;

    }
};

DimDiametric.prototype.getOperation = function(preview) {
    if (!isValidVector(this.pos) || isNull(this.shape)) {
        return undefined;
    }

    var radius = this.shape.getRadius();
    var center = this.shape.getCenter();
    var angle = center.getAngleTo(this.pos);

    this.data.setChordPoint(RVector.createPolar(radius, angle+Math.PI).operator_add(center));
    this.data.setFarChordPoint(RVector.createPolar(radius, angle).operator_add(center));

    var doc = this.getDocument();
    var scale = this.parseScale(this.getScaleString());
    var scaled_data = this.data;

    scaled_data.setLinearFactor(1/scale);

    var entity = new RDimDiametricEntity(doc, scaled_data);
    if (!isEntity(entity)) {
        return undefined;
    }

    return new RAddObjectOperation(entity, this.getToolTitle());
};

DimDiametric.prototype.getHighlightedEntities = function() {
    var ret = [];
    if (isEntity(this.entity)) {
        ret.push(this.entity.getId());
    }
    return ret;
};

DimDiametric.prototype.applyCommand = function(event, preview) {
    var di = this.getDocumentInterface();
    var cmd = event.getCommand();

    var pos = RMath.parseCoordinate(cmd);
    if (pos.isValid()) {
        return;
    }

    var value = RMath.eval(cmd);
    if (isNaN(value)) {
        return;
    }

    switch (this.state) {
    case DimDiametric.State.SettingDimPos:
        event.accept();
        var radius = this.shape.getRadius();
        var center = this.shape.getCenter();
        var v = RVector.createPolar(radius, RMath.deg2rad(value));
        this.pos = center.operator_add(v);
        if (preview) {
            this.updatePreview(true);
        }
        else {
            var op = this.getOperation(false);
            if (!isNull(op)) {
                di.applyOperation(op);
                di.setRelativeZero(this.pos);
                this.setState(DimDiametric.State.SettingEntity);
            }
        }
        break;
    }
};

