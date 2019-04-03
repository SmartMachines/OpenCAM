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

include("../ClipboardOperation.js");

/**
 * \class Cut
 * \brief Cuts the current selection to the clipboard. 
 * The reference point is defined by the user.
 * \ingroup ecma_edit
 */
function CutWithReference(guiAction) {
    ClipboardOperation.call(this, guiAction);
    this.cut = true;
    this.chooseReferencePoint = true;
}

CutWithReference.prototype = new ClipboardOperation();

