

#ifndef ITEM_H
#define   ITEM_H

class Item
{
public:






   Item();
        
        Item(int _id, bool _isStackable){
            id = _id;
            isStackable = _isStackable;
        }




   int id = -1;
   int stackAmount = 1;
   bool active = false;

   int price = 0;
   
        bool isStackable = false;

   bool isTrinket(){ return false; }


};




#endif   /* ITEM_H */

