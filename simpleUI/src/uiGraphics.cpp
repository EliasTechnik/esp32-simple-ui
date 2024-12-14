
#include "uiGraphics.h"
/*
//icon
icon::icon(){
    setDimension(0,0,0,0);
    setVisible(false); 
    bitmap = nullptr;
};

void icon::init(unsigned char* _bitmap, unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool isVisible){
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
    bitmap = _bitmap;
};

unsigned char* icon::getBitmap(){
    return bitmap;
};

void icon::draw(){
    if(visible){
        display.drawXBM(posX,posY,width,height,bitmap);
    }
};

//interactiveIcon

interactiveIcon::interactiveIcon(){
    icon();
};

void interactiveIcon::init(unsigned char* _bitmap, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true){
    bitmap = _bitmap;
    setDimension(_posX,_posY,_width,_height);
    setVisible(isVisible);
};

*/

//uiBox
uiBox::uiBox(){
}

void uiBox::drawBox(frameInfo* f, uiVisualTransformation vt, Dimension d){
    //Slog("draw box")

    if(vt.invertedBackground){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1);
    }

    f->display->drawBox(
        f->viewportOffset.convertX(d.getX()),
        f->viewportOffset.convertY(d.getY()), 
        f->viewportOffset.convertWidth(d.getWidth()),
        f->viewportOffset.convertHeight(d.getHeight())
    );
}

void uiBox::drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d){
    drawBox(f,vt,d);
}

//uiFrame
uiFrame::uiFrame(){
    borderWidth = 1;
}

uiFrame::uiFrame(unsigned int _borderWidth){
    borderWidth = _borderWidth;
}
void uiFrame::setBorderWidth(unsigned int _borderWidth){
    borderWidth = _borderWidth;
}

void uiFrame::drawFrame(frameInfo* f, uiVisualTransformation vt, Dimension d){
    
    if(vt.invertedBackground){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1); 
    }
    
    for(byte i = 0;i<=borderWidth-1;i++){
        //Slog("draw frame")

        f->display->drawFrame(
                f->viewportOffset.convertX(d.getX()+i),
                f->viewportOffset.convertY(d.getY()+i), 
                f->viewportOffset.convertWidth(d.getWidth()-i),
                f->viewportOffset.convertHeight(d.getHeight()-i)
            );
    }
}

void uiFrame::drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d){
    drawFrame(f,vt,d);
}

//uiCircle
uiCircle::uiCircle(){
    borderWidth = 1;
}

uiCircle::uiCircle(unsigned int _borderWidth){
    borderWidth = _borderWidth;
}
void uiCircle::setBorderWidth(unsigned int _borderWidth){
    borderWidth = _borderWidth;
}

void uiCircle::drawCircle(frameInfo* f, uiVisualTransformation vt, Position center, unsigned int r){
    
    if(vt.invertedBackground){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1); 
    }
    
    for(byte i = 0;i<=borderWidth-1;i++){
        //Slog("draw circle)

        f->display->drawCircle(
                f->viewportOffset.convertX(center.getX()+i),
                f->viewportOffset.convertY(center.getY()+i), 
                f->viewportOffset.convertWidth(r-i)
            );
    }
}

void uiCircle::drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d){
    drawCircle(f,vt,d.getCenter(),d.getShortestToCenter());
}

//uiFilledCircle
uiFilledCircle::uiFilledCircle(){
}

void uiFilledCircle::drawFilledCircle(frameInfo* f, uiVisualTransformation vt, Position center, unsigned int r){
    //Slog("draw FilledCircle")

    if(vt.invertedBackground){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1);
    }

    f->display->drawDisc(
        f->viewportOffset.convertX(center.getX()),
        f->viewportOffset.convertY(center.getY()), 
        f->viewportOffset.convertWidth(r)
    );
}

void uiFilledCircle::drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d){
    drawFilledCircle(f,vt,d.getCenter(),d.getShortestToCenter());
}


//uiLine
uiLine::uiLine(){
    borderWidth = 1;
}

uiLine::uiLine(unsigned int _borderWidth){
    borderWidth = _borderWidth;
}
void uiLine::setBorderWidth(unsigned int _borderWidth){
    borderWidth = _borderWidth;
}

void uiLine::drawLine(frameInfo* f, uiVisualTransformation vt, Position pos1, Position pos2){
    
    if(vt.invertedBackground){
        f->display->setDrawColor(0);
    }else{
        f->display->setDrawColor(1); 
    }
    
    for(byte i = 0;i<=borderWidth-1;i++){
        //Slog("draw line)

        f->display->drawLine(
                f->viewportOffset.convertX(pos1.getX()+i),
                f->viewportOffset.convertY(pos1.getY()+i), 
                f->viewportOffset.convertWidth(pos2.getX()-i),
                f->viewportOffset.convertHeight(pos2.getY()-i)
            );
        
    }
}

void uiLine::drawUIGraphic(frameInfo* f, uiVisualTransformation vt, Dimension d){
    drawLine(f,vt,d.getPosition(),d.getPosition(UICorner_BR));
}


//uiInteractiveBox
/*
uiInteractiveBox::uiInteractiveBox() : uiElement(){
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiBox";
}

uiInteractiveBox::uiInteractiveBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height)
:uiElement(_posX,_posY,_width,_height){
    selectionMode = SelectionMode::notSelectable;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiBox";
};

uiInteractiveBox::uiInteractiveBox(unsigned int _posX, unsigned int _posY, unsigned int _width, unsigned int _height, bool _filled, SelectionMode _selectionMode)
:uiElement(_posX,_posY,_width,_height, _selectionMode,true){
    filled = _filled;
    selectionMode = _selectionMode;
    focusMode = FocusMode::passive;
    focus = FocusState::parent;
    visible = true;
    id = "uiBox";
};

uiInteractiveBox::~uiInteractiveBox(){
    
}

void uiBox::init(unsigned int _id, unsigned int _posX = 0, unsigned int _posY = 0, unsigned int _width = 0, unsigned int _height = 0, bool isVisible = true){
    this->setDimension(_posX, _posY, _width, _height);
    this->visible = isVisible;
    //filled = _filled;
    borderWidth = borderWidth;
}


void uiInteractiveBox::drawThis(frameInfo* f){
    //Slog("draw2");
    bool showSelected = (selected == SelectionState::showAsSelected || selected == SelectionState::Selected);

    if(visible){
        if(filled){
            if(f->highlightSelected && showSelected){
                f->display->drawFrame(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }else{
                f->display->drawBox(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }
            
        }else{
            //not filled
            if(f->highlightSelected && showSelected){
                f->display->drawBox(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }else{
                f->display->drawFrame(
                    f->viewportOffset.convertX(posX),
                    f->viewportOffset.convertY(posY), 
                    f->viewportOffset.convertWidth(width),
                    f->viewportOffset.convertHeight(height)
                );
            }
        }
    }
}

*/