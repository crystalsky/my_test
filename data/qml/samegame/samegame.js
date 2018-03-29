/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

/* This script file handles the game logic */
var blockSize = 40;
var maxColume = 10;
var maxRow = 15;
var maxIndex = maxColume * maxRow;
var board = new Array(maxIndex);
var component;

//index function used instead of a 2D array
function index(column, row){
    return column + (row * maxColume);
}

function startNewGame(){
    //Delete Old Blocks
    for(var i = 0; i < maxIndex; ++i)
    {
        if(board[i] != null)
        {
            board[i].destroy();
        }
    }

    //caclulate board size
    maxColume = Math.floor((background.width) / blockSize);
    maxRow = Math.floor((background.height) / blockSize);
    maxIndex = maxColume * maxRow;

    //Initialize Board
    board = new Array(maxIndex);
    for(var column = 0; column < maxColume; column++)
    {
        for(var row = 0; row < maxRow; row++)
        {
            board[index(column, row)] = null;
            createBlock(row, column);
        }
    }
}

function createBlock(row, column)
{
    if(component == null)
    {
        component = Qt.createComponent("Block.qml");
    }

    // Note that if Block.qml was not a local file, component.status would be
        // Loading and we should wait for the component's statusChanged() signal to
        // know when the file is downloaded and ready before calling createObject().
    if(component.status == Component.Ready)
    {
        var dynamicObject = component.createObject(background);
        if(dynamicObject == null)
        {
            console.log("error creating blocks");
            console.log(component.errorString());
            return false;
        }
        dynamicObject.type = Math.floor(Math.random() * 3);
        dynamicObject.x = column * blockSize;
        dynamicObject.y = row * blockSize;
        dynamicObject.width = blockSize;
        dynamicObject.height = blockSize;
        board[index(column, row)] = dynamicObject;
    }
    else
    {
        console.log("error loading block component");
        console.log(component.errorString());
        return false;
    }

    return true;
}

var fillFound; //Set after a floodFill call to the number of blocks found
var floodBoard; //Set to 1 if the floodFill reaches off that node

function handleClick(x, y)
{
    var column = Math.floor(x / gameCanvas.blockSize);
    var row = Math.floor(y / gameCanvas.blockSize);

    if(column >= maxColume || column < 0 ||
            row >= maxRow || row < 0)
    {
        return;
    }

    if(board[index(column, row)] == null)
        return;

    //If it's a valid block, remove it and all connected (
    //does nothing if it's not connected)
    floodFill(column, row, -1);

    if(fillFound <= 0)
        return;

    gameCanvas.score += (fillFound - 1) * (fillFound - 1);
    shuffleDown();
    victoryCheck();
}

function floodFill(column, row, type)
{
    if(board[index(column, row)] == null)
        return;

    var first = false;
    if(type == -1)
    {
        first = true;
        type = board[index(column, row)].type;

        fillFound = 0;
        floodBoard = new Array(maxIndex);
    }

    if (column >= maxColume || column < 0 || row >= maxRow || row < 0)
        return;

    if (floodBoard[index(column, row)] == 1 || (!first && type != board[index(column, row)].type))
        return;

    floodBoard[index(column, row)] = 1;
    floodFill(column + 1, row, type);
    floodFill(column - 1, row, type);
    floodFill(column, row + 1, type);
    floodFill(column, row - 1, type);

    if(first == true && fillFound == 0)
        return;

    board[index(column, row)].opacity = 0;
    board[index(column, row)] = null;
    fillFound += 1;
}

function shuffleDown() {
    //Fall down
    for (var column = 0; column < maxColume; column++) {
        var fallDist = 0;
        for (var row = maxRow - 1; row >= 0; row--) {
            if (board[index(column, row)] == null) {
                fallDist += 1;
            } else {
                if (fallDist > 0) {
                    var obj = board[index(column, row)];
                    obj.y += fallDist * gameCanvas.blockSize;
                    board[index(column, row + fallDist)] = obj;
                    board[index(column, row)] = null;
                }
            }
        }
    }
    //Fall to the left
    var fallDist = 0;
    for (var column = 0; column < maxColume; column++) {
        if (board[index(column, maxRow - 1)] == null) {
            fallDist += 1;
        } else {
            if (fallDist > 0) {
                for (var row = 0; row < maxRow; row++) {
                    var obj = board[index(column, row)];
                    if (obj == null)
                        continue;
                    obj.x -= fallDist * gameCanvas.blockSize;
                    board[index(column - fallDist, row)] = obj;
                    board[index(column, row)] = null;
                }
            }
        }
    }
}

function victoryCheck() {
    //Award bonus points if no blocks left
    var deservesBonus = true;
    for (var column = maxColume - 1; column >= 0; column--)
        if (board[index(column, maxRow - 1)] != null)
        deservesBonus = false;
    if (deservesBonus)
        gameCanvas.score += 500;

    //Check whether game has finished
    if (deservesBonus || !(floodMoveCheck(0, maxRow - 1, -1)))
        dialog.show("Game Over. Your score is " + gameCanvas.score);
}

//only floods up and right, to see if it can find adjacent same-typed blocks
function floodMoveCheck(column, row, type) {
    if (column >= maxColume || column < 0 || row >= maxRow || row < 0)
        return false;
    if (board[index(column, row)] == null)
        return false;
    var myType = board[index(column, row)].type;
    if (type == myType)
        return true;
    return floodMoveCheck(column + 1, row, myType) || floodMoveCheck(column, row - 1, board[index(column, row)].type);
}

