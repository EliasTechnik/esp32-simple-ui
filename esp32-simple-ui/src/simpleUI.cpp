#include <simpleUI.h>


//dimmensions
dimensions::dimensions(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height){
    pos_x=_pos_x;
    pos_y=_pos_y;
    width=_width;
    height=_height;
};
unsigned int dimensions::getX(){
    return pos_x;
};
unsigned int dimensions::getY(){
    return pos_y;
};
unsigned int dimensions::getWidth(){
    return width;
};
unsigned int dimensions::getHeight(){
    return height;
};

//uielement
uielement::uielement(unsigned int _pos_x, unsigned int _pos_y, unsigned int _width, unsigned int _height, bool isVisible = true){
    using dimensions::dimensions(_pos_x, _pos_y, _width, _height);
};
void uielement::setVisible(bool isVisible){

};
bool uielement::getVisible(){

};
void uielement::setDisplay(U8G2 _display){

};
void uielement::setName(string _name){

};
void uielement::draw(){

}; //should be overwritten by every child class which inherrits from uielement
